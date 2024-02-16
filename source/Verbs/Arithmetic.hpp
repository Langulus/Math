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
#include <Flow/Verb.hpp>


namespace Langulus::Flow
{
   
   ///                                                                        
   /// Statically typed verb, used as CRTP for arithmetic verbs               
   ///                                                                        
   template<class VERB, bool NOEXCEPT>
   struct ArithmeticVerb : TVerb<VERB> {
      template<CT::Data T>
      using Operator = Conditional<NOEXCEPT,
         T(*)(const T*, const T*) noexcept, 
         T(*)(const T*, const T*)
      >;

      template<CT::Data T>
      using OperatorMutable = Conditional<NOEXCEPT,
         void(*)(T*, const T*) noexcept,
         void(*)(T*, const T*)
      >;

      using TVerb::TVerb;

      template<CT::Data T>
      static bool Vector(const Block&, const Block&, Verb&, Operator<T>) noexcept(NOEXCEPT);
      template<CT::Data T>
      static bool Vector(const Block&, Block&, Verb&, OperatorMutable<T>) noexcept(NOEXCEPT);

      template<CT::Data T>
      static bool Scalar(const Block&, const Block&, Verb&, Operator<T>) noexcept(NOEXCEPT);
      template<CT::Data T>
      static bool Scalar(const Block&, Block&, Verb&, OperatorMutable<T>) noexcept(NOEXCEPT);
   };

} // namespace Langulus::Flow