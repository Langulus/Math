///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Common.hpp"


namespace Langulus::CT
{

   namespace Inner
   {
      template<class T>
      concept Dimension = Trait<T> and requires { {T::Index} -> CT::Same<Offset>; };
   }

   /// Dimension is any trait, defined with an Index property                 
   /// Used for accessing individual vector components, for example           
   template<class... T>
   concept Dimension = (Inner::Dimension<T> and ...);

} // namespace Langulus::CT