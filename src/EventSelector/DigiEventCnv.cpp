// DigiEventCnv.cpp: implementation of the DigiEventCnv class.
//
//////////////////////////////////////////////////////////////////////


#define CNV_DIGIEVENTCNV_CPP 

// Include files
#include "GaudiKernel/CnvFactory.h"
#include "DigiEventCnv.h"
#include "GlastEvent/TopLevel/DigiEvent.h"

static const char* rcsid = "$Id: DigiEventCnv.cpp,v 1.1 2001/02/27 23:19:00 heather Exp $";

// Instantiation of a static factory class used by clients to create
// instances of this service
static CnvFactory<DigiEventCnv> s_factory;
const ICnvFactory& DigiEventCnvFactory = s_factory;


StatusCode DigiEventCnv::updateObj(int* iarray, DigiEvent* pEvent)          {
  return StatusCode::SUCCESS;
}

//! Standard Constructor
DigiEventCnv::DigiEventCnv(ISvcLocator* svc)
: ItemCnv<DigiEvent>(svc)               
{
  declareObject("/Event/Digi", objType(), "PASS");
}


//! Standard Destructor
DigiEventCnv::~DigiEventCnv()   { 
}

