/** 
* @file GlastSvc_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/Dll/GlastSvc_load.cpp,v 1.19 2002/03/27 18:50:15 burnett Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(GlastSvc) {
    DECLARE_SERVICE( GlastDetSvc);
    DECLARE_SERVICE( GlastEventSelector );
    DECLARE_SERVICE( EventCnvSvc );
    
    DECLARE_CONVERTER( EventCnv );
    DECLARE_CONVERTER( MCEventCnv );
   //THB DECLARE_CONVERTER( DigiEventCnv );
} 
