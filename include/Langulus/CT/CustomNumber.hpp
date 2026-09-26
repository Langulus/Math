///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: MIT                                              
///                                                                           
#pragma once
#include <Langulus/CT/Number.hpp>


namespace Langulus::CTTI
{
   /// Extends T by marking it as a custom number, as opposed to CT::Number,  
   /// which also considers bounded arrays of extent == 1 as numbers, too.    
   /// Examples:                                                              
   /// 1) template<> struct CustomNumber<YourType> {};                        
   /// 2) struct YourType { using CTTI_CustomNumber = Yup; };                 
   template<class T>
   struct CustomNumber;
}

LANGULUS_CTTI_CONCEPT_DECVQ(CustomNumber);

namespace Langulus::CT
{
   /// Built-in number                                                        
   template<class...T>
   concept BuiltinNumber = ((CT::Number<T> and not CT::CustomNumber<T>) and ...);
}
