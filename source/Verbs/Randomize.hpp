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
   ///   Randomization verb                                                   
   ///                                                                        
   struct Randomize : ArithmeticVerb<Randomize, false> {
      LANGULUS(VERB) "Randomize";
      LANGULUS(OPERATOR) " rand ";
      LANGULUS(PRECEDENCE) 9;
      LANGULUS(INFO) "Performs randomization";

      using ArithmeticVerb::ArithmeticVerb;

      template<CT::Dense, CT::NotVoid...>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense, CT::NotVoid...>
      static constexpr auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);

      static bool ExecuteDefault(const Many&, Verb&);
      static bool ExecuteDefault(Many&, Verb&);

      template<CT::NotVoid...>
      static bool OperateOnTypes(const Many&, const Many&, Verb&);
      template<CT::NotVoid...>
      static bool OperateOnTypes(const Many&, Many&, Verb&);
   };

} // namespace Langulus::Verbs