///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Primitives/TPlane.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{

   /// Signed distance function for a 2D/3D plane                             
   template<CT::Number T, Count C>
   T SignedDistance(const TVector<T, C>& point, const TPlane<TVector<T, C>>& plane) {
      return Dot(point, plane.mNormal) + plane.mOffset;
   };

} // namespace Langulus::Math
