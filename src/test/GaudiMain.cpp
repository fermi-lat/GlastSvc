// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/test/GaudiMain.cpp,v 1.1.1.1 2000/09/27 18:55:47 burnett Exp $
#define COMMON_MAIN_CPP


// Include files
#include "Gaudi/Kernel/SmartIF.h"
#include "Gaudi/Kernel/Bootstrap.h"
#include "Gaudi/Interfaces/IAppMgrUI.h"
#include "Gaudi/Interfaces/IProperty.h"
#include "Gaudi/JobOptionsSvc/Property.h"
#include "Gaudi/System/System.h"


//------------------------------------------------------------------------------
//
//  Package    : Gaudi Examples
//
//  Description: Main Program
//
//------------------------------------------------------------------------------
#ifndef WIN32
void FATAL(const char* text){std::cerr << text << std::endl;}
#endif // WIN32 


//--- Example main program
int main( int argn, char** argc) {
    


    // get the path to this package from its root environment variable: if not there,
    // assume that we are in the root
    const char * local_path = ::getenv("GLASTSVCROOT");
    
    std::string joboptions_file = std::string(local_path? local_path: "");

    joboptions_file +=  std::string("/src/test/jobOptions.txt");
    
    
    // Create an instance of an application manager
    IInterface* iface = Gaudi::createApplicationMgr();
    
    SmartIF<IProperty>     propMgr ( IID_IProperty, iface );
    SmartIF<IAppMgrUI>     appMgr  ( IID_IAppMgrUI, iface );
    
    // Set properties of algorithms and services
    StatusCode status = StatusCode::SUCCESS;
    if ( iface && propMgr == iface )    {
        status = propMgr->setProperty( StringProperty("JobOptionsPath", joboptions_file) );
    }
    else  {
        exit(-1);
    }

    
    // Run the application manager and process events
    if ( appMgr )   {
        status = appMgr->run();
    }
    else  {
        return 0;
    }
    
    // All done - exit
    return 0;
    
}
