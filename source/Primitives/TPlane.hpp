///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Primitive.hpp"
#include "../Vectors/TVector.inl"


namespace Langulus::Math
{

   ///                                                                        
   ///   Templated 2D/3D plane                                                
   ///                                                                        
   template<CT::Vector T>
   struct TPlane {
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Primitive);

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Can't have one-dimensional plane");

      // Default orientation is always towards user                     
      T mNormal {Axes::Backward<TypeOf<T>>};

      // The offset of the plane, along the normal                      
      TypeOf<T> mOffset {0};

   public:
      constexpr TPlane() noexcept = default;
      constexpr TPlane(const T& normal, TypeOf<T> offset) noexcept;
      constexpr TPlane(const TVector<TypeOf<T>, MemberCount + 1>& column) noexcept;
      constexpr TPlane(const T& offset) noexcept;

      TPlane& Flip() noexcept;
      TPlane& Normalize() noexcept;

      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };

} // namespace Langulus::Math