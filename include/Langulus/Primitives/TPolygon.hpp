///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Primitive.hpp"


namespace Langulus::Math
{
   template<CT::CustomVector T> requires (ExtentOf<T> > 1)
   struct TPolygon;

   using Polygon2 = TPolygon<Vec2>;
   using Polygon3 = TPolygon<Vec3>;

   /// An abstract polygon, also used as a topology type                      
   struct Polygon {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Polygon3;
      using CTTI_Bases     = Math::Topology;
   };

   ///                                                                        
   ///   A templated polygon                                                  
   ///                                                                        
   /// A list of coplanar points that form a surface with a complex edge      
   ///                                                                        
   template<CT::CustomVector T> requires (ExtentOf<T> > 1)
   struct TPolygon : Annies::TMany<T> {
      using CTTI_ReflectAs = TPolygon;
      using CTTI_Deep      = No;
      using CTTI_Bases     = Math::Polygon;

      using Base           = Annies::TMany<T>;
      using PointType      = T;
      using Base::operator ==;
   };
}
