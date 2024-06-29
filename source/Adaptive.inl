///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Adaptive.hpp"


namespace Langulus::Math
{

   /// Returns an inverted adaptive (standing operator)                       
   ///   @param a - adaptive to invert                                        
   template<CT::Adaptive T> requires CT::Signed<T> LANGULUS(INLINED)
   constexpr T operator - (const T& a) noexcept {
      return {-a.mValue, a.mLevel};
   }

   /// Returns the sum of two adaptives (standing operator)                   
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the sum of the adaptives                                     
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr auto operator + (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return Adaptive {lhs.mValue * fl + rhs.mValue * fr, commonLevel};
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS operator + (const LHS& lhs, const N& rhs) noexcept {
      return {lhs.mValue + rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr RHS operator + (const N& lhs, const RHS& rhs) noexcept {
      return {lhs + rhs.mValue, rhs.mLevel};
   }

   /// Returns the difference of two adaptives (standing operator)            
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the difference of the adaptives                              
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr auto operator - (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return Adaptive {lhs.mValue * fl - rhs.mValue * fr, commonLevel};
   }
    
   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS operator - (const LHS& lhs, const N& rhs) noexcept {
      return {lhs.mValue - rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr RHS operator - (const N& lhs, const RHS& rhs) noexcept {
      return {lhs - rhs.mValue, rhs.mLevel};
   }

   /// Returns the product of two adaptives (standing operator)               
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the product of the adaptives                                 
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr auto operator * (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return Adaptive {(lhs.mValue * fl) * (rhs.mValue * fr), commonLevel};
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS operator * (const LHS& lhs, const N& rhs) noexcept {
      return {lhs.mValue * rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr RHS operator * (const N& lhs, const RHS& rhs) noexcept {
      return {lhs * rhs.mValue, rhs.mLevel};
   }

   /// Returns the disivion of two adaptives (standing operator)              
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the division of the adaptives                                
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr auto operator / (const LHS& lhs, const RHS& rhs) {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return Adaptive {(lhs.mValue * fl) / (rhs.mValue * fr), commonLevel};
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS operator / (const LHS& lhs, const N& rhs) {
      return {lhs.mValue / rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr RHS operator / (const N& lhs, const RHS& rhs) {
      return {lhs / rhs.mValue, rhs.mLevel};
   }
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the modulo, picking a lossless type between the two          
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr auto operator % (const LHS& lhs, const RHS& rhs) {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return Adaptive {(lhs.mValue * fl) % (rhs.mValue * fr), commonLevel};
   }

   template<CT::CustomNumber LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS operator % (const LHS& lhs, const N& rhs) {
      return {lhs.mValue % rhs, lhs.mLevel};
   }

   template<CT::CustomNumber RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr RHS operator % (const N& lhs, const RHS& rhs) {
      return {lhs % rhs.mValue, rhs.mLevel};
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr LHS& operator += (LHS& lhs, const RHS& rhs) noexcept {
      return (lhs = lhs + rhs);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS& operator += (LHS& lhs, const N& rhs) noexcept {
      return (lhs = lhs + rhs);
   }

   /// Subtract                                                               
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr LHS& operator -= (LHS& lhs, const RHS& rhs) noexcept {
      return (lhs = lhs - rhs);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS& operator -= (LHS& lhs, const N& rhs) noexcept {
      return (lhs = lhs - rhs);
   }

   /// Multiply                                                               
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr LHS& operator *= (LHS& lhs, const RHS& rhs) noexcept {
      return (lhs = lhs * rhs);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS& operator *= (LHS& lhs, const N& rhs) noexcept {
      return (lhs = lhs * rhs);
   }

   /// Divide                                                                 
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr LHS& operator /= (LHS& lhs, const RHS& rhs) {
      return (lhs = lhs / rhs);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr LHS& operator /= (LHS& lhs, const N& rhs) {
      return (lhs = lhs / rhs);
   }


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr bool operator < (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return (lhs.mValue * fl) < (rhs.mValue * fr);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator < (const LHS& lhs, const N& rhs) noexcept {
      return lhs.mValue < rhs;
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator < (const N& lhs, const RHS& rhs) noexcept {
      return lhs < rhs.mValue;
   }

   /// Bigger                                                                 
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr bool operator > (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return (lhs.mValue * fl) > (rhs.mValue * fr);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator > (const LHS& lhs, const N& rhs) noexcept {
      return lhs.mValue > rhs;
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator > (const N& lhs, const RHS& rhs) noexcept {
      return lhs > rhs.mValue;
   }

   /// Bigger or equal                                                        
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr bool operator >= (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return (lhs.mValue * fl) >= (rhs.mValue * fr);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator >= (const LHS& lhs, const N& rhs) noexcept {
      return lhs.mValue >= rhs;
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator >= (const N& lhs, const RHS& rhs) noexcept {
      return lhs >= rhs.mValue;
   }

   /// Smaller or equal                                                       
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr bool operator <= (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return (lhs.mValue * fl) <= (rhs.mValue * fr);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator <= (const LHS& lhs, const N& rhs) noexcept {
      return lhs.mValue <= rhs;
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator <= (const N& lhs, const RHS& rhs) noexcept {
      return lhs <= rhs.mValue;
   }

   /// Equal                                                                  
   template<CT::Adaptive LHS, CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr bool operator == (const LHS& lhs, const RHS& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      const auto fl = lhs.mLevel.GetFactor(commonLevel);
      const auto fr = rhs.mLevel.GetFactor(commonLevel);
      return (lhs.mValue * fl) == (rhs.mValue * fr);
   }

   template<CT::Adaptive LHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator == (const LHS& lhs, const N& rhs) noexcept {
      return lhs.mValue == rhs;
   }

   template<CT::Adaptive RHS, CT::NotAdaptive N> LANGULUS(INLINED)
   constexpr bool operator == (const N& lhs, const RHS& rhs) noexcept {
      return lhs == rhs.mValue;
   }

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME
