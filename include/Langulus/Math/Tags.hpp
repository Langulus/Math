///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/TTag.hpp>


/// Built-in math tags                                                        
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
LANGULUS_DEFINE_TAG(MapMode,
   "Mapping mode");
LANGULUS_DEFINE_TAG(Topology,
   "Topology type");