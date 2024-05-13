///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Primitives/TCylinder.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{

   /// Signed distance function for a centered 3D cylinder                    
   template<CT::Number T, CT::Dimension D>
   T SignedDistance(const TVector<T, 3>& point, const TCylinderCapped<TVector<T, 3>, D>& cylinder) {
      using V2 = TVector<T, 2>;

      if constexpr (CT::Same<D, Traits::X>) {
         const V2 d =
            V2 {Length(point.yz()), Abs(point.x())} -
            V2 {cylinder.mRadius, cylinder.mHeight};
         return Length(d.Max(0)) + Min(Max(d[0], d[1]), T {0});
      }
      else if constexpr (CT::Same<D, Traits::Y>) {
         const V2 d =
            V2 {Length(point.xz()), Abs(point.y())} -
            V2 {cylinder.mRadius, cylinder.mHeight};
         return Length(d.Max(0)) + Min(Max(d[0], d[1]), T {0});
      }
      else {
         const V2 d =
            V2 {Length(point.xy()), Abs(point.z)} -
            V2 {cylinder.mRadius, cylinder.mHeight};
         return Length(d.Max(0)) + Min(Max(d[0], d[1]), T {0});
      }
   };

} // namespace Langulus::Math
