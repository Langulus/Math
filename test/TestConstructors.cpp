﻿///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Math/Vector.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Vector static creation from code", "[vec]",
   Vec1, Vec2, Vec3, Vec4
) {
   Allocator::State memoryState;

   GIVEN("Default construction") {
      const Code code = Code {NameOf<TestType>()} + "()";
      
      WHEN("Parsed") {
         Many required = TestType {};
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         REQUIRE(parsed == required);
      }

      // Check for memory leaks after each cycle                        
      REQUIRE(memoryState.Assert());
   }
}
