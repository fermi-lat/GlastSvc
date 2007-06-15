// File and Version Information:
// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/GlastDetSvc/DMmanager.cxx,v 1.12 2003/12/10 19:42:03 jrb Exp $
//
// Description:
// Wrapper class around detModel, to hide all the initialization and 
// provide defaults.

#include "DMmanager.h"

#include "detModel/Management/Manager.h"
#include "detModel/Management/XercesBuilder.h"
#include "detModel/Sections/Volume.h"
#include "detModel/Management/MaterialsVisitor.h"
#include "detModel/Gdd.h"
#include "xmlUtil/id/IdDict.h"

#include "idents/VolumeIdentifier.h"

#include "CLHEP/Geometry/Transform3D.h"
#include "facilities/Util.h" // for expandEnvVar
#include <string>
#include <cassert>
#include <iomanip>
#include <stdexcept>

DMmanager::DMmanager( )
:m_dm(detModel::Manager::getPointer())
{
}

void DMmanager::init(int argc, char* argv[] ) 
{
    // Purpose and Method:  Set up args: filename and topvol; 
    //   defaults are the standard flight.xml and LAT
    
    std::string filename = (argc<2)? std::string( "-") : std::string(argv[1]);
    std::string topvol   = (argc<3)? std::string("LAT") : std::string(argv[2]);
    std::string mode("fastmc");
    init( filename, mode, topvol);
}

void DMmanager::init(std::string filename, std::string mode, std::string topvol) 
{
    m_dm->setBuilder(new detModel::XercesBuilder);
    if( filename.empty() || filename == "-" ) filename = "$(XMLGEODBSROOT)/xml/flight/flight.xml" ;
    facilities::Util::expandEnvVar(&filename);
    m_dm->setNameFile( filename);
    m_dm->build(detModel::Manager::all);
    m_vol = m_dm->getGdd()->getVolumeByName(topvol);
    if( m_vol==0) {
        std::cerr << "Could not find a topvol " << topvol << std::endl;
        exit(-1);
    }

    // We setup the IDmap with the finest choice mode
    std::string temp = m_dm->getFineChoice();
    m_idMap = new detModel::IDmapBuilder(topvol);
    if (temp!="0")
      m_idMap->setMode(temp);
    m_dm->startVisitor(m_idMap);    
    m_dm->setMode(m_mode=mode);
}

bool DMmanager::getNumericConstByName(std::string name, double* res)
{
  return m_dm->getNumericConstByName(name,res);
}

bool DMmanager::getNumericConstByName(std::string name, int* res)
{
  return m_dm->getNumericConstByName(name,res);
}

void DMmanager::accept( detModel::SectionsVisitor* v){ m_vol->AcceptNotRec(v);  }

void DMmanager::accept( detModel::MaterialsVisitor* v){ m_dm->startVisitor(v);  }

void DMmanager::printSetup(std::ostream& out) { 
    out << " geometry setup: "<< std::endl
        << std::setw(15) << "document = " << m_dm->getNameFile() << std::endl
        << std::setw(15) << "mode = "     << m_mode << std::endl
        << std::setw(15) << "topvol = "   << std::string(m_vol->getName())  << std::endl;

     m_idMap->summary(out);
}

DMmanager::~DMmanager() {        delete m_dm;    }

std::string DMmanager::topvol()const{ return m_vol->getName(); }

idents::VolumeIdentifier DMmanager::getIDPrefix() const
{
  return m_idMap->getIDPrefix();
}

bool DMmanager::getTransform3DByID(idents::VolumeIdentifier id, HepTransform3D* tr)
{
  return m_idMap->getTransform3DByID(id,tr);
}

const HepTransform3D& DMmanager::getTransform3DPrefix() const
{
  return m_idMap->getTransform3DPrefix();
}

bool DMmanager::getShapeByID(idents::VolumeIdentifier id,
                             std::string* s, 
                             std::vector<double>* params){

  return m_idMap->getShapeByID(id,s,params);
}
     
void
DMmanager::orderRibbonSegments(std::vector<idents::VolumeIdentifier>& segs,
                               unsigned face, unsigned ribNum,
                               bool xOrient, bool increasing) {

  using detModel::IDmapBuilder;

// get some enum values for VolumeIdentifier fields
  static bool init = false;  
  static int eLATACD;  //
  static int eACDRibbon; 
  static int eMeasureX;
  static int eMeasureY;

  idents::VolumeIdentifier sample;

  if (!init) {
    bool ok = m_dm->getNumericConstByName("eLATACD", &eLATACD);
    if (ok) ok = m_dm->getNumericConstByName("eACDRibbon", &eACDRibbon);
    if (ok) ok = m_dm->getNumericConstByName("eMeasureX", &eMeasureX);
    if (ok) ok = m_dm->getNumericConstByName("eMeasureY", &eMeasureY);
    if (!ok) {
      std::cerr 
        << "FATAL: Ribbon volume identifier field values not found" 
        << std::endl;
      exit(1);
    }
    // Check that fields are what we think they should be
    xmlUtil::IdDict* dict = m_dm->getGdd()->getIdDictionary();

    xmlUtil::NamedId ribId(6);

    ribId.addField("fLATObjects", eLATACD);
    ribId.addField("fACDFace", 0);
    ribId.addField("fACDCmp", 41);
    ribId.addField("fMeasure", eMeasureX);
    ribId.addField("fRibbon", 1);
    ribId.addField("fRibbonSegment", 1);

    if (!dict->idOk(ribId)) {
      std::cerr 
        << "FATAL: Ribbon volume identifier structure not as expected!"
        << std::endl;
      exit(1);
    }

    init = true;
  }
  // Make a volume identifier for a ribbon

  IDmapBuilder::axisDir dir = IDmapBuilder::zDir; // for face != 0

  sample.append(eLATACD);           // ACD
  sample.append(face);
  sample.append(eACDRibbon);   // ribbon

  if (xOrient) {
    sample.append(eMeasureY);  // measures Y
    if (face==0) dir = IDmapBuilder::xDir;
  }
  else {
    sample.append(eMeasureX);  // measures X
    if (face==0) dir = IDmapBuilder::yDir;
  }
 
  sample.append(ribNum);
  sample.append(0);    

  // segment # doesn't matter; will be masked off

  std::vector<bool> wild;
  wild.reserve(6);
  wild.push_back(false);
  wild.push_back(false);
  wild.push_back(false);
  wild.push_back(false);
  wild.push_back(false);
  wild.push_back(true);

  m_idMap->orderSensitive(segs, sample, wild, dir, increasing);

}
