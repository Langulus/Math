///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "TColor.inl"


namespace Langulus::Math
{

   /// Register all commonly used color types and constants, so they can be   
   /// instantiated from scripts                                              
   void RegisterColors() {
      // Types                                                          
      (void) MetaOf<RGB24>();
      (void) MetaOf<RGB96>();
      (void) MetaOf<RGBA32>();
      (void) MetaOf<RGBA128>();

      (void) MetaOf<Red8>();
      (void) MetaOf<Green8>();
      (void) MetaOf<Blue8>();
      (void) MetaOf<Alpha8>();

      (void) MetaOf<Red32>();
      (void) MetaOf<Green32>();
      (void) MetaOf<Blue32>();
      (void) MetaOf<Alpha32>();

      (void) MetaOf<Depth16>();
      (void) MetaOf<Depth32>();

      // Constants                                                      
      (void) MetaOf<Constants::White>();
      (void) MetaOf<Constants::Black>();
      (void) MetaOf<Constants::Grey>();
      (void) MetaOf<Constants::Red>();
      (void) MetaOf<Constants::Green>();
      (void) MetaOf<Constants::DarkGreen>();
      (void) MetaOf<Constants::Blue>();
      (void) MetaOf<Constants::DarkBlue>();
      (void) MetaOf<Constants::Cyan>();
      (void) MetaOf<Constants::DarkCyan>();
      (void) MetaOf<Constants::Orange>();
      (void) MetaOf<Constants::Yellow>();
      (void) MetaOf<Constants::Purple>();
      (void) MetaOf<Constants::DarkPurple>();
   }

} // namespace Langulus::Math