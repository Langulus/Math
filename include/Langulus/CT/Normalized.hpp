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
   /// Extends T by marking it as normalized. Used for math primitives, such  
   /// as normals. Examples:                                                  
   /// 1) template<> struct Normalized<YourType> {};                          
   /// 2) struct YourType { using CTTI_Normalized = Yup; };                   
   template<class T>
   struct Normalized;
}

LANGULUS_CTTI_CONCEPT_DECVQ(Normalized);
