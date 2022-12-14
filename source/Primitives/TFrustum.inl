///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TFrustum.hpp"

namespace Langulus::Math
{

   /// Default unit frustum construction                                      
   template<CT::Vector T>
   TFrustum<T>::TFrustum() noexcept {
      const T right {0.5, 0, 0};
      const T top {0, 0.5, 0};

      mPlanes[Left] = TPlane<T>(right);
      mPlanes[Right] = TPlane<T>(-right);
      mPlanes[Top] = TPlane<T>(-top);
      mPlanes[Bottom] = TPlane<T>(top);

      if constexpr (MemberCount > 2) {
         const T far {0, 0, 0.5};
         mPlanes[Near] = TPlane<T>(far);
         mPlanes[Far] = TPlane<T>(-far);
      }
   }

   /// Create a frustum by deconstructing a view*projection matrix            
   ///   @param projectedView - projected view matrix                         
   template<CT::Vector T>
   TFrustum<T>::TFrustum(const TMatrix<MemberType, MemberCount + 1>& projectedView) noexcept {
      const auto right = projectedView.Column(0);
      const auto top = projectedView.Column(1);
      const auto eye = projectedView.Column(MemberCount > 2 ? 3 : 2) * (-1);

      mPlanes[Left] = TPlane<T>(eye + right);
      mPlanes[Right] = TPlane<T>(eye - right);
      mPlanes[Top] = TPlane<T>(eye - top);
      mPlanes[Bottom] = TPlane<T>(eye + top);

      if constexpr (MemberCount > 2) {
         const auto far = projectedView.Column(2);
         mPlanes[Near] = TPlane<T>(eye + far);
         mPlanes[Far] = TPlane<T>(eye - far);
      }
   }

   /// Check if frustum is degenerate                                         
   ///   @return true if at least one of the planes is degenerate             
   template<CT::Vector T>
   constexpr bool TFrustum<T>::IsDegenerate() const noexcept {
      for (auto& plane : mPlanes)
         if (plane.IsDegenerate())
            return true;
      return false;
   }

   /// Check if frustum is hollow                                             
   ///   @return true if at least one of the offsets is negative              
   template<CT::Vector T>
   constexpr bool TFrustum<T>::IsHollow() const noexcept {
      TODO();
      return false;
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   template<CT::Vector T>
   auto TFrustum<T>::SignedDistance(const T& point) const {
      return Min(
         mPlanes[0].SignedDistance(point),
         mPlanes[1].SignedDistance(point),
         mPlanes[2].SignedDistance(point),
         mPlanes[3].SignedDistance(point),
         mPlanes[4].SignedDistance(point),
         mPlanes[5].SignedDistance(point)
      );
   }

   /// Intersect with an AABB                                                 
   ///   @param box - 2D/3D axis-aligned bounding box                         
   ///   @return true if box intersects the frustum                           
   template<CT::Vector T>
   bool TFrustum<T>::Intersects(const TRange<T>& box) const noexcept {
      if (box.IsDegenerate() || box.Length().IsDegenerate())
         return false;

      // Not quite as fast, but wastes less space                       
      for (const auto& plane : mPlanes) {
         const auto& normal = plane.mNormal;
         const PointType point = {
            normal[0] >= 0 ? box.mMin[0] : box.mMax[0],
            normal[1] >= 0 ? box.mMin[1] : box.mMax[1],
            normal[2] >= 0 ? box.mMin[2] : box.mMax[2]
         };

         if (point.Dot(normal) > -plane.mOffset)
            return false;
      }

      return true;
   }

} // namespace Langulus::Math