///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Primitives/TTorus.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{
   /// Calculate signed distance to a torus                                   
   ///   @param point point to check distance from                            
   ///   @return the distance to the primitive                                
   template<CT::CustomVector T, CT::Dimension D>
   auto SignedDistance(T const& point, TTorus<T, D> const& torus) -> TypeOf<T> {
      using Inner = TypeOf<T>;
      if constexpr (Same<D, Tags::X>) {
         const auto q = TVector<Inner, 2>(point.yz().Length() - torus.mOuterRadius, point[0]);
         return q.Length() - torus.mInnerRadius;
      }
      else if constexpr (Same<D, Tags::Y>) {
         const auto q = TVector<Inner, 2>(point.xz().Length() - torus.mOuterRadius, point[1]);
         return q.Length() - torus.mInnerRadius;
      }
      else if constexpr (Same<D, Tags::Z>) {
         const auto q = TVector<Inner, 2>(point.xy().Length() - torus.mOuterRadius, point[2]);
         return q.Length() - torus.mInnerRadius;
      }
      else static_assert(false, "Unsupported dimension");
   }
}
