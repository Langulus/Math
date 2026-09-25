///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Langulus/CT/Able.hpp"
#include <Langulus/Verbs/Randomize.hpp>
#include <Langulus/TMany.hpp>

#if 0
   #define VERBOSE_RAND(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_RAND(...) LANGULUS(NOOP)
#endif


namespace Langulus::CTTI
{
   template<class T>
   concept ManualRandomizable = requires (T const& t, Verb& v) { t.Randomize(v); }
                             or requires (T& t,       Verb& v) { t.Randomize(v); };


   /// Imbue all types with Randomize method with the ability to randomize    
   LglsImplementAbilitiesForConcept(ManualRandomizable, LHS) {
      using Can = Verbs::Randomize;

      /// Just use the provided method                                        
      static bool Default(LHS&& lhs, CT::Executable auto& verb) {
         lhs.Randomize(verb);
         return verb.IsDone();
      }
   };

   //TODO add the arithmetic types that can use std
}

#undef VERBOSE_RAND