///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TNumber.hpp"

namespace Langulus::Math
{

   /// Returns an inverted number                                             
   template<TARGS(RHS)>
   constexpr auto operator - (const TNUM(RHS)& a) noexcept requires CT::Signed<RHST> {
      return TNUM(RHS) {-a.mValue};
   }

   /// Returns the sum of two numbers                                         
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator + (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      if constexpr (CT::Same<Lossless<LHST, RHST>, LHST>) {
         if constexpr (CT::Same<LHST, LHSW>)
            return TNUM(LHS) {static_cast<LHST>(lhs.mValue + rhs.mValue)};
         else
            return LHSW {static_cast<LHST>(lhs.mValue + rhs.mValue)};
      }
      else {
         if constexpr (CT::Same<RHST, RHSW>)
            return TNUM(RHS) {static_cast<RHST>(lhs.mValue + rhs.mValue)};
         else
            return RHSW {static_cast<RHST>(lhs.mValue + rhs.mValue)};
      }
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto operator + (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue + rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr auto operator + (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs + rhs.mValue;
   }

   /// Returns the difference of two numbers                                  
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator - (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue - rhs.mValue;
   }
    
   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto operator - (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue - rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr auto operator - (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs - rhs.mValue;
   }

   /// Returns the product of two numbers                                     
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator * (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      if constexpr (CT::Same<Lossless<LHST, RHST>, LHST>) {
         if constexpr (CT::Same<LHST, LHSW>)
            return TNUM(LHS) { static_cast<LHST>(lhs.mValue * rhs.mValue) };
         else
            return LHSW {static_cast<LHST>(lhs.mValue * rhs.mValue)};
      }
      else {
         if constexpr (CT::Same<RHST, RHSW>)
            return TNUM(RHS) { static_cast<RHST>(lhs.mValue * rhs.mValue) };
         else
            return RHSW {static_cast<RHST>(lhs.mValue * rhs.mValue)};
      }
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto operator * (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      if constexpr (CT::Same<LHST, LHSW>)
         return TNUM(LHS) { static_cast<LHST>(lhs.mValue * rhs) };
      else
         return LHSW {static_cast<LHST>(lhs.mValue * rhs)};
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr auto operator * (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      if constexpr (CT::Same<RHST, RHSW>)
         return TNUM(RHS) { static_cast<RHST>(lhs * rhs.mValue) };
      else
         return RHSW {static_cast<RHST>(lhs * rhs.mValue)};
   }

   /// Returns the division of two numbers                                    
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator / (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) requires CT::Same<LHSW, RHSW> {
      if constexpr (CT::Same<Lossless<LHST, RHST>, LHST>) {
         if constexpr (CT::Same<LHST, LHSW>)
            return TNUM(LHS) {static_cast<LHST>(lhs.mValue / rhs.mValue)};
         else
            return LHSW {static_cast<LHST>(lhs.mValue / rhs.mValue)};
      }
      else {
         if constexpr (CT::Same<RHST, RHSW>)
            return TNUM(RHS) {static_cast<RHST>(lhs.mValue / rhs.mValue)};
         else
            return RHSW {static_cast<RHST>(lhs.mValue / rhs.mValue)};
      }
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto operator / (const TNUM(LHS)& lhs, const N& rhs) requires (!CT::Same<LHSW, N>) {
      if constexpr (CT::Same<LHST, LHSW>)
         return TNUM(LHS) {static_cast<LHST>(lhs.mValue / rhs)};
      else
         return LHSW {static_cast<LHST>(lhs.mValue / rhs)};
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr auto operator / (const N& lhs, const TNUM(RHS)& rhs) requires (!CT::Same<RHSW, N>) {
      if constexpr (CT::Same<RHST, RHSW>)
         return TNUM(RHS) {static_cast<RHST>(lhs / rhs.mValue)};
      else
         return RHSW {static_cast<RHST>(lhs / rhs.mValue)};
   }
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Real, too   
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator % (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) requires CT::Same<LHSW, RHSW> {
      if constexpr (CT::Integer<LHST, RHST>)
         return lhs.mValue % rhs.mValue;
      else
         return lhs.mValue - rhs.mValue * ::std::floor(lhs.mValue / rhs.mValue);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto operator % (const TNUM(LHS)& lhs, const N& rhs) requires (!CT::Same<LHSW, N>) {
      if constexpr (CT::Integer<LHST, N>)
         return lhs.mValue % rhs;
      else
         return lhs.mValue - rhs * ::std::floor(lhs.mValue / rhs);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr auto operator % (const N& lhs, const TNUM(RHS)& rhs) requires (!CT::Same<RHSW, N>) {
      if constexpr (CT::Integer<RHST, N>)
         return lhs % rhs.mValue;
      else
         return lhs - rhs.mValue * ::std::floor(lhs / rhs.mValue);
   }

   /// Returns the left-shift of two integer vectors                          
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator << (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>) {
      return lhs.mValue << rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseInteger N>
   constexpr auto operator << (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue << rhs;
   }

   template<TARGS(RHS), CT::DenseInteger N>
   constexpr auto operator << (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs << rhs.mValue;
   }

   /// Returns the right-shift of two integer vectors                         
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator >> (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>) {
      return lhs.mValue >> rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseInteger N>
   constexpr auto operator >> (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue >> rhs;
   }

   template<TARGS(RHS), CT::DenseInteger N>
   constexpr auto operator >> (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs >> rhs.mValue;
   }

   /// Returns the xor of two integer vectors                                 
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto operator ^ (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>) {
      return lhs.mValue ^ rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseInteger N>
   constexpr auto operator ^ (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue ^ rhs;
   }

   template<TARGS(RHS), CT::DenseInteger N>
   constexpr auto operator ^ (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs ^ rhs.mValue;
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator += (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      lhs.mValue += rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator += (TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      lhs.mValue += rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }

   /// Subtract                                                               
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator -= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      lhs.mValue -= rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator -= (TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      lhs.mValue -= rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }

   /// Multiply                                                               
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator *= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      lhs.mValue *= rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator *= (TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      lhs.mValue *= rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }

   /// Divide                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator /= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) requires CT::Same<LHSW, RHSW> {
      lhs.mValue /= rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator /= (TNUM(LHS)& lhs, const N& rhs) requires (!CT::Same<LHSW, N>) {
      lhs.mValue /= rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<TARGS(LHS), TARGS(RHS)>
   constexpr bool operator < (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue < rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr bool operator < (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue < rhs;
   }

   template<TARGS(LHS), CT::Character N>
   constexpr bool operator < (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue < rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr bool operator < (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs < rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   constexpr bool operator < (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs < rhs.mValue;
   }

   /// Bigger                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   constexpr bool operator > (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue > rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr bool operator > (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue > rhs;
   }

   template<TARGS(LHS), CT::Character N>
   constexpr bool operator > (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue > rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr bool operator > (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs > rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   constexpr bool operator > (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs > rhs.mValue;
   }

   /// Bigger or equal                                                        
   template<TARGS(LHS), TARGS(RHS)>
   constexpr bool operator >= (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue >= rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr bool operator >= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue >= rhs;
   }

   template<TARGS(LHS), CT::Character N>
   constexpr bool operator >= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue >= rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr bool operator >= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs >= rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   constexpr bool operator >= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs >= rhs.mValue;
   }

   /// Smaller or equal                                                       
   template<TARGS(LHS), TARGS(RHS)>
   constexpr bool operator <= (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue <= rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr bool operator <= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue <= rhs;
   }

   template<TARGS(LHS), CT::Character N>
   constexpr bool operator <= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue <= rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr bool operator <= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs <= rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   constexpr bool operator <= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs <= rhs.mValue;
   }

   /// Equal                                                                  
   template<TARGS(LHS), TARGS(RHS)>
   constexpr bool operator == (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue == rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr bool operator == (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue == rhs;
   }

   template<TARGS(LHS), CT::Character N>
   constexpr bool operator == (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue == rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   constexpr bool operator == (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs == rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   constexpr bool operator == (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs == rhs.mValue;
   }

} // namespace Langulus::Math
