// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/Address.cpp,v 1.2 2001/04/19 01:32:29 igable Exp $
#define Address_cpp

#include <iostream>
#include "Address.h"

Address::Address(unsigned char svc, const CLID& clid, const std::string& path)
: GenericAddress(svc, clid, path, "", 0, 0) 
{
}

