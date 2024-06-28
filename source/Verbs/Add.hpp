///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Arithmetic.hpp"


namespace Langulus::Verbs
{
   using namespace Flow;


   ///                                                                        
   ///   Add/Subtract verb                                                    
   /// Performs arithmetic addition or subtraction                            
   ///                                                                        
   struct Add : ArithmeticVerb<Add, true> {
      LANGULUS(POSITIVE_VERB) "Add";
      LANGULUS(NEGATIVE_VERB) "Subtract";
      LANGULUS(POSITIVE_OPERATOR) " + ";
      LANGULUS(NEGATIVE_OPERATOR) " - ";
      LANGULUS(PRECEDENCE) 4;
      LANGULUS(INFO)
         "Performs arithmetic addition or subtraction";

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