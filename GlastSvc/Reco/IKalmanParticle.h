// $Header: /nfs/slac/g/glast/ground/cvs/GismoGenerator/GismoGenerator/IKalmanParticle.h,v 1.3 2001/09/23 18:57:06 burnett Exp $
//
//
#ifndef GismoGenerator_IKalmanParticle_H
#define GismoGenerator_IKalmanParticle_H

#include "CLHEP/Matrix/Matrix.h"
#include "geometry/Point.h"
#include "geometry/Vector.h"
#include <iostream>

/// Abstract class used to provide an interface to Bill Atwoods's KalParticle.
/** Initial version by T Burnett, who takes full responsibility to the design of this 
   class, and necessary modifications to Bill's code to allow it to implement 
   this interface.
   <br>
   Note that the initial parameters are set by the IGismoSvc interface, which instantiates
   the subclass KalParticle.
 */
class  IKalmanParticle
{
public:


    /// move from starting point to next plane: return false if failed
    virtual bool trackToNextPlane()=0;
    virtual bool trackToNextSamePlane()=0;

    /// return the number of planes crossed by trackToNextPlane
    virtual int numberPlanesCrossed()const=0; 

    /// is the current point inside the Act Area? 
    virtual float insideActArea()const=0;
    virtual bool isXPlane() const=0;

    /// is the current point at a live strip?
    virtual bool stripIsLive()const=0; 

    /// current position
    virtual Point position()const=0;
    
    /// return properties associated with the propagation
    /**
    sum up the multiple scattering contributions to the track covr. matrix
    over a distance s (s must be less than maxArcLen).
    Note: the slope must be given as the size of the terms depend on the plane being
         asked for.  
 
    */
    virtual HepMatrix mScat_Covr(float momentum, float s) const=0;

    virtual double arcLength() const=0; 

    virtual double radLength() const=0; 

    /// dump current status, to the stream
    virtual void printOn(std::ostream& str=std::cout )const=0;

    virtual ~IKalmanParticle(){};
protected:
    IKalmanParticle(){};

};

#endif

