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
   /// Linear interpolation verb                                              
   ///                                                                        
   struct Lerp : ArithmeticVerb<Modulate, false> {
      LANGULUS(VERB) "Lerp";
      LANGULUS(PRECEDENCE) 10;
      LANGULUS(INFO) "Performs linear interpolation";

      using ArithmeticVerb::ArithmeticVerb;

      template<CT::Dense, CT::Data...>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense, CT::Data...>
      static constexpr auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);

      static bool ExecuteDefault(const Many&, Verb&);
      static bool ExecuteDefault(Many&, Verb&);

      template<CT::Data...>
      static bool OperateOnTypes(const Many&, const Many&, Verb&);
      template<CT::Data...>
      static bool OperateOnTypes(const Many&, Many&, Verb&);
   };

} // namespace Langulus::Verbs