///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/CT/DefineConst.hpp>


namespace Langulus::Math
{
   ///                                                                        
   ///   Infinity representation for use in descriptors                       
   ///                                                                        
   struct Infinity {
      int mOrder;

      using CTTI_Values = NamedValue<1, "Infinity", "First order of infinity">;
   };
}