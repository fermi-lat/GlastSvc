
#ifndef _GlastSvc_IRandomAccess_H
#define _GlastSvc_IRandomAccess_H 1

// Include files
#include "GaudiKernel/IAlgTool.h"

class HepRandomEngine;

/** @class IRandomAccess
* @brief Abstract definition of a tool to be called from the
* GlastRandomSvc to set a local CLHEP static HepRandom instance to use a new engine 
* 
* $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/GlastSvc/GlastRandomSvc/IRandomAccess.h,v 1.1 2002/10/04 18:28:13 kyoung Exp $
*/

static const InterfaceID IID_IRandomAccess("IRandomAccess", 2 , 0);

class IRandomAccess :virtual public IAlgTool {
public:
    /// Retrieve interface ID
    static const InterfaceID& interfaceID() { return IID_IRandomAccess;}

    /// set the local engine, return previous pointer
    virtual HepRandomEngine* setTheEngine( HepRandomEngine* engine)=0;
};

#endif  // _GlastSvc_IRandomAccess_H
