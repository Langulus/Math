///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TGradient.hpp"
#include "Vectors/TVector.inl"
#include <Flow/Code.hpp>

#define TEMPLATE() template<CT::Dense T, Count S>
#define TME() TGradient<T, S>


namespace Langulus::Math
{

   /// Manual construction                                                    
   ///   @param initial - the initial value                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TGradient(const T& initial) noexcept {
      for (auto& i : mBuffer)
         i = initial;
   }
   
   /// Manual construction via a variadic head-tail                           
   TEMPLATE()
   template<class T1, class T2, class... TAIL>
   LANGULUS(INLINED)
   constexpr TME()::TGradient(const T1& t1, const T2& t2, const TAIL&... tail) noexcept
      : mBuffer {t1, t2, tail...} {}

   /// Access values in order of relevance (current value is at 0)            
   ///   @param index - the index                                             
   ///   @return a constant reference to the value                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto& TME()::operator [](const Offset& index) const noexcept {
      if (mIndex - index < S)
         return mBuffer[mIndex - index];
      return mBuffer[S - index];
   }

   /// Access values in order of relevance (current value is at 0)            
   ///   @param index - the index                                             
   ///   @return a reference to the value                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto& TME()::operator [](const Offset& index) noexcept {
      if (mIndex - index < S)
         return mBuffer[mIndex - index];
      return mBuffer[S - index];
   }

   /// Compare two gradients                                                  
   ///   @param other - the gradient to compare against                       
   ///   @return true if both gradients are the same                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::operator == (const TGradient& other) const noexcept {
      for (Offset i = 0; i < S; ++i) {
         if (mBuffer[i] != other.mBuffer[i])
            return false;
      }

      return true;
   }

   /// Revert                                                                 
   ///   @attention if size is too short you'll lose state                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr T& TME()::Revert() noexcept {
      --mIndex;
      if (mIndex >= S)
         mIndex = S - 1;

      Current() = Previous();
      return Current();
   }

   /// Progression                                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr T& TME()::Update() noexcept {
      // Move marker                                                    
      ++mIndex;
      if (mIndex >= S)
         mIndex = 0;

      // Initially, current value always equals previous                
      // You can modify it as many times you want before calling        
      // update again.                                                  
      Current() = Previous();
      return Current();
   }

   /// Get the current value                                                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr const T& TME()::Current() const noexcept {
      return mBuffer[mIndex];
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr T& TME()::Current() noexcept {
      return mBuffer[mIndex];
   }

   /// Get the previous value                                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr const T& TME()::Previous() const noexcept {
      return mIndex >= 1 ? mBuffer[mIndex - 1] : mBuffer[S - 1];
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr T& TME()::Previous() noexcept {
      return mIndex >= 1 ? mBuffer[mIndex - 1] : mBuffer[S - 1];
   }

   /// Get the last difference                                                
   ///   @return the difference between the last two states                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr T TME()::Delta() const {
      return Current() - Previous();
   }

   /// Get a projection in the future                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr T TME()::Project(const T& steps) const {
      return Current() + Delta() * steps;
   }

   /// Reset                                                                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr void TME()::Reset(const T& value) noexcept {
      for (auto& i : mBuffer)
         i = value;
      mIndex = 0;
   }

   /// Sum                                                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr T TME()::Sum() const noexcept {
      T sum = {};
      for (auto& i : mBuffer)
         sum += i;
      return sum;
   }

   /// Integrate/differentiate                                                
   TEMPLATE()
   void TME()::Integrate(Flow::Verb& verb) {
      if (verb.GetMass() > 0)
         verb << Sum();
      else if (verb.GetMass() < 0)
         verb << Delta();
   }

   /// Convert to text                                                        
   TEMPLATE()
   TME()::operator Flow::Code() const {
      using Flow::Code;
      Code result;
      result += NameOf<TGradient>();
      result += Code::Operator::OpenScope;
      for (Offset i = 0; i < S; ++i) {
         result += Anyness::Text {(*this)[i]};
         if (i < S - 1)
            result += ", ";
      }
      result += Code::Operator::CloseScope;
      return result;
   }

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME