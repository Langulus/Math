///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: MIT                                              
///                                                                           
#pragma once
#include <Langulus/CT/Vector.hpp>


namespace Langulus::CTTI
{
   /// Extends T by marking it as a custom vector, as opposed to CT::Vector,  
   /// which also considers bounded arrays of extent > 1 as vectors, too.     
   /// Examples:                                                              
   /// 1) template<> struct CustomVector<YourType> {};                        
   /// 2) struct YourType { using CTTI_CustomVector = Yup; };                 
   template<class T>
   struct CustomVector;
}

LANGULUS_CTTI_CONCEPT_DECVQ(CustomVector);

namespace Langulus::CT
{
   /// Built-in vector                                                        
   template<class...T>
   concept BuiltinVector = ((CT::Vector<T> and not CT::CustomVector<T>) and ...);
}
