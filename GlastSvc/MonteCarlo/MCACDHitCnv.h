// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/GlastSvc/MonteCarlo/MCACDHitCnv.h,v 1.2 2000/10/25 20:31:58 heather Exp $
#ifndef MCACDHitCnv_H 
#define MCACDHitCnv_H 1

// Include files
//#include "Gaudi/Kernel/Converter.h"
#include "src/EventSelector/BaseCnv.h"

// Abstract factory to create the converter
template <class TYPE> class CnvFactory;

//extern unsigned char SICB_StorageType;


//------------------------------------------------------------------------------
//ClassName:   MCACDhitCnv
/*!
A converter class that handles ACD data from the IRF file
*/
// Author:   
//
//------------------------------------------------------------------------------
class MCACDHitCnv : public BaseCnv   {
  friend class CnvFactory<BaseCnv>;

public:
  //! Standard Constructor
  MCACDHitCnv( ISvcLocator* svc );
  //! Standard Destructor
  virtual ~MCACDHitCnv();
  //! access class ID
  static const CLID& classID();
  //! Update complete object
  virtual StatusCode updateObj(IOpaqueAddress* pAddress, DataObject* pObject);
  //! Create object
  virtual StatusCode createObj(IOpaqueAddress* pAddress, DataObject*& refpObject);

protected:

};
#endif // ACDhitCnv_H
