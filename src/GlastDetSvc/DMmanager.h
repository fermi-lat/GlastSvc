// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/GlastDetSvc/DMmanager.h,v 1.5 2002/03/14 12:31:43 riccardo Exp $

#ifndef DM_DMmanager_h
#define DM_DMmanager_h

namespace detModel{
    class Manager;
    class Volume;
    class SectionsVisitor;
    class MaterialsVisitor;
    class IDmapBuilder;
}

namespace idents{class VolumeIdentifier;}

class HepTransform3D;

#include <string>
#include "detModel/Management/IDmapBuilder.h"

/**
  wrapper class around detModel, to hide all the initialization stuff, provide defaults
  */
class DMmanager  {
public:
    DMmanager();
    ~DMmanager();

    //! initialize with command-line args, supplying defaults
    void init(int argc, char* argv[] ) ;

    //! Note that if filename is "-" or blank, use xmlGeoDbs default
    void init(std::string filename, std::string mode, std::string topvol);

    //! start a visitor from the top volume
    void accept( detModel::SectionsVisitor* v);

    //! start a materials visitor
    void accept( detModel::MaterialsVisitor* v);

    //! retrive a numeric constant
    bool getNumericConstByName(std::string, double*);

    //! summarize setup.
    void printSetup(std::ostream& out);

    /// retrive the 3D transformation of a volume given a valid ID
    bool getTransform3DByID(idents::VolumeIdentifier, HepTransform3D*);

    /// retrive the parameters (type and dimensions) of a volume given a valid
    /// ID
    bool getShapeByID(idents::VolumeIdentifier id,
                      std::string*, 
                      std::vector<double>* params);

    //! access to name of selected top volume
    std::string topvol()const;

private:
    detModel::Manager* m_dm;
    detModel::Volume * m_vol;
    std::string m_mode;
    /// The idMapBuilder
    detModel::IDmapBuilder* m_idMap;
};

#endif
