#ifndef EVENTCNV_H
#define EVENTCNV_H 1

#include "BaseCnv.h"

namespace Event{ class EventHeader; }
extern const CLID& CLID_Event;

// Abstract factory to create the converter
template <class TYPE> class CnvFactory;


/** @class EventCnv
 * @brief Concrete Converter for the Event header
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/EventCnv.h,v 1.3 2002/03/18 19:00:35 heather Exp $
 */ 

class EventCnv : public BaseCnv { //public ItemCnv<Event>	    {

  friend class CnvFactory<EventCnv>;

public: 
  static const CLID& classID()   
  {
    return CLID_Event;
  }

protected:

  EventCnv(ISvcLocator* svc);

  virtual ~EventCnv() { };

  virtual StatusCode createObj(IOpaqueAddress* pAddress, DataObject*& refpObject);

  virtual StatusCode updateObj(int* data, Event::EventHeader* pObject);


};


#endif // EVENTCNV_H
