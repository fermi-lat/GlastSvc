// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/test/CreateEvent.cpp,v 1.6 2000/11/01 00:39:01 igable Exp $
#define GlastApps_CreateEvent_CPP 


//#define GlastApps_CreateEvent_CPP 


// Include files
#include "CreateEvent.h"

#include "Gaudi/MessageSvc/MsgStream.h"
#include "Gaudi/Kernel/AlgFactory.h"
#include "Gaudi/Interfaces/IDataProviderSvc.h"
#include "Gaudi/DataSvc/SmartDataPtr.h"

#include "GlastSvc/GlastDetSvc/IGlastDetSvc.h"
#include "GlastEvent/TopLevel/EventModel.h"
#include "GlastEvent/TopLevel/Event.h"
#include "GlastEvent/MonteCarlo/MCACDHit.h"
#include "GlastEvent/MonteCarlo/MCCalorimeterHit.h"
#include "GlastEvent/MonteCarlo/MCSiLayer.h"
#include "GlastEvent/TopLevel/ObjectVector.h"




static const AlgFactory<CreateEvent>  Factory;
const IAlgFactory& CreateEventFactory = Factory;

extern void GlastSvc_load();
//------------------------------------------------------------------------------
/// Algorithm parameters which can be set at run time must be declared.
/// This should be done in the constructor.
CreateEvent::CreateEvent(const std::string& name, ISvcLocator* pSvcLocator) :
Algorithm(name, pSvcLocator), m_detSvc(0), m_irfLoadSvc(0) {
    GlastSvc_load();
}


//------------------------------------------------------------------------------
/*! The "functional" part of the class: For the EmptyAlgorithm example they do
nothing apart from print out info messages.
NB in the initialize method: you must explicitly initialize the base class
before using any services (message service, event data service etc.) otherwise 
the behaviour will be unpredictable at best.
*/
StatusCode CreateEvent::initialize() {
    
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "initialize" << endreq;
    
    // Use the Job options service to set the Algorithm's parameters
    setProperties();
    
    // now try to find the GlastDevSvc service
    IGlastDetSvc* detSvc = 0;
    
    StatusCode sc = serviceLocator()->getService ("GlastDetSvc",
        IID_IGlastDetSvc, reinterpret_cast<IInterface*&>( detSvc ));
    
    if (sc.isSuccess ())
        log << MSG::INFO << "Succeeded in accessing the GlastDetSvc!" << endreq;
    else {
        log << MSG::ERROR << "Couldn't find the GlastDetSvc!" << endreq;
        return StatusCode::FAILURE;
    }
    m_detSvc = detSvc;


    return StatusCode::SUCCESS;
}


//------------------------------------------------------------------------------
StatusCode CreateEvent::execute() {
    
    StatusCode  sc = StatusCode::SUCCESS;
    MsgStream   log( msgSvc(), name() );
    log << MSG::INFO << "execute" << endreq;

    DataObject* pObject;


    /*! Causes the TDS to be searched, if the data is unavailable, the appropriate
    converter is called to retrieve the data. */
    sc = eventSvc()->retrieveObject("/Event/MC/MCACDHits", pObject);

    if( sc.isFailure() ) return sc;                                                             
    
        log << MSG::INFO << "Successfully retrieved ACD Container!!!" << endreq;

    ObjectVector<MCACDHit>* acdList;
    try {
        acdList  = dynamic_cast<ObjectVector<MCACDHit>*>(pObject);
    } catch(...) {
        log << MSG::INFO << "Failed to convert object to MCACDHitVector" << endreq;
        return StatusCode::FAILURE;
    }
    
    //! print out the ACD data
    for (ObjectVector<MCACDHit>::const_iterator it = acdList->begin(); it != acdList->end(); it++) {
        log << MSG::INFO << " ACD Tile Hit " 
            << (*it)->id() << " "
            << (*it)->energy() << endreq;
    }

    /*! Causes the TDS to be searched, if the data is unavailable, the appropriate
    converter is called to retrieve the data.  */
    sc = eventSvc()->retrieveObject("/Event/MC/MCCalorimeterHits", pObject);
    if( sc.isFailure() ) {
        log << MSG::INFO << "Failed to get MCCalorimeterHits" << endreq;
        return sc;                                                             
    } 
    
    log << MSG::INFO << "Retrieved MCCalorimeterHit Vector!" << endreq;

    ObjectVector<MCCalorimeterHit>* calList;
    try {
        calList  = dynamic_cast<ObjectVector<MCCalorimeterHit>*>(pObject);
    } catch(...) {
        log << MSG::INFO << "Failed to convert object to MCCalorimeterHitVector" << endreq;
        return StatusCode::FAILURE;
    }
    //! print out the CAL data
    for (ObjectVector<MCCalorimeterHit>::const_iterator xtal = calList->begin(); xtal != calList->end(); xtal++) {
        log << MSG::INFO << "Csi Log Hit: " << endreq;
        log <<MSG::INFO << "       " 
                        << (*xtal)->leftResponse() << " " 
                        << (*xtal)->rightResponse() << " "
                        << (*xtal)->energy() << " " << endreq;
    }


    /*! Causes the TDS to be seached, if the TKR data is unavailable, then the
        converter is called to retrieve the data */
    sc = eventSvc()->retrieveObject("/Event/MC/MCTKRHits", pObject);
    if( sc.isFailure() ) return sc;                                                             
    
        log << MSG::INFO << "Successfully retrieved TKR Container!!!" << endreq;

    ObjectVector<MCSiLayer>* tkrList;
    try {
        tkrList  = dynamic_cast<ObjectVector<MCSiLayer>*>(pObject);
    } catch(...) {
        log << MSG::INFO << "Failed to convert object to MCSiLayerVector" << endreq;
        return StatusCode::FAILURE;
    }
    
    //! print out the TKR data
    for (ObjectVector<MCSiLayer>::const_iterator silayer = tkrList->begin(); silayer != tkrList->end(); silayer++) {
        log << MSG::INFO << "SiLayer " << (*silayer)->id() << " "
            << (*silayer)->MaxEnergy() << endreq;

        for (ObjectVector<MCTKRHit>::const_iterator hit = ((*silayer)->getHits())->begin(); hit != ((*silayer)->getHits())->end(); hit++) {
            log << MSG::INFO << "Hit SSD Strip " 
                << (*hit)->id() << " "
                << (*hit)->energy() << " "
                << (*hit)->noise() << endreq;
        }
      }

    return sc;
}


//------------------------------------------------------------------------------
StatusCode CreateEvent::finalize() {
    
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "finalize" << endreq;
    
    return StatusCode::SUCCESS;
}






