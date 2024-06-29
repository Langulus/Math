///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Numbers/Level.hpp"


namespace Langulus
{
   namespace Math
   {

      template<class T>
      struct Adaptive;

   } // namespace Langulus::Math

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// adaptive                                                            
      struct Adaptive {
         LANGULUS(ABSTRACT) true;
      };

   } // namespace Langulus::A

   namespace CT
   {
      /// Concept for detecting adaptive data                                 
      template<class...T>
      concept Adaptive = (DerivedFrom<T, A::Adaptive> and ...);

      /// Concept for detecting nonadaptive data                              
      template<class...T>
      concept NotAdaptive = ((not Adaptive<T>) and ...);
   }

   /// Custom name generator at compile-time for adaptive types               
   template<class T>
   consteval auto CustomName(Of<Math::Adaptive<T>>&&) noexcept {
      using CLASS = Math::Adaptive<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
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

   namespace Math
   {

      ///                                                                     
      ///   Make any type adaptive, by sticking a Level member at the back    
      /// and scale properly by it on arithmetic operations.                  
      ///                                                                     
      template<class T>
      struct Adaptive : A::Adaptive {
         LANGULUS(ABSTRACT) false;
         LANGULUS(NAME)  CustomNameOf<Adaptive>::Generate();
         LANGULUS(TYPED) T;
         LANGULUS_BASES(A::Adaptive);
         LANGULUS_CONVERTS_TO(Flow::Code);

         // The data                                                    
         T mValue {};
         // The level in which the data is adapted to                   
         Level mLevel {};

         constexpr Adaptive() noexcept = default;
         constexpr Adaptive(const T& data, Level level = {}) noexcept
            : mValue {data}
            , mLevel {level} {}

         constexpr Adaptive& operator = (const CT::Adaptive auto& rhs) noexcept {
            mValue = rhs.mValue;
            mLevel = rhs.mLevel;
            return *this;
         }

         template<CT::NotSemantic RHS> requires CT::NotAdaptive<RHS>
         constexpr Adaptive& operator = (const RHS& rhs) noexcept {
            mValue = rhs;
            return *this;
         }

         /// Convert from any force to text                                   
         NOD() explicit operator Flow::Code() const {
            return static_cast<Flow::Code>(mValue);
         }

         constexpr operator T& () const noexcept {
            return const_cast<T&>(mValue);
         }
      };

      template<class T>
      Adaptive(const T& data, Level level) -> Adaptive<Desem<T>>;

   } // namespace Langulus::Math

} // namespace Langulus

namespace Langulus::Math
{
   
   ///                                                                        
   ///   Operations on adaptives                                              
   ///                                                                        

   /// Returns an inverted number                                             
   template<CT::Adaptive T> requires CT::Signed<T>
   NOD() constexpr T operator - (const T&) noexcept;

   /// Returns the sum of two numbers                                         
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr auto operator + (const LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr LHS operator + (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr RHS operator + (const N&, const RHS&) noexcept;

   /// Returns the difference of two numbers                                  
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr auto operator - (const LHS&, const RHS&) noexcept;
    
   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr LHS operator - (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr RHS operator - (const N&, const RHS&) noexcept;

   /// Returns the product of two numbers                                     
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr auto operator * (const LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr LHS operator * (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr RHS operator * (const N&, const RHS&) noexcept;

   /// Returns the division of two numbers                                    
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr auto operator / (const LHS&, const RHS&);

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr LHS operator / (const LHS&, const N&);

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr RHS operator / (const N&, const RHS&);
   
   /// Returns the remainder (a.k.a. modulation) of a division                
   /// We augment c++ builtin types, by providing % operators for Real, too   
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr auto operator % (const LHS&, const RHS&);

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr LHS operator % (const LHS&, const N&);

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr RHS operator % (const N&, const RHS&);


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   constexpr LHS& operator += (LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   constexpr LHS& operator += (LHS&, const N&) noexcept;

   /// Subtract                                                               
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   constexpr LHS& operator -= (LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   constexpr LHS& operator -= (LHS&, const N&) noexcept;

   /// Multiply                                                               
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   constexpr LHS& operator *= (LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   constexpr LHS& operator *= (LHS&, const N&) noexcept;

   /// Divide                                                                 
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   constexpr LHS& operator /= (LHS&, const RHS&);

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   constexpr LHS& operator /= (LHS&, const N&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr bool operator < (const LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr bool operator < (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr bool operator < (const N&, const RHS&) noexcept;

   /// Bigger                                                                 
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr bool operator > (const LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr bool operator > (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr bool operator > (const N&, const RHS&) noexcept;

   /// Bigger or equal                                                        
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr bool operator >= (const LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr bool operator >= (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr bool operator >= (const N&, const RHS&) noexcept;

   /// Smaller or equal                                                       
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr bool operator <= (const LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr bool operator <= (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr bool operator <= (const N&, const RHS&) noexcept;

   /// Equal                                                                  
   template<CT::Adaptive LHS, CT::Adaptive RHS>
   NOD() constexpr bool operator == (const LHS&, const RHS&) noexcept;

   template<CT::Adaptive LHS, CT::NotAdaptive N>
   NOD() constexpr bool operator == (const LHS&, const N&) noexcept;

   template<CT::Adaptive RHS, CT::NotAdaptive N>
   NOD() constexpr bool operator == (const N&, const RHS&) noexcept;

} // namespace Langulus::Math

#include "Adaptive.inl"