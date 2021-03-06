
#ifndef _H_GlastDetSvc_
#define _H_GlastDetSvc_

#include "GaudiKernel/Service.h"
#include "GaudiKernel/IEvtSelector.h"
#include "GlastSvc/GlastDetSvc/IGlastDetSvc.h"

class Instrument;
class GlastDetector;
namespace xml { class IFile; }
class DMmanager;
namespace idents{class VolumeIdentifier;}

/** @class GlastDetSvc
* @brief This Glast-defined Gaudi service provides access to the DMmanager
* which provides parameters and constants associated with the geometry.
* 
* @author Sawyer Gillespie
* $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/GlastDetSvc/GlastDetSvc.h,v 1.25 2007/06/15 15:57:02 jrb Exp $
*/
class GlastDetSvc : public Service, 
virtual public IGlastDetSvc
{
public:
    
    //! Create the service
    //! @param name The name of the service
    //!
    GlastDetSvc ( const std::string& name, ISvcLocator* al );
    
    virtual ~GlastDetSvc ();
    
    /// queryInterface - for implementing a Service this is necessary
    StatusCode queryInterface(const InterfaceID& riid, void** ppvUnknown);
    
    /// return the service type
    const InterfaceID& type() const;
    
    /// perform initializations for this service. This will
    ///    read in and create the GlastDetector hierarchy from the file
    ///    specified by the PersistencyFile property, unless it is
    ///    '(none)'
    StatusCode initialize ();
    
    /// kill off the detector hierarchy if it exists
    StatusCode finalize ();
    //! new detModel interface, will call back. 
    virtual void accept(IMedia& media);
    
    //! start a visitor of the detModel geometry description 
    //!(implements IGlastDetSvc)
    virtual void accept(IGeometry& geom);
    
    //! detModel interface to retrieve numeric constants
    virtual StatusCode getNumericConstByName(std::string, double*);
    
    /** detModel interface to retrieve integer numeric constants.
    Returns FAILURE and stores no value in val if constant doesn't
    exist or has not been declared of type int in the xml source.
    */
    virtual StatusCode getNumericConstByName(std::string name, int*);
    
    /// Return Volume identifer of top volume relative to world
    virtual idents::VolumeIdentifier getIDPrefix();
    
    
    /// retrieve the 3D transformation of a volume given a valid ID
    virtual StatusCode getTransform3DByID(idents::VolumeIdentifier,
        HepTransform3D*);
    
    /// Return transform of top volume relative to world
    virtual const HepGeom::Transform3D& getTransform3DPrefix();    
    
    /// retrieve the type and dimensions of a volume given a valid ID
    virtual StatusCode  getShapeByID(idents::VolumeIdentifier id,
        std::string*, 
        std::vector<double>*);
    /// Given a volume identifier, return equivalent vector of pair of
    /// strings.  In a pair the first string is to be interpreted as 
    /// a field name, the second as a value (unsigned int).
    virtual NamedId getNamedId(const idents::VolumeIdentifier& vid);

    /// Get all ribbon segments belonging to specified ribbon on specified
    /// face. Return in order along relevant axis direction.
    virtual void 
    orderRibbonSegments(std::vector<idents::VolumeIdentifier>& segs,
                        unsigned face, unsigned ribbonNumber, 
                        bool xOrient, bool increasing=true);

    /// retrieve the name of the top volume
    virtual std::string getTopVolume() {return m_topvol;}
    

    /// compute strip id from local coordinate for a tkr plane
    virtual unsigned int stripId (double x);
    virtual unsigned int stripId (const HepPoint3D&  x);

    /// (-) if non-active or gap (P is in local system)    
    virtual double insideActiveArea  ( const HepPoint3D& p);
    /// insideActive for local X
    virtual double insideActiveLocalX( const HepPoint3D& p);
    /// insideActive for local Y
    virtual double insideActiveLocalY( const HepPoint3D& p);
    
    /// location of strip ix in local coords
    virtual double stripLocalX ( double istrip); 
    
    /// return plane coordinate given wafer coordinate
    virtual HepPoint3D siPlaneCoord( const HepPoint3D &p, idents::VolumeIdentifier volId);
    
    /// return the global position of a strip in the plane, will accept int or double
    virtual HepPoint3D getStripPosition(idents::VolumeIdentifier id, double stripid);

private:
    
    /// Data Members
    Instrument*     m_instrument;
    std::string     m_xmlFile;
    std::string     m_iniFile;
    DMmanager*      m_dm;
    std::string     m_xmlfile;
    std::string     m_topvol;
    std::string     m_visitorMode;

};

#endif // _H_GlastDetSvc
