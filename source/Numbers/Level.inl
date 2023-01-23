///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Level.hpp"

namespace Langulus::Math
{

   /// Default (human level) construction                                     
   LANGULUS(ALWAYSINLINE)
   constexpr Level::Level() noexcept
      : TNumber {Level::Default} {}

   /// Real number construction                                               
   ///   @param octave - the real number to interpret as level                
   LANGULUS(ALWAYSINLINE)
   constexpr Level::Level(const CT::Real auto& octave) noexcept {
      if (octave < Level::Min || octave > Level::Max)
         mValue = Level::OutOfBounds;
      mValue = static_cast<Real>(octave);
   }

   /// Integer number construction                                            
   ///   @attention unsigned integers will be remapped to the signed range    
   ///   @param octave - the integer to interpret as level                    
   LANGULUS(ALWAYSINLINE)
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
   LANGULUS(ALWAYSINLINE)
   Real Level::GetFactor(const Level& level) const noexcept {
      return Math::Pow(Unit, level.mValue - mValue);
   }

   /// Get a reference point between two levels                               
   ///   @param level - the other level                                       
   ///   @return a middle level between this and other                        
   LANGULUS(ALWAYSINLINE)
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
   LANGULUS(ALWAYSINLINE)
   constexpr Level Level::GetRefPoint(const Level& o1, const Level& o2) noexcept {
      return o1.GetRefPoint(o2);
   }

   /// Get a zero based offset from this level                                
   ///   @return the zero-based offset                                        
   LANGULUS(ALWAYSINLINE)
   constexpr Real Level::GetOffset() const noexcept {
      return mValue - Level::Min;
   }

   /// Get a zero based offset from this level (as integer)                   
   ///   @return the zero-based offset                                        
   LANGULUS(ALWAYSINLINE)
   constexpr Offset Level::GetOffsetInt() const noexcept {
      return static_cast<Offset>(mValue - Level::Min);
   }

} // namespace Langulus::Math
