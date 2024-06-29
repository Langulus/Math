///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "TAngle.inl"


namespace Langulus::Math
{

   /// Register angle types                                                   
   void RegisterAngles() {
      (void) MetaOf<Degrees>();
      (void) MetaOf<Radians>();
             
      (void) MetaOf<Yawdf>();
      (void) MetaOf<Yawdd>();
      (void) MetaOf<Yawrf>();
      (void) MetaOf<Yawrd>();
             
      (void) MetaOf<Pitchdf>();
      (void) MetaOf<Pitchdd>();
      (void) MetaOf<Pitchrf>();
      (void) MetaOf<Pitchrd>();
             
      (void) MetaOf<Rolldf>();
      (void) MetaOf<Rolldd>();
      (void) MetaOf<Rollrf>();
      (void) MetaOf<Rollrd>();
   }

} // namespace Langulus::Math
