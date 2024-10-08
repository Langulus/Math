///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Primitives/TCone.hpp"


/// The following code follows specific guidelines, so it is used in C++, as  
/// well as used as a basis for generating GLSL/HLSL equivalent functions     
///TODO refer to guidelines
namespace Langulus::Math
{

   /// Signed distance function for a centered 3D cone                        
   template<CT::Number T, CT::Dimension D>
   T SignedDistance(const TVector<T, 3>& point, const TCone<TVector<T, 3>, D>& cone) {
      if constexpr (CT::Same<D, Traits::X>) {
         const T q = Length(point.yz());
         const TVector<T, 2> c {Sin(cone.mAngle), Cos(cone.mAngle)};
         return Max(Dot(c, TVector<T, 2>(q, point.x())), -cone.mHeight - point.x());
      }
      else if constexpr (CT::Same<D, Traits::Y>) {
         const T q = Length(point.xz());
         const TVector<T, 2> c {Sin(cone.mAngle), Cos(cone.mAngle)};
         return Max(Dot(c, TVector<T, 2>(q, point.y())), -cone.mHeight - point.y());
      }
      else {
         const T q = Length(point.xy());
         const TVector<T, 2> c {Sin(cone.mAngle), Cos(cone.mAngle)};
         return Max(Dot(c, TVector<T, 2>(q, point.z())), -cone.mHeight - point.z());
      }
   };

} // namespace Langulus::Math
