///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include <Math/Config.hpp>
#include <Flow/Resolvable.hpp>

using namespace ::Langulus;
using namespace ::Langulus::Anyness;
using namespace ::Langulus::Flow;
using namespace ::Langulus::Math;

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#define UNSIGNED_TYPES        ::std::uint8_t, ::std::uint16_t, ::std::uint32_t, ::std::uint64_t
#define REAL_TYPES            Float, Double
#define SIGNED_INTEGER_TYPES  ::std::int8_t, ::std::int16_t, ::std::int32_t, ::std::int64_t
#define INTEGER_TYPES         UNSIGNED_TYPES, SIGNED_INTEGER_TYPES
#define SIGNED_TYPES          SIGNED_INTEGER_TYPES, REAL_TYPES
#define ALL_TYPES             UNSIGNED_TYPES, SIGNED_TYPES

/// A mockup of a fraction                                                    
struct Fraction : public Flow::Resolvable {
   LANGULUS(ABSTRACT) false;
   LANGULUS(UNINSERTABLE) false;
   LANGULUS_BASES(Resolvable);
   Fraction() : Resolvable {this} {}
};

/// Dump parse results and requirements                                       
template<class INPUT, class OUTPUT, class REQUIRED>
void DumpResults(const INPUT& in, const OUTPUT& out, const REQUIRED& required) {
   Logger::Special("-------------");
   Logger::Special("Script:   ", in);
   Logger::Special("Parsed:   ", out);
   Logger::Special("Required: ", required);
   Logger::Special("-------------");
}