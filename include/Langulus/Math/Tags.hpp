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
   "Model transformation tag");
LANGULUS_DEFINE_TAG(View,
   "View transformation tag");
LANGULUS_DEFINE_TAG(Projection,
   "Projection transformation tag");
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
   "Relativity tag");
LANGULUS_DEFINE_TAG(Place,
   "Position tag");
LANGULUS_DEFINE_TAG(Size,
   "Size tag");
LANGULUS_DEFINE_TAG(Aim,
   "Aim tag, used as a looking direction, or normals in general");
LANGULUS_DEFINE_TAG(Velocity,
   "Velocity tag");
LANGULUS_DEFINE_TAG(Acceleration,
   "Acceleration tag");
LANGULUS_DEFINE_TAG(Sampler,
   "Sampler tag, used for sampling surfaces/volumes");
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
