///                                                                           
/// Langulus::Flow                                                            
/// Copyright(C) 2017 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Common.hpp"

namespace Langulus::Verbs
{

   ///                                                                        
   /// Move verb                                                              
   /// Performs spatial movement/rotation on a physical instance              
   ///                                                                        
   struct Move : public StaticVerb<Move> {
      LANGULUS(VERB) "Move";
      LANGULUS(INFO) "Performs spatial movement/scale/rotation on physical instances";

      template<CT::Dense T, CT::Data... A>
      static constexpr bool AvailableFor() noexcept;
      template<CT::Dense T, CT::Data... A>
      static constexpr auto Of() noexcept;

      template<CT::Dense T>
      static bool ExecuteIn(T&, Verb&);
   };

} // namespace Langulus::Verbs

#include "Move.inl"