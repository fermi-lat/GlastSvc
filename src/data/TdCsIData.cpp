//old School version
#include "TdCsIData.h"
//#include "instrument/Calorimeter.h"

//! Default constructor
TdCsIData::TdCsIData (int numLayers)
{
    for(int i=0; i<numLayers; i++)  {    
        calorList.push_back((new std::vector<Xtal>));
    }
}

/*! Method to copy  all the relevant information from another TdCsIData
    object.
*/
void TdCsIData::copyUp( TdCsIData* copy,int numLayers)
{
    for(int i = 0; i < numLayers; i++)
    {
        for(int j = 0;j  < copy->nHits(i); j++)
        {
            // Taking out the diodes for now...fix later.
            calorList[i]->push_back(Xtal(copy->xtalPos(i,j), copy->energy(i,j),0/*moduleId*/,
            copy->xtalId(i,j), copy->Lresp(i,j), copy->Rresp(i,j)/*copy->Diodes_Energy(i,j)*/));
        }
    }
}

//! Destructor
TdCsIData::~TdCsIData ()
{
    clear();
    for(unsigned i=0; i<calorList.size(); i++) {
        delete calorList[i];
    }
}

//! retern the number of Hits of a specific layer
int TdCsIData::nHits (unsigned int layer) const
{
    return calorList[layer]->size();
}

//! renurn energy on specific xtal at layer and index
float TdCsIData::energy (unsigned int layer, unsigned int n) const
{
    if(n < calorList[layer]->size())
    {
        return (*calorList[layer])[n].energy;
    } else
        return -2;
}

//! return position of specific xtal at layer and index
Point TdCsIData::xtalPos (unsigned int layer, unsigned int n) const
{
    return  (*calorList[layer])[n].pos;
}


idents::ModuleId TdCsIData::moduleId (unsigned int layer, unsigned int n) const
{
    return (*calorList[layer])[n].module;
}

//! get the id 
idents::XtalId TdCsIData::xtalId (unsigned int layer, unsigned int n) const
{
    return (*calorList[layer])[n].id;
}

//! get the  Lresp of specific xtal at layer and index
float TdCsIData::Lresp (unsigned int layer, unsigned int n) const
{
    return (*calorList[layer])[n].Lresp;
}

//! get the Rresp of specific xtal at layer and index
float TdCsIData::Rresp (unsigned int layer, unsigned int n) const
{
    return (*calorList[layer])[n].Rresp;
}


const std::vector<double>& TdCsIData::Diodes_Energy (unsigned int layer, unsigned int n) const
{
    return (*calorList[layer])[n].Diodes_Energy;
}



/*! Takes in a TdCsIData object makes an xtal object and pushes in back onto
    the  calorList of xtal objects. Currently called from IRFConverter
*/
void TdCsIData::load (const CsIDetector& xtal, idents::ModuleId tower)
{
    
    if (xtal.hit()) {
        calorList[xtal.layer()]->push_back(Xtal(xtal.xtalPos(), xtal.energy(),tower ,
            xtal.xtalId(), xtal.Lresp(), xtal.Rresp(),
				xtal.getDiodesEnergy()));

        // put the "raw" information into the basic list
        idents::XtalId id( tower, xtal.layer(), xtal.xtalId());
        int	left =  static_cast<int>(xtal.Lresp()*1e6),
            right = static_cast<int>(xtal.Rresp()*1e6);
        m_xtals[id]=std::pair<int,int>(left,right);
    }

}




void TdCsIData::clear ()
{
//    m_xtals.clear();
    for(unsigned i=0; i<calorList.size(); i++) {
        calorList[i]->clear();
    }
}

void TdCsIData::printOn (std::ostream& cout) const
{
  cout << "\nCsIData:\n";
  for(unsigned layer=0; layer < calorList.size(); layer++)
  {
    int nh = nHits(layer);
    if( nh==0 ) continue;
    for(int i=0; i<nh; i++)
      cout << '\t' << energy(layer,i) << '\t' << xtalPos(layer,i) << '\n';
  }

}
