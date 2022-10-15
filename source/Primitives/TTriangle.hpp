///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TPoint.hpp"

namespace Langulus::Math
{

   template<CT::Vector> struct TTriangle;
   template<CT::Vector> struct TTriangleStrip;
   template<CT::Vector> struct TTriangleFan;

   using Triangle2 = TTriangle<Point2>;
   using Triangle3 = TTriangle<Point3>;
   using TriangleStrip2 = TTriangleStrip<Point2>;
   using TriangleStrip3 = TTriangleStrip<Point3>;
   using TriangleFan2 = TTriangleFan<Point2>;
   using TriangleFan3 = TTriangleFan<Point3>;

   using Triangle = Triangle3;
   using TriangleStrip = TriangleStrip3;
   using TriangleFan = TriangleFan3;

} // namespace Langulus::Math

namespace Langulus::A
{

   ///   An abstract triangle, also used as a topology type                   
   struct Triangle {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::Triangle;
      LANGULUS_BASES(Topology);
   };

   ///   An abstract triangle strip, also used as a topology type             
   struct TriangleStrip {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::TriangleStrip;
      LANGULUS_BASES(Topology);
   };

   ///   An abstract triangle fan, also used as a topology type               
   struct TriangleFan {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::TriangleFan;
      LANGULUS_BASES(Topology);
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   A templated triangle                                                 
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::Vector T>
   struct TTriangle {
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS_BASES(A::Triangle);

      using PointType = T;
      using typename T::MemberType;
      using T::MemberCount;
      static_assert(MemberCount > 1, "Triangles don't exist below two dimensions");

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
             || mABC[0] == mABC[2]
             || mABC[1] == mABC[2];
      }

      /// Subdivide triangle                                                  
      ///   @return the four new triangles                                    
      NOD() ::std::array<TTriangle, 4> Subdivide() const noexcept {
         constexpr MemberType two {2};
         const T m01 = mABC[0] + (mABC[1] - mABC[0]) / two;
         const T m12 = mABC[1] + (mABC[2] - mABC[1]) / two;
         const T m20 = mABC[2] + (mABC[0] - mABC[2]) / two;
         return {
            {mABC[0], m01, m20}, 
            {m01, mABC[1], m12}, 
            {m20, m12, mABC[2]}, 
            {m01, m12, m20}
         };
      }

      /// Calculate signed distance                                           
      ///   @param point - the point from which distance is calculated        
      ///   @return the distance                                              
      NOD() auto SignedDistance(const T& point) const {
         const auto e0 = mABC[1] - mABC[0];
         const auto e1 = mABC[2] - mABC[1];
         const auto e2 = mABC[0] - mABC[2];
         const auto v0 = point - mABC[0];
         const auto v1 = point - mABC[1];
         const auto v2 = point - mABC[2];

         if constexpr (MemberCount < 3) {
            // 2D signed distance field                                 
            const auto pq0 = v0 - e0 * Clamp01(v0.Dot(e0) / Dot2(e0));
            const auto pq1 = v1 - e1 * Clamp01(v1.Dot(e1) / Dot2(e1));
            const auto pq2 = v2 - e2 * Clamp01(v2.Dot(e2) / Dot2(e2));
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
                  Dot2(e0 * Clamp01(e0.Dot(v0) / Dot2(e0)) - v0),
                  Dot2(e1 * Clamp01(e1.Dot(v1) / Dot2(e1)) - v1),
                  Dot2(e2 * Clamp01(e2.Dot(v2) / Dot2(e2)) - v2))
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
   ///      1________3_______ 5     Notice all trianlges are clockwise        
   ///      /\      /\      /       0,1,2 - first triangle                    
   ///     /  \    /  \    /        2,1,3 - second triangle                   
   ///    /    \  /    \  /         2,3,4 - third triangle                    
   ///   /______\/______\/          4,3,5 - fourth triangle                   
   ///  0        2        4                                                   
   template<CT::Vector T>
   struct TTriangleStrip : public TAny<T> {
      LANGULUS(DEEP) false;
      LANGULUS_BASES(A::TriangleStrip);

      using Base = TAny<T>;
      using PointType = T;
      using typename T::MemberType;
      using T::MemberCount;
      static_assert(MemberCount > 1, "Triangles don't exist below two dimensions");

      NOD() TTriangleStrip Clone() const {
         TTriangleStrip cloned;
         static_cast<Base&>(cloned) = Base::Clone();
         return cloned;
      }
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
   template<CT::Vector T>
   struct TTriangleFan : public TAny<T> {
      LANGULUS(DEEP) false;
      LANGULUS_BASES(A::TriangleFan);

      using Base = TAny<T>;
      using PointType = T;
      using typename T::MemberType;
      using T::MemberCount;
      static_assert(MemberCount > 1, "Triangles don't exist below two dimensions");

      NOD() TTriangleFan Clone() const {
         TTriangleFan cloned;
         static_cast<Base&>(cloned) = Base::Clone();
         return cloned;
      }
   };

} // namespace Langulus::Math

