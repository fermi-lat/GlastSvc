#ifndef CNV_DIGIEVENTCNV_H 
#define CNV_DIGIEVENTCNV_H 1

#include "BaseCnv.h"

class IDataDirectory;
class ISvcLocator;
class DigiEvent;

extern const CLID& CLID_DigiEvent;

// Abstract factory to create the converter
template <class T> class CnvFactory;

/** @class DigiEventCnv
 * @brief Right now this converter does nothing particularly useful other than
 * make the Digi branch of the TDS work.
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/DigiEventCnv.h,v 1.2 2002/03/15 21:16:48 heather Exp $
*/
class DigiEventCnv : public BaseCnv {
  friend class CnvFactory<DigiEventCnv>;

public: 
  static const CLID& classID()   
  {
    return CLID_DigiEvent;
  }

protected:
  DigiEventCnv(ISvcLocator* svc);
  virtual ~DigiEventCnv() { };
  virtual StatusCode createObj(IOpaqueAddress* pAddress, DataObject*& refpObject);
  virtual StatusCode updateObj(int* data, DigiEvent* pObject);
};
#endif // CNV_DIGIEVENTCNV_H
