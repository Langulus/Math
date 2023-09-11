///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Math/Vectors.hpp>
#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("4D Vectors", "[vec]", SIGNED_TYPES) {
	GIVEN("An uninitialized vector") {
		using T = TestType;
		TVector<T, 4> x;

		WHEN("Creating a default vector") {
			THEN("The vector must be initialized to zero") {
				REQUIRE(x[0] == 0);
				REQUIRE(x[1] == 0);
				REQUIRE(x[2] == 0);
				REQUIRE(x[3] == 0);
			}
		}

		WHEN("Creating and asigning a vector manually") {
			x = TVector<T, 4>(0, 5, 12, 1);

			THEN("The result should be correct") {
				REQUIRE(x[0] == 0);
				REQUIRE(x[1] == 5);
				REQUIRE(x[2] == 12);
				REQUIRE(x[3] == 1);
			}
		}
	}

	GIVEN("Two vectors and a resulting vector") {
		using T = TestType;
		TVector<T, 4> x(0, 5, 12, 1);
		TVector<T, 4> y(2, 24, 4, 2);
		TVector<T, 4> r;

		WHEN("Adding the vectors") {
			r = x + y;

			THEN("The result should be correct") {
				REQUIRE(r[0] == 2);
				REQUIRE(r[1] == 29);
				REQUIRE(r[2] == 16);
				REQUIRE(r[3] == 3);
			}
		}

		WHEN("Adding the vectors in reverse order") {
			r = y + x;

			THEN("The result should be correct") {
				REQUIRE(r[0] == 2);
				REQUIRE(r[1] == 29);
				REQUIRE(r[2] == 16);
				REQUIRE(r[3] == 3);
			}
		}

		WHEN("Subtracting the vectors") {
			r = x - y;

			THEN("The result should be correct") {
				REQUIRE(r[0] == -2);
				REQUIRE(r[1] == -19);
				REQUIRE(r[2] == 8);
				REQUIRE(r[3] == -1);
			}
		}

		WHEN("Subtracting the vectors in reverse order") {
			r = y - x;

			THEN("The result should be correct") {
				REQUIRE(r[0] == 2);
				REQUIRE(r[1] == 19);
				REQUIRE(r[2] == -8);
				REQUIRE(r[3] == 1);
			}
		}

		WHEN("Multiplying the vectors") {
			r = x * y;

			THEN("The result should be correct") {
				REQUIRE(r[0] == 0);
				REQUIRE(r[1] == 120);
				REQUIRE(r[2] == 48);
				REQUIRE(r[3] == 2);
			}
		}

		WHEN("Multiplying the vectors in reverse order") {
			r = y * x;

			THEN("The result should be correct") {
				REQUIRE(r[0] == 0);
				REQUIRE(r[1] == 120);
				REQUIRE(r[2] == 48);
				REQUIRE(r[3] == 2);
			}
		}

		WHEN("Dividing the vectors") {
			r = x / y;

			THEN("The result should be correct") {
				REQUIRE(r[0] == 0);
				REQUIRE(r[1] == Approx(T(5) / T(24)));
				REQUIRE(r[2] == Approx(T(12) / T(4)));
				REQUIRE(r[3] == Approx(T(1) / T(2)));
			}
		}

		/*WHEN("Dividing the vectors in reverse order") {
			THEN("The operation should throw due to division by zero") {
				REQUIRE_THROWS(r = y / x);
			}
		}*/
	}
}