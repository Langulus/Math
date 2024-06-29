///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Common.hpp"


namespace Langulus::Verbs
{

   ///                                                                        
   /// Move verb                                                              
   /// Performs spatial movement/rotation/scaling on a physical instance      
   ///                                                                        
   struct Move : public TVerb<Move> {
      LANGULUS(VERB) "Move";
      LANGULUS(INFO) "Performs spatial movement/scale/rotation on physical instances";

      template<CT::Dense, CT::Data...>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense, CT::Data...>
      static constexpr auto Of() noexcept;

      static bool ExecuteIn(CT::Dense auto&, Verb&);
   };

} // namespace Langulus::Verbs

#include "Move.inl"