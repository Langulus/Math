///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Primitive.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::Vector> struct TRay;

      using Ray2 = TRay<Vec2>;
      using Ray3 = TRay<Vec3>;
      using Ray  = Ray3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract ray                                                     
      struct Ray {
         using CTTI_Abstract = Yup;
         using CTTI_Concrete = Math::Ray;
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace Math
   {

      ///                                                                     
      ///   A ray                                                             
      /// A line segment with a discrete starting point, but no ending point  
      ///                                                                     
      template<CT::Vector T>
      struct TRay {
         using CTTI_POD = CT::POD<T>;
         using CTTI_Nullable = CT::Nullifiable<T>;
         using CTTI_Typed = TypeOf<T>;
         LANGULUS_BASES(A::Ray);

         using PointType = T;
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
         constexpr T Point(const TypeOf<T>& distance) const noexcept {
            return mOrigin + mNormal * distance;
         }

         /// Move the ray origin                                              
         constexpr TRay& Step(const TypeOf<T>& distance) noexcept {
            mOrigin += mNormal * distance;
            return *this;
         }

         constexpr TRay Stepped(const TypeOf<T>& distance) const noexcept {
            TRay copy = *this;
            return copy.Step(distance);
         }

         /// Self-dot the ray                                                 
         constexpr TypeOf<T> Dot() const noexcept {
            return Dot(mOrigin, mNormal);
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus