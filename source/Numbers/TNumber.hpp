///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
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
   template<CT::Dense T, CT::Dense WRAPPER = T>
   struct TNumber {
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS_BASES(
         Conditional<CT::Real<T>
            , A::Real
            , Conditional<CT::Signed<T>, A::SignedInteger, A::UnsignedInteger>
         >
      );
      LANGULUS(TYPED) T;

      static constexpr Count MemberCount {1};

      T mValue {};

   public:
      constexpr TNumber() noexcept = default;
      constexpr TNumber(const TNumber&) noexcept = default;
      constexpr TNumber(TNumber&&) noexcept = default;

      constexpr TNumber(const T&) noexcept;
      constexpr TNumber(const WRAPPER&) noexcept requires (!CT::Same<T, WRAPPER>);
      template<class N>
      constexpr TNumber(const N&) noexcept requires CT::Convertible<N, T>;

      TNumber& operator = (const TNumber&) noexcept = default;
      TNumber& operator = (TNumber&&) noexcept = default;
      TNumber& operator = (const T&) noexcept;
      TNumber& operator = (const WRAPPER&) noexcept requires (!CT::Same<T, WRAPPER>);

      /// All conversions are explicit only, to preserve type                 
      constexpr explicit operator const T& () const noexcept;
      constexpr explicit operator T& () noexcept;

      operator Flow::Code() const;

      /// Prefix operators                                                    
      TNumber& operator ++ () noexcept;
      TNumber& operator -- () noexcept;

      /// Suffix operators                                                    
      NOD() TNumber operator ++ (int) noexcept;
      NOD() TNumber operator -- (int) noexcept;
   };

   /// A type-safe unsigned 8-bit integer, that won't get mistaken for a char 
   using uint8 = TNumber<::std::uint8_t>;


   ///                                                                        
   ///   Operations on numbers                                                
   ///                                                                        
   #define TARGS(a) CT::Dense a##T, CT::Dense a##W
   #define TNUM(a) TNumber<a##T, a##W>
   #define TEMPLATE() template<CT::Dense T, CT::Dense W>
   #define TME() TNumber<T, W>

   /// Returns an inverted number                                             
   template<TARGS(RHS)>
   NOD() constexpr auto operator - (const TNUM(RHS)&) noexcept requires CT::Signed<RHST>;

   /// Returns the sum of two numbers                                         
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator + (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr auto operator + (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr auto operator + (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Returns the difference of two numbers                                  
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator - (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;
    
   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr auto operator - (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr auto operator - (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Returns the product of two numbers                                     
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator * (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr auto operator * (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr auto operator * (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Returns the division of two numbers                                    
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator / (const TNUM(LHS)&, const TNUM(RHS)&) requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr auto operator / (const TNUM(LHS)&, const N&) requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr auto operator / (const N&, const TNUM(RHS)&) requires (!CT::Same<RHSW, N>);
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Real, too   
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator % (const TNUM(LHS)&, const TNUM(RHS)&) requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr auto operator % (const TNUM(LHS)&, const N&) requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr auto operator % (const N&, const TNUM(RHS)&) requires (!CT::Same<RHSW, N>);

   /// Returns the left-shift of two integer vectors                          
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator << (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>);

   template<TARGS(LHS), CT::DenseInteger N>
   NOD() constexpr auto operator << (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseInteger N>
   NOD() constexpr auto operator << (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Returns the right-shift of two integer vectors                         
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator >> (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires (CT::Integer<LHST, RHST>&& CT::Same<LHSW, RHSW>);

   template<TARGS(LHS), CT::DenseInteger N>
   NOD() constexpr auto operator >> (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseInteger N>
   NOD() constexpr auto operator >> (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Returns the xor of two integer vectors                                 
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr auto operator ^ (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires (CT::Integer<LHST, RHST>&& CT::Same<LHSW, RHSW>);

   template<TARGS(LHS), CT::DenseInteger N>
   NOD() constexpr auto operator ^ (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseInteger N>
   NOD() constexpr auto operator ^ (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator += (TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator += (TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   /// Subtract                                                               
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator -= (TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator -= (TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   /// Multiply                                                               
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator *= (TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator *= (TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   /// Divide                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   constexpr auto& operator /= (TNUM(LHS)&, const TNUM(RHS)&) requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   constexpr auto& operator /= (TNUM(LHS)&, const N&) requires (!CT::Same<LHSW, N>);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr bool operator < (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr bool operator < (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);
   template<TARGS(LHS), CT::Character N>
   NOD() constexpr bool operator < (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr bool operator < (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);
   template<TARGS(RHS), CT::Character N>
   NOD() constexpr bool operator < (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Bigger                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr bool operator > (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr bool operator > (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);
   template<TARGS(LHS), CT::Character N>
   NOD() constexpr bool operator > (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr bool operator > (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);
   template<TARGS(RHS), CT::Character N>
   NOD() constexpr bool operator > (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Bigger or equal                                                        
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr bool operator >= (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr bool operator >= (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);
   template<TARGS(LHS), CT::Character N>
   NOD() constexpr bool operator >= (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr bool operator >= (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);
   template<TARGS(RHS), CT::Character N>
   NOD() constexpr bool operator >= (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Smaller or equal                                                       
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr bool operator <= (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr bool operator <= (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);
   template<TARGS(LHS), CT::Character N>
   NOD() constexpr bool operator <= (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr bool operator <= (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);
   template<TARGS(RHS), CT::Character N>
   NOD() constexpr bool operator <= (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

   /// Equal                                                                  
   template<TARGS(LHS), TARGS(RHS)>
   NOD() constexpr bool operator == (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() constexpr bool operator == (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);
   template<TARGS(LHS), CT::Character N>
   NOD() constexpr bool operator == (const TNUM(LHS)&, const N&) noexcept requires (!CT::Same<LHSW, N>);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() constexpr bool operator == (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);
   template<TARGS(RHS), CT::Character N>
   NOD() constexpr bool operator == (const N&, const TNUM(RHS)&) noexcept requires (!CT::Same<RHSW, N>);

} // namespace Langulus::Math

#include "TNumber.inl"

#undef TARGS
#undef TNUM
#undef TEMPLATE
#undef TME
