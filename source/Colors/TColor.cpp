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
      (void) MetaOf<Constants::ColorWhite>();
      (void) MetaOf<Constants::ColorBlack>();
      (void) MetaOf<Constants::ColorGrey>();
      (void) MetaOf<Constants::ColorRed>();
      (void) MetaOf<Constants::ColorGreen>();
      (void) MetaOf<Constants::ColorDarkGreen>();
      (void) MetaOf<Constants::ColorBlue>();
      (void) MetaOf<Constants::ColorDarkBlue>();
      (void) MetaOf<Constants::ColorCyan>();
      (void) MetaOf<Constants::ColorDarkCyan>();
      (void) MetaOf<Constants::ColorOrange>();
      (void) MetaOf<Constants::ColorYellow>();
      (void) MetaOf<Constants::ColorPurple>();
      (void) MetaOf<Constants::ColorDarkPurple>();
   }

} // namespace Langulus::Math