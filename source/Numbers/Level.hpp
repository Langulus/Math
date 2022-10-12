///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TNumber.hpp"
#include "../Functions/Arithmetics.hpp"

namespace Langulus::Math
{

   ///                                                                        
   ///   Physical levels of simulation and instancing                         
   ///                                                                        
   ///   A level is a layer inside the world fractal. Zero level is the       
   /// human level. There are levels below, and levels above humans'.         
   /// The level number is the index of the layer in the fractal.             
   /// Each level represents a scale of 10^3 units.                           
   /// Level of zero in 3D space can contain (10^3)^3 human units.            
   /// Level of seven in 3D space can contain (10^3)^3 galaxy units.          
   /// The absolute amount of units in a level is 10^(3*(o - omin))           
   /// An entity might exist in multiple levels at the same time.             
   /// For example, a planet in planetary level can also exist as terrain on  
   /// human level, or a dot on galaxy level.                                 
   /// Generally, stuff in higher levels is more likely to affect stuff in    
   /// lower levels.                                                          
   ///                                                                        
   ///                                                                        
   /// An example of 1D level subdivisions:                                   
   ///   Planets  |                       |                       |           
   ///            +-----------------------+-----------------------+           
   ///   Humans   |           |           |           |           |           
   ///            +-----------+-----------+-----------+-----------+           
   ///   Atoms    |     |     |     |     |     |     |     |     |           
   ///                                                                        
   struct Level : public TNumber<Real, Level> {
      constexpr Level() noexcept
         : TNumber {Level::Default} {}

      constexpr Level(const Level& other) noexcept
         : TNumber {other.mValue} {}

      template<CT::Real T>
      constexpr Level(const T octave) noexcept {
         if (octave < Level::Min || octave > Level::Max)
            mValue = Level::OutOfBounds;
         mValue = octave;
      }

      template<CT::Integer T>
      constexpr Level(const T octave) noexcept {
         Real ioct;
         if constexpr (CT::Signed<T>)
            ioct = static_cast<Real>(octave);
         else
            ioct = static_cast<Real>(octave) + Level::Min;

         if (ioct < Level::Min || ioct > Level::Max)
            mValue = Level::OutOfBounds;
         mValue = ioct;
      }

      static constexpr Real Unit = 1000;
      static constexpr Real Exponent = 3;
      static constexpr Real OutOfBounds = -100;

      // Humans inhabit level 0 at scale of 1 meter                     
      static constexpr Real Human = 0;

      // Asteroids inhabit level 1 (10^3), at scale of 1 kilometer      
      // Ceres is, for example, 473 km. in radius                       
      static constexpr Real Asteroid = 1;

      // Planets inhabit level 2 (10^6), at scale of 1 megameter        
      // Earth for example is 3.1855 megameters   in radius             
      // Our sun also falls in this category, with 695.7 Mm radius      
      static constexpr Real Planet = 2;

      // Planetary systems inhabit level 3 (scale of 10^9 meters)       
      // The solar system expands to 150 gigameters radius              
      // Some of the largest stars fall into this category              
      // Like UY Scuti - 139.14 gigameters                              
      static constexpr Real System = 3;

      // Galaxies inhabit level 7 (10^21), at scale of 1 zettameter     
      // The Milky Way's radius is 0.473 zettameters                    
      // IC 1101's radius is 56.764 zettameters                         
      static constexpr Real Galaxy = 7;

      // Universes inhabit level 9 (10^27), at scale of 1... universe   
      // Our observable universe is 0.861 * (10^26) meters              
      static constexpr Real Universe = 9;

      // Cells inhabit level -2 (10^-6), at scale of 1 micrometer       
      // The human egg is 65 micrometers in radius                      
      static constexpr Real Cell = -2;

      // Viruses inhabit level -3 (10^-9), at scale of 1 nanometer      
      // The HIV virus is 65 nanometers in radius                       
      // There are ginormous virus-sized macromolecules                 
      static constexpr Real Virus = -3;

      // Atoms inhabit level -4 (10^-12), at scale of 1 picometer       
      // Atoms range from 50 pm to 250 pm   in radius                   
      static constexpr Real Atom = -4;

      // Neutrons inhabit level -5 (10^-15), at scale of 1 femtometer   
      // Radius of a neutron is 5 femtometers                           
      // The radius of an electron is 0.5 femtometers                   
      static constexpr Real Neutron = -5;

      // Quarks inhabit level -6 (10^-18), at scale of 1 attometer      
      // An up quark is 5 attometers in radius                          
      static constexpr Real Quark = -6;

      // Neutrinos inhabit level -8 (10^-24), at scale of 1 yoctometer  
      // A neutrino is 5 yoctometers in radius                          
      static constexpr Real Neutrino = -8;
   
      // Planck length inhabits level -12 (10^-36)                      
      // A Planck length is about 0.8 * (10^-35) meters in radius       
      static constexpr Real Planck = -12;

      static constexpr Real Max = Universe;
      static constexpr Real Min = Planck;
      static constexpr Real Range = Level::Max - Level::Min + 1;
      static constexpr Offset RangeInt = static_cast<Offset>(Level::Max - Level::Min + 1);

      // Human is the default level                                     
      static constexpr Real Default = Human;

      /// Get a factor for scaling a relative level to this one               
      ///   @param level - the level to factor against                        
      ///   @param return the invlog scale that maps this to other            
      inline Real GetFactor(const Level& level) const noexcept {
         return Math::Pow(Unit, level.mValue - mValue);
      }

      /// Get a reference point between two levels                            
      ///   @param level - the other level                                    
      ///   @return a middle level between this and other                     
      constexpr Level GetRefPoint(const Level& level) const noexcept {
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
      constexpr static Level GetRefPoint(const Level& o1, const Level& o2) noexcept {
         return o1.GetRefPoint(o2);
      }

      /// Get a zero based offset from this level                             
      ///   @return the zero-based offset                                     
      constexpr Real GetOffset() const noexcept {
         return mValue - Level::Min;
      }

      /// Get a zero based offset from this level (as integer)                
      ///   @return the zero-based offset                                     
      constexpr Offset GetOffsetInt() const noexcept {
         return static_cast<Offset>(mValue - Level::Min);
      }
   };

} // namespace Langulus::Math
