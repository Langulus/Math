///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Langulus/CT/Able.hpp"
#include <Langulus/Verbs/Modulate.hpp>
#include <Langulus/TMany.hpp>

#if 0
   #define VERBOSE_MOD(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_MOD(...) LANGULUS(NOOP)
#endif


namespace Langulus::CTTI
{
   template<class T>
   concept BuiltinModulatable = requires (T const& t) { {t %  t} -> ::std::same_as<T>;  }
                            and requires (T& t)       { {t %= t} -> ::std::same_as<T&>; };


   /// Imbue all arithmetic types with the ability to modulate                
   //TODO Implement the same ability from Vulkan POV in order to utilize GPU. 
   //TODO Each module reflects its own verbs. We can inspect these verbs at   
   //TODO runtime and decide which implementation to use depending on context.
   LglsImplementAbilitiesForConcept(BuiltinModulatable, LHS) {
      using Can = Verbs::Modulate;

      /// Destructive version, LHS is mutable. This won't allocate unless     
      /// conversion occurs.                                                  
      static bool Default(LHS& lhs, CT::Executable auto& verb) {
         auto const& rhs = verb.GetArgument();
         if (rhs.template IsSame<LHS>()) {
            // Easy path - types are the same                           
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(rhs);
            Inner(lhs, rhs_typed.GetRaw(), rhs_typed.GetCount());
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            Inner(lhs, converted.GetRaw(), converted.GetCount());
            return true;
         }
      }
       
      /// Non-destructive version, LHS is constant. Will allocate if          
      /// conversion occurs, or if verb output isn't reserved enough.         
      static bool Default(LHS const& lhs, CT::Executable auto& verb) {
         auto const& rhs = verb.GetArgument();
         auto result = lhs;
         if (rhs.template IsSame<LHS>()) {
            // Easy path - types are the same                           
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(rhs);
            Inner(result, rhs_typed.GetRaw(), rhs_typed.GetCount());
            verb << result;
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            Inner(result, converted.GetRaw(), converted.GetCount());
            verb << result;
            return true;
         }
      }

   private:
      static void Inner(LHS& lhs, LHS const* raw, size_t count) {
         while(count--)
            lhs = lhs % *(raw++);
      }
   };
}

#undef VERBOSE_MOD