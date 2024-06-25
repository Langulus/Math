///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../../source/Primitives/TBox.inl"
#include "../../source/Primitives/TCone.inl"
#include "../../source/Primitives/TCylinder.inl"
#include "../../source/Primitives/TFrustum.inl"
#include "../../source/Primitives/TLine.inl"
#include "../../source/Primitives/TPlane.inl"
#include "../../source/Primitives/TPolygon.hpp"
#include "../../source/Primitives/TRay.hpp"
#include "../../source/Primitives/TSphere.hpp"
#include "../../source/Primitives/TTriangle.hpp"
#include "../../source/Primitives/TTorus.hpp"


namespace Langulus::Math
{

   /// Register primitives                                                    
   inline void RegisterPrimitives() {
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