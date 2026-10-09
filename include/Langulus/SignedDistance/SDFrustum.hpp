///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Primitives/TFrustum.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{
   /// Calculate signed distance of a frustum                                 
   ///   @param point point to check distance from                            
   ///   @param frusta the frusta                                             
   ///   @return the distance to the primitive                                
   template<CT::CustomVector T>
   auto SignedDistance(T const& point, const TFrustum<T>& frusta) -> TypeOf<T> {
      return Min(
         frusta.mPlanes[0].SignedDistance(point),
         frusta.mPlanes[1].SignedDistance(point),
         frusta.mPlanes[2].SignedDistance(point),
         frusta.mPlanes[3].SignedDistance(point),
         frusta.mPlanes[4].SignedDistance(point),
         frusta.mPlanes[5].SignedDistance(point)
      );
   }
}
