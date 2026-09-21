///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/TVerb.hpp>


///                                                                           
/// MARK: Exponent/Root                                                       
/// Performs exponentiation or root                                           
///                                                                           
LANGULUS_DEFINE_OPERATOR(Exponent, Root, "^", "^-", 6,
   "Performs exponentiation or root"
);


/*namespace Langulus::Verbs
{
   using namespace Flow;

   struct Exponent : ArithmeticVerb<Exponent, true> {
      LANGULUS(POSITIVE_VERB) "Exponent";
      LANGULUS(NEGATIVE_VERB) "Root";
      LANGULUS(POSITIVE_OPERATOR) "^";
      LANGULUS(NEGATIVE_OPERATOR) "^^";
      LANGULUS(PRECEDENCE) 6;
      LANGULUS(INFO) "Performs exponentiation or root";

      using ArithmeticVerb::ArithmeticVerb;*/

      /*template<CT::Dense, CT::NotVoid...>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense, CT::NotVoid...>
      static constexpr auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);*/

      /*static bool ExecuteDefault(const Many&, Verb&);
      static bool ExecuteDefault(Many&, Verb&);

      template<CT::NotVoid...>
      static bool OperateOnTypes(const Many&, const Many&, Verb&);
      template<CT::NotVoid...>
      static bool OperateOnTypes(const Many&, Many&, Verb&);
   };
}*/