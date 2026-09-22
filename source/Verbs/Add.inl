///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Langulus/CT/Able.hpp"
#include <Langulus/Verbs/Add.hpp>
#include <Langulus/Numbers/Infinity.hpp>
#include <Langulus/TMany.hpp>
#include <concepts>

#if 0
   #define VERBOSE_ADD(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_ADD(...) LANGULUS(NOOP)
#endif


namespace Langulus::CTTI
{
   template<class T>
   concept BuiltinAddable = requires (T& t)         { {t += t} -> ::std::same_as<T&>; }
                        and requires (T& t)         { {t -= t} -> ::std::same_as<T&>; }
                        and requires (T const& t)   { {t +  t} -> ::std::same_as<T>;  }
                        and requires (T const& t)   { {t -  t} -> ::std::same_as<T>;  };


   /// Imbue all arithmetic types with the ability to add and subtract        
   /// each other.                                                            
   //TODO Implement the same ability from Vulkan POV in order to utilize GPU. 
   //TODO Each module reflects its own verbs. We can inspect these verbs at   
   //TODO runtime and decide which implementation to use depending on context.
   LglsImplementAbilitiesForConcept(BuiltinAddable, LHS) {
      using Can = Verbs::Add;

      //TODO eventually for constexpr verb execution?
      /*
      static constexpr LHS& Positive(LHS& lhs, CT::Executable auto& rhs) noexcept {
          return lhs += rhs;
      }
                          
      static constexpr LHS Positive(LHS const& lhs, CT::Executable auto& rhs) noexcept {
         return lhs + rhs;
      }

      static constexpr LHS& Negative(LHS& lhs, CT::Executable auto& rhs) noexcept {
          return lhs -= rhs;
      }
                          
      static constexpr LHS Negative(LHS const& lhs, CT::Executable auto& rhs) noexcept {
         return lhs - rhs;
      }*/

      /// Destructive version, LHS is mutable. This won't allocate unless     
      /// conversion occurs.                                                  
      static bool Default(LHS& lhs, CT::Executable auto& verb) {
         auto const mass = static_cast<LHS>(verb.GetMass());
         auto const& rhs = verb.GetArgument();
         if (rhs.template IsSame<LHS>()) {
            // Easy path - types are the same                           
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(rhs);
            for (LHS const& i : rhs_typed)
               lhs += i * mass;
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            for (LHS const& i : converted)
               lhs += i * mass;
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
            for (LHS const& i : rhs_typed)
               result += i * mass;

            verb << result;
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            for (LHS const& i : converted)
               result += i * mass;

            verb << result;
            return true;
         }
      } 

      /// Unary version just imagines there's a zero on the left of each      
      /// individual element. The order is preserved.                         
      ///   @note if unary version is reached, this means verb argument has   
      ///      already been checked and guarantees to contain at least one    
      ///      element of type LHS! We can safely use reinterpret_cast here!  
      static bool Default(CT::Executable auto& verb) {
         auto const mass = static_cast<LHS>(verb.GetMass());
         auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(verb.GetArgument());
         TMany<LHS> result; result.Reserve(rhs_typed.GetCount());
         for (LHS const& i : rhs_typed)
            result << i * mass;
         verb << Abandon(result);
         return true;
      }
   };

   /// Addition/subtraction of infinities                                     
   LglsImplementAbilitiesFor(Math::Infinity) {
      using Can = Verbs::Add;

      /// Infinity +/- anything = infinity                                    
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

#undef VERBOSE_ADD