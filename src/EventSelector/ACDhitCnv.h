// $Header: /cvs/cmt/GlastSvc/src/EventSelector/ACDhitCnv.h,v 1.3 2000/09/18 13:39:15 heather Exp $
#ifndef ACDhitCnv_H 
#define ACDhitCnv_H 1

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
class ACDhitCnv : public BaseCnv   {
  friend class CnvFactory<BaseCnv>;

public:
  /// Standard Constructor
  ACDhitCnv( ISvcLocator* svc );
  /// Standard Destructor
  virtual ~ACDhitCnv();
  /// class ID
  static const CLID& classID();
  /// Update complete object
  virtual StatusCode updateObj(IOpaqueAddress* pAddress, DataObject* pObject);
  /// Create object
  virtual StatusCode createObj(IOpaqueAddress* pAddress, DataObject*& refpObject);

protected:
    /// Storage type and class ID
  //static const unsigned char storageType()     { return SICB_StorageType; }

};
#endif // ACDhitCnv_H
