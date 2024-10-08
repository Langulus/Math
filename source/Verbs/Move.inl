///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Move.hpp"
#include "Arithmetic.inl"

#if 0
   #define VERBOSE_MOVE(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_MOVE(...) LANGULUS(NOOP)
#endif


namespace Langulus::Verbs
{

   /// Compile-time check if a verb is implemented in the provided type       
   ///   @return true if verb is available                                    
   template<CT::Dense T, CT::Data...A>
   constexpr bool Move::AvailableFor() noexcept {
      if constexpr (sizeof...(A) == 0)
         return requires (T& t, Verb& v) { t.Move(v); };
      else
         return requires (T& t, Verb& v, A...a) { t.Move(v, a...); };
   }

   /// Get the verb functor for the given type and arguments                  
   ///   @return the function, or nullptr if not available                    
   template<CT::Dense T, CT::Data...A>
   constexpr auto Move::Of() noexcept {
      if constexpr (CT::Constant<T>) {
         return [](const void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<const T*>(context);
            typedContext->Move(verb, args...);
         };
      }
      else {
         return [](void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<T*>(context);
            typedContext->Move(verb, args...);
         };
      }
   }

   /// Execute the modulate verb in a specific context                        
   ///   @param context - the context to execute in                           
   ///   @param verb - the verb to execute                                    
   ///   @return true if verb has been satisfied                              
   template<CT::Dense T>
   bool Move::ExecuteIn(T& context, Verb& verb) {
      static_assert(Move::AvailableFor<T>(),
         "Verb is not available for this context, "
         "this shouldn't be reached by flow");
      context.Move(verb);
      return verb.IsDone();
   }

} // namespace Langulus::Verbs

#undef VERBOSE_MOVE