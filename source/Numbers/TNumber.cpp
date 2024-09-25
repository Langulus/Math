///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "TAngle.hpp"
#include "Level.inl"
#include "Infinity.hpp"


namespace Langulus::Math
{

   /// Register number types                                                  
   void RegisterNumbers() {
      RegisterAngles();

      (void) MetaOf<Constants::Infinity>();

      (void) MetaOf<Constants::LevelHuman>();
      (void) MetaOf<Constants::LevelAsteroid>();
      (void) MetaOf<Constants::LevelPlanet>();
      (void) MetaOf<Constants::LevelSystem>();
      (void) MetaOf<Constants::LevelGalaxy>();
      (void) MetaOf<Constants::LevelUniverse>();
      (void) MetaOf<Constants::LevelCell>();
      (void) MetaOf<Constants::LevelVirus>();
      (void) MetaOf<Constants::LevelAtom>();
      (void) MetaOf<Constants::LevelNeutron>();
      (void) MetaOf<Constants::LevelQuark>();
      (void) MetaOf<Constants::LevelNeutrino>();
      (void) MetaOf<Constants::LevelPlanck>();
      (void) MetaOf<Constants::LevelMax>();
      (void) MetaOf<Constants::LevelMin>();
      (void) MetaOf<Constants::LevelDefault>();
   }

} // namespace Langulus::Math
