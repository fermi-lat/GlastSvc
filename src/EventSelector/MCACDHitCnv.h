// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/ACDhitCnv.h,v 1.2 2000/09/28 04:37:49 burnett Exp $
#ifndef MCACDHitCnv_H 
#define MCACDHitCnv_H 1

// Include files
//#include "Gaudi/Kernel/Converter.h"
#include "BaseCnv.h"

// Abstract factory to create the converter
template <class TYPE> class CnvFactory;

//extern unsigned char SICB_StorageType;


//------------------------------------------------------------------------------
//
// ClassName:   ACDhitCnv
//  
// Description:
//
// Author:   
//
//------------------------------------------------------------------------------
class MCACDHitCnv : public BaseCnv   {
  friend class CnvFactory<BaseCnv>;

public:
  /// Standard Constructor
  MCACDHitCnv( ISvcLocator* svc );
  /// Standard Destructor
  virtual ~MCACDHitCnv();
  /// class ID
  static const CLID& classID();
  /// Update complete object
  virtual StatusCode updateObj(IOpaqueAddress* pAddress, DataObject* pObject);
  /// Create object
  virtual StatusCode createObj(IOpaqueAddress* pAddress, DataObject*& refpObject);

protected:

};
#endif // ACDhitCnv_H
