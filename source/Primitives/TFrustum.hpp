///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TPlane.hpp"
#include "../Ranges/TRange.hpp"

namespace Langulus::Math
{

   ///                                                                        
   /// 2D/3D frustum, centered around origin                                  
   ///                                                                        
   template<CT::Vector T>
   struct TFrustum {
      LANGULUS(POD) true;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Primitive);

      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Can't have one-dimensional frustum");
      using PointType = T;
      using MatrixType = TMatrix<TypeOf<T>, MemberCount + 1>;

      TPlane<T> mPlanes[MemberCount * 2];

      enum {Left = 0, Right, Top, Bottom, Near, Far};

   public:
      TFrustum() noexcept;
      TFrustum(const MatrixType&) noexcept;

      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
      NOD() bool Intersects(const TRange<T>&) const noexcept;
   };

} // namespace Langulus::Math

#include "TFrustum.inl"