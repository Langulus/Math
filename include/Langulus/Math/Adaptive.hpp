///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Level.hpp"


namespace Langulus::Math
{
   ///                                                                        
   /// Make any type adaptive, by sticking a Level member at the back and     
   /// scale properly by it on arithmetic operations.                         
   ///                                                                        
   template<class T>
   struct Adaptive {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<Adaptive>();
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
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Typed     = T;
      using CTTI_Adaptive  = Yup;

      // The data                                                       
      T mValue {};
      // The level in which the data is adapted to                      
      Level mLevel {};

   public:
      constexpr Adaptive() noexcept = default;
      constexpr Adaptive(T const& data, Level level = {}) noexcept
         : mValue {data}
         , mLevel {level} {}

      constexpr Adaptive& operator = (CT::Adaptive auto const& rhs) noexcept {
         mValue = DeintCast(rhs).mValue;
         mLevel = DeintCast(rhs).mLevel;
         return *this;
      }

      constexpr Adaptive& operator = (CT::NotAdaptive auto const& rhs) noexcept {
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
   Adaptive(T const&, Level) -> Adaptive<Deint<T>>;


   ///                                                                        
   ///   Operations on adaptives                                              
   ///                                                                        

   /// Returns an inverted number                                             
   template<CT::Adaptive T> requires CT::Signed<T>
   constexpr T operator - (T const&) noexcept;

   /// Returns the sum of two numbers                                         
   constexpr auto operator + (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS operator + (LHS const&, CT::NotAdaptive auto const&) noexcept;

   template<CT::Adaptive RHS>
   constexpr RHS operator + (CT::NotAdaptive auto const&, RHS const&) noexcept;

   /// Returns the difference of two numbers                                  
   constexpr auto operator - (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS operator - (LHS const&, CT::NotAdaptive auto const&) noexcept;

   template<CT::Adaptive RHS>
   constexpr RHS operator - (CT::NotAdaptive auto const&, RHS const&) noexcept;

   /// Returns the product of two numbers                                     
   constexpr auto operator * (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS operator * (LHS const&, CT::NotAdaptive auto const&) noexcept;

   template<CT::Adaptive RHS>
   constexpr RHS operator * (CT::NotAdaptive auto const&, RHS const&) noexcept;

   /// Returns the division of two numbers                                    
   constexpr auto operator / (CT::Adaptive auto const&, CT::Adaptive auto const&);

   template<CT::Adaptive LHS>
   constexpr LHS operator / (LHS const&, CT::NotAdaptive auto const&);

   template<CT::Adaptive RHS>
   constexpr RHS operator / (CT::NotAdaptive auto const&, RHS const&);
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Real, too   
   constexpr auto operator % (CT::Adaptive auto const&, CT::Adaptive auto const&);

   template<CT::Adaptive LHS>
   constexpr LHS operator % (LHS const&, CT::NotAdaptive auto const&);

   template<CT::Adaptive RHS>
   constexpr RHS operator % (CT::NotAdaptive auto const&, RHS const&);


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::Adaptive LHS>
   constexpr LHS& operator += (LHS&, CT::Adaptive auto const&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS& operator += (LHS&, CT::NotAdaptive auto const&) noexcept;

   /// Subtract                                                               
   template<CT::Adaptive LHS>
   constexpr LHS& operator -= (LHS&, CT::Adaptive auto const&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS& operator -= (LHS&, CT::NotAdaptive auto const&) noexcept;

   /// Multiply                                                               
   template<CT::Adaptive LHS>
   constexpr LHS& operator *= (LHS&, CT::Adaptive auto const&) noexcept;

   template<CT::Adaptive LHS>
   constexpr LHS& operator *= (LHS&, CT::NotAdaptive auto const&) noexcept;

   /// Divide                                                                 
   template<CT::Adaptive LHS>
   constexpr LHS& operator /= (LHS&, CT::Adaptive auto const&);

   template<CT::Adaptive LHS>
   constexpr LHS& operator /= (LHS&, CT::NotAdaptive auto const&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   constexpr bool operator <  (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;
   constexpr bool operator <  (CT::Adaptive auto const&, CT::NotAdaptive auto const&) noexcept;
   constexpr bool operator <  (CT::NotAdaptive auto const&, CT::Adaptive auto const&) noexcept;

   /// Bigger                                                                 
   constexpr bool operator >  (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;
   constexpr bool operator >  (CT::Adaptive auto const&, CT::NotAdaptive auto const&) noexcept;
   constexpr bool operator >  (CT::NotAdaptive auto const&, CT::Adaptive auto const&) noexcept;

   /// Bigger or equal                                                        
   constexpr bool operator >= (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;
   constexpr bool operator >= (CT::Adaptive auto const&, CT::NotAdaptive auto const&) noexcept;
   constexpr bool operator >= (CT::NotAdaptive auto const&, CT::Adaptive auto const&) noexcept;

   /// Smaller or equal                                                       
   constexpr bool operator <= (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;
   constexpr bool operator <= (CT::Adaptive auto const&, CT::NotAdaptive auto const&) noexcept;
   constexpr bool operator <= (CT::NotAdaptive auto const&, CT::Adaptive auto const&) noexcept;

   /// Equal                                                                  
   constexpr bool operator == (CT::Adaptive auto const&, CT::Adaptive auto const&) noexcept;
   constexpr bool operator == (CT::Adaptive auto const&, CT::NotAdaptive auto const&) noexcept;
   constexpr bool operator == (CT::NotAdaptive auto const&, CT::Adaptive auto const&) noexcept;
}

#include "Adaptive.inl"