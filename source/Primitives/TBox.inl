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

namespace Langulus::Math
{

   /// Check if box is degenerate                                             
   ///   @return true if at least one offset is zero                          
   template<CT::Vector T>
   constexpr bool TBox<T>::IsDegenerate() const noexcept {
      return mOffsets.IsDegenerate();
   }

   /// Check if box is hollow                                                 
   ///   @return true if at least one of the offsets is negative              
   template<CT::Vector T>
   constexpr bool TBox<T>::IsHollow() const noexcept {
      return mOffsets[0] < MemberType {0};
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   template<CT::Vector T>
   auto TBox<T>::SignedDistance(const T& point) const {
      return ::Langulus::Math::SignedDistance(point, *this);
   }

   /// Check if box is degenerate                                             
   ///   @return true if at least one offset is zero                          
   template<CT::Vector T>
   constexpr bool TBoxRounded<T>::IsDegenerate() const noexcept {
      return mOffsets.Length() - mRadius, MemberType {0};
   }

   /// Check if box is hollow                                                 
   ///   @return true if at least one of the offsets is negative              
   template<CT::Vector T>
   constexpr bool TBoxRounded<T>::IsHollow() const noexcept {
      return mOffsets[0] - mRadius < MemberType {0};
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   template<CT::Vector T>
   auto TBoxRounded<T>::SignedDistance(const T& point) const {
      return ::Langulus::Math::SignedDistance(point, *this);
   }

} // namespace Langulus::Math

