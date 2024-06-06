///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <Core/Exceptions.hpp>
#include <Anyness/Trait.hpp>
#include <Flow/Code.hpp>


#if defined(LANGULUS_EXPORT_ALL) or defined(LANGULUS_EXPORT_MATH)
   #define LANGULUS_API_MATH() LANGULUS_EXPORT()
#else
   #define LANGULUS_API_MATH() LANGULUS_IMPORT()
#endif

LANGULUS_EXCEPTION(Arithmetic);


/// Built-in math traits                                                      
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(X, "X (first) vector component",
   static constexpr Offset Index = 0);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(Y, "Y (second) vector component",
   static constexpr Offset Index = 1);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(Z, "Z (third) vector component",
   static constexpr Offset Index = 2);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(W, "W (fourth) vector component",
   static constexpr Offset Index = 3);

LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(U, "U (first) vector component",
   static constexpr Offset Index = 0);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(V, "V (second) vector component",
   static constexpr Offset Index = 1);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(S, "S (third) vector component",
   static constexpr Offset Index = 2);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(T, "T (fourth) vector component",
   static constexpr Offset Index = 3);

LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(R, "Red (first) color component",
   static constexpr Offset Index = 0);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(G, "Green (second) color component",
   static constexpr Offset Index = 1);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(B, "Blue (third) color component",
   static constexpr Offset Index = 2);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(A, "Alpha (fourth) color component",
   static constexpr Offset Index = 3);

LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(D, "Depth (first) component",
   static constexpr Offset Index = 0);

LANGULUS_DEFINE_TRAIT(Transform,
   "Model transformation trait");
LANGULUS_DEFINE_TRAIT(View,
   "View transformation trait");
LANGULUS_DEFINE_TRAIT(Projection,
   "Projection transformation trait");
LANGULUS_DEFINE_TRAIT(Solid,
   "Solidity state");
LANGULUS_DEFINE_TRAIT(Pickable,
   "Pickability state (true to be able to select with mouse)");
LANGULUS_DEFINE_TRAIT(Signed,
   "Signed state (the capability to invert domains/geometry, flip faces, negates numbers)");
LANGULUS_DEFINE_TRAIT(Bilateral,
   "Bilateral state (doublesidedness of flat shapes)");
LANGULUS_DEFINE_TRAIT(Static,
   "Static state (used mainly as an optimization)");
LANGULUS_DEFINE_TRAIT(Boundness,
   "Boundness state (shifts control from simulation to user and vice-versa)");
LANGULUS_DEFINE_TRAIT(Relative,
   "Relativity trait");
LANGULUS_DEFINE_TRAIT(Place,
   "Position trait");
LANGULUS_DEFINE_TRAIT(Size,
   "Size trait");
LANGULUS_DEFINE_TRAIT(Aim,
   "Aim trait, used as a looking direction, or normals in general");
LANGULUS_DEFINE_TRAIT(Velocity,
   "Velocity trait");
LANGULUS_DEFINE_TRAIT(Acceleration,
   "Acceleration trait");
LANGULUS_DEFINE_TRAIT(Sampler,
   "Sampler trait, used for sampling surfaces/volumes");
LANGULUS_DEFINE_TRAIT(Level,
   "Level of an instance");
LANGULUS_DEFINE_TRAIT(Interpolator,
   "Interpolation mode");
LANGULUS_DEFINE_TRAIT(Perspective,
   "Perspective state (boolean)");


/// Namespace containing all built-in math verbs                              
namespace Langulus::Verbs
{

   struct Exponent;
   struct Multiply;
   struct Modulate;
   struct Randomize;
   struct Add;
   struct Lerp;
   struct Cerp;

} // namespace Langulus::Verbs


namespace Langulus::CT
{

   /// Anything that has the quaternion trait                                 
   template<class...T>
   concept QuaternionBased = ((Desem<T>::CTTI_QuaternionTrait) and ...);

   /// Anything that has the vector trait                                     
   template<class...T>
   concept VectorBased = ((Desem<T>::CTTI_VectorTrait) and ...);
   
   /// Anything that has the vector trait and contains integers               
   template<class...T>
   concept VectorBasedInt = ((VectorBased<T> and CT::Integer<TypeOf<T>>) and ...);
   
   /// Anything that has the color trait                                      
   template<class...T>
   concept ColorBased = ((Desem<T>::CTTI_ColorTrait) and ...);

   /// Anything that has the range trait                                      
   template<class...T>
   concept RangeBased = ((Desem<T>::CTTI_RangeTrait) and ...);

   /// Anything that has the matrix trait                                     
   template<class...T>
   concept MatrixBased = ((Desem<T>::CTTI_MatrixTrait) and ...);

   /// Anything that has the gradient trait                                   
   template<class...T>
   concept GradientBased = ((Desem<T>::CTTI_GradientTrait) and ...);

   /// For recognizing proxy-arrays (intermediate vectors after swizzling)    
   template<class...T>
   concept ProxyArray = ((Desem<T>::CTTI_ProxyArray) and ...);

   /// For recognizing proxy-arrays that contain integers                     
   template<class...T>
   concept ProxyArrayInt = ((ProxyArray<T> and CT::Integer<TypeOf<T>>) and ...);

   /// Anything that doesn't have any of the above traits                     
   ///   @maintenance keep this one up to date, if adding new math traits     
   template<class...T>
   concept ScalarBased = Scalar<T...> and
     not ((QuaternionBased<T>
        or VectorBased<T>
        or RangeBased<T>
        or MatrixBased<T>
        or GradientBased<T>
        or ProxyArray<T>
      ) and ...);

   /// Anything ScalarBased that contains integers                            
   template<class...T>
   concept ScalarBasedInt = ((ScalarBased<T> and CT::Integer<TypeOf<T>>) and ...);

   /// Anything that is a CT::CustomNumber and CT::CastsToFundamental         
   /// It is a more constrained version of CT::CustomNumber, that omits any   
   /// iterators and other irrelevant stuff                                   
   template<class...T>
   concept NumberBased = CustomNumber<T...> and CastsToFundamental<T...>
       and ((not VectorBased<T>) and ...);

} // namespace Langulus::CT

/// Make the rest of the code aware, that Langulus::Math has been included    
#define LANGULUS_LIBRARY_MATH() 1
