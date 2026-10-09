///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Primitives/TSphere.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{
   /// Calculate signed distance to a sphere                                  
   ///   @param point point to check distance from                            
   ///   @return the distance to the primitive                                
   template<CT::CustomVector T>
   auto SignedDistance(T const& point, TSphere<T> const& sphere) -> TypeOf<T> {
      const auto k0 = (point / sphere.mRadii).Length();
      const auto k1 = (point / (sphere.mRadii * sphere.mRadii)).Length();
      return k0 * (k0 - TypeOf<T> {1}) / k1;
   }
}
