// RawEventCnv.cpp: implementation of the RawEventCnv class.
//
//////////////////////////////////////////////////////////////////////


#define CNV_RAWEVENTCNV_CPP 

// Include files
#include "Gaudi/Kernel/CnvFactory.h"
#include "RawEventCnv.h"
#include "GlastEvent/TopLevel/RawEvent.h"

static const char* rcsid = "$Id: RawEvent.cpp,v 1.1 2000/11/16 21:49:22 igable Exp $";

// Instantiation of a static factory class used by clients to create
// instances of this service
static CnvFactory<RawEventCnv> s_factory;
const ICnvFactory& RawEventCnvFactory = s_factory;


StatusCode RawEventCnv::updateObj(int* iarray, RawEvent* pEvent)          {
  // Elements from the PASS bank: Pileup value
//  pEvent->setPileUp( iarray[12] );
  return StatusCode::SUCCESS;
}

//! Standard Constructor
RawEventCnv::RawEventCnv(ISvcLocator* svc)
: ItemCnv<RawEvent>(svc)               
{
  declareObject("/Event/Raw", objType(), "PASS");
  //m_sourceDef = SicbObjBank("PASS");
}


//! Standard Destructor
RawEventCnv::~RawEventCnv()   { 
}

