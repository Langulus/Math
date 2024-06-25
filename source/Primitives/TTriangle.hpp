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

      template<CT::Vector>
      struct TTriangle;

      template<CT::Vector>
      struct TTriangleStrip;

      template<CT::Vector>
      struct TTriangleFan;

      using Triangle2      = TTriangle<Vec2>;
      using Triangle3      = TTriangle<Vec3>;
      using Triangle4      = TTriangle<Vec4>;

      using TriangleStrip2 = TTriangleStrip<Vec2>;
      using TriangleStrip3 = TTriangleStrip<Vec3>;
      using TriangleStrip4 = TTriangleStrip<Vec4>;

      using TriangleFan2   = TTriangleFan<Vec2>;
      using TriangleFan3   = TTriangleFan<Vec3>;
      using TriangleFan4   = TTriangleFan<Vec4>;

      using Triangle       = Triangle3;
      using TriangleStrip  = TriangleStrip3;
      using TriangleFan    = TriangleFan3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract triangle, also used as a topology type                  
      struct Triangle : Topology {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Triangle;
         LANGULUS_BASES(Topology);
      };

      /// An abstract triangle strip, also used as a topology type            
      struct TriangleStrip : Triangle {
         LANGULUS(CONCRETE) Math::TriangleStrip;
         LANGULUS_BASES(Triangle);
      };

      /// An abstract triangle fan, also used as a topology type              
      struct TriangleFan : Triangle {
         LANGULUS(CONCRETE) Math::TriangleFan;
         LANGULUS_BASES(Triangle);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing triangle primitives                      
      template<class...T>
      concept Triangle = (DerivedFrom<T, A::Triangle> and ...);

      /// Concept for distinguishing triangle strip topologies                
      template<class...T>
      concept TriangleStrip = (DerivedFrom<T, A::TriangleStrip> and ...);

      /// Concept for distinguishing triangle fan topologies                  
      template<class...T>
      concept TriangleFan = (DerivedFrom<T, A::TriangleFan> and ...);

   } // namespace Langulus::CT
   
   /// Custom name generator at compile-time for triangles                    
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TTriangle<T>>&&) noexcept {
      using CLASS = Math::TTriangle<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
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
   
   /// Custom name generator at compile-time for triangle strips              
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TTriangleStrip<T>>&&) noexcept {
      using CLASS = Math::TTriangleStrip<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
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
   
   /// Custom name generator at compile-time for triangle fans                
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TTriangleFan<T>>&&) noexcept {
      using CLASS = Math::TTriangleFan<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
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

} // namespace Langulus

namespace Langulus::Math
{

   ///                                                                        
   ///   A templated triangle                                                 
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::Vector T>
   struct TTriangle : A::Triangle {
      LANGULUS(NAME) CustomNameOf<TTriangle>::Generate();
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Triangle);

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1,
         "Triangles don't exist below two dimensions");

      T mABC[3] {};

   public:
      constexpr TTriangle() = default;

      /// Manual construction                                                 
      ///   @param p1 - first point                                           
      ///   @param p2 - second point                                          
      ///   @param p3 - third point                                           
      template<CT::Vector ALT_T = T>
      constexpr TTriangle(const ALT_T& p1, const ALT_T& p2, const ALT_T& p3) noexcept
         : mABC {p1, p2, p3} {}

      /// Manual construction from three points of any type                   
      ///   @param points - pointer to the three points                       
      template<CT::Vector ALT_T = T>
      constexpr TTriangle(const ALT_T* points) noexcept
         : mABC {points[0], points[1], points[2]} {}

      /// Manual construction from dense memory of any type, indexed          
      ///   @param points - pointer to the point array                        
      ///   @param indices - three indices for the points array               
      template<CT::Vector ALT_T = T, CT::Integer IDX>
      constexpr TTriangle(const ALT_T* points, const IDX(&indices)[3]) noexcept
         : mABC {points[indices[0]], points[indices[1]], points[indices[2]]} {}

      /// Check if triangle is degenerate                                     
      ///   @return true if any of the points overlap                         
      NOD() constexpr bool IsDegenerate() const noexcept {
         return mABC[0] == mABC[1]
             or mABC[0] == mABC[2]
             or mABC[1] == mABC[2];
      }

      /// Subdivide triangle                                                  
      ///   @return the four new triangles                                    
      NOD() ::std::array<TTriangle, 4> Subdivide() const noexcept {
         constexpr TypeOf<T> two {2};
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

      /// Calculate signed distance                                           
      ///   @param point - the point from which distance is calculated        
      ///   @return the distance                                              
      NOD() auto SignedDistance(const T& point) const {
         const auto e0 = mABC[1] - mABC[0];
         const auto e1 = mABC[2] - mABC[1];
         const auto e2 = mABC[0] - mABC[2];
         const auto v0 =   point - mABC[0];
         const auto v1 =   point - mABC[1];
         const auto v2 =   point - mABC[2];

         if constexpr (MemberCount < 3) {
            // 2D signed distance field                                 
            const auto pq0 = v0 - e0 * Saturate(v0.Dot(e0) / Dot2(e0));
            const auto pq1 = v1 - e1 * Saturate(v1.Dot(e1) / Dot2(e1));
            const auto pq2 = v2 - e2 * Saturate(v2.Dot(e2) / Dot2(e2));
            const auto s = Sign(e0[0] * e2[1] - e0[1] * e2[0]);

            const T d = Min(
               T(Dot2(pq0), s * (v0[0] * e0[1] - v0[1] * e0[0])),
               T(Dot2(pq1), s * (v1[0] * e1[1] - v1[1] * e1[0])),
               T(Dot2(pq2), s * (v2[0] * e2[1] - v2[1] * e2[0]))
            );

            return -Sqrt(d[0]) * Sign(d[1]);
         }
         else {
            // 3D signed distance field                                 
            const auto nor = e0.Cross(e2);
            return Sqrt((
                  Sign(e0.Cross(nor).Dot(v0)) +
                  Sign(e1.Cross(nor).Dot(v1)) +
                  Sign(e2.Cross(nor).Dot(v2)) < Real {2})
               ? Min(
                  Dot2(e0 * Saturate(e0.Dot(v0) / Dot2(e0)) - v0),
                  Dot2(e1 * Saturate(e1.Dot(v1) / Dot2(e1)) - v1),
                  Dot2(e2 * Saturate(e2.Dot(v2) / Dot2(e2)) - v2))
               : Sq(nor.Dot(v0)) / Dot2(nor)
            );
         }
      }

      ///   Access points                                                     
      NOD() auto& operator [] (Offset index) const noexcept {
         return mABC[index];
      }
      NOD() auto& operator [] (Offset index) noexcept {
         return mABC[index];
      }

      /// Convert to other kinds of triangles                                 
      template<CT::Vector ALT>
      NOD() explicit operator TTriangle<ALT>() const noexcept {
         return { 
            static_cast<ALT>(mABC[0]),
            static_cast<ALT>(mABC[1]),
            static_cast<ALT>(mABC[2])
         };
      }

      /// Modify the triangle                                                 
      TTriangle operator + (const T& rhs) const noexcept {
         return {mABC[0] + rhs, mABC[1] + rhs, mABC[2] + rhs};
      }
      TTriangle operator - (const T& rhs) const noexcept {
         return {mABC[0] - rhs, mABC[1] - rhs, mABC[2] - rhs};
      }
      TTriangle operator * (const T& rhs) const noexcept {
         return {mABC[0] * rhs, mABC[1] * rhs, mABC[2] * rhs};
      }
      TTriangle operator / (const T& rhs) const {
         return {mABC[0] / rhs, mABC[1] / rhs, mABC[2] / rhs};
      }
   };
   #pragma pack(pop)


   ///                                                                        
   ///   A templated triangle strip                                           
   /// List of points, forming triangles, by always sharing the last two      
   /// points in the sequence                                                 
   ///                                                                        
   ///      1________3_______ 5     Notice all trianlges are clockwise        
   ///      /\      /\      /       0,1,2 - first triangle                    
   ///     /  \    /  \    /        2,1,3 - second triangle                   
   ///    /    \  /    \  /         2,3,4 - third triangle                    
   ///   /______\/______\/          4,3,5 - fourth triangle                   
   ///  0        2        4                                                   
   ///                                                                        
   template<CT::Vector T>
   struct TTriangleStrip : A::TriangleStrip {
      LANGULUS(NAME) CustomNameOf<TTriangleStrip>::Generate();
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::TriangleStrip);

      Anyness::TMany<T> mPoints;

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1,
         "Triangles don't exist below two dimensions");
   };


   ///                                                                        
   ///   A templated triangle fan                                             
   /// List of points, forming triangles, by always sharing the first and     
   /// last points in the sequence                                            
   ///                                                                        
   ///      2________3             Notice all trianlges are clockwise         
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
   template<CT::Vector T>
   struct TTriangleFan : A::TriangleFan {
      LANGULUS(NAME) CustomNameOf<TTriangleFan>::Generate();
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::TriangleFan);

      Anyness::TMany<T> mPoints;

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1,
         "Triangles don't exist below two dimensions");
   };

} // namespace Langulus::Math

