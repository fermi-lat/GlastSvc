// $Header: /cvs/cmt/GlastSvc/src/test/CreateEvent.cpp,v 1.9 2000/09/18 18:32:17 heather Exp $
#define GlastApps_CreateEvent_CPP 


// Include files
#include "CreateEvent.h"
#include "Gaudi/MessageSvc/MsgStream.h"
#include "Gaudi/Kernel/AlgFactory.h"
#include "Gaudi/Interfaces/IDataProviderSvc.h"
#include "Gaudi/DataSvc/SmartDataPtr.h"

#include "GlastSvc/GlastDetSvc/IGlastDetSvc.h"
#include "GlastEvent/TopLevel/EventModel.h"
#include "GlastEvent/TopLevel/Event.h"
#include "GlastEvent/Hits/ACDhit.h"
#include "GlastEvent/TopLevel/ObjectVector.h"

//--------------------------------------------------------------------
//
//  CreateEvent : Standard 'Hello World' applications
//
//  Author :   SawyerGillespie
//
//--------------------------------------------------------------------

// define the class-id (unique) for the GlastDetSvc
// const IID&  IID_IGlastDetSvc  =  401;   // Unique to GLAST 
// define the class-id (unique) for the GlastIRFSvc
// const IID&  IID_IGlastIRFLoadSvc  =  402;   // Unique to GLAST


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
/// The "functional" part of the class: For the EmptyAlgorithm example they do
///  nothing apart from print out info messages.
/// NB in the initialize method: you must explicitly initialize the base class
/// before using any services (message service, event data service etc.) otherwise 
/// the behaviour will be unpredictable at best.
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

    // ----------------------------------------------------
    return StatusCode::SUCCESS;
}


//------------------------------------------------------------------------------
StatusCode CreateEvent::execute() {
    
    StatusCode  sc = StatusCode::SUCCESS;
    MsgStream   log( msgSvc(), name() );
    log << MSG::INFO << "execute" << endreq;

    DataObject* pObject;

//    sc = eventSvc()->retrieveObject("/Event/Hits/ACDTile", pObject);
    // simplifying this example, one less level of indirection!
    sc = eventSvc()->retrieveObject("/Event/ACDTile", pObject);
    if( sc.isFailure() ) return sc;                                                             
    
	log << MSG::INFO << "Successfully retrieved ACD Container!!!" << endreq;

    ObjectVector<ACDhit>* acdList;
    try {
        acdList  = dynamic_cast<ObjectVector<ACDhit>*>(pObject);
    } catch(...) {
        log << MSG::INFO << "Failed to convert object to ACDhitVector" << endreq;
        return StatusCode::FAILURE;
    }
    
    for (ObjectVector<ACDhit>::const_iterator it = acdList->begin(); it != acdList->end(); it++) {
        log << MSG::INFO << " tile Energy = " << (*it)->energy() << " Id = " << (*it)->id() << endreq;
      }



    return sc;
}


//------------------------------------------------------------------------------
StatusCode CreateEvent::finalize() {
    
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "finalize" << endreq;
    
    return StatusCode::SUCCESS;
}






