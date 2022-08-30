#pragma once
#include <PCFW.Math.hpp>
using namespace PCFW;
using namespace Memory;
using namespace Math;
using namespace Flow;

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#define UNSIGNED_TYPES        pcu8, pcu16, pcu32, pcu64
#define REAL_TYPES            pcr32, pcr64
#define SIGNED_INTEGER_TYPES  pci8, pci16, pci32, pci64
#define INTEGER_TYPES         UNSIGNED_TYPES, SIGNED_INTEGER_TYPES
#define SIGNED_TYPES          SIGNED_INTEGER_TYPES, REAL_TYPES
#define ALL_TYPES             UNSIGNED_TYPES, SIGNED_TYPES

