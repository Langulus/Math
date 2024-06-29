///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "TBox.inl"
#include "TCone.inl"
#include "TCylinder.inl"
#include "TFrustum.inl"
#include "TLine.inl"
#include "TPlane.inl"
#include "TPolygon.hpp"
#include "TRay.hpp"
#include "TSphere.hpp"
#include "TTriangle.hpp"
#include "TTorus.hpp"


namespace Langulus::Math
{

   /// Register primitives                                                    
   void RegisterPrimitives() {
      (void) MetaOf<Box2>();
      (void) MetaOf<Box3>();
      (void) MetaOf<BoxRounded2>();
      (void) MetaOf<BoxRounded3>();
             
      (void) MetaOf<Cylinder3>();
      (void) MetaOf<CylinderCapped3>();
             
      (void) MetaOf<Frustum2>();
      (void) MetaOf<Frustum3>();
             
      (void) MetaOf<Line2>();
      (void) MetaOf<Line3>();
      (void) MetaOf<LineLoop2>();
      (void) MetaOf<LineLoop3>();
      (void) MetaOf<LineStrip2>();
      (void) MetaOf<LineStrip3>();
             
      (void) MetaOf<Vec1>();
      (void) MetaOf<Vec2>();
      (void) MetaOf<Vec3>();
      (void) MetaOf<Vec4>();
             
      (void) MetaOf<Polygon2>();
      (void) MetaOf<Polygon3>();
             
      (void) MetaOf<Ray2>();
      (void) MetaOf<Ray3>();
             
      (void) MetaOf<Triangle2>();
      (void) MetaOf<Triangle3>();
      (void) MetaOf<Triangle4>();
      (void) MetaOf<TriangleStrip2>();
      (void) MetaOf<TriangleStrip3>();
      (void) MetaOf<TriangleStrip4>();
      (void) MetaOf<TriangleFan2>();
      (void) MetaOf<TriangleFan3>();
      (void) MetaOf<TriangleFan4>();
   }

} // namespace Langulus::Math