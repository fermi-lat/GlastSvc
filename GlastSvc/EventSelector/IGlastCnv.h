#ifndef _IGlastCnv_H
#define _IGlastCnv_H 1

#include <string>
#include "GaudiKernel/IConverter.h"

/** @class IGlastCnv
* @brief An abstract interface to GLAST converters
*
* $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/GlastSvc/EventSelector/IGlastCnv.h,v 1.0 2002/09/06 14:40:00 heather Exp $
*/
class IGlastCnv : virtual public IConverter    
{
public:
    virtual void setPath(const std::string& path) = 0;
    virtual const std::string& getPath() const = 0;
};


#endif // _IGlastCnv_H
