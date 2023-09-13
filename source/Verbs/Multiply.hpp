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

      template<CT::Dense T, CT::Data... A>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense T, CT::Data... A>
      static constexpr auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);

      static bool ExecuteDefault(const Block&, Verb&);
      static bool ExecuteDefault(Block&, Verb&);
      static bool ExecuteStateless(Verb&);

      template<CT::Data... T>
      static bool OperateOnTypes(const Block&, const Block&, Verb&);
      template<CT::Data... T>
      static bool OperateOnTypes(const Block&, Block&, Verb&);
      template<CT::Data... T>
      static bool OperateOnTypes(Block&, Verb&);
   };

} // namespace Langulus::Verbs