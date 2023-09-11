///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Common.hpp"

namespace Langulus::Math
{

   ///                                                                        
   ///   Blending modes                                                       
   ///                                                                        
   /// Represents different tactics for blending colors                       
   ///                                                                        
   struct BlendMode {
      LANGULUS(POD) true;
      LANGULUS(NULLIFIABLE) true;
      LANGULUS(INFO) "Blending mode";

      using Type = uint8_t;

      enum Enum : Type {
         // No blending - final color becomes source color              
         None = 0,
         // No blending - final color becomes source color only         
         // if an alpha threshold is reached per pixel                  
         Threshold = 1,
         // Final color = source color * alpha + destination color      
         // * (1 - alpha)                                               
         Alpha = 2,
         // Final color = source color + destination color              
         Add = 3,
         // Final color = source color * destination color              
         Multiply = 4,

         Counter
      };

   protected:
      Type mMode {Enum::None};

      LANGULUS_NAMED_VALUES(Enum) {
         {"None", Enum::None,
            "No blending - final color is always source color"},
         {"Threshold",  Enum::Threshold,
            "No blending - final color becomes source color only if an alpha threshold is reached per pixel"},
         {"Alpha",      Enum::Alpha,
            "Final color = source color * alpha + destination color * (1 - alpha)"},
         {"Add",        Enum::Add,
            "Final color = source color + destination color"},
         {"Multiply",   Enum::Multiply,
            "Final color = source color * destination color"}
      };

   public:
      constexpr BlendMode() noexcept = default;
      constexpr BlendMode(Type value) noexcept
         : mMode {value} {}
   };

} // namespace Langulus::Math
