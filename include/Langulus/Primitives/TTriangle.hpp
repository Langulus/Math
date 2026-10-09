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
   struct TTriangle;

   using Triangle2      = TTriangle<Vec2>;
   using Triangle3      = TTriangle<Vec3>;
   using Triangle4      = TTriangle<Vec4>;

   template<CT::CustomVector>
   struct TTriangleStrip;

   using TriangleStrip2 = TTriangleStrip<Vec2>;
   using TriangleStrip3 = TTriangleStrip<Vec3>;
   using TriangleStrip4 = TTriangleStrip<Vec4>;

   template<CT::CustomVector>
   struct TTriangleFan;

   using TriangleFan2   = TTriangleFan<Vec2>;
   using TriangleFan3   = TTriangleFan<Vec3>;
   using TriangleFan4   = TTriangleFan<Vec4>;


   /// An abstract triangle, also used as a topology type                     
   struct Triangle : Topology {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Triangle3;
      using CTTI_Bases     = Math::Topology;
   };

   /// An abstract triangle strip, also used as a topology type               
   struct TriangleStrip : Triangle {
      using CTTI_Concrete  = Math::TriangleStrip3;
      using CTTI_Bases     = Math::Triangle;
   };

   /// An abstract triangle fan, also used as a topology type                 
   struct TriangleFan : Triangle {
      using CTTI_Concrete  = Math::TriangleFan3;
      using CTTI_Bases     = Math::Triangle;
   };
}

namespace Langulus::CT
{
   /// Concept for distinguishing triangle primitives                         
   template<class...T>
   concept Triangle = (DerivedFrom<T, Math::Triangle> and ...);

   /// Concept for distinguishing triangle strip topologies                   
   template<class...T>
   concept TriangleStrip = (DerivedFrom<T, Math::TriangleStrip> and ...);

   /// Concept for distinguishing triangle fan topologies                     
   template<class...T>
   concept TriangleFan = (DerivedFrom<T, Math::TriangleFan> and ...);
}

namespace Langulus::Math
{
   ///                                                                        
   ///   A templated triangle                                                 
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::CustomVector T>
   struct TTriangle : Math::Triangle {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TTriangle>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "Tri")
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
      using CTTI_Nullable  = Maybe<CT::Nullable<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::Triangle;

      using PointType  = T;
      using ScalarType = TypeOf<T>;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Triangles don't exist below two dimensions");

      T mABC[3] {};

   public:
      constexpr TTriangle() = default;

      /// Manual construction                                                 
      template<CT::Vector ALT_T = T>
      constexpr TTriangle(const ALT_T& p1, const ALT_T& p2, const ALT_T& p3) noexcept
         : mABC {p1, p2, p3} {}

      /// Manual construction from three points of any type                   
      template<CT::CustomVector ALT_T = T>
      constexpr TTriangle(const ALT_T* points) noexcept
         : mABC {points[0], points[1], points[2]} {}

      /// Manual construction from dense memory of any type, indexed          
      ///   @param points pointer to the point array                          
      ///   @param indices three indices for the points array                 
      template<CT::CustomVector ALT_T = T, CT::Integer IDX>
      constexpr TTriangle(const ALT_T* points, const IDX(&indices)[3]) noexcept
         : mABC {points[indices[0]], points[indices[1]], points[indices[2]]} {}

      /// Check if triangle is degenerate                                     
      ///   @return true if any of the points overlap                         
      constexpr bool IsDegenerate() const noexcept {
         return mABC[0] == mABC[1]
             or mABC[0] == mABC[2]
             or mABC[1] == mABC[2];
      }

      /// Subdivide triangle                                                  
      ///   @return the four new triangles                                    
      auto Subdivide() const noexcept -> ::std::array<TTriangle, 4> {
         constexpr ScalarType two {2};
         const T m01 = mABC[0] + (mABC[1] - mABC[0]) / two;
         const T m12 = mABC[1] + (mABC[2] - mABC[1]) / two;
         const T m20 = mABC[2] + (mABC[0] - mABC[2]) / two;
         return {
            {mABC[0],     m01,     m20}, 
            {    m01, mABC[1],     m12}, 
            {    m20,     m12, mABC[2]}, 
            {    m01,     m12,     m20}
         };
      }

      ///   Access points                                                     
      auto& operator [] (size_t index) const noexcept {
         return mABC[index];
      }
      auto& operator [] (size_t index) noexcept {
         return mABC[index];
      }

      /// Convert to other kinds of triangles                                 
      template<CT::CustomVector ALT>
      explicit operator TTriangle<ALT>() const noexcept {
         return { static_cast<ALT>(mABC[0]),
                  static_cast<ALT>(mABC[1]),
                  static_cast<ALT>(mABC[2])  };
      }

      /// Modify the triangle                                                 
      TTriangle operator + (T const& rhs) const noexcept {
         return {mABC[0] + rhs, mABC[1] + rhs, mABC[2] + rhs};
      }
      TTriangle operator - (T const& rhs) const noexcept {
         return {mABC[0] - rhs, mABC[1] - rhs, mABC[2] - rhs};
      }
      TTriangle operator * (T const& rhs) const noexcept {
         return {mABC[0] * rhs, mABC[1] * rhs, mABC[2] * rhs};
      }
      TTriangle operator / (T const& rhs) const {
         return {mABC[0] / rhs, mABC[1] / rhs, mABC[2] / rhs};
      }
   };
   #pragma pack(pop)


   ///                                                                        
   ///   A templated triangle strip                                           
   /// List of points, forming triangles, by always sharing the last two      
   /// points in the sequence                                                 
   ///                                                                        
   ///      1________3_______ 5     Notice all triangles are clockwise        
   ///      /\      /\      /       0,1,2 - first triangle                    
   ///     /  \    /  \    /        2,1,3 - second triangle                   
   ///    /    \  /    \  /         2,3,4 - third triangle                    
   ///   /______\/______\/          4,3,5 - fourth triangle                   
   ///  0        2        4                                                   
   ///                                                                        
   template<CT::CustomVector T>
   struct TTriangleStrip : Math::TriangleStrip {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TTriangleStrip>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "TriStrip")
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
      using CTTI_Named = Yes<GenerateToken()>;
      using CTTI_Typed = TypeOf<T>;
      using CTTI_Bases = Math::TriangleStrip;

      Annies::TMany<T> mPoints;

      using PointType = T;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Triangles don't exist below two dimensions");
   };


   ///                                                                        
   ///   A templated triangle fan                                             
   /// List of points, forming triangles, by always sharing the first and     
   /// last points in the sequence                                            
   ///                                                                        
   ///      2________3             Notice all triangles are clockwise         
   ///      /\      /\             0,1,2 - first triangle                     
   ///     /  \    /  \            0,2,3 - second triangle                    
   ///    /    \  /    \           0,3,4 - third triangle                     
   ///   /______\/______\          0,4,5 - fourth triangle                    
   ///  1       0\      /4                                                    
   ///            \    /                                                      
   ///             \  /                                                       
   ///              \/                                                        
   ///               5                                                        
   ///                                                                        
   template<CT::CustomVector T>
   struct TTriangleFan : Math::TriangleFan {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TTriangleFan>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "TriFan")
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
      using CTTI_Named = Yes<GenerateToken()>;;
      using CTTI_Typed = TypeOf<T>;
      using CTTI_Bases = Math::TriangleFan;

      Annies::TMany<T> mPoints;

      using PointType = T;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Triangles don't exist below two dimensions");
   };
}

