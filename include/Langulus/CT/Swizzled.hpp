///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: MIT                                              
///                                                                           
#pragma once
#include <Langulus/CT/Vector.hpp>
#include <Langulus/CT/Integer.hpp>


namespace Langulus::CTTI
{
   /// Extends T by marking it as a swizzle vector. Examples:                 
   /// 1) template<> struct Swizzled<YourType> {};                            
   /// 2) struct YourType { using CTTI_Swizzled = Yup; };                     
   template<class T>
   struct Swizzled;
}

LANGULUS_CTTI_CONCEPT_DECVQ(Swizzled);

namespace Langulus::CT
{
   /// Swizzled integer vector                                                
   template<class...T>
   concept SwizzledInt = ((Swizzled<T> and Integer<TypeOf<T>>) and ...);
}
