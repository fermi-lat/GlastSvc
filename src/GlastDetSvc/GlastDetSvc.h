// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/GlastDetSvc/GlastDetSvc.h,v 1.1.1.1 2000/09/27 18:55:46 burnett Exp $
// 
//  Original author: Sawyer Gillespie
//                   hgillesp@u.washington.edu
//

#ifndef _H_GlastDetSvc_
#define _H_GlastDetSvc_

// includes
#include "Gaudi/Kernel/Service.h"
#include "Gaudi/Interfaces/IEvtSelector.h"
#include "GlastSvc/GlastDetSvc/IGlastDetSvc.h"
#include "GlastSvc/GlastDetSvc/IGlastIRFLoadSvc.h"

// forward declarations
class Instrument;
namespace xml { class IFile; }

/*!  This Gaudi service provides access to a tree of GlastDetector objects.
*/
class GlastDetSvc : public Service, 
    virtual public IGlastDetSvc
{
public:
    
    //! Create the service
    //! @param name The name of the service
    //!
    GlastDetSvc ( const std::string& name, ISvcLocator* al );
    
    /// destructor
    virtual ~GlastDetSvc ();

    /// queryInterface - for implementing a Service this is necessary
    StatusCode queryInterface(const IID& riid, void** ppvUnknown);
    
    /// return the service type
    const IID& type() const;
    
    /// perform initializations for this service. This will
    ///    read in and create the GlastDetector hierarchy from the file
    ///    specified by the PersistencyFile property.
    StatusCode initialize ();
    
    /// kill off the detector hierarchy if it exists
    StatusCode finalize ();
    
    /// return the root detector for this service (implements IGlastDetSvc)
    GlastDetector*  getRootDetector ();
    

    //! access to the IFile containing detector constants (implements IGlastDetSvc)
    virtual const xml::IFile* iniFile()const;

    
    /// open the IRF file
    StatusCode  openIRF(std::string filename);
    
    /// load the next event from the IRF file (implements IGlastIRFLoadSvc)
    StatusCode  readIRF ();

    
    //! return the number of detectors currently with data
    int detectors_with_data() const;

    
    //! accept a visitor to traverse the structure 
    void accept(DetectorConverter&)const;


    
private:
    
    // Data Members
    Instrument*		m_instrument;
    std::string		m_xmlFile;
    std::string		m_iniFile;
    std::string		m_irfFile;
    
};

#endif // _H_GlastDetSvc