//------------------------------------------------------------------------------
//
// Implementation of class :  MCEventCnv
//
// Author :                   Markus Frank
//
//------------------------------------------------------------------------------
// $Header: /nfs/slac/g/glast/ground/cvs/SicbCnv/SicbCnv/TopLevel/SicbMCEventCnv.cpp,v 1.1.1.1 2000/10/09 19:33:36 burnett Exp $
#define CNV_MCEVENTCNV_CPP 

// Include files
#include "Gaudi/Kernel/CnvFactory.h"
#include "MCEventCnv.h"
#include "GlastEvent/TopLevel/MCEvent.h"

// RCS Id for identification of object version
static const char* rcsid = "$Id: MCEventCnv.cpp,v 1.1.1.1 2000/10/09 19:33:36 burnett Exp $";

// Instantiation of a static factory class used by clients to create
// instances of this service
static CnvFactory<MCEventCnv> s_factory;
const ICnvFactory& MCEventCnvFactory = s_factory;


/// Update object from ZEBRA
StatusCode MCEventCnv::updateObj(int* iarray, MCEvent* pEvent)          {
  // Elements from the PASS bank: Pileup value
//  pEvent->setPileUp( iarray[12] );
  return StatusCode::SUCCESS;
}

/// Standard Constructor
MCEventCnv::MCEventCnv(ISvcLocator* svc)
: ItemCnv<MCEvent>(svc)               
{
  declareObject("/Event/MC", objType(), "PASS");
  //m_sourceDef = SicbObjBank("PASS");
}


/// Standard Destructor
MCEventCnv::~MCEventCnv()   { 
}
