// File and Version Information:
//      $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/EventCnv.cpp,v 1.4 2002/03/18 19:00:35 heather Exp $
//
// Description:
//      EventCnv is the concrete converter for the event header.
//
// Author(s):

#define EVENTCNV_CPP 

#include "GaudiKernel/RegistryEntry.h"
#include "EventCnv.h"
#include "GaudiKernel/MsgStream.h"

#include "Event/TopLevel/Event.h"

// Instantiation of a static factory class used by clients to create
// instances of this service
static CnvFactory<EventCnv> s_factory;
const ICnvFactory& EventCnvFactory = s_factory;

EventCnv::EventCnv(ISvcLocator* svc)
: BaseCnv(classID(), svc)
{
    declareObject("/Event", objType(), "PASS");
}


StatusCode EventCnv::createObj(IOpaqueAddress* pAddress, DataObject*& refpObject) {
    refpObject = new Event();
    return StatusCode::SUCCESS;
};

StatusCode EventCnv::updateObj(int* iarray, Event* pEvent)             {
    MsgStream log(msgSvc(), "EventCnv");
    log << MSG::DEBUG << "EventCnv::updateObj" << endreq;
    return StatusCode::SUCCESS;
}



