///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Numbers/TAngle.hpp"


namespace Langulus::Math
{

   /// Register angle types                                                   
   inline void RegisterAngles() {
      (void)MetaOf<Degrees>();
      (void)MetaOf<Radians>();

      (void)MetaOf<Yawdf>();
      (void)MetaOf<Yawdd>();
      (void)MetaOf<Yawrf>();
      (void)MetaOf<Yawrd>();

      (void)MetaOf<Pitchdf>();
      (void)MetaOf<Pitchdd>();
      (void)MetaOf<Pitchrf>();
      (void)MetaOf<Pitchrd>();

      (void)MetaOf<Rolldf>();
      (void)MetaOf<Rolldd>();
      (void)MetaOf<Rollrf>();
      (void)MetaOf<Rollrd>();
   }

} // namespace Langulus::Math