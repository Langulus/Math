///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"

namespace Langulus::Math
{

   ///                                                                        
   ///   Vector component                                                     
   ///                                                                        
   template<CT::DenseNumber T, CT::Dimension D>
   struct TVectorComponent : TNumber<T, TVectorComponent<T, D>> {
      LANGULUS(TYPED) T;
      using Base = TNumber<T, TVectorComponent<T, D>>;
      using Dimension = D;
      using Base::Base;
   };

} // namespace Langulus::Math