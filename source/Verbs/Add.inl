///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Add.hpp"
#include "Arithmetic.inl"

#if 0
   #define VERBOSE_ADD(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_ADD(...) LANGULUS(NOOP)
#endif


namespace Langulus::Verbs
{

   /// Compile-time check if a verb is implemented in the provided type       
   ///   @return true if verb is available                                    
   template<CT::Dense T, CT::Data...A>
   constexpr bool Add::AvailableFor() noexcept {
      if constexpr (sizeof...(A) == 0) {
         return requires (T& t, Verb& v) { t.Add(v); }
             or requires (T& t) { t += t; }
             or requires (T& t) { t -= t; }
             or requires (const T& t) { {t + t} -> CT::Same<T>; }
             or requires (const T& t) { {t - t} -> CT::Same<T>; };
      }
      else if constexpr (sizeof...(A) == 1) {
         return requires (T& t, Verb& v, A... a) { t.Add(v, a...); }
             or requires (T& t, A... a) { t += (a + ...); }
             or requires (T& t, A... a) { t -= (a - ...); }
             or requires (const T& t, A... a) { {t + (a + ...)} -> CT::Same<T>; }
             or requires (const T& t, A... a) { {t - (a + ...)} -> CT::Same<T>; };
      }
      else return requires (T& t, Verb& v, A... a) { t.Add(v, a...); };
   }

   /// Get the verb functor for the given type and arguments                  
   ///   @return the function, or nullptr if not available                    
   template<CT::Dense T, CT::Data...A>
   constexpr auto Add::Of() noexcept {
      if constexpr (CT::Constant<T>) {
         return [](const void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<const T*>(context);
            typedContext->Add(verb, args...);
         };
      }
      else {
         return [](void* context, Flow::Verb& verb, A...args) {
            auto typedContext = static_cast<T*>(context);
            typedContext->Add(verb, args...);
         };
      }
   }

   /// Execute the add/subtract verb in a specific context                    
   ///   @param context - the context to execute in                           
   ///   @param verb - the verb to execute                                    
   ///   @return true if verb has been satisfied                              
   template<CT::Dense T>
   bool Add::ExecuteIn(T& context, Verb& verb) {
      static_assert(Add::AvailableFor<T>(),
         "Verb is not available for this context, this shouldn't be reached by flow");
      context.Add(verb);
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
   bool Add::OperateOnTypes(const Many& context, const Many& common, Verb& verb) {
      return ((common.CastsTo<T, true>()
         and ArithmeticVerb::Vector<T>(context, common, verb,
            verb.GetMass() < 0
               ? [](const T* lhs, const T* rhs) noexcept -> T {
                  return *lhs - *rhs;
               }
               : [](const T* lhs, const T* rhs) noexcept -> T {
                  return *lhs + *rhs;
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
   template<CT::Data... T>
   bool Add::OperateOnTypes(const Many& context, Many& common, Verb& verb) {
      return ((common.CastsTo<T, true>()
         and ArithmeticVerb::Vector<T>(context, common, verb,
            verb.GetMass() < 0
               ? [](T* lhs, const T* rhs) noexcept {
                  *lhs -= *rhs;
               }
               : [](T* lhs, const T* rhs) noexcept {
                  *lhs += *rhs;
               }
         )) or ...);
   }

   /// Invert verb's arguments                                                
   ///   @tparam ...T - the list of types to operate on                       
   ///                  order matters!                                        
   ///   @param common - the base to operate on                               
   ///   @param verb - the original verb                                      
   ///   @return if at least one of the types matched verb                    
   template<CT::Data... T>
   bool Add::OperateOnTypes(Many& common, Verb& verb) {
      return ((common.template CastsTo<T, true>()
         and ArithmeticVerb::Scalar<T>(common, common, verb,
            [](T* lhs, const T*) noexcept {
               *lhs *= T {-1};
            }
         )) or ...);
   }

   /// Default add/subtract in an immutable context                           
   ///   @param context - the block to execute in                             
   ///   @param verb - add/subtract verb                                      
   inline bool Add::ExecuteDefault(const Many& context, Verb& verb) {
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

   /// Default add/subtract in mutable context                                
   ///   @param context - the block to execute in                             
   ///   @param verb - add/subtract verb                                      
   inline bool Add::ExecuteDefault(Many& context, Verb& verb) {
      auto common = context.ReinterpretAs(verb.GetArgument());
      if (common.template CastsTo<A::Number>()) {
         return OperateOnTypes<
            Float, Double,
            int32_t, uint32_t, int64_t, uint64_t,
            int8_t, uint8_t, int16_t, uint16_t
         >(context, common, verb);
      }

      return false;
   }

   /// A stateless subtraction                                                
   /// Basically negates rhs when mass is below zero, otherwise does nothing  
   ///   @param verb - the verb instance to execute                           
   ///   @return true if execution was a success                              
   inline bool Add::ExecuteStateless(Verb& verb) {
      if (verb.CastsTo<A::Number>()) {
         if (verb.GetMass() < 0) {
            // Negate signed numbers, otherwise verb is not satisfied   
            return OperateOnTypes<
               Float, Double,
               int32_t, int64_t,
               int8_t, int16_t
            >(verb, verb);
         }
         else {
            // Don't do anything                                        
            verb << verb.GetArgument();
            return true;
         }
      }

      return false;
   }

} // namespace Langulus::Verbs

#undef VERBOSE_ADD