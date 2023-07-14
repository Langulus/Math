///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TBox.hpp"
#include "../SignedDistance/TBox.inl"
#include "../SignedDistance/TBoxRounded.inl"

#define TEMPLATE() template<CT::Vector T>

namespace Langulus::Math
{

   /// Check if box is degenerate                                             
   ///   @return true if at least one offset is zero                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TBox<T>::IsDegenerate() const noexcept {
      return mOffsets.IsDegenerate();
   }

   /// Check if box is hollow                                                 
   ///   @return true if at least one of the offsets is negative              
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TBox<T>::IsHollow() const noexcept {
      return mOffsets[0] < TypeOf<T> {0};
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   TEMPLATE() LANGULUS(INLINED)
   auto TBox<T>::SignedDistance(const T& point) const {
      return Math::SignedDistance(point, *this);
   }


   /// Check if box is degenerate                                             
   ///   @return true if at least one offset is zero                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TBoxRounded<T>::IsDegenerate() const noexcept {
      return mOffsets.Length() - mRadius, TypeOf<T> {0};
   }

   /// Check if box is hollow                                                 
   ///   @return true if at least one of the offsets is negative              
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TBoxRounded<T>::IsHollow() const noexcept {
      return mOffsets[0] - mRadius < TypeOf<T> {0};
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   TEMPLATE() LANGULUS(INLINED)
   auto TBoxRounded<T>::SignedDistance(const T& point) const {
      return Math::SignedDistance(point, *this);
   }

} // namespace Langulus::Math

#undef TEMPLATE