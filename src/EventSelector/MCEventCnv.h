#ifndef CNV_MCEVENTCNV_H 
#define CNV_MCEVENTCNV_H 1

#include "BaseCnv.h"

class IDataDirectory;
class ISvcLocator;
class MCEvent;

// Abstract factory to create the converter
template <class T> class CnvFactory;

/** @class MCEventCnv
* @brief Concrete converter for the McEvent header on the TDS /Event/MC
*
* $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/MCEventCnv.h,v 1.4 2002/03/18 19:00:35 heather Exp $
*/
class MCEventCnv : public BaseCnv { 
    friend class CnvFactory<MCEventCnv>;
public:
    
    MCEventCnv(ISvcLocator* svc);
    
    virtual ~MCEventCnv() { };
    static const CLID& classID();
    
    /// Create object
    virtual StatusCode createObj(IOpaqueAddress* pAddress, DataObject*& refpObject);
    
private:
};
#endif // CNV_MCEVENTCNV_H
