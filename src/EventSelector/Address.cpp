// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/EventSelector/Address.cpp,v 1.1.1.1 2000/09/27 18:55:46 burnett Exp $
#define SICBCNV_Address_CPP 


// Include files
#include <iostream>
#include "GaudiKernel/AddrFactory.h"
#include "Address.h"

// RCS Id for identification of object version
static const char* rcsid = "$Id: Address.cpp,v 1.1.1.1 2000/09/27 18:55:46 burnett Exp $";


//------------------------------------------------------------------------------
//
// Implementation of class :  (Address)
//
// Author :                   Markus Frank
//
//------------------------------------------------------------------------------


// Address Factory definition
static const AddrFactory<Address> s_Factory(SICB_StorageType);
const IAddrFactory& DummyAddressFactory = s_Factory;


/// Standard constructor
Address::Address(const CLID& cl, const std::string& fid, int recid, const std::string& bank)
: GenericAddress(SICB_StorageType, cl)
{
}

/// Standard Constructor for non-initialized addresses
Address::Address(const GenericLink& link)
: GenericAddress(link)
{
}

/// Standard Constructor for non-initialized addresses
Address::Address(const GenericLink* link)
: GenericAddress(*link)
{
}

/// Validate address
StatusCode Address::validate()    {
  return StatusCode::SUCCESS;
}

