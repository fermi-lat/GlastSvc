#ifndef Address_H
#define Address_H 1

#include <string>
#include <vector>
#include "GaudiKernel/StatusCode.h"
#include "GaudiKernel/GenericAddress.h"

class IDataDirectory;

extern unsigned const char SICB_StorageType;

/** @class Address
 * @brief Definition of a GLAST address, derived from IOpaqueAddress.
 *
 * Based on SICb's Address class.
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/Address.h,v 1.4 2002/09/06 14:39:59 heather Exp $
 */
class Address : public GenericAddress   {
public:


  /// Map of references contained in this object
  class Entry  {
  public:
    int   m_id;
    int*  m_ptr;
    void* m_obj;
    Entry(int id, int* ptr, void* obj) : m_id(id), m_ptr(ptr), m_obj(obj)   {
    }
    int id()  {
      return m_id;
    }
    int* pointer()  {
      return m_ptr;
    }
    template <class TYPE> void loadPointer(TYPE*& pObject)  {
      pObject = static_cast<TYPE*>(m_obj);
    }
  };
  typedef std::vector<Entry>    References;

protected:
  References      m_refs;
  int m_recid;  //THB: does this make sense?
public:

  Address( unsigned char svc,const CLID& clid, const std::string& path);
  virtual ~Address()    {}
};


#endif  // Address_H
