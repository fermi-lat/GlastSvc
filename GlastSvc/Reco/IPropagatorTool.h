
#ifndef IPROPAGATORTOOL_H
#define IPROPAGATORTOOL_H

#include "GaudiKernel/IAlgTool.h"

class IKalmanParticle;

/** @class IPropagatorTool
* @brief Abstract interface for GLAST reconstruction service, giving access to  
* to a IKalmanParticle object.
*
* @author Toby Burnett
* $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/GlastSvc/Reco/IPropagatorTool.h,v 1.2 2002/09/06 14:34:48 heather Exp $
*/
static const InterfaceID IID_IPropagatorTool("IPropagatorTool", 1 , 0);

class IPropagatorTool 
{
public:
	/// Retrieve interface ID
	static const InterfaceID& interfaceID() { return IID_IPropagatorTool; }
    
    /// return a IKalmanParticle object
    virtual IKalmanParticle* getPropagator() = 0;
};



#endif 
