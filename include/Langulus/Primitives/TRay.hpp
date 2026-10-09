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
   template<CT::CustomVector> struct TRay;

   using Ray2 = TRay<Vec2>;
   using Ray3 = TRay<Vec3>;

   /// An abstract ray                                                        
   struct Ray {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Ray3;
      using CTTI_Bases     = Math::Primitive;
   };

   ///                                                                        
   ///   A ray                                                                
   /// A line segment with a discrete starting point, but no ending point     
   ///                                                                        
   template<CT::CustomVector T>
   struct TRay {
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Nullable  = Maybe<CT::Nullable<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::Ray;

      using PointType  = T;
      using ScalarType = TypeOf<T>;
      static constexpr auto MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Rays don't exist below two dimensions");

      T mOrigin {};
      T mNormal {};

   public:
      constexpr TRay() = default;

      constexpr TRay(T const& position, T const& normal) noexcept
         : mOrigin {position}
         , mNormal {normal.Normalize()} {}

      /// Check if ray is degenerate                                          
      constexpr bool IsDegenerate() const noexcept {
         return mNormal.Length() == 0;
      }

      /// Get a point along the ray                                           
      constexpr T Point(ScalarType const& distance) const noexcept {
         return mOrigin + mNormal * distance;
      }

      /// Move the ray origin                                                 
      constexpr TRay& Step(ScalarType const& distance) noexcept {
         mOrigin += mNormal * distance;
         return *this;
      }

      constexpr TRay Stepped(ScalarType const& distance) const noexcept {
         TRay copy = *this;
         return copy.Step(distance);
      }

      /// Self-dot the ray                                                    
      constexpr auto Dot() const noexcept -> ScalarType {
         return Dot(mOrigin, mNormal);
      }
   };
}