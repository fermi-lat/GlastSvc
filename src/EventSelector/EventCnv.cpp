// $Header: /cvs/cmt/GlastSvc/src/EventSelector/EventCnv.cpp,v 1.5 2000/09/18 17:54:41 heather Exp $
#define EVENTCNV_CPP 


// Include files
#include "Gaudi/Kernel/CnvFactory.h"
#include "Gaudi/DataSvc/RegistryEntry.h"
#include "EventCnv.h"
#include "Gaudi/MessageSvc/MsgStream.h"

#include "GlastEvent/TopLevel/Event.h"



// RCS Id for identification of object version
static const char* rcsid = "$Id: EventCnv.cpp,v 1.5 2000/09/18 17:54:41 heather Exp $";


//------------------------------------------------------------------------------
//
// Implementation of class :  EventCnv
//
// Modified SicbEventCnv
//
//------------------------------------------------------------------------------


// Instantiation of a static factory class used by clients to create
// instances of this service
static CnvFactory<EventCnv> s_factory;
const ICnvFactory& EventCnvFactory = s_factory;


StatusCode EventCnv::updateObj(int* iarray, Event* pEvent)             {
  MsgStream log(messageService(), "EventCnv");
  log << MSG::DEBUG << "EventCnv::updateObj" << endreq;
  return StatusCode::SUCCESS;
}

/*

StatusCode EventCnv::updateObjRefs(int* iarray, Event* pEvent)         {
  MsgStream log(messageService(), "EventCnv");
  log << MSG::DEBUG << "EventCnv::updateObjRefs" << endreq;

  RegistryEntry*  ent = dynamic_cast<RegistryEntry*>(pEvent->directory());
  if ( 0 != ent )   {
    Address* addr = dynamic_cast<Address*>(pEvent->address());
    if ( 0 != addr )  {
      const std::string& fid = addr->dbName();
      int recid = addr->sicbInfo()->entryID();
      return StatusCode::SUCCESS;
    }
  }
  return StatusCode::FAILURE;
}
*/


/// Standard Constructor
EventCnv::EventCnv(ISvcLocator* svc)
  : ItemCnv<Event>(svc)                                  
{
      declareObject("/Event", objType(), "PASS");
}


/// Standard Destructor
EventCnv::~EventCnv() { }

