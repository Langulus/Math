///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Primitives/TLine.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{
   /// Calculate signed distance                                           
   ///   @param point the point from which distance is calculated          
   ///   @param line the line                                              
   ///   @return the distance                                              
   template<CT::CustomVector T>
   auto SignedDistance(T const& point, TLine<T> const& line) -> TypeOf<T> {
      const auto pa = point - line.mAB[0];
      const auto ba = line.mAB[1] - line.mAB[0];
      const auto h = Saturate(Dot(pa, ba) / Dot2(ba));
      return Math::Length(pa - ba * h);
   }
}
