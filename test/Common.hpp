///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           

/// INTENTIONALLY NOT GUARDED                                                 
/// Include this file once in each cpp file, after all other headers          
#include <Langulus/Math/Config.hpp>
#include <Langulus/Flow/Downcastable.hpp>
#include <Langulus/Testing.hpp>

using namespace Math;
using namespace Flow;

/// A mockup of a fraction                                                    
struct Fraction : public Flow::Resolvable {
   using CTTI_Abstract = No;
   LANGULUS_BASES(Resolvable);
   Fraction() : Downcastable {this} {}
};