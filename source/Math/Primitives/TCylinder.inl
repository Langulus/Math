///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TCylinder.hpp"
#include "../SignedDistance/TCylinder.inl"
#include "../SignedDistance/TCylinderCapped.inl"

namespace Langulus::Math
{

   /// Check if cylinder is degenerate                                        
   ///   @return true if at least one offset is zero                          
   template<CT::Vector T, CT::Dimension D>
   constexpr bool TCylinder<T, D>::IsDegenerate() const noexcept {
      return mRadius == 0;
   }

   /// Check if cylinder is hollow                                            
   ///   @return true if at least one of the offsets is negative              
   template<CT::Vector T, CT::Dimension D>
   constexpr bool TCylinder<T, D>::IsHollow() const noexcept {
      return mRadius < 0;
   }

   /// Calculate signed distance from cylinder                                
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   template<CT::Vector T, CT::Dimension D>
   auto TCylinder<T, D>::SignedDistance(const T& point) const {
      return ::Langulus::Math::SignedDistance(point, *this);
   }
   
   /// Check if cylinder is degenerate                                        
   ///   @return true if at least one offset is zero                          
   template<CT::Vector T, CT::Dimension D>
   constexpr bool TCylinderCapped<T, D>::IsDegenerate() const noexcept {
      return mRadius == 0 || mHeight == 0;
   }

   /// Check if cylinder is hollow                                            
   ///   @return true if at least one of the offsets is negative              
   template<CT::Vector T, CT::Dimension D>
   constexpr bool TCylinderCapped<T, D>::IsHollow() const noexcept {
      return mRadius < 0 || mHeight < 0;
   }

   /// Calculate signed distance from cylinder                                
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   template<CT::Vector T, CT::Dimension D>
   auto TCylinderCapped<T, D>::SignedDistance(const T& point) const {
      return ::Langulus::Math::SignedDistance(point, *this);
   }

} // namespace Langulus::Math

