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

   /// Modulation verb                                                        
   /// Performs arithmetic modulation                                         
   struct Modulate : ArithmeticVerb<Modulate, false> {
      LANGULUS(VERB) "Modulate";
      LANGULUS(OPERATOR) "%";
      LANGULUS(PRECEDENCE) 8;
      LANGULUS(INFO) "Performs arithmetic modulation";

      using ArithmeticVerb::ArithmeticVerb;

      template<CT::Dense T, CT::Data... A>
      static consteval bool AvailableFor() noexcept;
      template<CT::Dense T, CT::Data... A>
      static consteval auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);

      static bool ExecuteDefault(const Block&, Verb&);
      static bool ExecuteDefault(Block&, Verb&);

      template<CT::Data... T>
      static bool OperateOnTypes(const Block&, const Block&, Verb&);
      template<CT::Data... T>
      static bool OperateOnTypes(const Block&, Block&, Verb&);
   };

} // namespace Langulus::Verbs