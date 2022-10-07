///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"
#include <catch2/catch.hpp>


TEMPLATE_TEST_CASE("4D Vectors", "[vec]", SIGNED_TYPES) {
	GIVEN("An uninitialized vector") {
		using T = TestType;
		TVector<T, 4> x;

		WHEN("Creating a default vector") {
			THEN("The vector must be initialized to zero") {
				REQUIRE(Approx(x[0], T(0)));
				REQUIRE(Approx(x[1], T(0)));
				REQUIRE(Approx(x[2], T(0)));
				REQUIRE(Approx(x[3], T(0)));
			}
		}

		WHEN("Creating and asigning a vector manually") {
			x = TVector<T, 4>(T(0), T(5), T(12), T(1));

			THEN("The result should be correct") {
				REQUIRE(Approx(x[0], T(0)));
				REQUIRE(Approx(x[1], T(5)));
				REQUIRE(Approx(x[2], T(12)));
				REQUIRE(Approx(x[3], T(1)));
			}
		}
	}

	GIVEN("Two vectors and a resulting vector") {
		using T = TestType;
		TVector<T, 4> x(T(0), T(5), T(12), T(1));
		TVector<T, 4> y(T(2), T(24), T(4), T(2));
		TVector<T, 4> r;

		WHEN("Adding the vectors") {
			r = x + y;

			THEN("The result should be correct") {
				REQUIRE(Approx(r[0], T(2)));
				REQUIRE(Approx(r[1], T(29)));
				REQUIRE(Approx(r[2], T(16)));
				REQUIRE(Approx(r[3], T(3)));
			}
		}

		WHEN("Adding the vectors in reverse order") {
			r = y + x;

			THEN("The result should be correct") {
				REQUIRE(Approx(r[0], T(2)));
				REQUIRE(Approx(r[1], T(29)));
				REQUIRE(Approx(r[2], T(16)));
				REQUIRE(Approx(r[3], T(3)));
			}
		}

		WHEN("Subtracting the vectors") {
			r = x - y;

			THEN("The result should be correct") {
				REQUIRE(Approx(r[0], T(-2)));
				REQUIRE(Approx(r[1], T(-19)));
				REQUIRE(Approx(r[2], T(8)));
				REQUIRE(Approx(r[3], T(-1)));
			}
		}

		WHEN("Subtracting the vectors in reverse order") {
			r = y - x;

			THEN("The result should be correct") {
				REQUIRE(Approx(r[0], T(2)));
				REQUIRE(Approx(r[1], T(19)));
				REQUIRE(Approx(r[2], T(-8)));
				REQUIRE(Approx(r[3], T(1)));
			}
		}

		WHEN("Multiplying the vectors") {
			r = x * y;

			THEN("The result should be correct") {
				REQUIRE(Approx(r[0], T(0)));
				REQUIRE(Approx(r[1], T(120)));
				REQUIRE(Approx(r[2], T(48)));
				REQUIRE(Approx(r[3], T(2)));
			}
		}

		WHEN("Multiplying the vectors in reverse order") {
			r = y * x;

			THEN("The result should be correct") {
				REQUIRE(Approx(r[0], T(0)));
				REQUIRE(Approx(r[1], T(120)));
				REQUIRE(Approx(r[2], T(48)));
				REQUIRE(Approx(r[3], T(2)));
			}
		}

		WHEN("Dividing the vectors") {
			r = x / y;

			THEN("The result should be correct") {
				REQUIRE(Approx(r[0], T(0) / T(2)));
				REQUIRE(Approx(r[1], T(5) / T(24)));
				REQUIRE(Approx(r[2], T(12) / T(4)));
				REQUIRE(Approx(r[3], T(1) / T(2)));
			}
		}

		/*WHEN("Dividing the vectors in reverse order") {
			THEN("The operation should throw due to division by zero") {
				REQUIRE_THROWS(r = y / x);
			}
		}*/
	}
}