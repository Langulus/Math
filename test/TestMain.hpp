///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include <LangulusMath.hpp>

using namespace ::Langulus;
using namespace ::Langulus::Anyness;
using namespace ::Langulus::Flow;
using namespace ::Langulus::Math;

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#define UNSIGNED_TYPES        uint8, ::std::uint16_t, ::std::uint32_t, ::std::uint64_t
#define REAL_TYPES            RealSP, RealDP
#define SIGNED_INTEGER_TYPES  ::std::int8_t, ::std::int16_t, ::std::int32_t, ::std::int64_t
#define INTEGER_TYPES         UNSIGNED_TYPES, SIGNED_INTEGER_TYPES
#define SIGNED_TYPES          SIGNED_INTEGER_TYPES, REAL_TYPES
#define ALL_TYPES             UNSIGNED_TYPES, SIGNED_TYPES

