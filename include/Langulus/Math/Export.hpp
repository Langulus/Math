///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/CT/Typed.hpp>
#include <Langulus/CT/Integer.hpp>

#if defined(LANGULUS_EXPORT_ALL) or defined(LANGULUS_EXPORT_MATH)
   #define LANGULUS_API_MATH() LANGULUS_EXPORT()
#else
   #define LANGULUS_API_MATH() LANGULUS_IMPORT()
#endif

/// Make the rest of the code aware, that Langulus::Math has been included    
#define LANGULUS_LIBRARY_MATH() 1

/// Namespace containing all built-in math verbs                              
namespace Langulus::Verbs
{
   struct Exponent;
   struct Multiply;
   struct Modulate;
   struct Randomize;
   struct Move;
   struct Add;
   struct Lerp;
   struct Cerp;
}

namespace Langulus::CT
{
   /// Anything that is adaptive                                              
   template<class...T>
   concept Adaptive = Dense<T...> and ((Decay<T>::CTTI_Adaptive) and ...);

   /// Anything that has the quaternion trait                                 
   template<class...T>
   concept Quaternion = Dense<T...> and ((Decay<T>::CTTI_Quaternion) and ...);

   /// Anything that has the vector trait                                     
   template<class...T>
   concept Vector = Dense<T...> and ((Decay<T>::CTTI_Vector) and ...);
   
   /// Anything that has the vector trait and contains integers               
   template<class...T>
   concept VectorInt = ((Vector<T> and Integer<TypeOf<T>>) and ...);
   
   /// Anything that has the color trait                                      
   template<class...T>
   concept Color = Dense<T...> and ((Decay<T>::CTTI_Color) and ...);

   /// Anything that has the range trait                                      
   template<class...T>
   concept Range = Dense<T...> and ((Decay<T>::CTTI_Range) and ...);

   /// Anything that has the matrix trait                                     
   template<class...T>
   concept Matrix = Dense<T...> and ((Decay<T>::CTTI_Matrix) and ...);

   /// Anything that has the gradient trait                                   
   template<class...T>
   concept Gradient = Dense<T...> and ((Decay<T>::CTTI_Gradient) and ...);

   /// For recognizing proxy-arrays (intermediate vectors after swizzling)    
   template<class...T>
   concept ProxyArray = Dense<T...> and ((Decay<T>::CTTI_ProxyArray) and ...);

   /// For recognizing proxy-arrays that contain integers                     
   template<class...T>
   concept ProxyArrayInt = ((ProxyArray<T> and Integer<TypeOf<T>>) and ...);

   /// Anything ScalarBased that contains integers                            
   //template<class...T>
   //concept ScalarInt = ((Scalar<T> and Integer<TypeOf<T>>) and ...);
}

namespace Langulus::Math
{
   LANGULUS_API(MATH) extern void RegisterTraits();
   LANGULUS_API(MATH) extern void RegisterVerbs();
   LANGULUS_API(MATH) extern void RegisterPrimitives();
   LANGULUS_API(MATH) extern void RegisterVectors();
   LANGULUS_API(MATH) extern void RegisterColors();
   LANGULUS_API(MATH) extern void RegisterAngles();

   /*namespace Typelists
   {
      using Arithmetic = Types<
         float, double,
         uint8_t, uint16_t, uint32_t, uint64_t,
         int8_t,  int16_t,  int32_t,  int64_t
      >;

      using Fundamental = decltype(Arithmetic{} + Types<bool>{});
   }*/
}
