#pragma once
#include <Math/Common.hpp>
#include <Flow/Resolvable.hpp>

using namespace ::Langulus;
using namespace ::Langulus::Anyness;
using namespace ::Langulus::Flow;
using namespace ::Langulus::Math;

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#define UNSIGNED_TYPES        uint8, ::std::uint16_t, ::std::uint32_t, ::std::uint64_t
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
   Fraction() : Resolvable(MetaOf<Fraction>()) {}
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

/// See https://github.com/catchorg/Catch2/blob/devel/docs/tostring.md        
#define LANGULUS_EXCEPTION_HANDLER \
   CATCH_TRANSLATE_EXCEPTION(::Langulus::Exception const& ex) { \
      const Text serialized {ex}; \
      return ::std::string {Token {serialized}}; \
   }
