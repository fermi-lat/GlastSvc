// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/GlastSvc/mainpage.h,v 1.1.1.1 2000/09/27 18:55:46 burnett Exp $
// Mainpage for doxygen

/*! \mainpage package GlastSvc

\section NewConverters New Converters

Heather and Ian have defined a new set of converters to go from the IRF format to
the new set of Monte Carlo classes. They all inherit from from the BaseCnv class.

  - BaseCnv classes
    - MCACDHitCnv
    - MCCalorimeterHitCnv
    - MCSiLayerCnv

\section Testing Testing

Heather has made a small testing Algorithm called CreateEvent.

Also working in conjuction with the MC Converters is the IRFConverter which uses 
the IRF parsers defined in the intrument package.

\section General General


 Defines the services
 - IGlastDetSvc, implmented by GlastDetSvc. 
 - IGlastIRFLoadSvc also implemented by GlastDetSvc.

  <hr>
  \section notes release notes
  \include release.notes
  \section requirements requirements
  \include requirements

*/

