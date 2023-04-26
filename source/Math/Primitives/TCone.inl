///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TCone.hpp"
#include "../SignedDistance/TCone.inl"

namespace Langulus::Math
{

   /// Check if cone is degenerate                                            
   ///   @return true if at least one offset is zero                          
   template<CT::Vector T, CT::Dimension D>
   constexpr bool TCone<T, D>::IsDegenerate() const noexcept {
      return mHeight == 0 || mAngle == 0;
   }

   /// Check if cone is hollow                                                
   ///   @return true if at least one of the offsets is negative              
   template<CT::Vector T, CT::Dimension D>
   constexpr bool TCone<T, D>::IsHollow() const noexcept {
      return mHeight < 0;
   }

   /// Calculate signed distance from cone                                    
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   template<CT::Vector T, CT::Dimension D>
   auto TCone<T, D>::SignedDistance(const T& point) const {
      return ::Langulus::Math::SignedDistance(point, *this);
   }

} // namespace Langulus::Math

