///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <Core/Exceptions.hpp>
#include <Anyness/Trait.hpp>
#include <Flow/Verb.hpp>

#if defined(LANGULUS_EXPORT_ALL) || defined(LANGULUS_EXPORT_MATH)
   #define LANGULUS_API_MATH() LANGULUS_EXPORT()
#else
   #define LANGULUS_API_MATH() LANGULUS_IMPORT()
#endif

LANGULUS_EXCEPTION(Arithmetic);

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

/// Make the rest of the code aware, that Langulus::Math has been included    
#define LANGULUS_LIBRARY_MATH() 1

/// Namespace containing all built-in Langulus verbs                          
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

namespace Langulus::Math
{

   using namespace ::Langulus::Anyness;
   using Flow::Verb;

   /// Register traits                                                        
   inline void RegisterTraits() {
      (void)MetaTrait::Of<Traits::Transform>();
      (void)MetaTrait::Of<Traits::View>();
      (void)MetaTrait::Of<Traits::Projection>();
      (void)MetaTrait::Of<Traits::Solid>();
      (void)MetaTrait::Of<Traits::Pickable>();
      (void)MetaTrait::Of<Traits::Signed>();
      (void)MetaTrait::Of<Traits::Bilateral>();
      (void)MetaTrait::Of<Traits::Static>();
      (void)MetaTrait::Of<Traits::Boundness>();
      (void)MetaTrait::Of<Traits::Relative>();
      (void)MetaTrait::Of<Traits::Place>();
      (void)MetaTrait::Of<Traits::Size>();
      (void)MetaTrait::Of<Traits::Aim>();
      (void)MetaTrait::Of<Traits::Velocity>();
      (void)MetaTrait::Of<Traits::Acceleration>();
      (void)MetaTrait::Of<Traits::Sampler>();
      (void)MetaTrait::Of<Traits::Level>();
      (void)MetaTrait::Of<Traits::Interpolator>();
   }

} // namespace Langulus::Math