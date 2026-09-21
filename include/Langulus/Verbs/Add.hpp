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
/// MARK: Add/Subtract                                                        
/// Performs arithmetic addition or subtraction                               
///                                                                           
LANGULUS_DEFINE_OPERATOR(Add, Subtract, " + ", " - ", 4,
   "Performs arithmetic addition or subtraction"
);

/*namespace Langulus::Verbs
{
   using namespace Flow;

   struct Add : ArithmeticVerb<Add, true> {
      LANGULUS(POSITIVE_VERB) "Add";
      LANGULUS(NEGATIVE_VERB) "Subtract";
      LANGULUS(POSITIVE_OPERATOR) " + ";
      LANGULUS(NEGATIVE_OPERATOR) " - ";
      LANGULUS(PRECEDENCE) 4;
      LANGULUS(INFO) "";

      using ArithmeticVerb::ArithmeticVerb;*/

      /*template<CT::Dense, CT::NotVoid...>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense, CT::NotVoid...>
      static constexpr auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);*/

      /*static bool ExecuteDefault(const Many&, Verb&);
      static bool ExecuteDefault(Many&, Verb&);
      static bool ExecuteStateless(Verb&);

      template<CT::NotVoid...>
      static bool OperateOnTypes(const Many&, const Many&, Verb&);
      template<CT::NotVoid...>
      static bool OperateOnTypes(const Many&, Many&, Verb&);
      template<CT::NotVoid...>
      static bool OperateOnTypes(Many&, Verb&);
   };
}*/