// $Header: /cvs/cmt/GlastSvc/src/Dll/GlastSvc_load.cpp,v 1.7 2000/09/14 23:42:24 heather Exp $
//====================================================================
//  GlastSvc_load.cpp
//--------------------------------------------------------------------
//
//  Package    : Gaudi/System
//
//  Description: Implementation of <Package>_load routine.
//               This routine is needed for forcing the linker
//               to load all the components of the library. 
//
//====================================================================

#include "Gaudi/Interfaces/ICnvFactory.h"
#include "Gaudi/Interfaces/ISvcFactory.h"
#include "Gaudi/Interfaces/IAlgFactory.h"


#define DLL_DECL_SERVICE(x)    extern const ISvcFactory& x##Factory; x##Factory.addRef();
#define DLL_DECL_CONVERTER(x)  extern const ICnvFactory& x##Factory; x##Factory.addRef();
#define DLL_DECL_ALGORITHM(x)  extern const IAlgFactory& x##Factory; x##Factory.addRef();
#define DLL_DECL_OBJECT(x)     extern const IFactory& x##Factory; x##Factory.addRef();

//! Load all GlastSvc services: 
void GlastSvc_load() {
    // GlastSvc services
    DLL_DECL_SERVICE( GlastDetSvc );
    DLL_DECL_SERVICE( GlastEventSelector );
    DLL_DECL_SERVICE( EventCnvSvc );
    DLL_DECL_CONVERTER( ACDhitCnv );
//    DLL_DECL_SERVICE( EventCnv );
//    DLL_DECL_SERVICE( GlastIRFLoadSvc );
} 

extern "C" void GlastSvc_loadRef()    {
  GlastSvc_load();
}

