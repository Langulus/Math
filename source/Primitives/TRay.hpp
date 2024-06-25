///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"


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
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Ray;
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
         LANGULUS(POD) CT::POD<T>;
         LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(A::Ray);

         using PointType = T;
         static constexpr auto MemberCount = T::MemberCount;
         static_assert(MemberCount > 1, "Rays don't exist below two dimensions");

         T mOrigin {};
         T mNormal {};

      public:
         constexpr TRay() = default;

         constexpr TRay(const T& position, const T& normal) noexcept
            : mOrigin {position}
            , mNormal {normal.Normalize()} {}

         /// Check if ray is degenerate                                       
         NOD() constexpr bool IsDegenerate() const noexcept {
            return mNormal.Length() == 0;
         }

         /// Get a point along the ray                                        
         NOD() constexpr T Point(const TypeOf<T>& distance) const noexcept {
            return mOrigin + mNormal * distance;
         }

         /// Move the ray origin                                              
         NOD() constexpr TRay& Step(const TypeOf<T>& distance) noexcept {
            mOrigin += mNormal * distance;
            return *this;
         }

         NOD() constexpr TRay Stepped(const TypeOf<T>& distance) const noexcept {
            TRay copy = *this;
            return copy.Step(distance);
         }

         /// Self-dot the ray                                                 
         NOD() constexpr TypeOf<T> Dot() const noexcept {
            return Dot(mOrigin, mNormal);
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus