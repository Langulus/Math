///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Exponent.hpp"
#include "Arithmetic.inl"

#if 0
   #define VERBOSE_EXP(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_EXP(...) LANGULUS(NOOP)
#endif


namespace Langulus::Verbs
{

   /// Compile-time check if a verb is implemented in the provided type       
   ///   @return true if verb is available                                    
   template<CT::Dense T, CT::Data...A>
   constexpr bool Exponent::AvailableFor() noexcept {
      if constexpr (sizeof...(A) == 0)
         return requires (T& t, Verb& v) { t.Exponent(v); };
      else
         return requires (T& t, Verb& v, A...a) { t.Exponent(v, a...); };
   }

   /// Get the verb functor for the given type and arguments                  
   ///   @return the function, or nullptr if not available                    
   template<CT::Dense T, CT::Data...A>
   constexpr auto Exponent::Of() noexcept {
      if constexpr (CT::Constant<T>) {
         return [](const void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<const T*>(context);
            typedContext->Exponent(verb, args...);
         };
      }
      else {
         return [](void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<T*>(context);
            typedContext->Exponent(verb, args...);
         };
      }
   }

   /// Execute the exponentiation/root verb in a specific context             
   ///   @param context - the context to execute in                           
   ///   @param verb - the verb to execute                                    
   ///   @return true if verb has been satisfied                              
   template<CT::Dense T>
   bool Exponent::ExecuteIn(T& context, Verb& verb) {
      static_assert(Exponent::AvailableFor<T>(),
         "Verb is not available for this context, this shouldn't be reached by flow");
      context.Exponent(verb);
      return verb.IsDone();
   }

   /// Operate in a number of types                                           
   ///   @tparam ...T - the list of types to operate on                       
   ///                  order matters!                                        
   ///   @param context - the original context                                
   ///   @param common - the base to operate on                               
   ///   @param verb - the original verb                                      
   ///   @return if at least one of the types matched verb                    
   template<CT::Data... T>
   bool Exponent::OperateOnTypes(const Many& context, const Many& common, Verb& verb) {
      return ((common.template CastsTo<T, true>()
         and ArithmeticVerb::Vector<T>(context, common, verb,
            verb.GetMass() < 0
               ? [](const T* lhs, const T* rhs) noexcept -> T {
                  return static_cast<T>(::std::pow(*lhs, T {1} / *rhs));
               }
               : [](const T* lhs, const T* rhs) noexcept -> T {
                  return static_cast<T>(::std::pow(*lhs, *rhs));
               }
         )) or ...);
   }

   /// Default power/root in an immutable context                             
   ///   @param context - the block to execute in                             
   ///   @param verb - power/root verb                                        
   inline bool Exponent::ExecuteDefault(const Many& context, Verb& verb) {
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

   /// Default power/root in mutable context                                  
   ///   @param context - the block to execute in                             
   ///   @param verb - power/root verb                                        
   inline bool Exponent::ExecuteDefault(Many& context, Verb& verb) {
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

#undef VERBOSE_EXP