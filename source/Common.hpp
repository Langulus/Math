///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <LangulusRTTI.hpp>
#include <LangulusSIMD.hpp>
#include <LangulusAnyness.hpp>
#include <LangulusFlow.hpp>

namespace Langulus::Math
{

   using namespace ::Langulus::Anyness;
   using ::Langulus::Flow::Verb;

} // namespace Langulus::Math

LANGULUS_EXCEPTION(Arithmetic);

LANGULUS_DEFINE_TRAIT(Transformation,
   "Model transformation trait");
LANGULUS_DEFINE_TRAIT(Solid,
   "Solidity state");
LANGULUS_DEFINE_TRAIT(Pickable,
   "Pickability state (true to be able to select with mouse)");
LANGULUS_DEFINE_TRAIT(Signed,
   "Signed state (inverts domains/geometry; flips faces; negates numbers)");
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
LANGULUS_DEFINE_TRAIT(Aim,
   "Aim trait, used as a looking direction, or normals in general");
LANGULUS_DEFINE_TRAIT(Velocity,
   "Velocity trait");
LANGULUS_DEFINE_TRAIT(Acceleration,
   "Acceleration trait");
LANGULUS_DEFINE_TRAIT(Sampler,
   "Sampler trait, used for sampling surfaces/volumes");
