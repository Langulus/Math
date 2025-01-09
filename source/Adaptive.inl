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

   /// Get the appropriately scaled data                                      
   ///   @param level - the level we're accessing the data from               
   ///   @return the adapted data                                             
   template<class T>
   constexpr T Adaptive<T>::GetMidref(Level level) const noexcept {
      return mValue * mLevel.GetFactor(level);
   }

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
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return Adaptive {
         lhs.GetMidref(commonLevel) + rhs.GetMidref(commonLevel),
         commonLevel
      };
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS operator + (const LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return {lhs.mValue + rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr RHS operator + (const CT::NotAdaptive auto& lhs, const RHS& rhs) noexcept {
      return {lhs + rhs.mValue, rhs.mLevel};
   }

   /// Returns the difference of two adaptives (standing operator)            
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the difference of the adaptives                              
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return Adaptive {
         lhs.GetMidref(commonLevel) - rhs.GetMidref(commonLevel),
         commonLevel
      };
   }
    
   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS operator - (const LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return {lhs.mValue - rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr RHS operator - (const CT::NotAdaptive auto& lhs, const RHS& rhs) noexcept {
      return {lhs - rhs.mValue, rhs.mLevel};
   }

   /// Returns the product of two adaptives (standing operator)               
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the product of the adaptives                                 
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return Adaptive {
         lhs.GetMidref(commonLevel) * rhs.GetMidref(commonLevel),
         commonLevel
      };
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS operator * (const LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return {lhs.mValue * rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr RHS operator * (const CT::NotAdaptive auto& lhs, const RHS& rhs) noexcept {
      return {lhs * rhs.mValue, rhs.mLevel};
   }

   /// Returns the disivion of two adaptives (standing operator)              
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the division of the adaptives                                
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return Adaptive {
         lhs.GetMidref(commonLevel) / rhs.GetMidref(commonLevel),
         commonLevel
      };
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS operator / (const LHS& lhs, const CT::NotAdaptive auto& rhs) {
      return {lhs.mValue / rhs, lhs.mLevel};
   }

   template<CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr RHS operator / (const CT::NotAdaptive auto& lhs, const RHS& rhs) {
      return {lhs / rhs.mValue, rhs.mLevel};
   }
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   ///   @param lhs - left adaptive                                           
   ///   @param rhs - right adaptive                                          
   ///   @return the modulo, picking a lossless type between the two          
   LANGULUS(INLINED)
   constexpr auto operator % (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return Adaptive {
         lhs.GetMidref(commonLevel) % rhs.GetMidref(commonLevel),
         commonLevel
      };
   }

   template<CT::CustomNumber LHS> LANGULUS(INLINED)
   constexpr LHS operator % (const LHS& lhs, const CT::NotAdaptive auto& rhs) {
      return {lhs.mValue % rhs, lhs.mLevel};
   }

   template<CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr RHS operator % (const CT::NotAdaptive auto& lhs, const RHS& rhs) {
      return {lhs % rhs.mValue, rhs.mLevel};
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator += (LHS& lhs, const CT::Adaptive auto& rhs) noexcept {
      return (lhs = lhs + rhs);
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator += (LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return (lhs = lhs + rhs);
   }

   /// Subtract                                                               
   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator -= (LHS& lhs, const CT::Adaptive auto& rhs) noexcept {
      return (lhs = lhs - rhs);
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator -= (LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return (lhs = lhs - rhs);
   }

   /// Multiply                                                               
   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator *= (LHS& lhs, const CT::Adaptive auto& rhs) noexcept {
      return (lhs = lhs * rhs);
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator *= (LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return (lhs = lhs * rhs);
   }

   /// Divide                                                                 
   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator /= (LHS& lhs, const CT::Adaptive auto& rhs) {
      return (lhs = lhs / rhs);
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr LHS& operator /= (LHS& lhs, const CT::NotAdaptive auto& rhs) {
      return (lhs = lhs / rhs);
   }


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   LANGULUS(INLINED)
   constexpr bool operator < (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return lhs.GetMidref(commonLevel) < rhs.GetMidref(commonLevel);
   }

   LANGULUS(INLINED)
   constexpr bool operator < (const CT::Adaptive auto& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return lhs.mValue < rhs;
   }

   LANGULUS(INLINED)
   constexpr bool operator < (const CT::NotAdaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      return lhs < rhs.mValue;
   }

   /// Bigger                                                                 
   LANGULUS(INLINED)
   constexpr bool operator > (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return lhs.GetMidref(commonLevel) > rhs.GetMidref(commonLevel);
   }

   LANGULUS(INLINED)
   constexpr bool operator > (const CT::Adaptive auto& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return lhs.mValue > rhs;
   }

   LANGULUS(INLINED)
   constexpr bool operator > (const CT::NotAdaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      return lhs > rhs.mValue;
   }

   /// Bigger or equal                                                        
   LANGULUS(INLINED)
   constexpr bool operator >= (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return lhs.GetMidref(commonLevel) >= rhs.GetMidref(commonLevel);
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr bool operator >= (const LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return lhs.mValue >= rhs;
   }

   template<CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr bool operator >= (const CT::NotAdaptive auto& lhs, const RHS& rhs) noexcept {
      return lhs >= rhs.mValue;
   }

   /// Smaller or equal                                                       
   LANGULUS(INLINED)
   constexpr bool operator <= (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return lhs.GetMidref(commonLevel) <= rhs.GetMidref(commonLevel);
   }

   LANGULUS(INLINED)
   constexpr bool operator <= (const CT::Adaptive auto& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return lhs.mValue <= rhs;
   }

   LANGULUS(INLINED)
   constexpr bool operator <= (const CT::NotAdaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      return lhs <= rhs.mValue;
   }

   /// Equal                                                                  
   LANGULUS(INLINED)
   constexpr bool operator == (const CT::Adaptive auto& lhs, const CT::Adaptive auto& rhs) noexcept {
      const auto commonLevel = lhs.mLevel.GetRefPoint(rhs.mLevel);
      return lhs.GetMidref(commonLevel) == rhs.GetMidref(commonLevel);
   }

   template<CT::Adaptive LHS> LANGULUS(INLINED)
   constexpr bool operator == (const LHS& lhs, const CT::NotAdaptive auto& rhs) noexcept {
      return lhs.mValue == rhs;
   }

   template<CT::Adaptive RHS> LANGULUS(INLINED)
   constexpr bool operator == (const CT::NotAdaptive auto& lhs, const RHS& rhs) noexcept {
      return lhs == rhs.mValue;
   }

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME
