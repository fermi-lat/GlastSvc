//$Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/GlastSvc/GlastDetSvc/IGeometry.h,v 1.3 2002/03/11 17:25:14 riccardo Exp $


#ifndef GLASTDET_IGEOMETRY_H
#define GLASTDET_IGEOMETRY_H
#include <vector>
#include <string>
/** Abstract class that defines callbacks from a traversal of the detector geometry tree

  */
class IGeometry {
public:

    typedef std::vector<double> DoubleVector;
    typedef std::vector<unsigned int>UintVector;
    enum VolumeType{ Simple, posSensitive, intSensitive, Composite, Xstack, Ystack, Zstack };
    enum ShapeType{ Box, Tube };
    /** Create a new shape

        @param s type of the shape
        @param id vector of unsigned ints (maybe null)
        @param name of the shape
        @param material  material name, possibly meaningful in detModel
        @param params vector with the six transformation parameters, followed by 3 or so dimensions
        */
    virtual void pushShape(ShapeType s, const UintVector& id, std::string name, std::string material, 
        const DoubleVector& params, VolumeType type)=0;
    
    //* called to signal end of nesting */
    virtual void popShape()=0;

    virtual ~IGeometry(){}

protected:
    IGeometry(){};
};



#endif
