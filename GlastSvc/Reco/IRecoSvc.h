// $Id: IGlastDetSvc.h,v 1.5 2001/04/19 01:32:28 igable Exp $
// 
//!  \author: Toby Burnett tburnett@u.washington.edu
//

#ifndef _H_IRecoSvc_
#define _H_IRecoSvc_

// includes
#include "GaudiKernel/IInterface.h"
#include "geometry/Point.h"

#include <memory> // for auto_ptr

//forward declarations
class IKalmanParticle;

// Declaration of the interface ID ( interface id, major version, minor version) 
static const InterfaceID IID_IRecoSvc(905, 1 , 0); 

//!  \author: T Burnett
/** Abstract interface for GLAST reconstruction service, giving access to  
   to a IKalmanParticle object.

*/

class   IRecoSvc : virtual public IInterface {
public:
 
    
    /// return a IKalmanParticle object (auto_ptr guarantees deletion)
    virtual std::auto_ptr<IKalmanParticle> kalmanParticle(Point p0, Vector v0, double step)=0; 


    /// Retrieve interface ID
    static const InterfaceID& interfaceID() { return IID_IRecoSvc; }


};



#endif  // _H_IGlastDetSvc_
