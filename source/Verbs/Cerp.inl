///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Cerp.hpp"
#include "Arithmetic.inl"
#include "../Functions/Arithmetics.hpp"

#if 0
   #define VERBOSE_CERP(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_CERP(...) LANGULUS(NOOP)
#endif


namespace Langulus::Verbs
{

   /// Compile-time check if a verb is implemented in the provided type       
   ///   @return true if verb is available                                    
   template<CT::Dense T, CT::Data...A>
   constexpr bool Cerp::AvailableFor() noexcept {
      if constexpr (sizeof...(A) == 1) {
         using A0 = FirstOf<A...>;
         return requires (T& t, Verb& v, A0 a) { t.Cerp(v, a); };
      }
      else return false;
   }

   /// Get the verb functor for the given type and arguments                  
   ///   @return the function, or nullptr if not available                    
   template<CT::Dense T, CT::Data...A>
   constexpr auto Cerp::Of() noexcept {
      if constexpr (CT::Constant<T>) {
         return [](const void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<const T*>(context);
            typedContext->Cerp(verb, args...);
         };
      }
      else {
         return [](void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<T*>(context);
            typedContext->Cerp(verb, args...);
         };
      }
   }

   /// Execute the modulate verb in a specific context                        
   ///   @param context - the context to execute in                           
   ///   @param verb - the verb to execute                                    
   ///   @return true if verb has been satisfied                              
   template<CT::Dense T>
   bool Cerp::ExecuteIn(T& context, Verb& verb) {
      static_assert(Cerp::AvailableFor<T>(),
         "Verb is not available for this context, this shouldn't be reached by flow");
      context.Cerp(verb);
      return verb.IsDone();
   }

   /// Operate in a number of types                                           
   ///   @tparam ...T - the list of types to operate on                       
   ///                  order matters!                                        
   ///   @param context - the original context                                
   ///   @param common - the base to operate on                               
   ///   @param verb - the original verb                                      
   ///   @return if at least one of the types matched verb                    
   template<CT::Data...T>
   bool Cerp::OperateOnTypes(const Many& context, const Many& common, Verb& verb) {
      return ((common.CastsTo<T, true>()
         and ArithmeticVerb::Vector<T>(
            context, common, verb,
            [](const T* lhs, const T* rhs) -> T {
               return Math::Mod(*lhs, *rhs);
            }
         )) or ...);
   }

   /// Operate in a number of types (destructive version)                     
   ///   @tparam ...T - the list of types to operate on                       
   ///                  order matters!                                        
   ///   @param context - the original context                                
   ///   @param common - the base to operate on                               
   ///   @param verb - the original verb                                      
   ///   @return if at least one of the types matched verb                    
   template<CT::Data...T>
   bool Cerp::OperateOnTypes(const Many& context, Many& common, Verb& verb) {
      return ((common.CastsTo<T, true>()
         and ArithmeticVerb::Vector<T>(
            context, common, verb,
            [](T* lhs, const T* rhs) {
               *lhs = Math::Mod(*lhs, *rhs);
            }
         )) or ...);
   }

   /// Default multiply/divide in an immutable context                        
   ///   @param context - the block to execute in                             
   ///   @param verb - multiply/divide verb                                   
   inline bool Cerp::ExecuteDefault(const Many& context, Verb& verb) {
      const auto common = context.ReinterpretAs(verb.GetArgument());
      if (common.template CastsTo<A::Number>()) {
         return OperateOnTypes<
            Float, Double,
            int32_t, uint32_t, int64_t, uint64_t,
            int8_t, uint8_t, int16_t, uint16_t
         >(context, common, verb);
      }

      return false;
   }

   /// Default multiply/divide in mutable context                             
   ///   @param context - the block to execute in                             
   ///   @param verb - multiply/divide verb                                   
   inline bool Cerp::ExecuteDefault(Many& context, Verb& verb) {
      const auto common = context.ReinterpretAs(verb.GetArgument());
      if (common.template CastsTo<A::Number>()) {
         return OperateOnTypes<
            Float, Double,
            int32_t, uint32_t, int64_t, uint64_t,
            int8_t, uint8_t, int16_t, uint16_t
         >(context, common, verb);
      }

      return false;
   }

} // namespace Langulus::Verbs

#undef VERBOSE_CERP