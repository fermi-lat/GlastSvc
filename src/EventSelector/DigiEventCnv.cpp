// File and Version Information:
//      $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/DigiEventCnv.cpp,v 1.5 2002/05/08 22:46:22 heather Exp $
//
// Description:
//      DigiEventCnv is the concrete converter for the digi event header.
//
// Author(s):


#define CNV_DIGIEVENTCNV_CPP 

#include "GaudiKernel/CnvFactory.h"
#include "DigiEventCnv.h"
#include "Event/TopLevel/DigiEvent.h"

static const char* rcsid = "$Id: DigiEventCnv.cpp,v 1.5 2002/05/08 22:46:22 heather Exp $";

// Instantiation of a static factory class used by clients to create
// instances of this service
static CnvFactory<DigiEventCnv> s_factory;
const ICnvFactory& DigiEventCnvFactory = s_factory;

DigiEventCnv::DigiEventCnv(ISvcLocator* svc)
: BaseCnv(classID(), svc)
{
  declareObject("/Event/Digi", objType(), "PASS");
}


StatusCode DigiEventCnv::createObj(IOpaqueAddress* pAddress, DataObject*& refpObject) {
    refpObject = new Event::DigiEvent();
    return StatusCode::SUCCESS;
};


