///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
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

      LANGULUS_NAMED_VALUES(None, Threshold, Alpha, Add, Multiply);

   public:
      constexpr BlendMode() noexcept = default;
      constexpr BlendMode(Type value) noexcept
         : mMode {value} {}
   };

} // namespace Langulus::Math
