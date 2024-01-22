///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TNumber.hpp"
#include <Flow/Verbs/Interpret.hpp>

#define TARGS(a) CT::Dense a##T, CT::Dense a##W
#define TNUM(a) TNumber<a##T, a##W>
#define TEMPLATE() template<CT::Dense T, CT::Dense W>
#define TME() TNumber<T, W>


namespace Langulus::Math
{

   /// Construct from any number-convertible thing                            
   ///   @param a - value to set                                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TNumber(const CT::DenseNumber auto& a) noexcept {
      using ALT = Deref<decltype(a)>;
      if constexpr (CT::Same<T, ALT>)
         mValue = a;
      else if constexpr (CT::Same<W, ALT>)
         mValue = a.mValue;
      else if constexpr (CT::Convertible<ALT, T>)
         mValue = static_cast<T>(a);
      else LANGULUS_ERROR("Bad number construction");
   }

   /// Assign any number-convertible thing                                    
   ///   @param a - value to set                                              
   ///   @return a reference to this number                                   
   TEMPLATE() LANGULUS(INLINED)
   TME()& TME()::operator = (const CT::DenseNumber auto& a) noexcept {
      using ALT = Deref<decltype(a)>;
      if constexpr (CT::Same<T, ALT>)
         mValue = a;
      else if constexpr (CT::Same<W, ALT>)
         mValue = a.mValue;
      else if constexpr (CT::Convertible<ALT, T>)
         mValue = static_cast<T>(a);
      else LANGULUS_ERROR("Bad number assignment");
      return *this;
   }

   /// All conversions are explicit only, to preserve type                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::operator const T& () const noexcept {
      return mValue;
   }

   /// All conversions are explicit only, to preserve type                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::operator T& () noexcept {
      return mValue;
   }

   /// Stringify the number                                                   
   ///   @return a string                                                     
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      using Flow::Code;
      Code result;
      if constexpr (CT::Same<T, W>)
         result += Code {mValue};
      else {
         result += MetaDataOf<W>();
         result += Code::OpenScope;
         result += Code {mValue};
         result += Code::CloseScope;
      }
      return result;
   }

   /// Prefix increment operator                                              
   ///   @return the modified value                                           
   TEMPLATE() LANGULUS(INLINED)
   TME()& TME()::operator ++ () noexcept {
      ++mValue;
      return *this;
   }

   /// Prefix decrement operator                                              
   ///   @return the modified value                                           
   TEMPLATE() LANGULUS(INLINED)
   TME()& TME()::operator -- () noexcept {
      --mValue;
      return *this;
   }

   /// Suffix increment operator                                              
   ///   @return the previous value                                           
   TEMPLATE() LANGULUS(INLINED)
   TME() TME()::operator ++ (int) noexcept {
      const auto backup = *this;
      operator ++ ();
      return backup;
   }

   /// Suffix decrement operator                                              
   ///   @return the previous value                                           
   TEMPLATE() LANGULUS(INLINED)
   TME() TME()::operator -- (int) noexcept {
      const auto backup = *this;
      operator -- ();
      return backup;
   }

   /// Returns an inverted number (standing operator)                         
   ///   @param a - number to invert                                          
   template<TARGS(RHS)>
   LANGULUS(INLINED)
   constexpr auto operator - (const TNUM(RHS)& a) noexcept requires CT::Signed<RHST> {
      return TNUM(RHS) {-a.mValue};
   }

   /// Returns the sum of two numbers (standing operator)                     
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the addition, picking a lossless type between the two        
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

   /// Returns the difference of two numbers (standing operator)              
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the difference, picking a lossless type between the two      
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

   /// Returns the product of two numbers (standing operator)                 
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the product, picking a lossless type between the two         
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

   /// Returns the division of two numbers (standing operator)                
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the division, picking a lossless type between the two        
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
   /// We augment c++ builtin types, by providing % operators for Reals, too  
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the modulo, picking a lossless type between the two          
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

#undef TARGS
#undef TNUM
#undef TEMPLATE
#undef TME
