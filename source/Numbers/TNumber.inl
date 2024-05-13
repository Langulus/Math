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

#define TEMPLATE()   template<CT::Dense T, CT::Dense W>
#define TME()        TNumber<T, W>


namespace Langulus::Math
{

   /// Construct from any number-convertible thing                            
   ///   @param a - value to set                                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TNumber(const CT::Number auto& a) noexcept {
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
   TME()& TME()::operator = (const CT::Number auto& a) noexcept {
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

   /// All conversions are explicit only, to preserve type                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::operator bool () const noexcept {
      return mValue != T {};
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
         result += Code::Operator::OpenScope;
         result += Code {mValue};
         result += Code::Operator::CloseScope;
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
   template<CT::CustomNumber T> requires CT::Signed<T> LANGULUS(INLINED)
   constexpr T operator - (const T& a) noexcept {
      return -FundamentalCast(a);
   }

   /// Returns the sum of two cunstom numbers (standing operator)             
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the sum, by picking the most concrete number                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr auto operator + (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) + FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) + FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) + FundamentalCast(rhs));
      }
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS operator + (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) + rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr RHS operator + (const N& lhs, const RHS& rhs) noexcept {
      return lhs + FundamentalCast(rhs);
   }

   /// Returns the difference of two numbers (standing operator)              
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the difference, picking a lossless type between the two      
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr auto operator - (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) - FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) - FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) - FundamentalCast(rhs));
      }
   }
    
   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS operator - (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) - rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr RHS operator - (const N& lhs, const RHS& rhs) noexcept {
      return lhs - FundamentalCast(rhs);
   }

   /// Returns the product of two numbers (standing operator)                 
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the product, picking a lossless type between the two         
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr auto operator * (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) * FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) * FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) * FundamentalCast(rhs));
      }
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS operator * (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) * rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr RHS operator * (const N& lhs, const RHS& rhs) noexcept {
      return lhs * FundamentalCast(rhs);
   }

   /// Returns the division of two numbers (standing operator)                
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the division, picking a lossless type between the two        
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr auto operator / (const LHS& lhs, const RHS& rhs) {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) / FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) / FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) / FundamentalCast(rhs));
      }
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS operator / (const LHS& lhs, const N& rhs) {
      return FundamentalCast(lhs) / rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr RHS operator / (const N& lhs, const RHS& rhs) {
      return lhs / FundamentalCast(rhs);
   }
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Reals, too  
   ///   @param lhs - left number                                             
   ///   @param rhs - right number                                            
   ///   @return the modulo, picking a lossless type between the two          
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr auto operator % (const LHS& lhs, const RHS& rhs) {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>) {
         if constexpr (CT::Integer<TypeOf<LHS>, TypeOf<RHS>>)
            return LHS {FundamentalCast(lhs) % FundamentalCast(rhs)};
         else {
            return LHS {FundamentalCast(lhs) - FundamentalCast(rhs)
               * ::std::floor(FundamentalCast(lhs) / FundamentalCast(rhs))};
         }
      }
      else if constexpr (CT::DerivedFrom<RHS, LHS>) {
         if constexpr (CT::Integer<TypeOf<LHS>, TypeOf<RHS>>)
            return RHS {FundamentalCast(lhs) % FundamentalCast(rhs)};
         else {
            return RHS {FundamentalCast(lhs) - FundamentalCast(rhs)
               * ::std::floor(FundamentalCast(lhs) / FundamentalCast(rhs))};
         }
      }
      else LANGULUS_ERROR("Incompatible custom numbers for modulation");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS operator % (const LHS& lhs, const N& rhs) {
      if constexpr (CT::Integer<TypeOf<LHS>, N>)
         return FundamentalCast(lhs) % rhs;
      else
         return FundamentalCast(lhs) - rhs * ::std::floor(FundamentalCast(lhs) / rhs);
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr RHS operator % (const N& lhs, const RHS& rhs) {
      if constexpr (CT::Integer<TypeOf<RHS>, N>)
         return lhs % FundamentalCast(rhs);
      else
         return lhs - FundamentalCast(rhs) * ::std::floor(lhs / FundamentalCast(rhs));
   }

   /// Returns the left-shift of two integer vectors                          
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> LANGULUS(INLINED)
   constexpr auto operator << (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) << FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) << FundamentalCast(rhs)};
      else
         LANGULUS_ERROR("Incompatible custom numbers for left bitshift");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N> LANGULUS(INLINED)
   constexpr LHS operator << (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) << rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N> LANGULUS(INLINED)
   constexpr RHS operator << (const N& lhs, const RHS& rhs) noexcept {
      return lhs << FundamentalCast(rhs);
   }

   /// Returns the right-shift of two integer vectors                         
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> LANGULUS(INLINED)
   constexpr auto operator >> (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) >> FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) >> FundamentalCast(rhs)};
      else
         LANGULUS_ERROR("Incompatible custom numbers for right bitshift");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N> LANGULUS(INLINED)
   constexpr LHS operator >> (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) >> rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N> LANGULUS(INLINED)
   constexpr RHS operator >> (const N& lhs, const RHS& rhs) noexcept {
      return lhs >> FundamentalCast(rhs);
   }

   /// Returns the xor of two integer vectors                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> LANGULUS(INLINED)
   constexpr auto operator ^ (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::Same<LHS, RHS> or CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) ^ FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) ^ FundamentalCast(rhs)};
      else
         LANGULUS_ERROR("Incompatible custom numbers for xor");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N> LANGULUS(INLINED)
   constexpr LHS operator ^ (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) ^ rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N> LANGULUS(INLINED)
   constexpr RHS operator ^ (const N& lhs, const RHS& rhs) noexcept {
      return lhs ^ FundamentalCast(rhs);
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr LHS& operator += (LHS& lhs, const RHS& rhs) noexcept {
      FundamentalCast(lhs) += FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS& operator += (LHS& lhs, const N& rhs) noexcept {
      FundamentalCast(lhs) += rhs;
      return lhs;
   }

   /// Subtract                                                               
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr LHS& operator -= (LHS& lhs, const RHS& rhs) noexcept {
      FundamentalCast(lhs) -= FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS& operator -= (LHS& lhs, const N& rhs) noexcept {
      FundamentalCast(lhs) -= rhs;
      return lhs;
   }

   /// Multiply                                                               
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr LHS& operator *= (LHS& lhs, const RHS& rhs) noexcept {
      FundamentalCast(lhs) *= FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS& operator *= (LHS& lhs, const N& rhs) noexcept {
      FundamentalCast(lhs) *= rhs;
      return lhs;
   }

   /// Divide                                                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr LHS& operator /= (LHS& lhs, const RHS& rhs) {
      FundamentalCast(lhs) /= FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr LHS& operator /= (LHS& lhs, const N& rhs) {
      FundamentalCast(lhs) /= rhs;
      return lhs;
   }


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr bool operator < (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) < FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator < (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) < rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator < (const N& lhs, const RHS& rhs) noexcept {
      return lhs < FundamentalCast(rhs);
   }

   /// Bigger                                                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr bool operator > (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) > FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator > (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) > rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator > (const N& lhs, const RHS& rhs) noexcept {
      return lhs > FundamentalCast(rhs);
   }

   /// Bigger or equal                                                        
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr bool operator >= (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) >= FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator >= (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) >= rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator >= (const N& lhs, const RHS& rhs) noexcept {
      return lhs >= FundamentalCast(rhs);
   }

   /// Smaller or equal                                                       
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr bool operator <= (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) <= FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator <= (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) <= rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator <= (const N& lhs, const RHS& rhs) noexcept {
      return lhs <= FundamentalCast(rhs);
   }

   /// Equal                                                                  
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(INLINED)
   constexpr bool operator == (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) == FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator == (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) == rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(INLINED)
   constexpr bool operator == (const N& lhs, const RHS& rhs) noexcept {
      return lhs == FundamentalCast(rhs);
   }

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME
