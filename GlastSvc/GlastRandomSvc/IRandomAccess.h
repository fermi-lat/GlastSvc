
#ifndef _GlastSvc_IRandomAccess_H
#define _GlastSvc_IRandomAccess_H 1

// Include files
#include "GaudiKernel/IAlgTool.h"

class HepRandomEngine;

/** @class IRandomAccess
* @brief Abstract definition of a tool to be called from the
* GlastRandomSvc to set a local CLHEP static HepRandom instance to use a new engine 
* 
* $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/GlastSvc/GlastRandomSvc/IRandomAccess.h,v 1.2 2003/02/11 19:22:57 burnett Exp $
*/

static const InterfaceID IID_IRandomAccess("IRandomAccess", 3 , 0);

class IRandomAccess :virtual public IAlgTool {
public:
    /// Retrieve interface ID
    static const InterfaceID& interfaceID() { return IID_IRandomAccess;}

    /// set the local engine, return previous pointer
    virtual HepRandomEngine* setTheEngine( HepRandomEngine* engine)=0;

    /// return pointer to a static function that sets the flag in the RandGauss
    typedef void(*SetFlag)(bool);
    virtual  SetFlag getRandSet();

};

#endif  // _GlastSvc_IRandomAccess_H
