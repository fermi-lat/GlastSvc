#ifndef DM_DMmanager_h
#define DM_DMmanager_h

namespace detModel{
    class Manager;
    class Volume;
    class SectionsVisitor;
    class MaterialsVisitor;
    class IDmapBuilder;
}

namespace xmlUtil {
  class IdDict;
} 

namespace idents{class VolumeIdentifier;}

namespace HepGeom {class Transform3D;}
typedef HepGeom::Transform3D HepTransform3D;

#include <string>
#include "detModel/Management/IDmapBuilder.h"
#include "xmlUtil/id/IdDict.h"

/** @class DMmanager
* @brief Wrapper class around detModel, to hide all the initialization 
* and provide defaults.
*
* $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/GlastDetSvc/DMmanager.h,v 1.10 2007/06/15 15:57:02 jrb Exp $
*/
class DMmanager  {
public:
    DMmanager();
    ~DMmanager();
    
    /// initialize with command-line args, supplying defaults
    void init(int argc, char* argv[] ) ;

    /// Note that if filename is "-" or blank, use xmlGeoDbs default
    void init(std::string filename, std::string mode, std::string topvol);

    /// start a visitor from the top volume
    void accept( detModel::SectionsVisitor* v);

    /// start a materials visitor
    void accept( detModel::MaterialsVisitor* v);

    /// retrieve a numeric constant as floating point
    bool getNumericConstByName(std::string, double*);

    /// retrieve a numeric constant -- must be int
    bool getNumericConstByName(std::string, int*);

    /// summarize setup.
    void printSetup(std::ostream& out);

    /// Return Volume identifer of top volume relative to world
    idents::VolumeIdentifier getIDPrefix() const;

    /// retrieve the 3D transformation of a volume given a valid ID
    bool getTransform3DByID(idents::VolumeIdentifier, HepTransform3D*);

    /// Return transform of top volume relative to world
    const HepTransform3D& getTransform3DPrefix() const;    

    /// retrieve the parameters (type and dimensions) of a volume given a valid
    /// ID
    bool getShapeByID(idents::VolumeIdentifier id,
                      std::string*, 
                      std::vector<double>* params);

    void orderRibbonSegments(std::vector<idents::VolumeIdentifier>& segs,
                             unsigned face, unsigned ribbonNumber, 
                             bool xOrient, bool increasing=true);

    xmlUtil::IdDict* getIdDictionary();

    /// access to name of selected top volume
    std::string topvol() const;

private:
    detModel::Manager* m_dm;
    detModel::Volume * m_vol;
    std::string m_mode;
    /// The idMapBuilder
    detModel::IDmapBuilder* m_idMap;
};

#endif
