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

      template<CT::Vector>
      struct TSphere;

      template<CT::Vector>
      struct TEllipsoid;

      using Circle     = TSphere<Vec2>;
      using Sphere     = TSphere<Vec3>;

      using Ellipsoid2 = TEllipsoid<Vec2>;
      using Ellipsoid3 = TEllipsoid<Vec3>;
      using Ellipsoid  = Ellipsoid3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract sphere                                                  
      struct Sphere : Primitive {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Sphere;
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing sphere primitives                        
      template<class...T>
      concept Sphere = (DerivedFrom<T, A::Sphere> and ...);

   } // namespace Langulus::CT


   /// Custom name generator at compile-time for boxes                        
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TSphere<T>>&&) noexcept {
      using CLASS = Math::TSphere<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      if constexpr (T::MemberCount > 3) {
         for (auto i : defaultClassName)
            name[offset++] = i;
         return name;
      }
      else if constexpr (T::MemberCount == 3) {
         for (auto i : "Sphere")
            name[offset++] = i;
      }
      else if constexpr (T::MemberCount == 2) {
         for (auto i : "Circle")
            name[offset++] = i;
      }

      // Write suffix                                                   
      for (auto i : SuffixOf<TypeOf<T>>())
         name[offset++] = i;
      return name;
   }

   /// Custom name generator at compile-time for rounded boxes                
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TEllipsoid<T>>&&) noexcept {
      using CLASS = Math::TEllipsoid<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      if constexpr (T::MemberCount > 3) {
         for (auto i : defaultClassName)
            name[offset++] = i;
         return name;
      }

      // Write prefix                                                   
      for (auto i : "Ellipsoid")
         name[offset++] = i;

      // Write size                                                     
      --offset;
      name[offset++] = '0' + T::MemberCount;

      // Write suffix                                                   
      for (auto i : SuffixOf<TypeOf<T>>())
         name[offset++] = i;
      return name;
   }

} // namespace Langulus

namespace Langulus::Math
{

   ///                                                                        
   /// 2D circle, or 3D sphere, centered around origin                        
   ///                                                                        
   template<CT::Vector T>
   struct TSphere {
      LANGULUS(NAME) CustomNameOf<TSphere>::Generate();
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Sphere);

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Roundness doesn't exist below two dimensions");

      TypeOf<T> mRadius {.5};

   public:
      /// Check if sphere is degenerate                                       
      ///   @return true if radius is zero                                    
      NOD() constexpr bool IsDegenerate() const noexcept {
         return mRadius == 0;
      }

      /// Check if sphere is hollow                                           
      ///   @return true if radius is negative                                
      NOD() constexpr bool IsHollow() const noexcept {
         return mRadius < 0;
      }

      /// Calculate signed distance                                           
      ///   @param point - point to check distance from                       
      ///   @return the distance to the primitive                             
      NOD() auto SignedDistance(const T& point) const {
         return point.Length() - mRadius;
      }
   };


   ///                                                                        
   /// 2D/3D ellipsoid, centered around origin                                
   ///                                                                        
   template<CT::Vector T>
   struct TEllipsoid {
   public:
      LANGULUS(NAME) CustomNameOf<TEllipsoid>::Generate();
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Sphere);

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Roundness doesn't exist below two dimensions");

      // A radius for each cardinal direction                           
      T mRadii {.5};

   public:
      /// Check if ellipsoid is degenerate                                    
      ///   @return true if any radius is zero                                
      NOD() constexpr bool IsDegenerate() const noexcept {
         return mRadii == 0;
      }

      /// Check if ellipsoid is hollow                                        
      ///   @return true if any radius is negative                            
      NOD() constexpr bool IsHollow() const noexcept {
         return mRadii < 0;
      }

      /// Calculate signed distance                                           
      ///   @param point - point to check distance from                       
      ///   @return the distance to the primitive                             
      NOD() auto SignedDistance(const T& point) const {
         const auto k0 = (point / mRadii).Length();
         const auto k1 = (point / (mRadii * mRadii)).Length();
         return k0 * (k0 - TypeOf<T> {1}) / k1;
      }
   };

} // namespace Langulus::Math

