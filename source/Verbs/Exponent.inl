///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/Verbs/Exponent.hpp>
#include <Langulus/Verbs/Multiply.hpp>
#include <Langulus/TMany.hpp>

#if 0
   #define VERBOSE_EXP(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_EXP(...) LANGULUS(NOOP)
#endif


namespace Langulus::CTTI
{
   template<class T>
   concept BuiltinExponentiable = requires (T const& t) {
      {::std::pow(t,t)} -> ::std::same_as<T>;
   };

   /// Imbue all arithmetic types with the ability to exponentiate or root.   
   /// Tetration included via mass modifiers.                                 
   //TODO Implement the same ability from Vulkan POV in order to utilize GPU. 
   //TODO Each module reflects its own verbs. We can inspect these verbs at   
   //TODO runtime and decide which implementation to use depending on context.
   LglsImplementAbilitiesForConcept(BuiltinExponentiable, LHS) {
      using Can = Verbs::Exponent;

      /// Destructive version, LHS is mutable. This won't allocate unless     
      /// conversion occurs.                                                  
      static bool Default(LHS& lhs, CT::Executable auto& verb) {
         auto const mass = static_cast<LHS>(verb.GetMass());
         auto const& rhs = verb.GetArgument();
         if (rhs.template IsSame<LHS>()) {
            // Easy path - types are the same                           
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(rhs);
            Inner(mass, lhs, rhs_typed);
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            Inner(mass, lhs, converted);
            return true;
         }
      }
       
      /// Non-destructive version, LHS is constant. Will allocate if          
      /// conversion occurs, or if verb output isn't reserved enough.         
      static bool Default(LHS const& lhs, CT::Executable auto& verb) {
         auto const mass = static_cast<LHS>(verb.GetMass());
         auto const& rhs = verb.GetArgument();
         auto result = lhs;
         if (rhs.template IsSame<LHS>()) {
            // Easy path - types are the same                           
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(rhs);
            Inner(mass, result, rhs_typed);
            verb << result;
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            Inner(mass, result, converted);
            verb << result;
            return true;
         }
      }

   private:
      /// Common helper                                                       
      static void Inner(LHS const mass, LHS& lhs, TMany<LHS> const& rhs) noexcept {
         if (mass > 0) {
            // Raise to a power                                         
            for (LHS const& i : rhs) {
               auto m = mass;
               while(m > 0) {
                  lhs = ::std::pow(lhs, i);
                  m -= 1;
               }
            }
         }
         else {
            // Root                                                     
            for (LHS const& i : rhs) {
               auto m = mass;
               auto inverse = LHS{1} / i;
               while(m < 0) {
                  lhs = ::std::pow(lhs, inverse);
                  m += 1;
               }
            }
         }
      }
   };
}

#undef VERBOSE_EXP