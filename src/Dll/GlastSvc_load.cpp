/** 
* @file GlastSvc_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/Dll/GlastSvc_load.cpp,v 1.22 2003/02/14 21:02:39 usher Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"
// #include "GaudiKernel/IToolFactory.h"

// #define DLL_DECL_TOOL(x)       extern const IToolFactory& x##Factory; x##Factory.addRef();

DECLARE_FACTORY_ENTRIES(GlastSvc) {
    DECLARE_SERVICE( GlastDetSvc);
    DECLARE_SERVICE( GlastPropagatorSvc);
    DECLARE_SERVICE( GlastRandomSvc);
    DECLARE_SERVICE( GlastEventSelector );
    DECLARE_SERVICE( EventCnvSvc );
    DECLARE_CONVERTER( EventCnv );
    DECLARE_CONVERTER( MCEventCnv );

       DECLARE_ALGORITHM( SetSeeds );    

} 
