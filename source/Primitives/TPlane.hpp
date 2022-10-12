///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Primitive.hpp"

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated 2D/3D plane                                                
   ///                                                                        
   template<CT::Vector T>
   struct TPlane {
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS_BASES(A::Primitive);

      using PointType = T;
      using MemberType = typename T::MemberType;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Can't have one-dimensional plane");

      // Default orientation is always towards user                     
      T mNormal {Cardinal::Backward<MemberType>};

      // The offset of the plane, along the normal                      
      MemberType mOffset {0};

   public:
      constexpr TPlane() noexcept = default;
      constexpr TPlane(const T& normal, MemberType offset) noexcept;
      constexpr TPlane(const TVector<MemberType, MemberCount + 1>& column) noexcept;
      constexpr TPlane(const T& offset) noexcept;

      TPlane& Flip() noexcept;
      TPlane& Normalize() noexcept;

      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };

} // namespace Langulus::Math

#include "TPlane.inl"