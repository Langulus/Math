///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Langulus/CT/Able.hpp"
#include <Langulus/Verbs/Multiply.hpp>
#include <Langulus/Numbers/Infinity.hpp>
#include <Langulus/TMany.hpp>
#include <concepts>

#if 0
   #define VERBOSE_MUL(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_MUL(...) LANGULUS(NOOP)
#endif


namespace Langulus::CTTI
{
   template<class T>
   concept BuiltinMullable = requires (T& t)         { {t *= t} -> ::std::same_as<T&>; }
                         and requires (T& t)         { {t /= t} -> ::std::same_as<T&>; }
                         and requires (T const& t)   { {t *  t} -> ::std::same_as<T>;  }
                         and requires (T const& t)   { {t /  t} -> ::std::same_as<T>;  };


   /// Imbue all arithmetic types with the ability to multiply and divide     
   /// each other.                                                            
   //TODO Implement the same ability from Vulkan POV in order to utilize GPU. 
   //TODO Each module reflects its own verbs. We can inspect these verbs at   
   //TODO runtime and decide which implementation to use depending on context.
   LglsImplementAbilitiesForConcept(BuiltinMullable, LHS) {
      using Can = Verbs::Multiply;

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

      /// Unary version just imagines there's a 1 on the left of each         
      /// individual element. The order is preserved.                         
      ///   @note if unary version is reached, this means verb argument has   
      ///      already been checked and guarantees to contain at least one    
      ///      element of type LHS! We can safely use reinterpret_cast here!  
      static bool Default(CT::Executable auto& verb) {
         auto const mass = static_cast<LHS>(verb.GetMass());
         if (mass < 0) {
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(verb.GetArgument());
            TMany<LHS> result; result.Reserve(rhs_typed.GetCount());
            for (LHS const& i : rhs_typed)
               result << LHS{1} / (i * mass);
            verb << Abandon(result);
         }
         else if (mass != 1) {
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(verb.GetArgument());
            TMany<LHS> result; result.Reserve(rhs_typed.GetCount());
            for (LHS const& i : rhs_typed)
               result << i * mass;
            verb << Abandon(result);
         }
         return true;//TODO note that returning true without pushing anything to output means context IS output (i.e. nothing changed). this needs to be taken care outside of this, applies to many verbs!
      }

   private:
      /// Common helper                                                       
      static void Inner(LHS const mass, LHS& lhs, TMany<LHS> const& rhs) noexcept {
         if (mass > 0) {
            // Multiply                                                 
            for (LHS const& i : rhs)
               lhs *= i * mass;
         }
         else {
            // Divide                                                   
            for (LHS const& i : rhs)
               lhs /= i * mass;
         }
      }
   };


   ///                                                                        
   /// Addition/subtraction of infinities                                     
   LglsImplementAbilitiesFor(Math::Infinity) {
      using Can = Verbs::Multiply;

      /// Infinity * or / anything = infinity                                 
      static bool Default(Math::Infinity const&, CT::Executable auto&) {
         return true;
      }

      /// Unary version can flip the sign of the infinity                     
      static bool Default(CT::Executable auto& verb) {
         if (verb.GetMass() >= 0)
            return true;

         auto& rhs_typed = reinterpret_cast<TMany<Math::Infinity> const&>(verb.GetArgument());
         TMany<Math::Infinity> result; result.Reserve(rhs_typed.GetCount());
         for (Math::Infinity const& i : rhs_typed)
            result << Math::Infinity {-i.mOrder};
         verb << Abandon(result);
         return true;
      }
   };
}

#undef VERBOSE_MUL