//  ====================================================================
//  BaseCnv.cpp
//  --------------------------------------------------------------------
//
//  Package   : GlastSvc/src/EventSelector
//
//  Implementation of class :  BaseCnv
//
//  Modified SicbBaseCnv
//
//  ====================================================================
#define _BASECNV_CPP 

#include "GaudiKernel/IService.h"
#include "GaudiKernel/ISvcLocator.h"

#include "GlastSvc/GlastDetSvc/IGlastDetSvc.h"
#include "GaudiKernel/MsgStream.h"

#include "BaseCnv.h"


//extern const IID& IID_ISicbEventCnvSvc;
static const InterfaceID IID_IBaseCnv(902, 1 , 0); 

// RCS Id for identification of object version
static const char* rcsid = "$Id: BaseCnv.cpp,v 1.3 2000/12/11 16:37:29 burnett Exp $";

/// Convert the transient object to the requested representation.
StatusCode BaseCnv::createRep(DataObject* pObject, IOpaqueAddress*& refpAddress)   {
  return StatusCode::FAILURE;
}

/// Resolve the references of the converted object. 
StatusCode BaseCnv::fillRepRefs(IOpaqueAddress* pAddress,DataObject* pObject)    {
  return StatusCode::FAILURE;
}

/// Update the converted representation of a transient object.
StatusCode BaseCnv::updateRep(IOpaqueAddress* pAddress, DataObject* pObject)   {
  return StatusCode::FAILURE;
}

/// Update the references of an already converted object.
StatusCode BaseCnv::updateRepRefs(IOpaqueAddress* pAddress, DataObject* pObject)   {
  return StatusCode::FAILURE;
}


/// Initialize the converter
StatusCode BaseCnv::initialize()   {
  StatusCode status = Converter::initialize();
  if ( status.isSuccess() )   {
    IService* isvc = 0;
    status = serviceLocator()->getService("EventCnvSvc", isvc);
    if ( status.isSuccess() )   {
      status = isvc->queryInterface(IID_IBaseCnv, (void**)&m_CnvSvc);
      if ( status.isSuccess() )   {
        for ( std::vector<IEventCnvSvc::Leaf>::iterator i = m_leaves.begin(); i != m_leaves.end(); i++ )    {
          m_CnvSvc->declareObject(*i);
        }
      }
    }
  }
  return status;
}

/// Initialize the converter
StatusCode BaseCnv::finalize()   {
  if ( m_CnvSvc )     {
    m_CnvSvc->release();
    m_CnvSvc = 0;
  }
  // Put in here SicbConverter initialization
  return Converter::finalize();
}

/// Declare target leaf
void BaseCnv::declareObject(const std::string& path, const CLID& cl, const std::string& bank, long par)  {
  m_leaves.push_back(IEventCnvSvc::Leaf(path, cl, bank, par));
}

/// Standard Constructor
BaseCnv::BaseCnv(const CLID& clid, ISvcLocator* svc)
: Converter(SICB_StorageType, clid, svc), m_CnvSvc(0)   {

    StatusCode sc;
    MsgStream log(msgSvc(), "BaseCnv");

    // provide access to the Glast Detector Service, so that we may call the accept method
    // from within our converters
    sc = serviceLocator()->getService ("GlastDetSvc",
        IID_IGlastDetSvc, reinterpret_cast<IInterface*&>( m_detSvc ));
    
    if(sc.isFailure()){
       log << MSG::ERROR << "Unable start Glast detector service within BaseCnv" << endreq;
    } 
}

/// Standard Destructor
BaseCnv::~BaseCnv()    { 
}

