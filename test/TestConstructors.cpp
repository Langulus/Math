///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Math/Vector.hpp>
#include <catch2/catch.hpp>

LANGULUS_EXCEPTION_HANDLER

TEMPLATE_TEST_CASE("Vector static creation from code", "[vec]",
   Vec1, Vec2, Vec3, Vec4
) {
   Allocator::State memoryState;

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

      // Check for memory leaks after each cycle                        
      REQUIRE(memoryState.Assert());
   }
}
