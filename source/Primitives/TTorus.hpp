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

   ///                                                                        
   /// 3D torus                                                               
   ///                                                                        
   template<CT::Vector T, CT::Dimension D = Traits::Y>
   struct TTorus {
      LANGULUS(POD) true;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Primitive);

      using PointType = T;
      using T::MemberCount;
      static_assert(MemberCount == 3, "Can't have a non-three-dimensional torus");
      static_assert(D::Index < 3, "Can't extend torus in that dimension");

      TypeOf<T> mOuterRadius {.5};
      TypeOf<T> mInnerRadius {.5};

   public:
      /// Check if torus is degenerate                                        
      ///   @return true if at least one radius is zero                       
      NOD() constexpr bool IsDegenerate() const noexcept {
         return mInnerRadius == 0 || mOuterRadius == 0;
      }

      /// Check if torus is hollow                                            
      ///   @return true if at least one of the radii is negative             
      NOD() constexpr bool IsHollow() const noexcept {
         return mInnerRadius * mOuterRadius < 0;
      }

      /// Calculate signed distance                                           
      ///   @param point - point to check distance from                       
      ///   @return the distance to the primitive                             
      NOD() auto SignedDistance(const T& point) const {
         if constexpr (CT::Same<D, Traits::X>) {
            const auto q = TVector<TypeOf<T>, 2>(point.yz().Length() - mOuterRadius, point[0]);
            return q.Length() - mInnerRadius;
         }
         else if constexpr (CT::Same<D, Traits::Y>) {
            const auto q = TVector<TypeOf<T>, 2>(point.xz().Length() - mOuterRadius, point[1]);
            return q.Length() - mInnerRadius;
         }
         else if constexpr (CT::Same<D, Traits::Z>) {
            const auto q = TVector<TypeOf<T>, 2>(point.xy().Length() - mOuterRadius, point[2]);
            return q.Length() - mInnerRadius;
         }
         else static_assert(false, "Unsupported dimension");
      }
   };

} // namespace Langulus::Math

