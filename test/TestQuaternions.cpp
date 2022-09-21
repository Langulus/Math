///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"
#include <catch2/catch.hpp>


TEMPLATE_TEST_CASE("Quaternions", "[quat]", REAL_TYPES) {
	GIVEN("An uninitialized quaternion") {
		using T = TestType;
		TQuat<T> x;

		WHEN("Creating a default quaternion") {
			THEN("The quaternion must be initialized to identity") {
				REQUIRE(pcNear(x[0], T(0)));
				REQUIRE(pcNear(x[1], T(0)));
				REQUIRE(pcNear(x[2], T(0)));
				REQUIRE(pcNear(x[3], T(1)));
			}
		}

		WHEN("Creating a quaternion from an axis and angle") {
			x = TQuat<T>::FromAxisAngle(Vectors::Up<T>, pcD2R(T(45)));

			THEN("The result should be correct") {
				REQUIRE(pcNear(x[0], T(0)));
				REQUIRE(pcNear(x[1], T(0.38268343236508978)));
				REQUIRE(pcNear(x[2], T(0)));
				REQUIRE(pcNear(x[3], T(0.92387953251128674)));
			}
		}

		WHEN("Creating a quaternion from an axis and angle, and then normalizing it") {
			x = TQuat<T>::FromAxisAngle(Vectors::Up<T>, pcD2R(T(45)));
			x = x.Normalize();

			THEN("The result should be correct") {
				REQUIRE(pcNear(x[0], T(0)));
				REQUIRE(pcNear(x[1], T(0.38268343236508978)));
				REQUIRE(pcNear(x[2], T(0)));
				REQUIRE(pcNear(x[3], T(0.92387953251128674)));
			}
		}

		WHEN("Creating a quaternion from an axis and angle, and then converting it to a 3x3 rotation matrix") {
			x = TQuat<T>::FromAxisAngle(Vectors::Up<T>, pcD2R(T(45)));
			auto as_mat = static_cast<TMat<T, 3, 3>>(x);

			THEN("The result should be correct") {
				REQUIRE(pcNear(as_mat.Get(0, 0), T(0.70710678118654746)));
				REQUIRE(pcNear(as_mat.Get(1, 0), T(0)));
				REQUIRE(pcNear(as_mat.Get(2, 0), T(-0.70710678118654757)));
				REQUIRE(pcNear(as_mat.Get(0, 1), T(0)));
				REQUIRE(pcNear(as_mat.Get(1, 1), T(1)));
				REQUIRE(pcNear(as_mat.Get(2, 1), T(0)));
				REQUIRE(pcNear(as_mat.Get(0, 2), T(0.70710678118654746)));
				REQUIRE(pcNear(as_mat.Get(1, 2), T(0)));
				REQUIRE(pcNear(as_mat.Get(2, 2), T(0.70710678118654757)));
			}
		}
	}

	GIVEN("Two quaternions and a resulting quaternion") {
		using T = TestType;
		TQuat<T> x, y, r;
		x = TQuat<T>::FromAxisAngle(Vectors::Up<T>, pcD2R(T(45)));
		y = TQuat<T>::FromAxisAngle(Vectors::Right<T>, pcD2R(T(45)));

		REQUIRE(pcNear(y[0], T(0.38268343236508978)));
		REQUIRE(pcNear(y[1], T(0)));
		REQUIRE(pcNear(y[2], T(0)));
		REQUIRE(pcNear(y[3], T(0.92387953251128674)));

		WHEN("Multiplying the quaternions") {
			r = x * y;

			THEN("The result should be correct") {
				REQUIRE(pcNear(r[0], T(0.35355339059327379)));
				REQUIRE(pcNear(r[1], T(0.35355339059327379)));
				REQUIRE(pcNear(r[2], T(-0.14644660940672624)));
				REQUIRE(pcNear(r[3], T(0.85355339059327373)));
			}
		}

		WHEN("Multiplying the quaternions in reverse order") {
			r = y * x;

			THEN("The result should be correct") {
				REQUIRE(pcNear(r[0], T(0.35355339059327379)));
				REQUIRE(pcNear(r[1], T(0.35355339059327379)));
				REQUIRE(pcNear(r[2], T(0.14644660940672624)));
				REQUIRE(pcNear(r[3], T(0.85355339059327373)));
			}
		}
	}

	GIVEN("An initialized quaternion and a point in space") {
		using T = TestType;
		TQuat<T> orientation;
		TVec<T, 3> point;

		orientation = TQuat<T>::FromAxisAngle(Vectors::Up<T>, pcD2R(T(45)));
		point = { 0, 0, 50 };

		WHEN("Doing a quaternion * point multiplication") {
			TVec<T, 3> r1 = orientation * point;
			TVec<T, 3> r2 = point * orientation;

			THEN("The point should be correctly transformed") {
				REQUIRE(r1 != r2);

				REQUIRE(pcNear(r1.Length(), T(50)));
				REQUIRE(pcNear(r1[0], T(-35.355339059327378)));
				REQUIRE(pcNear(r1[1], T(0)));
				REQUIRE(pcNear(r1[2], T(35.355339059327378)));

				REQUIRE(pcNear(r2.Length(), T(50)));
				REQUIRE(pcNear(r2[0], T(35.355339059327378)));
				REQUIRE(pcNear(r2[1], T(0)));
				REQUIRE(pcNear(r2[2], T(35.355339059327378)));
			}
		}

		WHEN("Doing a static_cast<mat3>(quaternion) * point multiplication") {
			TVec<T, 3> r1 = TMat<T, 3, 3>(orientation) * point;
			TVec<T, 3> r2 = point * TMat<T, 3, 3>(orientation);

			THEN("The point should be correctly transformed, and same as the previous test") {
				REQUIRE(r1 != r2);

				REQUIRE(pcNear(r1.Length(), T(50)));
				REQUIRE(pcNear(r1[0], T(35.355339059327378)));
				REQUIRE(pcNear(r1[1], T(0)));
				REQUIRE(pcNear(r1[2], T(35.355339059327378)));

				REQUIRE(pcNear(r2.Length(), T(50)));
				REQUIRE(pcNear(r2[0], T(-35.355339059327378)));
				REQUIRE(pcNear(r2[1], T(0)));
				REQUIRE(pcNear(r2[2], T(35.355339059327378)));
			}
		}

		WHEN("When doing a conversions matrix -> quat, and quat -> matrix") {
			auto matrix = TMat<T, 3, 3>(orientation);

			THEN("The state must be perfectly conserved") {
				auto back_to_quat = TQuat<T>(matrix);
				REQUIRE(back_to_quat == orientation);
			}
		}
	}
}