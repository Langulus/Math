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
   ///   Color channel                                                        
   ///                                                                        
   template<CT::DenseNumber T, CT::Dimension D>
   struct TColorComponent : public TNumber<T, TColorComponent<T, D>> {
      using Base = TNumber<T, TColorComponent<T, D>>;
   public:
      using Dimension = D;
      using MemberType = T;
      using Base::Base;
   };

} // namespace Langulus::Math
