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
   template<CT::CustomVector>
   struct TSphere;

   using Sphere2    = TSphere<Vec2>;
   using Sphere3    = TSphere<Vec3>;

   template<CT::CustomVector>
   struct TEllipsoid;

   using Ellipsoid2 = TEllipsoid<Vec2>;
   using Ellipsoid3 = TEllipsoid<Vec3>;

   /// An abstract sphere                                                     
   struct Sphere : Primitive {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Sphere3;
      using CTTI_Bases     = Math::Primitive;
   };
}

namespace Langulus::CT
{
   /// Concept for distinguishing sphere primitives                           
   template<class...T>
   concept Sphere = (DerivedFrom<T, Math::Sphere> and ...);
}

namespace Langulus::Math
{
   ///                                                                        
   /// 2D circle, or 3D sphere, centered around origin                        
   ///                                                                        
   template<CT::CustomVector T>
   struct TSphere {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TSphere>();
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

   public:
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Abstract  = No;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::Sphere;

      using PointType  = T;
      using ScalarType = TypeOf<T>;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Roundness doesn't exist below two dimensions");

      ScalarType mRadius {.5};

   public:
      /// Check if sphere is degenerate                                       
      ///   @return true if radius is zero                                    
      constexpr bool IsDegenerate() const noexcept {
         return mRadius == 0;
      }

      /// Check if sphere is hollow                                           
      ///   @return true if radius is negative                                
      constexpr bool IsHollow() const noexcept {
         return mRadius < 0;
      }

      /// Calculate signed distance                                           
      ///   @param point - point to check distance from                       
      ///   @return the distance to the primitive                             
      auto SignedDistance(T const& point) const {
         return point.Length() - mRadius;
      }
   };


   ///                                                                        
   /// 2D/3D ellipsoid, centered around origin                                
   ///                                                                        
   template<CT::CustomVector T>
   struct TEllipsoid {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TEllipsoid>();
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

   public:
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Abstract  = No;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::Sphere;

      using PointType  = T;
      using ScalarType = TypeOf<T>;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Roundness doesn't exist below two dimensions");

      // A radius for each cardinal direction                           
      T mRadii {.5};

   public:
      /// Check if ellipsoid is degenerate                                    
      ///   @return true if any radius is zero                                
      constexpr bool IsDegenerate() const noexcept {
         return mRadii == 0;
      }

      /// Check if ellipsoid is hollow                                        
      ///   @return true if any radius is negative                            
      constexpr bool IsHollow() const noexcept {
         return mRadii < 0;
      }
   };
}

