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
#include <Langulus/TTag.hpp>


#if defined(LANGULUS_EXPORT_ALL) or defined(LANGULUS_EXPORT_MATH)
   #define LANGULUS_API_MATH() LANGULUS_EXPORT()
#else
   #define LANGULUS_API_MATH() LANGULUS_IMPORT()
#endif

/// Make the rest of the code aware, that Langulus::Math has been included    
#define LANGULUS_LIBRARY_MATH() 1


/// Built-in math traits                                                      
LANGULUS_DEFINE_TAG(X, "X (first) vector component",
   static constexpr size_t Index = 0);
LANGULUS_DEFINE_TAG(Y, "Y (second) vector component",
   static constexpr size_t Index = 1);
LANGULUS_DEFINE_TAG(Z, "Z (third) vector component",
   static constexpr size_t Index = 2);
LANGULUS_DEFINE_TAG(W, "W (fourth) vector component",
   static constexpr size_t Index = 3);

LANGULUS_DEFINE_TAG(U, "U (first) vector component",
   static constexpr size_t Index = 0);
LANGULUS_DEFINE_TAG(V, "V (second) vector component",
   static constexpr size_t Index = 1);
LANGULUS_DEFINE_TAG(S, "S (third) vector component",
   static constexpr size_t Index = 2);
LANGULUS_DEFINE_TAG(T, "T (fourth) vector component",
   static constexpr size_t Index = 3);

LANGULUS_DEFINE_TAG(R, "Red (first) color component",
   static constexpr size_t Index = 0);
LANGULUS_DEFINE_TAG(G, "Green (second) color component",
   static constexpr size_t Index = 1);
LANGULUS_DEFINE_TAG(B, "Blue (third) color component",
   static constexpr size_t Index = 2);
LANGULUS_DEFINE_TAG(A, "Alpha (fourth) color component",
   static constexpr size_t Index = 3);

LANGULUS_DEFINE_TAG(D, "Depth (first) component",
   static constexpr size_t Index = 0);

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

} // namespace Langulus::Verbs


namespace Langulus::CT
{
   namespace Inner
   {
      template<class T>
      concept Dimension = Trait<T> and requires { {T::Index} -> CT::Same<size_t>; };
   }

   /// Dimension is any trait, defined with an Index property                 
   /// Used for accessing individual vector components, for example           
   template<class... T>
   concept Dimension = (Inner::Dimension<T> and ...);

   /// Anything that is adaptive                                              
   template<class...T>
   concept Adaptive = ((Decay<Deint<T>>::CTTI_AdaptiveTrait) and ...);
   template<class...T>
   concept NotAdaptive = ((not Adaptive<T>) and ...);

   /// Anything that has the quaternion trait                                 
   template<class...T>
   concept QuaternionBased = ((Decay<Deint<T>>::CTTI_QuaternionTrait) and ...);

   /// Anything that has the vector trait                                     
   template<class...T>
   concept VectorBased = ((Decay<Deint<T>>::CTTI_VectorTrait) and ...);
   
   /// Anything that has the vector trait and contains integers               
   template<class...T>
   concept VectorBasedInt = ((VectorBased<T> and CT::Integer<TypeOf<T>>) and ...);
   
   /// Anything that has the color trait                                      
   template<class...T>
   concept ColorBased = ((Decay<Deint<T>>::CTTI_ColorTrait) and ...);

   /// Anything that has the range trait                                      
   template<class...T>
   concept RangeBased = ((Decay<Deint<T>>::CTTI_RangeTrait) and ...);

   /// Anything that has the matrix trait                                     
   template<class...T>
   concept MatrixBased = ((Decay<Deint<T>>::CTTI_MatrixTrait) and ...);

   /// Anything that has the gradient trait                                   
   template<class...T>
   concept GradientBased = ((Decay<Deint<T>>::CTTI_GradientTrait) and ...);

   /// For recognizing proxy-arrays (intermediate vectors after swizzling)    
   template<class...T>
   concept ProxyArray = ((Decay<Deint<T>>::CTTI_ProxyArray) and ...);

   /// For recognizing proxy-arrays that contain integers                     
   template<class...T>
   concept ProxyArrayInt = ((ProxyArray<T> and CT::Integer<TypeOf<T>>) and ...);

   /// Anything that doesn't have any of the above traits                     
   ///   @maintenance keep this one up to date, if adding new math traits     
   template<class...T>
   concept ScalarBased = Scalar<T...> and not ((
           QuaternionBased<T>
        or VectorBased<T>
        or RangeBased<T>
        or MatrixBased<T>
        or GradientBased<T>
        or ProxyArray<T>
        or Adaptive<T>
      ) and ...);

   /// Anything ScalarBased that contains integers                            
   template<class...T>
   concept ScalarBasedInt = ((ScalarBased<T> and CT::Integer<TypeOf<T>>) and ...);

   /// Anything that is a CT::CustomNumber and CT::CastsToFundamental         
   /// It is a more constrained version of CT::CustomNumber, that omits any   
   /// iterators and other irrelevant stuff                                   
   template<class...T>
   concept NumberBased = CustomNumber<T...> and CastsToFundamental<T...>
       and ((not VectorBased<T> and not Adaptive<T>) and ...);

} // namespace Langulus::CT

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
         int8_t, int16_t, int32_t, int64_t
      >;

      using Fundamental = typename Arithmetic::Cat<bool>;
   }

} // namespace Langulus::Math
