// File and Version Iinformation:
// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/Address.cpp,v 1.3 2002/03/15 21:16:48 heather Exp $
//
// Description:
//   
//

#define Address_cpp

#include <iostream>
#include "Address.h"

Address::Address(unsigned char svc, const CLID& clid, const std::string& path)
: GenericAddress(svc, clid, path, "", 0, 0) 
{
}

