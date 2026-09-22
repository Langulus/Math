///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Numbers/Level.hpp"


namespace Langulus::Math
{

   ///                                                                        
   ///   Make any type adaptive, by sticking a Level member at the back and   
   /// scale properly by it on arithmetic operations.                         
   ///                                                                        
   template<class T>
   struct Adaptive {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = RTTI::LastCppNameOf<Adaptive>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset = 0;

         // Write prefix                                                
         for (auto i : "Adaptive")
            name[offset++] = i;
         --offset;

         // Write the rest                                              
         for (auto i : NameOf<T>())
            name[offset++] = i;
         return name;
      }

   public:
      LANGULUS(NAME)     GenerateToken();
      LANGULUS(ABSTRACT) false;
      LANGULUS(TYPED)    T;
      LANGULUS_CONVERTS_TO(Flow::Code);
      static constexpr bool CTTI_AdaptiveTrait = true;

      // The data                                                       
      T mValue {};
      // The level in which the data is adapted to                      
      Level mLevel {};

   public:
      constexpr Adaptive() noexcept = default;
      constexpr Adaptive(const T& data, Level level = {}) noexcept
         : mValue {data}
         , mLevel {level} {}

      constexpr Adaptive& operator = (const CT::Adaptive auto& rhs) noexcept {
         mValue = DeintCast(rhs).mValue;
         mLevel = DeintCast(rhs).mLevel;
         return *this;
      }

      constexpr Adaptive& operator = (const CT::NotAdaptive auto& rhs) noexcept {
         mValue = DeintCast(rhs);
         return *this;
      }

      /// Convert from any force to text                                      
      explicit operator Flow::Code() const {
         return static_cast<Flow::Code>(mValue);
      }

      constexpr operator T& () const noexcept {
         return const_cast<T&>(mValue);
      }

      constexpr T GetMidref(Level) const noexcept;
   };

   template<class T>
   Adaptive(const T&, Level) -> Adaptive<Deint<T>>;


   ///                                                                        
   ///   Operations on adaptives                                              
   ///                                                                        

   /// Returns an inverted number                                             
   template<CT::Adaptive T> requires CT::Signed<T>
   constexpr T operator - (const T&) noexcept;

   /// Returns the sum of two numbers                                         
   constexpr auto operator + (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS operator + (const LHS&, const CT::NotAdaptive auto&) noexcept;

   template<CT::Adaptive RHS>
   constexpr RHS operator + (const CT::NotAdaptive auto&, const RHS&) noexcept;

   /// Returns the difference of two numbers                                  
   constexpr auto operator - (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS operator - (const LHS&, const CT::NotAdaptive auto&) noexcept;

   template<CT::Adaptive RHS>
   constexpr RHS operator - (const CT::NotAdaptive auto&, const RHS&) noexcept;

   /// Returns the product of two numbers                                     
   constexpr auto operator * (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS operator * (const LHS&, const CT::NotAdaptive auto&) noexcept;

   template<CT::Adaptive RHS>
   constexpr RHS operator * (const CT::NotAdaptive auto&, const RHS&) noexcept;

   /// Returns the division of two numbers                                    
   constexpr auto operator / (const CT::Adaptive auto&, const CT::Adaptive auto&);

   template<CT::Adaptive LHS>
   constexpr LHS operator / (const LHS&, const CT::NotAdaptive auto&);

   template<CT::Adaptive RHS>
   constexpr RHS operator / (const CT::NotAdaptive auto&, const RHS&);
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Real, too   
   constexpr auto operator % (const CT::Adaptive auto&, const CT::Adaptive auto&);

   template<CT::Adaptive LHS>
   constexpr LHS operator % (const LHS&, const CT::NotAdaptive auto&);

   template<CT::Adaptive RHS>
   constexpr RHS operator % (const CT::NotAdaptive auto&, const RHS&);


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::Adaptive LHS>
   constexpr LHS& operator += (LHS&, const CT::Adaptive auto&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS& operator += (LHS&, const CT::NotAdaptive auto&) noexcept;

   /// Subtract                                                               
   template<CT::Adaptive LHS>
   constexpr LHS& operator -= (LHS&, const CT::Adaptive auto&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS& operator -= (LHS&, const CT::NotAdaptive auto&) noexcept;

   /// Multiply                                                               
   template<CT::Adaptive LHS>
   constexpr LHS& operator *= (LHS&, const CT::Adaptive auto&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS& operator *= (LHS&, const CT::NotAdaptive auto&) noexcept;

   /// Divide                                                                 
   template<CT::Adaptive LHS>
   constexpr LHS& operator /= (LHS&, const CT::Adaptive auto&);

   template<CT::Adaptive LHS>
   constexpr LHS& operator /= (LHS&, const CT::NotAdaptive auto&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   constexpr bool operator <  (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;
   constexpr bool operator <  (const CT::Adaptive auto&, const CT::NotAdaptive auto&) noexcept;
   constexpr bool operator <  (const CT::NotAdaptive auto&, const CT::Adaptive auto&) noexcept;

   /// Bigger                                                                 
   constexpr bool operator >  (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;
   constexpr bool operator >  (const CT::Adaptive auto&, const CT::NotAdaptive auto&) noexcept;
   constexpr bool operator >  (const CT::NotAdaptive auto&, const CT::Adaptive auto&) noexcept;

   /// Bigger or equal                                                        
   constexpr bool operator >= (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;
   constexpr bool operator >= (const CT::Adaptive auto&, const CT::NotAdaptive auto&) noexcept;
   constexpr bool operator >= (const CT::NotAdaptive auto&, const CT::Adaptive auto&) noexcept;

   /// Smaller or equal                                                       
   constexpr bool operator <= (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;
   constexpr bool operator <= (const CT::Adaptive auto&, const CT::NotAdaptive auto&) noexcept;
   constexpr bool operator <= (const CT::NotAdaptive auto&, const CT::Adaptive auto&) noexcept;

   /// Equal                                                                  
   constexpr bool operator == (const CT::Adaptive auto&, const CT::Adaptive auto&) noexcept;
   constexpr bool operator == (const CT::Adaptive auto&, const CT::NotAdaptive auto&) noexcept;
   constexpr bool operator == (const CT::NotAdaptive auto&, const CT::Adaptive auto&) noexcept;

} // namespace Langulus::Math

#include "Adaptive.inl"