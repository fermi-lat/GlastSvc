// $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/GlastDetSvc/GeometryVisitor.cxx,v 1.6 2002/04/24 00:04:16 jrb Exp $

#include <string>

#include "GeometryVisitor.h"
#include "GlastSvc/GlastDetSvc/IGlastDetSvc.h"

#include "detModel/Management/Manager.h"
#include "detModel/Sections/Section.h"
#include "detModel/Sections/Volume.h"
#include "detModel/Gdd.h"
#include "detModel/Sections/Box.h"
#include "detModel/Sections/Tube.h"
#include "detModel/Sections/Composition.h"
#include "detModel/Sections/Ensemble.h"
#include "detModel/Sections/PosXYZ.h"
#include "detModel/Sections/Stack.h"
#include "detModel/Sections/AxisMPos.h"
#include "detModel/Sections/IdField.h"
#include "detModel/Sections/Position.h"


#include <cassert>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GeometryVisitor::GeometryVisitor( IGeometry& geom, std::string visitorMode )
: m_geom(geom)
{
    setRecursive(0);
    cacheTransform(); // set initial tranformation
    std::string mode = geom.getMode();
    if (mode.size() > 0) {  // use client-requested mode
      setMode(mode); 
    }
    else { // use GlastDetSvc default
      setMode(visitorMode);
    }
      
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  GeometryVisitor::visitEnsemble(detModel::Ensemble* ensemble)
{
    using namespace detModel;
    typedef std::vector<detModel::Position*> PosVector;
//    IGeometry::DoubleVector params;

    
    IGeometry::VolumeType type = IGeometry::Composite;
    std::string material;
    
    if ( Stack* stack = dynamic_cast<Stack*>(ensemble) ){
        switch (stack->getAxisDir()){
        case Stack::xDir : type = IGeometry::Xstack; break;
        case Stack::yDir : type = IGeometry::Ystack; break;
        case Stack::zDir : type = IGeometry::Zstack; break;
        }
        m_params.push_back(ensemble->getBBox()->getXDim());
        m_params.push_back(ensemble->getBBox()->getYDim());
        m_params.push_back(ensemble->getBBox()->getZDim());
    }else {
        detModel::Composition* comp = dynamic_cast<detModel::Composition*>(ensemble);
        assert( comp);
        detModel::Box* b = dynamic_cast<detModel::Box*>(comp->getEnvelope());
        assert(b);
        
        m_params.push_back(b->getX());
        m_params.push_back(b->getY());
        m_params.push_back(b->getZ());
        
        material = comp->getEnvelope()->getMaterial();
    }
    IGeometry::VisitorRet vret = 
      m_geom.pushShape(IGeometry::Box, m_idvec, ensemble->getName(), material,
                       m_params,  type);

    // Do these belong in the "if" or not?  Probably only really need
    // to be done inside, but are harmless outside.
    m_params.clear();
    m_idvec.clear();

    if (vret == IGeometry::More) {   // traverse subtree
      PosVector p = ensemble->getPositions();
      for(PosVector::iterator i=p.begin(); i!=p.end();i++)
        (*i)->AcceptNotRec(this);
    }
    
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  GeometryVisitor::visitBox(detModel::Box* b)
{
    //IGeometry::DoubleVector params;
  IGeometry::VolumeType type;
  m_params.push_back(b->getX());
  m_params.push_back(b->getY());
  m_params.push_back(b->getZ());
  if (b->getSensitive() == 0) type = IGeometry::Simple;
  else if (b->getSensitive() == 1) type = IGeometry::posSensitive;
  else type = IGeometry::intSensitive;
  // No possibility of subtree here so can ignore return
  IGeometry::VisitorRet vRet =
    m_geom.pushShape(IGeometry::Box, m_idvec, b->getName(), b->getMaterial(), 
                     m_params, type);
  m_params.clear();
  m_idvec.clear();

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  GeometryVisitor::visitTube(detModel::Tube* t)
{
  IGeometry::VolumeType type;
  m_params.push_back(t->getZ());
  m_params.push_back(t->getRin());
  m_params.push_back(t->getRout());
  if (t->getSensitive() == 0) type = IGeometry::Simple;
  else if (t->getSensitive() == 1) type = IGeometry::posSensitive;
  else type = IGeometry::intSensitive;
  // No possibility of subtree here so can ignore return
  IGeometry::VisitorRet vRet =
    m_geom.pushShape(IGeometry::Tube, m_idvec, t->getName(), t->getMaterial(),
                     m_params, type);
  m_params.clear();
  m_idvec.clear();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  GeometryVisitor::visitPosXYZ(detModel::PosXYZ* pos)
{
    using detModel::IdField;
    cacheTransform(pos->getX(), pos->getY(), pos->getZ(),
        pos->getXRot(), pos->getYRot(), pos->getZRot());
    IdVector ids = pos->getIdFields();
    
    for( IdVector::const_iterator i=ids.begin(); i !=ids.end(); ++i) {
        cacheId(*i,0);
    }
    
    pos->getVolume()->AcceptNotRec(this);
    m_geom.popShape();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  GeometryVisitor::visitAxisMPos(detModel::AxisMPos* pos)
{
    
    IdVector& ids = pos->getIdFields();
    // get the rotation angle
    double rot = pos->getRotation();
    
    for( unsigned int i = 0; i< pos->getNcopy(); ++i) {
        
        double disp = pos->getDisp(i),
            rx=0, ry=0, rz=0,
            x = pos->getDx(),
            y = pos->getDy(),
            z = pos->getDz();
        
        switch(pos->getAxisDir()){
        case (detModel::Stack::xDir): x+=disp; rx=rot;	break;
        case (detModel::Stack::yDir): y+=disp; ry=rot;	break;
        case (detModel::Stack::zDir): z+=disp; rz=rot;	break;
        }
        
        cacheTransform(x,y,z,rx,ry,rz);
        
        for( IdVector::iterator j= ids.begin(); j< ids.end(); ++j)
            cacheId(*j,i);
        
        pos->getVolume()->AcceptNotRec(this);
        
        m_geom.popShape();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void GeometryVisitor::cacheId(detModel::IdField* id, int step )
{
    //m_geom.id(id->getName(), id->getValue() + id->getStep()*step);
    m_idvec.push_back(id->getValue() + id->getStep()*step);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void GeometryVisitor::cacheTransform(double x, double y, double z, double rx, double ry, double rz)
{
    m_params.push_back(x);
    m_params.push_back(y);
    m_params.push_back(z);
    m_params.push_back(rx);
    m_params.push_back(ry);
    m_params.push_back(rz);
}
