///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"


namespace Langulus::Math
{

   ///                                                                        
   ///   Color channel                                                        
   ///                                                                        
   template<CT::Number T, CT::Dimension D>
   struct TColorComponent : TNumber<T, TColorComponent<T, D>> {
      LANGULUS(TYPED) T;
      using Base = TNumber<T, TColorComponent<T, D>>;
      using Dimension = D;
      using Base::Base;
   };

} // namespace Langulus::Math
