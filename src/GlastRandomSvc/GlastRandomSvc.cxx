// Implementation file for GlastRandomSvc which gets adresses 
// of CLHEP random number engines used in Gleam shared libraries
// and sets seeds for them based on run and particle sequence
// number obtained from the MCHeader
//
// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/GlastRandomSvc/GlastRandomSvc.cxx,v 1.13 2003/03/16 00:16:22 burnett Exp $
//
// Author: Toby Burnett, Karl Young


#include "GlastRandomSvc.h"

#include <iterator>
#include <fstream>
#include "GaudiKernel/Incident.h"
#include "GaudiKernel/IIncidentSvc.h"
#include "GaudiKernel/SvcFactory.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/DataStoreItem.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/IDataManagerSvc.h"
#include "GaudiKernel/IObjManager.h"
#include "GaudiKernel/IToolFactory.h"
#include "GaudiKernel/SmartDataPtr.h"

#include "GlastSvc/GlastRandomSvc/IRandomAccess.h"
#include "Event/TopLevel/MCEvent.h"
#include "Event/TopLevel/Event.h"
#include "Event/TopLevel/EventModel.h"

#include "CLHEP/Random/RandomEngine.h"

// for list of random engines
#include "CLHEP/Random/DualRand.h"
#include "CLHEP/Random/TripleRand.h"
#include "CLHEP/Random/RandEngine.h"
#include "CLHEP/Random/DRand48Engine.h"
#include "CLHEP/Random/Hurd160Engine.h"
#include "CLHEP/Random/Hurd288Engine.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/MTwistEngine.h"
#include "CLHEP/Random/RanecuEngine.h"
#include "CLHEP/Random/Ranlux64Engine.h"
#include "CLHEP/Random/RanluxEngine.h"
#include "CLHEP/Random/RanshiEngine.h"


// declare the service factories for the GlastRandomSvc
static SvcFactory<GlastRandomSvc> a_factory;
const ISvcFactory& GlastRandomSvcFactory = a_factory; 

GlastRandomSvc::GlastRandomSvc(const std::string& name,ISvcLocator* svc) : Service(name,svc)
{
    // Purpose and Method: Constructor - Declares and sets default properties
    //                     
    // Inputs: service name and locator 
    //         
    // Outputs: None
    // Dependencies: None
    // Restrictions and Caveats:  None

    // declare the properties
    declareProperty("RandomEngine",  m_randomEngine="TripleRand");
    declareProperty("RunNumber",      m_RunNumber=10);
    declareProperty("InitialSequenceNumber", m_InitialSequenceNumber=0);
    declareProperty("SeedFile", m_seedFile="");
}

GlastRandomSvc::~GlastRandomSvc()  
{
    // this is  repetetive in case finalize was
    // not called.
    finalize();
}


/** @class RanGenFactoryBase
 *
* @brief abstract base class for list of HepRandomEngine factories 
*/
class RanGenFactoryBase {
public:
  virtual ~RanGenFactoryBase(){}
    virtual HepRandomEngine * create() =0;
    virtual std::string name()const =0;
};

/** @class RanGenFactory
 *
* @brief Templated class  to create a particular HepRandomEngine factory 
*/
template <class T> class RanGenFactory : public RanGenFactoryBase{ 
public:
    RanGenFactory(std::string name):m_name(name){}
    virtual HepRandomEngine * create(){return new T;}
    std::string name()const { return m_name;}
private:
    std::string m_name;

};

HepRandomEngine* GlastRandomSvc::createEngine(std::string  engineName) 
{
    // Purpose and Method: Given a string containing a valid CLHEP
    //                     random engine type returns an instance 
    //
    // Inputs:  Name of CLHEP random engine to set
    // Outputs: pointer to a HepRandomEngine, or zero
    // Dependencies: None
    // Restrictions and Caveats:  None

    static RanGenFactoryBase*  factories[] = { 
        {new RanGenFactory<DRand48Engine>("DRand48Engine")   },
        {new RanGenFactory<DualRand>("DualRand")             },
        {new RanGenFactory<TripleRand>("TripleRand")         },
        {new RanGenFactory<RandEngine>("RandEngine")         },
        {new RanGenFactory<HepJamesRandom>("HepJamesRandom") },
        {new RanGenFactory<HepJamesRandom>("JamesRandom")    },
        {new RanGenFactory<Hurd160Engine>("Hurd160Engine")   },
        {new RanGenFactory<Hurd288Engine>("Hurd288Engine")   },
        {new RanGenFactory<MTwistEngine>("MTwistEngine")     },
        {new RanGenFactory<RanecuEngine>("RanecuEngine")     },
        {new RanGenFactory<RanshiEngine>("RanshiEngine")     },
        {new RanGenFactory<RanluxEngine>("RanluxEngine")     },
        {new RanGenFactory<Ranlux64Engine>("Ranlux64Engine") }
    };

    for(unsigned int i=0; i< sizeof(factories)/sizeof(void*); ++i){
        if( engineName==factories[i]->name()) return factories[i]->create();
    }
    return 0;
}

StatusCode GlastRandomSvc::initialize () 
{
    // Purpose and Method: initialization: see class description
    //
    // Inputs:  none
    // Outputs: none
    // Dependencies: None
    // Restrictions and Caveats:  None
    StatusCode  status = StatusCode::SUCCESS;

    // Open the message log
    MsgStream log( msgSvc(), name() );

    // Call super-class
    Service::initialize ();

    // Bind all of the properties for this service
    if ( (status = setProperties()).isFailure() ) {
        log << MSG::ERROR << "Failed to set properties" << endreq;
        return status;
    }
    m_SequenceNumber = m_InitialSequenceNumber;

    // use the incident service to register begin, end events
    IIncidentSvc* incsvc = 0;
    status = service ("IncidentSvc", incsvc, true);

    if( status.isFailure() ) return status;

    incsvc->addListener(this, "BeginEvent", 0);


    // read seeds from file
    if(m_seedFile.value() != "") {

        std::ifstream input(m_seedFile.value().c_str());
        if(!input) {
            log << MSG::ERROR << "Unable to find seed file: " << m_seedFile
                << endreq;
            status = StatusCode::FAILURE;
            return status;
        }

        std::istream_iterator<GlastRandomSeed> begin(input);
        std::istream_iterator<GlastRandomSeed> end;
        std::copy(begin, end, std::back_inserter(m_seeds));

        // set no of events
        IProperty* propMgr=0;
        status = serviceLocator()->service("ApplicationMgr", propMgr );
        if( status.isFailure()) {
            log << MSG::ERROR << 
                "Unable to locate PropertyManager Service" << endreq;
            return status;
        }

        IntegerProperty evtMax("EvtMax", m_seeds.size());
        status = propMgr->setProperty(evtMax);
        if (status.isFailure()) return status;
    }

    // Look for a factory of an AlgTool that implements the
    // IRandomAccess interface:
    // if found, make one and call the special method
    // Manager of the AlgTool Objects
    IObjManager* objManager=0;

    // locate Object Manager to locate later the tools
    status = serviceLocator()->service("ApplicationMgr",
        objManager );
    if( status.isFailure()) {
        log << MSG::ERROR << "Unable to locate ObjectManager Service"
            << endreq;
        return status;
    }

    IToolFactory* toolfactory = 0;

    // Search through all objects (factories?)
    for(IObjManager::ObjIterator it = objManager->objBegin(); it
        !=objManager->objEnd(); ++ it){
            std::string tooltype= (*it)->ident();
            // is it a tool factory?
            const IFactory* factory = objManager->objFactory( tooltype );
            IFactory* fact = const_cast<IFactory*>(factory);
            status = fact->queryInterface( IID_IToolFactory,
                (void**)&toolfactory );
            if( status.isSuccess() ) {
                std::string fullname = this->name()+"."+tooltype;
                IAlgTool* itool = toolfactory->instantiate(fullname,  this );
		IRandomAccess* ranacc ;
                status =itool->queryInterface(IRandomAccess::interfaceID(),  
                    (void**)&ranacc);
                if( status.isSuccess() ){
                    // Set the Random engine by name
                    HepRandomEngine* hr =createEngine(m_randomEngine);
                    if( hr==0) {
                        log << MSG::ERROR << "Could not set up the random engine " 
                            << m_randomEngine << endreq;
                        return StatusCode::FAILURE;
                    }
                    log << MSG::INFO << "Setting CLHEP Engine "<< m_randomEngine
                        << " for " << tooltype << " at " << hr << endreq;
                    HepRandomEngine* old = ranacc->setTheEngine(hr);
                    // make sure that the old one was not already stored
                    for( EngineMap::iterator eit = m_engineMap.begin(); eit != m_engineMap.end(); ++eit){
                        if( eit->second != old) continue;
                        log << MSG::WARNING 
                            << " Previous engine ("<< old << ") for " 
                            << tooltype << " was also set for "<< eit->first << endreq;
                        break;
                    }
                    // Store its name and address in a map
                    m_engineMap[tooltype] = hr;
		    
		  itool->release();
		}
            }
        }
        return StatusCode::SUCCESS;
    }



void GlastRandomSvc::handle(const Incident &inc)
{
     // Purpose and Method: handle "incidents" - i.e. set seeds at beginning of event loop 
    //
    // Inputs:  the incident to handle (begin event)
    // Outputs: new seeds in all the engines
    // Dependencies: None
    // Restrictions and Caveats:  None

    MsgStream log( msgSvc(), name() );

    if( inc.type()=="BeginEvent") {
        IDataProviderSvc* eventSvc;
        StatusCode status;
        if( serviceLocator() ) {
            status = serviceLocator()->service("EventDataSvc", eventSvc, true );
        }
        if(status.isFailure())
        {
            log << MSG::ERROR << "Could not find EventDataSvc" << endreq;
        }
        // See if MCEvent was set up properly
        SmartDataPtr<Event::MCEvent> mcevt(eventSvc, EventModel::MC::Event);
        if (mcevt == 0) {
            log << MSG::ERROR << "Error accessing MCEvent" << endreq;
            return;
        }

        int runNo, seqNo;

        if(m_seedFile.value() == "") {
            runNo = m_RunNumber;
            seqNo = m_SequenceNumber;
            ++m_SequenceNumber;
        }
        else {

            // index of which event is being generated, only used when reading seeds
            // from a file to generate a set of events
            static int iEvent = 0;

            runNo = m_seeds[iEvent].m_run;
            seqNo = m_seeds[iEvent].m_seqNo;
            ++iEvent; 
        }

        // recorde seeds to TDS
        mcevt->initialize(runNo, -1, seqNo);

        // Set run number in EventHeader for consistency with
        // with run number in MCEvent
        SmartDataPtr<Event::EventHeader> header(eventSvc, 
            EventModel::EventHeader);
        if (header == 0) {
            log << MSG::ERROR << "Error accessing Event Header: not setting seed" << endreq;
            return;
        }    

        header->setRun(runNo);

        int multiplier = 1; 
        int dummy = 0; // for 2nd argument to setSeed
        EngineMap::const_iterator dllEngine;
        for (dllEngine = m_engineMap.begin(); dllEngine != m_engineMap.end(); ++dllEngine ) {
            long theSeed = multiplier * 100000 * ((runNo+1) % 20000) + 2*seqNo+1;

            log << MSG::DEBUG;
            if(log.isActive() ){
                log << "Setting seed for " <<  dllEngine->first << " to " <<  theSeed ;
            }
            log << endreq;
            
            dllEngine->second->setSeed(theSeed,dummy);
            ++multiplier;
        }
    }
}

StatusCode GlastRandomSvc::finalize () 
{
    // Purpose and Method: finish up, delete the list of engines
    //
    // Inputs:  none
    // Outputs: none
    // Dependencies: None
    // Restrictions and Caveats:  None

    for (EngineMap::iterator dllEngine = m_engineMap.begin(); 
        dllEngine != m_engineMap.end(); ++dllEngine ) {
        delete dllEngine->second;       
    }
    m_engineMap.clear();
    return StatusCode::SUCCESS;
}

