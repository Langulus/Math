///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../../source/Primitives/TBox.hpp"
#include "../../source/Primitives/TCone.hpp"
#include "../../source/Primitives/TCylinder.hpp"
#include "../../source/Primitives/TFrustum.hpp"
#include "../../source/Primitives/TLine.hpp"
#include "../../source/Primitives/TPlane.hpp"
#include "../../source/Primitives/TPoint.hpp"
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
             
      (void) MetaOf<Point1>();
      (void) MetaOf<Point2>();
      (void) MetaOf<Point3>();
             
      (void) MetaOf<Polygon2>();
      (void) MetaOf<Polygon3>();
             
      (void) MetaOf<Ray2>();
      (void) MetaOf<Ray3>();
             
      (void) MetaOf<Triangle2>();
      (void) MetaOf<Triangle3>();
      (void) MetaOf<TriangleStrip2>();
      (void) MetaOf<TriangleStrip3>();
      (void) MetaOf<TriangleFan2>();
      (void) MetaOf<TriangleFan3>();
   }

} // namespace Langulus::Math