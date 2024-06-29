///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Primitives/TBox.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{

   /// Signed distance function for a centered 2D/3D box                      
   template<CT::Number T, Count C>
   T SignedDistance(const TVector<T, C>& point, const TBox<TVector<T, C>>& box) {
      const TVector<T, C> d = Abs(point) - box.mOffsets;
      if constexpr (C == 3)
         return Length(Max(d, T {0})) + Min(Max(d.x(), Max(d.y(), d.z())), T {0});
      else if constexpr (C == 2)
         return Length(Max(d, T {0})) + Min(Max(d.x(), d.y()), T {0});
      else
         LANGULUS_ERROR("Unsupported box dimensions");
   };

} // namespace Langulus::Math
