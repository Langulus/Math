///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Primitives/TTriangle.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{
   /// Calculate signed distance to a triangle                                
   ///   @param point the point from which distance is calculated             
   ///   @return the distance                                                 
   template<CT::CustomVector T>
   auto SignedDistance(T const& point, TTriangle<T> const& triangle) -> TypeOf<T> {
      const auto e0 = triangle.mABC[1] - triangle.mABC[0];
      const auto e1 = triangle.mABC[2] - triangle.mABC[1];
      const auto e2 = triangle.mABC[0] - triangle.mABC[2];
      const auto v0 =            point - triangle.mABC[0];
      const auto v1 =            point - triangle.mABC[1];
      const auto v2 =            point - triangle.mABC[2];

      if constexpr (triangle.MemberCount < 3) {
         // 2D signed distance field                                    
         const auto pq0 = v0 - e0 * Saturate(v0.Dot(e0) / Dot2(e0));
         const auto pq1 = v1 - e1 * Saturate(v1.Dot(e1) / Dot2(e1));
         const auto pq2 = v2 - e2 * Saturate(v2.Dot(e2) / Dot2(e2));
         const auto s = Sign(e0[0] * e2[1] - e0[1] * e2[0]);

         const T d = Min(
            T(Dot2(pq0), s * (v0[0] * e0[1] - v0[1] * e0[0])),
            T(Dot2(pq1), s * (v1[0] * e1[1] - v1[1] * e1[0])),
            T(Dot2(pq2), s * (v2[0] * e2[1] - v2[1] * e2[0]))
         );

         return -Sqrt(d[0]) * Sign(d[1]);
      }
      else {
         // 3D signed distance field                                    
         const auto nor = e0.Cross(e2);
         return Sqrt((
               Sign(e0.Cross(nor).Dot(v0)) +
               Sign(e1.Cross(nor).Dot(v1)) +
               Sign(e2.Cross(nor).Dot(v2)) < Real {2})
            ? Min(
               Dot2(e0 * Saturate(e0.Dot(v0) / Dot2(e0)) - v0),
               Dot2(e1 * Saturate(e1.Dot(v1) / Dot2(e1)) - v1),
               Dot2(e2 * Saturate(e2.Dot(v2) / Dot2(e2)) - v2))
            : Sq(nor.Dot(v0)) / Dot2(nor)
         );
      }
   }
}
