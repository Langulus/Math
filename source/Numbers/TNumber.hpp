///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Common.hpp"


namespace Langulus::Math
{

   ///                                                                        
   ///   Templated number                                                     
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
   ///   -  Whenever you do int8 * int8, you get the truncated int8 as result,
   ///      instead of an int - whatever comes in will come out!              
   ///   -  Whenever you do int8 * int16, you get the truncated int16 as      
   ///      result, instead of an int - the better of the two is chosen!      
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::Dense T, CT::Dense WRAPPER = T>
   struct TNumber {
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS(TYPED) T;
      LANGULUS(SUFFIX) SuffixOf<T>();
      LANGULUS_BASES(
         Conditional<CT::Real<T>
            , A::Real
            , Conditional<CT::Signed<T>
               , A::SignedInteger
               , A::UnsignedInteger>>);
      LANGULUS_CONVERTS_TO(Flow::Code);

      static constexpr Count MemberCount = 1;

      T mValue {};

   public:
      constexpr TNumber() noexcept = default;
      constexpr TNumber(const TNumber&) noexcept = default;
      constexpr TNumber(TNumber&&) noexcept = default;
      constexpr TNumber(const CT::Number auto&) noexcept;

      TNumber& operator = (const TNumber&) noexcept = default;
      TNumber& operator = (TNumber&&) noexcept = default;
      TNumber& operator = (const CT::Number auto&) noexcept;

      /// All conversions are explicit only, to preserve type                 
      constexpr explicit operator const T& () const noexcept;
      constexpr explicit operator T& () noexcept;
      constexpr explicit operator bool () const noexcept;

      operator Flow::Code() const;

      /// Prefix operators                                                    
      TNumber& operator ++ () noexcept;
      TNumber& operator -- () noexcept;

      /// Suffix operators                                                    
      NOD() TNumber operator ++ (int) noexcept;
      NOD() TNumber operator -- (int) noexcept;
   };
   #pragma pack(pop)



   ///                                                                        
   ///   Operations on numbers                                                
   ///                                                                        

   /// Returns an inverted number                                             
   template<CT::CustomNumber T> requires CT::Signed<T>
   NOD() constexpr T operator - (const T&) noexcept;

   /// Returns the sum of two numbers                                         
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr auto operator + (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr LHS operator + (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr RHS operator + (const N&, const RHS&) noexcept;

   /// Returns the difference of two numbers                                  
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr auto operator - (const LHS&, const RHS&) noexcept;
    
   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr LHS operator - (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr RHS operator - (const N&, const RHS&) noexcept;

   /// Returns the product of two numbers                                     
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr auto operator * (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr LHS operator * (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr RHS operator * (const N&, const RHS&) noexcept;

   /// Returns the division of two numbers                                    
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr auto operator / (const LHS&, const RHS&);

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr LHS operator / (const LHS&, const N&);

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr RHS operator / (const N&, const RHS&);
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Real, too   
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr auto operator % (const LHS&, const RHS&);

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr LHS operator % (const LHS&, const N&);

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr RHS operator % (const N&, const RHS&);

   /// Returns the left-shift of two integer vectors                          
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>
   NOD() constexpr auto operator << (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N>
   NOD() constexpr LHS operator << (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N>
   NOD() constexpr RHS operator << (const N&, const RHS&) noexcept;

   /// Returns the right-shift of two integer vectors                         
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>
   NOD() constexpr auto operator >> (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N>
   NOD() constexpr LHS operator >> (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N>
   NOD() constexpr RHS operator >> (const N&, const RHS&) noexcept;

   /// Returns the xor of two integer vectors                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>
   NOD() constexpr auto operator ^ (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<LHS>, N>
   NOD() constexpr LHS operator ^ (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   requires CT::Integer<TypeOf<RHS>, N>
   NOD() constexpr RHS operator ^ (const N&, const RHS&) noexcept;


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   constexpr LHS& operator += (LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   constexpr LHS& operator += (LHS&, const N&) noexcept;

   /// Subtract                                                               
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   constexpr LHS& operator -= (LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   constexpr LHS& operator -= (LHS&, const N&) noexcept;

   /// Multiply                                                               
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   constexpr LHS& operator *= (LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   constexpr LHS& operator *= (LHS&, const N&) noexcept;

   /// Divide                                                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   constexpr LHS& operator /= (LHS&, const RHS&);

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   constexpr LHS& operator /= (LHS&, const N&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr bool operator < (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator < (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator < (const N&, const RHS&) noexcept;

   /// Bigger                                                                 
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr bool operator > (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator > (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator > (const N&, const RHS&) noexcept;

   /// Bigger or equal                                                        
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr bool operator >= (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator >= (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator >= (const N&, const RHS&) noexcept;

   /// Smaller or equal                                                       
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr bool operator <= (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator <= (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator <= (const N&, const RHS&) noexcept;

   /// Equal                                                                  
   template<CT::CustomNumber LHS, CT::CustomNumber RHS>
   NOD() constexpr bool operator == (const LHS&, const RHS&) noexcept;

   template<CT::CustomNumber LHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator == (const LHS&, const N&) noexcept;

   template<CT::CustomNumber RHS, CT::BuiltinNumber N>
   NOD() constexpr bool operator == (const N&, const RHS&) noexcept;

} // namespace Langulus::Math
