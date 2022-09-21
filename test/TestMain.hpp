///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include <LangulusMath.hpp>

using namespace ::Langulus::Math;

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#define UNSIGNED_TYPES        pcu8, pcu16, pcu32, pcu64
#define REAL_TYPES            pcr32, pcr64
#define SIGNED_INTEGER_TYPES  pci8, pci16, pci32, pci64
#define INTEGER_TYPES         UNSIGNED_TYPES, SIGNED_INTEGER_TYPES
#define SIGNED_TYPES          SIGNED_INTEGER_TYPES, REAL_TYPES
#define ALL_TYPES             UNSIGNED_TYPES, SIGNED_TYPES

