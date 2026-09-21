///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/Core.hpp>
//#include <Langulus/CT/Lossless.hpp>
//#include <Langulus/CT/Scalar.hpp>
#include <Langulus/TTag.hpp>


#if defined(LANGULUS_EXPORT_ALL) or defined(LANGULUS_EXPORT_MATH)
   #define LANGULUS_API_MATH() LANGULUS_EXPORT()
#else
   #define LANGULUS_API_MATH() LANGULUS_IMPORT()
#endif

/// Make the rest of the code aware, that Langulus::Math has been included    
#define LANGULUS_LIBRARY_MATH() 1


/// Built-in math traits                                                      
LANGULUS_DEFINE_TAG(Transform,
   "Model transformation trait");
LANGULUS_DEFINE_TAG(View,
   "View transformation trait");
LANGULUS_DEFINE_TAG(Projection,
   "Projection transformation trait");
LANGULUS_DEFINE_TAG(Solid,
   "Solidity state");
LANGULUS_DEFINE_TAG(Pickable,
   "Pickability state (true to be able to select with mouse)");
LANGULUS_DEFINE_TAG(Signed,
   "Signed state (the capability to invert domains/geometry, flip faces, negates numbers)");
LANGULUS_DEFINE_TAG(Bilateral,
   "Bilateral state (doublesidedness of flat shapes)");
LANGULUS_DEFINE_TAG(Static,
   "Static state (used mainly as an optimization)");
LANGULUS_DEFINE_TAG(Boundness,
   "Boundness state (shifts control from simulation to user and vice-versa)");
LANGULUS_DEFINE_TAG(Relative,
   "Relativity trait");
LANGULUS_DEFINE_TAG(Place,
   "Position trait");
LANGULUS_DEFINE_TAG(Size,
   "Size trait");
LANGULUS_DEFINE_TAG(Aim,
   "Aim trait, used as a looking direction, or normals in general");
LANGULUS_DEFINE_TAG(Velocity,
   "Velocity trait");
LANGULUS_DEFINE_TAG(Acceleration,
   "Acceleration trait");
LANGULUS_DEFINE_TAG(Sampler,
   "Sampler trait, used for sampling surfaces/volumes");
LANGULUS_DEFINE_TAG(Level,
   "Level of an instance");
LANGULUS_DEFINE_TAG(Interpolator,
   "Interpolation mode");
LANGULUS_DEFINE_TAG(Perspective,
   "Perspective state (boolean)");


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
   using Flow::Verb;

   LANGULUS_API(MATH) extern void RegisterTraits();
   LANGULUS_API(MATH) extern void RegisterVerbs();

   namespace Typelists
   {
      using Arithmetic = Types<
         float, double,
         uint8_t, uint16_t, uint32_t, uint64_t,
         int8_t,  int16_t,  int32_t,  int64_t
      >;

      using Fundamental = decltype(Arithmetic{} + Types<bool>{});
   }
}
