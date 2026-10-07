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
   /// Extends T by marking it as a matrix. Examples:                         
   /// 1) template<> struct Matrix<YourType> {};                              
   /// 2) struct YourType { using CTTI_Matrix = Yup; };                       
   template<class T>
   struct Matrix;
}

LANGULUS_CTTI_CONCEPT_DECVQ(Matrix);
