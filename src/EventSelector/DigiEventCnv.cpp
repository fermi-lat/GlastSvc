// File and Version Information:
//      $Header$
//
// Description:
//      DigiEventCnv is the concrete converter for the digi event header.
//
// Author(s):


#define CNV_DIGIEVENTCNV_CPP 

#include "GaudiKernel/CnvFactory.h"
#include "DigiEventCnv.h"
#include "GlastEvent/TopLevel/DigiEvent.h"

static const char* rcsid = "$Id: DigiEventCnv.cpp,v 1.3 2002/03/15 21:16:48 heather Exp $";

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
    refpObject = new DigiEvent();
    return StatusCode::SUCCESS;
};

StatusCode DigiEventCnv::updateObj(int* iarray, DigiEvent* pEvent)          {
  return StatusCode::SUCCESS;
}

