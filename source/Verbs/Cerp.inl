///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Langulus/CT/Able.hpp"
#include <Langulus/Functions/Arithmetics.hpp>
#include <Langulus/Verbs/Cerp.hpp>
#include <Langulus/TMany.hpp>
#include <concepts>

#if 0
   #define VERBOSE_CERP(...) Logger::Verbose(__VA_ARGS__)
#else
   #define VERBOSE_CERP(...) LANGULUS(NOOP)
#endif


namespace Langulus::CTTI
{
   template<class T>
   concept BuiltinCerpable = requires (T const& t) {
      {Math::Cerp(t,t,t,t,t)} -> ::std::same_as<T>;
   };


   /// Imbue all arithmetic types with the ability to interpolate cubicly     
   //TODO Implement the same ability from Vulkan POV in order to utilize GPU. 
   //TODO Each module reflects its own verbs. We can inspect these verbs at   
   //TODO runtime and decide which implementation to use depending on context.
   LglsImplementAbilitiesForConcept(BuiltinCerpable, LHS) {
      using Can = Verbs::Cerp;

      static void Inner(LHS& lhs, LHS const* raw, Langulus::Real mass, size_t count) {
         switch(count) {
         case 1:
            lhs = *raw; break;
         case 2:
            lhs = Math::Cerp(raw[0], raw[0], raw[1], raw[1], mass); break;
         case 3:
            lhs = Math::Cerp(
               raw[0],
               Math::Cerp(raw[0], raw[0], raw[1], raw[1]), //TODO this is probably wrong, i made it up cuz it made sense to me
               Math::Cerp(raw[1], raw[1], raw[2], raw[2]),
               raw[2],
               mass
            ); break;
         default:
            lhs = Math::Cerp(
               raw[0], raw[1], raw[2], raw[3], mass
            ); break;
         }
      }

      /// Destructive version, LHS is mutable. This won't allocate unless     
      /// conversion occurs.                                                  
      static bool Default(LHS& lhs, CT::Executable auto& verb) {
         auto const mass = static_cast<LHS>(verb.GetMass());
         auto const& rhs = verb.GetArgument();
         if (rhs.template IsSame<LHS>()) {
            // Easy path - types are the same                           
            auto& rhs_typed = reinterpret_cast<TMany<LHS> const&>(rhs);
            Inner(lhs, rhs_typed.GetRaw(), mass, rhs_typed.GetCount());
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            Inner(lhs, converted.GetRaw(), mass, converted.GetCount());
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
            Inner(result, rhs_typed.GetRaw(), mass, rhs_typed.GetCount());
            verb << result;
            return true;
         }
         else {
            // Hard path - we must attempt conversion to LHS            
            auto converted = rhs.template ConvertTo<LHS>();
            if (not converted)
               return false;

            Inner(result, converted.GetRaw(), mass, converted.GetCount());
            verb << result;
            return true;
         }
      }
   };
}

#undef VERBOSE_CERP