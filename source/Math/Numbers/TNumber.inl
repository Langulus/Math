///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <Flow/Verb.hpp>
#include "TNumber.hpp"

namespace Langulus::Math
{
   TEMPLATE()
   LANGULUS(INLINED)
   constexpr TME()::TNumber(const T& a) noexcept
      : mValue {a} {}

   TEMPLATE()
   LANGULUS(INLINED)
   constexpr TME()::TNumber(const W& a) noexcept requires (!CT::Same<T, W>)
      : mValue {a.mValue} {}

   TEMPLATE()
   template<class N>
   LANGULUS(INLINED)
   constexpr TME()::TNumber(const N& a) noexcept requires CT::Convertible<N, T>
      : mValue {static_cast<T>(a)} {}

   TEMPLATE()
   LANGULUS(INLINED)
   TME()& TME()::operator = (const T& a) noexcept {
      mValue = a;
      return *this;
   }

   TEMPLATE()
   LANGULUS(INLINED)
   TME()& TME()::operator = (const W& a) noexcept requires (!CT::Same<T, W>) {
      mValue = a.mValue;
      return *this;
   }

   /// All conversions are explicit only, to preserve type                    
   TEMPLATE()
   LANGULUS(INLINED)
   constexpr TME()::operator const T& () const noexcept {
      return mValue;
   }

   /// All conversions are explicit only, to preserve type                    
   TEMPLATE()
   LANGULUS(INLINED)
   constexpr TME()::operator T& () noexcept {
      return mValue;
   }

   /// Convert from any angle to text                                         
   TEMPLATE()
   LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      Flow::Code result;
      result += MetaOf<W>();
      result += Flow::Code::OpenScope;
      if constexpr (CT::Same<T, uint8_t>)
         result += Flow::Code {static_cast<unsigned int>(mValue)};
      else
         result += Flow::Code {mValue};
      result += Flow::Code::CloseScope;
      return result;
   }

   /// Prefix increment operator                                              
   ///   @return the modified value                                           
   TEMPLATE()
   LANGULUS(INLINED)
   TME()& TME()::operator ++ () noexcept {
      ++mValue;
      return *this;
   }

   /// Prefix decrement operator                                              
   ///   @return the modified value                                           
   TEMPLATE()
   LANGULUS(INLINED)
   TME()& TME()::operator -- () noexcept {
      --mValue;
      return *this;
   }

   /// Suffix increment operator                                              
   ///   @return the previous value                                           
   TEMPLATE()
   LANGULUS(INLINED)
   TME() TME()::operator ++ (int) noexcept {
      const auto backup = *this;
      operator ++ ();
      return backup;
   }

   /// Suffix decrement operator                                              
   ///   @return the previous value                                           
   TEMPLATE()
   LANGULUS(INLINED)
   TME() TME()::operator -- (int) noexcept {
      const auto backup = *this;
      operator -- ();
      return backup;
   }

   /// Returns an inverted number                                             
   template<TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto operator - (const TNUM(RHS)& a) noexcept requires CT::Signed<RHST> {
      return TNUM(RHS) {-a.mValue};
   }

   /// Returns the sum of two numbers                                         
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
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
   LANGULUS(INLINED)
   constexpr auto operator + (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue + rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto operator + (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs + rhs.mValue;
   }

   /// Returns the difference of two numbers                                  
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto operator - (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue - rhs.mValue;
   }
    
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto operator - (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue - rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto operator - (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs - rhs.mValue;
   }

   /// Returns the product of two numbers                                     
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
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
   LANGULUS(INLINED)
   constexpr auto operator * (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      if constexpr (CT::Same<LHST, LHSW>)
         return TNUM(LHS) { static_cast<LHST>(lhs.mValue * rhs) };
      else
         return LHSW {static_cast<LHST>(lhs.mValue * rhs)};
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto operator * (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      if constexpr (CT::Same<RHST, RHSW>)
         return TNUM(RHS) { static_cast<RHST>(lhs * rhs.mValue) };
      else
         return RHSW {static_cast<RHST>(lhs * rhs.mValue)};
   }

   /// Returns the division of two numbers                                    
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
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
   LANGULUS(INLINED)
   constexpr auto operator / (const TNUM(LHS)& lhs, const N& rhs) requires (!CT::Same<LHSW, N>) {
      if constexpr (CT::Same<LHST, LHSW>)
         return TNUM(LHS) {static_cast<LHST>(lhs.mValue / rhs)};
      else
         return LHSW {static_cast<LHST>(lhs.mValue / rhs)};
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto operator / (const N& lhs, const TNUM(RHS)& rhs) requires (!CT::Same<RHSW, N>) {
      if constexpr (CT::Same<RHST, RHSW>)
         return TNUM(RHS) {static_cast<RHST>(lhs / rhs.mValue)};
      else
         return RHSW {static_cast<RHST>(lhs / rhs.mValue)};
   }
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Real, too   
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto operator % (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) requires CT::Same<LHSW, RHSW> {
      if constexpr (CT::Integer<LHST, RHST>)
         return lhs.mValue % rhs.mValue;
      else
         return lhs.mValue - rhs.mValue * ::std::floor(lhs.mValue / rhs.mValue);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto operator % (const TNUM(LHS)& lhs, const N& rhs) requires (!CT::Same<LHSW, N>) {
      if constexpr (CT::Integer<LHST, N>)
         return lhs.mValue % rhs;
      else
         return lhs.mValue - rhs * ::std::floor(lhs.mValue / rhs);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto operator % (const N& lhs, const TNUM(RHS)& rhs) requires (!CT::Same<RHSW, N>) {
      if constexpr (CT::Integer<RHST, N>)
         return lhs % rhs.mValue;
      else
         return lhs - rhs.mValue * ::std::floor(lhs / rhs.mValue);
   }

   /// Returns the left-shift of two integer vectors                          
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto operator << (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>) {
      return lhs.mValue << rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseInteger N>
   LANGULUS(INLINED)
   constexpr auto operator << (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue << rhs;
   }

   template<TARGS(RHS), CT::DenseInteger N>
   LANGULUS(INLINED)
   constexpr auto operator << (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs << rhs.mValue;
   }

   /// Returns the right-shift of two integer vectors                         
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto operator >> (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>) {
      return lhs.mValue >> rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseInteger N>
   LANGULUS(INLINED)
   constexpr auto operator >> (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue >> rhs;
   }

   template<TARGS(RHS), CT::DenseInteger N>
   LANGULUS(INLINED)
   constexpr auto operator >> (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs >> rhs.mValue;
   }

   /// Returns the xor of two integer vectors                                 
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto operator ^ (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>) {
      return lhs.mValue ^ rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseInteger N>
   LANGULUS(INLINED)
   constexpr auto operator ^ (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue ^ rhs;
   }

   template<TARGS(RHS), CT::DenseInteger N>
   LANGULUS(INLINED)
   constexpr auto operator ^ (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs ^ rhs.mValue;
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto& operator += (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      lhs.mValue += rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto& operator += (TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      lhs.mValue += rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }

   /// Subtract                                                               
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto& operator -= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      lhs.mValue -= rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto& operator -= (TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      lhs.mValue -= rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }

   /// Multiply                                                               
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto& operator *= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      lhs.mValue *= rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto& operator *= (TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      lhs.mValue *= rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }

   /// Divide                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto& operator /= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) requires CT::Same<LHSW, RHSW> {
      lhs.mValue /= rhs.mValue;
      return reinterpret_cast<LHSW&>(lhs);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr auto& operator /= (TNUM(LHS)& lhs, const N& rhs) requires (!CT::Same<LHSW, N>) {
      lhs.mValue /= rhs;
      return reinterpret_cast<LHSW&>(lhs);
   }


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr bool operator < (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue < rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator < (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue < rhs;
   }

   template<TARGS(LHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator < (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue < rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator < (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs < rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator < (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs < rhs.mValue;
   }

   /// Bigger                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr bool operator > (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue > rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator > (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue > rhs;
   }

   template<TARGS(LHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator > (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue > rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator > (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs > rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator > (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs > rhs.mValue;
   }

   /// Bigger or equal                                                        
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr bool operator >= (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue >= rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator >= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue >= rhs;
   }

   template<TARGS(LHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator >= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue >= rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator >= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs >= rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator >= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs >= rhs.mValue;
   }

   /// Smaller or equal                                                       
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr bool operator <= (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue <= rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator <= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue <= rhs;
   }

   template<TARGS(LHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator <= (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue <= rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator <= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs <= rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator <= (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs <= rhs.mValue;
   }

   /// Equal                                                                  
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr bool operator == (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
      return lhs.mValue == rhs.mValue;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator == (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue == rhs;
   }

   template<TARGS(LHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator == (const TNUM(LHS)& lhs, const N& rhs) noexcept requires (!CT::Same<LHSW, N>) {
      return lhs.mValue == rhs;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr bool operator == (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs == rhs.mValue;
   }

   template<TARGS(RHS), CT::Character N>
   LANGULUS(INLINED)
   constexpr bool operator == (const N& lhs, const TNUM(RHS)& rhs) noexcept requires (!CT::Same<RHSW, N>) {
      return lhs == rhs.mValue;
   }

} // namespace Langulus::Math
