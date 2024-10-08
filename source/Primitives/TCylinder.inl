///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TCylinder.hpp"
#include "../SignedDistance/TCylinder.inl"
#include "../SignedDistance/TCylinderCapped.inl"

#define TEMPLATE() template<CT::Vector T, CT::Dimension D>


namespace Langulus::Math
{

   /// Check if cylinder is degenerate                                        
   ///   @return true if at least one offset is zero                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TCylinder<T, D>::IsDegenerate() const noexcept {
      return mRadius == 0;
   }

   /// Check if cylinder is hollow                                            
   ///   @return true if at least one of the offsets is negative              
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TCylinder<T, D>::IsHollow() const noexcept {
      return mRadius < 0;
   }

   /// Calculate signed distance from cylinder                                
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   TEMPLATE() LANGULUS(INLINED)
   auto TCylinder<T, D>::SignedDistance(const T& point) const {
      return Math::SignedDistance(point, *this);
   }
   
   /// Check if cylinder is degenerate                                        
   ///   @return true if at least one offset is zero                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TCylinderCapped<T, D>::IsDegenerate() const noexcept {
      return mRadius == 0 || mHeight == 0;
   }

   /// Check if cylinder is hollow                                            
   ///   @return true if at least one of the offsets is negative              
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TCylinderCapped<T, D>::IsHollow() const noexcept {
      return mRadius < 0 || mHeight < 0;
   }

   /// Calculate signed distance from cylinder                                
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   TEMPLATE() LANGULUS(INLINED)
   auto TCylinderCapped<T, D>::SignedDistance(const T& point) const {
      return Math::SignedDistance(point, *this);
   }

} // namespace Langulus::Math

#undef TEMPLATE