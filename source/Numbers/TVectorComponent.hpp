///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
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
   struct TVectorComponent : public TNumber<T, TVectorComponent<T, D>> {
      using Base = TNumber<T, TVectorComponent<T, D>>;
      using Dimension = D;
      using MemberType = T;
      using Base::Base;
   };

} // namespace Langulus::Math