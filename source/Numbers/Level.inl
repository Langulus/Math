///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Level.hpp"
#include "../Functions/Arithmetics.hpp"
#include "TNumber.inl"


namespace Langulus::Math
{

   /// Default (human level) construction                                     
   LANGULUS(INLINED)
   constexpr Level::Level() noexcept
      : Base {Level::Default} {}

   /// Real number construction                                               
   ///   @param octave - the real number to interpret as level                
   LANGULUS(INLINED)
   constexpr Level::Level(const CT::Real auto& octave) noexcept {
      if (octave < Level::Min || octave > Level::Max)
         mValue = Level::OutOfBounds;
      mValue = static_cast<Real>(octave);
   }

   /// Integer number construction                                            
   ///   @attention unsigned integers will be remapped to the signed range    
   ///   @param octave - the integer to interpret as level                    
   LANGULUS(INLINED)
   constexpr Level::Level(const CT::Integer auto& octave) noexcept {
      Real ioct;
      if constexpr (CT::Signed<decltype(octave)>)
         ioct = static_cast<Real>(octave);
      else
         ioct = static_cast<Real>(octave) + Level::Min;

      if (ioct < Level::Min || ioct > Level::Max)
         mValue = Level::OutOfBounds;
      mValue = ioct;
   }

   /// Get a factor for scaling a relative level to this one                  
   ///   @param level - the level to factor against                           
   ///   @param return the invlog scale that maps this to other               
   LANGULUS(INLINED)
   Real Level::GetFactor(const Level& level) const noexcept {
      return Math::Pow(Unit, level.mValue - mValue);
   }

   /// Get a reference point between two levels                               
   ///   @param level - the other level                                       
   ///   @return a middle level between this and other                        
   LANGULUS(INLINED)
   constexpr Level Level::GetRefPoint(const Level& level) const noexcept {
      if (mValue == Level::OutOfBounds || level.mValue == Level::OutOfBounds) {
         // Reference point can't exist                                 
         return Level::OutOfBounds;
      }
      else if (mValue == level.mValue) {
         // Reference point is same                                     
         return *this;
      }
            
      // Reference point is middle                                      
      return (mValue + level.mValue) / 2;
   }

   /// Get a reference point between two levels                               
   ///   @param o1 - the first level                                          
   ///   @param o2 - the second level                                         
   ///   @return a middle level                                               
   LANGULUS(INLINED)
   constexpr Level Level::GetRefPoint(const Level& o1, const Level& o2) noexcept {
      return o1.GetRefPoint(o2);
   }

   /// Get a zero based offset from this level                                
   ///   @return the zero-based offset                                        
   LANGULUS(INLINED)
   constexpr Real Level::GetOffset() const noexcept {
      return mValue - Level::Min;
   }

   /// Get a zero based offset from this level (as integer)                   
   ///   @return the zero-based offset                                        
   LANGULUS(INLINED)
   constexpr Offset Level::GetOffsetInt() const noexcept {
      return static_cast<Offset>(mValue - Level::Min);
   }

} // namespace Langulus::Math


LANGULUS_DEFINE_CONSTANT(LevelHuman,
   ::Langulus::Math::Level {::Langulus::Math::Level::Human},
   "Level::Human", "A canonical human level"
)

LANGULUS_DEFINE_CONSTANT(LevelAsteroid,
   ::Langulus::Math::Level {::Langulus::Math::Level::Asteroid},
   "Level::Asteroid", "A canonical asteroid level"
)

LANGULUS_DEFINE_CONSTANT(LevelPlanet,
   ::Langulus::Math::Level {::Langulus::Math::Level::Planet},
   "Level::Planet", "A canonical planet level"
)

LANGULUS_DEFINE_CONSTANT(LevelSystem,
   ::Langulus::Math::Level {::Langulus::Math::Level::System},
   "Level::System", "A canonical system level"
)

LANGULUS_DEFINE_CONSTANT(LevelGalaxy,
   ::Langulus::Math::Level {::Langulus::Math::Level::Galaxy},
   "Level::Galaxy", "A canonical galaxy level"
)

LANGULUS_DEFINE_CONSTANT(LevelUniverse,
   ::Langulus::Math::Level {::Langulus::Math::Level::Universe},
   "Level::Universe", "A canonical universe level"
)

LANGULUS_DEFINE_CONSTANT(LevelCell,
   ::Langulus::Math::Level {::Langulus::Math::Level::Cell},
   "Level::Cell", "A canonical cell level"
)

LANGULUS_DEFINE_CONSTANT(LevelVirus,
   ::Langulus::Math::Level {::Langulus::Math::Level::Virus},
   "Level::Virus", "A canonical virus level"
)

LANGULUS_DEFINE_CONSTANT(LevelAtom,
   ::Langulus::Math::Level {::Langulus::Math::Level::Atom},
   "Level::Atom", "A canonical atom level"
)

LANGULUS_DEFINE_CONSTANT(LevelNeutron,
   ::Langulus::Math::Level {::Langulus::Math::Level::Neutron},
   "Level::Neutron", "A canonical neutron level"
)

LANGULUS_DEFINE_CONSTANT(LevelQuark,
   ::Langulus::Math::Level {::Langulus::Math::Level::Quark},
   "Level::Quark", "A canonical quark level"
)

LANGULUS_DEFINE_CONSTANT(LevelNeutrino,
   ::Langulus::Math::Level {::Langulus::Math::Level::Neutrino},
   "Level::Neutrino", "A canonical neutrino level"
)

LANGULUS_DEFINE_CONSTANT(LevelPlanck,
   ::Langulus::Math::Level {::Langulus::Math::Level::Planck},
   "Level::Planck", "A canonical Planck level"
)

LANGULUS_DEFINE_CONSTANT(LevelMax,
   ::Langulus::Math::Level {::Langulus::Math::Level::Max},
   "Level::Max", "A canonical max level"
)

LANGULUS_DEFINE_CONSTANT(LevelMin,
   ::Langulus::Math::Level {::Langulus::Math::Level::Min},
   "Level::Min", "A canonical min level"
)

LANGULUS_DEFINE_CONSTANT(LevelDefault,
   ::Langulus::Math::Level {::Langulus::Math::Level::Default},
   "Level::Default", "The default level"
)