#ifndef GLASTCNV_GLASTEVENTSELECTORITERATOR_H
#define GLASTCNV_GLASTEVENTSELECTORITERATOR_H 1

#include "GaudiKernel/IEvtSelector.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/Service.h"

#include <list>
#include <string>

/* @class GlastEvtIterator
* @brief
*
* $Header$
*/
class GlastEvtIterator: public IEvtSelector::Iterator {
public:
  friend class GlastEventSelector;
  GlastEvtIterator() {}
  GlastEvtIterator( const IEvtSelector* glastEvtSel): m_glastEvtSel(glastEvtSel),
    m_recId(0) { }
  GlastEvtIterator( const IEvtSelector* glastEvtSel, int recId, std::list<std::string>::const_iterator inpIt)
    : m_glastEvtSel(glastEvtSel){
	  m_inputDataIt =  inpIt;
	  m_recId = recId;
          m_evtCount = 0;
  }
  virtual ~GlastEvtIterator() { }
  virtual IOpaqueAddress* operator*() const  { return m_glastEvtSel->reference(*this);}
  virtual IOpaqueAddress* operator->() const { return m_glastEvtSel->reference(*this);}
  virtual IEvtSelector::Iterator& operator++()    { return m_glastEvtSel->next(*this);}
  virtual IEvtSelector::Iterator& operator--()    { return m_glastEvtSel->previous(*this);}
  virtual IEvtSelector::Iterator& operator++(int) { return m_glastEvtSel->next(*this);}
  virtual IEvtSelector::Iterator& operator--(int) { return m_glastEvtSel->previous(*this);}
  virtual bool operator==(const IEvtSelector::Iterator& it) const {
    const GlastEvtIterator* glastIt = dynamic_cast<const GlastEvtIterator*>(&it);
    return((m_recId == glastIt->m_recId));
  }
  virtual bool operator!=(const IEvtSelector::Iterator& it) const {
    const GlastEvtIterator* glastIt = dynamic_cast<const GlastEvtIterator*>(&it);
    return((m_recId != glastIt->m_recId));
  }
  void setFileNameIterator(std::list<std::string>::const_iterator inpIt) { m_inputDataIt = inpIt; }
private:
  const IEvtSelector*   m_glastEvtSel;
  int                   m_recId;
  std::list<std::string>::const_iterator  m_inputDataIt;
  int                   m_evtCount;

};

#endif  // GLASTCNV_GLASTEVENTSELECTORITERATOR_H



















