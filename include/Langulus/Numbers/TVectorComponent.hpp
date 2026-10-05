///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TNumber.hpp"
#include "../Vectors/TVector.hpp"


namespace Langulus::Math
{
   ///                                                                        
   /// A number associated with a dimension. When used in arithmetics, it     
   /// will affect only the dimension it is associated with:                  
   ///   TVector{1,2,3} + TVectorComponent<int, 1>{5} -> TVector{1,7,3}       
   template<CT::Number T, CT::Dimension D>
   struct TVectorComponent : TNumber<T> {
      using Base      = TNumber<T>;
      using Dimension = D;
      using TNumber<T>::TNumber;
   };
}