//------------------------------------------------------------------------------
//
// Implementation of class :  MCEventCnv
//
// Author :                   
//
//------------------------------------------------------------------------------
// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/MCEventCnv.cpp,v 1.3 2001/08/27 04:17:43 burnett Exp $
#define CNV_MCEVENTCNV_CPP 

// Include files
#include "GaudiKernel/CnvFactory.h"
#include "MCEventCnv.h"

// GlastEvent for creating the McEvent stuff
#include "GlastEvent/TopLevel/MCEvent.h"

#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/ObjectVector.h"

// RCS Id for identification of object version
static const char* rcsid = "$Id: MCEventCnv.cpp,v 1.3 2001/08/27 04:17:43 burnett Exp $";

// Instantiation of a static factory class used by clients to create
// instances of this service
static CnvFactory<MCEventCnv> s_factory;
const ICnvFactory& MCEventCnvFactory = s_factory;


MCEventCnv::MCEventCnv(ISvcLocator* svc)
: BaseCnv(classID(), svc)
{
  declareObject("/Event/MC", objType(), "PASS");
}


StatusCode MCEventCnv::createObj(IOpaqueAddress* pAddress, DataObject*& refpObject)
{

    refpObject = new MCEvent();
    StatusCode sc=StatusCode::SUCCESS;
    return sc;
}


const CLID& MCEventCnv::classID(){ return MCEvent::classID();}
