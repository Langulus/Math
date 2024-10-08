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
