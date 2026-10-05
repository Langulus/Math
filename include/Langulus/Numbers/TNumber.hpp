///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/CT/POD.hpp>
#include <Langulus/CT/Nullable.hpp>
#include <Langulus/CT/Suffix.hpp>
#include <Langulus/CT/Real.hpp>
#include <Langulus/CT/Signed.hpp>
#include <Langulus/CT/CustomNumber.hpp>
#include <Langulus/CT/Derived.hpp>
#include <Langulus/CT/Lossless.hpp>
#include <Langulus/IntentOf.hpp>
#include <cmath>


namespace Langulus::Math
{
   /// An abstract number that depends on context. Defaults to Real.          
   struct Number {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Langulus::Real;
   };

   ///                                                                        
   ///   Custom number                                                        
   ///                                                                        
   /// Might seem pointless, but serves various kinds of purposes:            
   ///   1. Provides type-safety layer, that asserts underflows/overflows     
   ///      when building in safe-mode                                        
   ///   2. Provides consistent handling of infinities across all arithmetic  
   ///      types                                                             
   ///   3. Allows for character types to be considered CT::Number, without   
   ///      suffering the usual implicit conversion-to-text-hell              
   ///   4. Gives a layer for integration with langulus flows and verbs       
   ///   5. Makes all numbers equivalent to 1D vectors, and thus compatible   
   ///      with the CT::Vector concept                                       
   ///   6. Never allows for integer promotions, unless types differ, in      
   ///      which case type promotion goes to no futher than the bigger type: 
   ///      * Whenever you do int8 * int8, you get the truncated int8 as      
   ///        result, instead of an int - whatever comes in will come out!    
   ///      * Whenever you do int8 * int16, you get the truncated int16 as    
   ///        result, instead of an int - the better of the two is chosen,    
   ///        instead of silently promoting it to int32!                      
   ///   7. Allows for infinite precision numbers, floating bar, etc.         
   ///      alternatives to seamlessly integrate everywhere.                  
   #pragma pack(push, 1)
   template<class T>
   struct TNumber : Number {
      using CTTI_Abstract     = No;
      using CTTI_Number       = Yup;
      using CTTI_CustomNumber = Yup;
      using CTTI_Typed        = T;
      using CTTI_Suffix       = Yes<SuffixOf<T>()>;
      using CTTI_POD          = Maybe<CT::POD<T>>;
      using CTTI_Nullable     = Maybe<CT::Nullable<T>>;
      using CTTI_Real         = Maybe<CT::Real<T>>;
      using CTTI_Signed       = Maybe<CT::Signed<T>>;
      using CTTI_Bases        = Number;
      
      T mValue {};

   public:
      constexpr TNumber() noexcept = default;
      constexpr TNumber(TNumber const&) noexcept = default;
      constexpr TNumber(TNumber&&) noexcept = default;

      /// Construct from any number-convertible thing. Supports intents.      
      LANGULUS(ALWAYS_INLINED)
      constexpr TNumber(CT::Number auto const& a) noexcept
         : mValue {static_cast<T>(DeintCast(a))} {}

      TNumber& operator = (TNumber const&) noexcept = default;
      TNumber& operator = (TNumber&&) noexcept = default;

      /// Assign any number-convertible thing. Supports intents.              
      LANGULUS(ALWAYS_INLINED)
      TNumber& operator = (CT::Number auto const& a) noexcept {
         mValue = static_cast<T>(DeintCast(a));
         return *this;
      }

      /// All conversions are explicit only, to preserve type                 
      LANGULUS(ALWAYS_INLINED)
      constexpr explicit operator T const& () const noexcept {
         return mValue;
      }
      LANGULUS(ALWAYS_INLINED)
      constexpr explicit operator T& () noexcept {
         return mValue;
      }
      LANGULUS(ALWAYS_INLINED)
      constexpr explicit operator bool () const noexcept {
         return mValue != T {};
      }

      /// Prefix operators                                                    
      LANGULUS(ALWAYS_INLINED)
      TNumber& operator ++ () noexcept {
         ++mValue;
         return *this;
      }
      LANGULUS(ALWAYS_INLINED)
      TNumber& operator -- () noexcept {
         --mValue;
         return *this;
      }

      /// Suffix operators                                                    
      LANGULUS(ALWAYS_INLINED)
      TNumber operator ++ (int) noexcept {
         const auto backup = *this;
         operator ++ ();
         return backup;
      }
      LANGULUS(ALWAYS_INLINED)
      TNumber operator -- (int) noexcept {
         const auto backup = *this;
         operator -- ();
         return backup;
      }
   };
   #pragma pack(pop)
}

namespace Langulus::Math
{
   ///                                                                        
   ///   Operations with custom numbers                                       
   ///                                                                        

   /// Returns an inverted number (standing operator)                         
   template<CT::CustomNumber T> requires CT::Signed<T> LANGULUS(ALWAYS_INLINED)
   constexpr T operator - (const T& a) noexcept {
      return -FundamentalCast(a);
   }

   /// Returns the sum of two cunstom numbers (standing operator)             
   ///   @return the sum, picking a lossless type between the two             
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator + (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) + FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) + FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) + FundamentalCast(rhs));
      }
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator + (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) + rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator + (const N& lhs, const RHS& rhs) noexcept {
      return lhs + FundamentalCast(rhs);
   }

   /// Returns the difference of two numbers (standing operator)              
   ///   @return the difference, picking a lossless type between the two      
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator - (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) - FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) - FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) - FundamentalCast(rhs));
      }
   }
    
   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator - (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) - rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator - (const N& lhs, const RHS& rhs) noexcept {
      return lhs - FundamentalCast(rhs);
   }

   /// Returns the product of two numbers (standing operator)                 
   ///   @return the product, picking a lossless type between the two         
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator * (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) * FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) * FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) * FundamentalCast(rhs));
      }
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator * (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) * rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator * (const N& lhs, const RHS& rhs) noexcept {
      return lhs * FundamentalCast(rhs);
   }

   /// Returns the division of two numbers (standing operator)                
   ///   @return the division, picking a lossless type between the two        
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator / (const LHS& lhs, const RHS& rhs) {
      if constexpr (CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) / FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) / FundamentalCast(rhs)};
      else {
         using LOSSLESS = Lossless<TypeOf<LHS>, TypeOf<RHS>>;
         return static_cast<LOSSLESS>(FundamentalCast(lhs) / FundamentalCast(rhs));
      }
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator / (const LHS& lhs, const N& rhs) {
      return FundamentalCast(lhs) / rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator / (const N& lhs, const RHS& rhs) {
      return lhs / FundamentalCast(rhs);
   }
   
   /// Returns the remainder (a.k.a. modulation) of a division.               
   /// Augment c++ builtin types by providing % operators for reals as well.  
   ///   @return the modulo, picking a lossless type between the two          
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator % (const LHS& lhs, const RHS& rhs) {
      if constexpr (CT::DerivedFrom<LHS, RHS>) {
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
      else static_assert(false, "Incompatible custom numbers for modulation");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator % (const LHS& lhs, const N& rhs) {
      if constexpr (CT::Integer<TypeOf<LHS>, N>)
         return FundamentalCast(lhs) % rhs;
      else
         return FundamentalCast(lhs) - rhs * ::std::floor(FundamentalCast(lhs) / rhs);
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator % (const N& lhs, const RHS& rhs) {
      if constexpr (CT::Integer<TypeOf<RHS>, N>)
         return lhs % FundamentalCast(rhs);
      else
         return lhs - FundamentalCast(rhs) * ::std::floor(lhs / FundamentalCast(rhs));
   }

   /// Returns the left-shift of two integer vectors                          
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator << (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) << FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) << FundamentalCast(rhs)};
      else
         static_assert(false, "Incompatible custom numbers for left bitshift");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator << (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) << rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator << (const N& lhs, const RHS& rhs) noexcept {
      return lhs << FundamentalCast(rhs);
   }

   /// Returns the right-shift of two integer vectors                         
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator >> (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) >> FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) >> FundamentalCast(rhs)};
      else
         static_assert(false, "Incompatible custom numbers for right bitshift");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator >> (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) >> rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator >> (const N& lhs, const RHS& rhs) noexcept {
      return lhs >> FundamentalCast(rhs);
   }

   /// Returns the xor of two integer vectors                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> LANGULUS(ALWAYS_INLINED)
   constexpr auto operator ^ (const LHS& lhs, const RHS& rhs) noexcept {
      if constexpr (CT::DerivedFrom<LHS, RHS>)
         return LHS {FundamentalCast(lhs) ^ FundamentalCast(rhs)};
      else if constexpr (CT::DerivedFrom<RHS, LHS>)
         return RHS {FundamentalCast(lhs) ^ FundamentalCast(rhs)};
      else
         static_assert(false, "Incompatible custom numbers for xor");
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS operator ^ (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) ^ rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N> LANGULUS(ALWAYS_INLINED)
   constexpr RHS operator ^ (const N& lhs, const RHS& rhs) noexcept {
      return lhs ^ FundamentalCast(rhs);
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator += (LHS& lhs, const RHS& rhs) noexcept {
      FundamentalCast(lhs) += FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator += (LHS& lhs, const N& rhs) noexcept {
      FundamentalCast(lhs) += rhs;
      return lhs;
   }

   /// Subtract                                                               
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator -= (LHS& lhs, const RHS& rhs) noexcept {
      FundamentalCast(lhs) -= FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator -= (LHS& lhs, const N& rhs) noexcept {
      FundamentalCast(lhs) -= rhs;
      return lhs;
   }

   /// Multiply                                                               
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator *= (LHS& lhs, const RHS& rhs) noexcept {
      FundamentalCast(lhs) *= FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator *= (LHS& lhs, const N& rhs) noexcept {
      FundamentalCast(lhs) *= rhs;
      return lhs;
   }

   /// Divide                                                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator /= (LHS& lhs, const RHS& rhs) {
      FundamentalCast(lhs) /= FundamentalCast(rhs);
      return lhs;
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr LHS& operator /= (LHS& lhs, const N& rhs) {
      FundamentalCast(lhs) /= rhs;
      return lhs;
   }


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator < (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) < FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator < (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) < rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator < (const N& lhs, const RHS& rhs) noexcept {
      return lhs < FundamentalCast(rhs);
   }

   /// Bigger                                                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator > (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) > FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator > (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) > rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator > (const N& lhs, const RHS& rhs) noexcept {
      return lhs > FundamentalCast(rhs);
   }

   /// Bigger or equal                                                        
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator >= (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) >= FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator >= (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) >= rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator >= (const N& lhs, const RHS& rhs) noexcept {
      return lhs >= FundamentalCast(rhs);
   }

   /// Smaller or equal                                                       
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator <= (const LHS& lhs, const RHS& rhs) noexcept {
      return FundamentalCast(lhs) <= FundamentalCast(rhs);
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator <= (const LHS& lhs, const N& rhs) noexcept {
      return FundamentalCast(lhs) <= rhs;
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator <= (const N& lhs, const RHS& rhs) noexcept {
      return lhs <= FundamentalCast(rhs);
   }

   /// Equal                                                                  
   template<CT::CustomNumber LHS, CT::CustomNumber RHS> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator == (const LHS& lhs, const RHS& rhs) noexcept {
      using T = Lossless<decltype(FundamentalCast(lhs)), decltype(FundamentalCast(rhs))>;
      return static_cast<T>(FundamentalCast(lhs)) == static_cast<T>(FundamentalCast(rhs));
   }

   template<CT::CustomNumber LHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator == (const LHS& lhs, const N& rhs) noexcept {
      using T = Lossless<decltype(FundamentalCast(lhs)), N>;
      return static_cast<T>(FundamentalCast(lhs)) == static_cast<T>(rhs);
   }

   template<CT::CustomNumber RHS, CT::BuiltinNumber N> LANGULUS(ALWAYS_INLINED)
   constexpr bool operator == (const N& lhs, const RHS& rhs) noexcept {
      using T = Lossless<decltype(FundamentalCast(rhs)), N>;
      return static_cast<T>(lhs) == static_cast<T>(FundamentalCast(rhs));
   }
}