///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: MIT                                              
///                                                                           
#pragma once
#include <Langulus/Typenav.hpp>


namespace Langulus::CTTI
{
   /// Extends T by marking it as scale. Examples:                            
   /// 1) template<> struct Scale<YourType> {};                               
   /// 2) struct YourType { using CTTI_Scale = Yup; };                        
   template<class T>
   struct Scale;
}

LANGULUS_CTTI_CONCEPT_DECVQ(Scale);
