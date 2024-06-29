///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Arithmetic.hpp"


namespace Langulus::Verbs
{
   using namespace Flow;


   ///                                                                        
   ///   Multiply/Divide verb                                                 
   /// Performs arithmetic multiplication or division                         
   /// If context is no specified, it is always 1                             
   ///                                                                        
   struct Multiply : ArithmeticVerb<Multiply, false> {
      LANGULUS(POSITIVE_VERB) "Multiply";
      LANGULUS(NEGATIVE_VERB) "Divide";
      LANGULUS(POSITIVE_OPERATOR) "*";
      LANGULUS(NEGATIVE_OPERATOR) "/";
      LANGULUS(PRECEDENCE) 5;
      LANGULUS(INFO)
         "Performs arithmetic multiplication or division. "
         "If context is not specified, it is always 1";

      using ArithmeticVerb::ArithmeticVerb;

      template<CT::Dense, CT::Data...>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense, CT::Data...>
      static constexpr auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);

      static bool ExecuteDefault(const Many&, Verb&);
      static bool ExecuteDefault(Many&, Verb&);
      static bool ExecuteStateless(Verb&);

      template<CT::Data...>
      static bool OperateOnTypes(const Many&, const Many&, Verb&);
      template<CT::Data...>
      static bool OperateOnTypes(const Many&, Many&, Verb&);
      template<CT::Data...>
      static bool OperateOnTypes(Many&, Verb&);
   };

} // namespace Langulus::Verbs