///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Verbs/Add.hpp"
#include "Verbs/Cerp.hpp"
#include "Verbs/Exponent.hpp"
#include "Verbs/Lerp.hpp"
#include "Verbs/Modulate.hpp"
#include "Verbs/Multiply.hpp"
#include "Verbs/Randomize.hpp"
#include "Verbs/Move.hpp"


namespace Langulus::Math
{

   /// Register verbs                                                         
   inline void RegisterVerbs() {
      (void)MetaVerb::Of<Verbs::Exponent>();
      (void)MetaVerb::Of<Verbs::Multiply>();
      (void)MetaVerb::Of<Verbs::Modulate>();
      (void)MetaVerb::Of<Verbs::Randomize>();
      (void)MetaVerb::Of<Verbs::Add>();
      (void)MetaVerb::Of<Verbs::Lerp>();
      (void)MetaVerb::Of<Verbs::Cerp>();
      (void)MetaVerb::Of<Verbs::Move>();
   }

} // namespace Langulus::Math