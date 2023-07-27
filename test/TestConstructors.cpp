#include "Main.hpp"
#include <Math/Vectors.hpp>
#include <catch2/catch.hpp>

LANGULUS_EXCEPTION_HANDLER

#if LANGULUS_FEATURE(MEMORY_STATISTICS)
static bool statistics_provided = false;
static Anyness::Allocator::Statistics memory_statistics;
#endif

TEMPLATE_TEST_CASE("Vector static creation from code", "[vec]",
   Vec1, Vec2, Vec3, Vec4
) {
   GIVEN("Default construction") {
      const Code code = Code {NameOf<TestType>()} + "()";
      
      WHEN("Parsed") {
         Any required = TestType {};

         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
      
      #if LANGULUS_FEATURE(MEMORY_STATISTICS)
         Fractalloc.CollectGarbage();

         // Detect memory leaks                                         
         if (statistics_provided) {
            if (memory_statistics != Fractalloc.GetStatistics()) {
               Fractalloc.DumpPools();
               memory_statistics = Fractalloc.GetStatistics();
               FAIL("Memory leak detected");
            }
         }

         memory_statistics = Fractalloc.GetStatistics();
         statistics_provided = true;
      #endif
   }
}
