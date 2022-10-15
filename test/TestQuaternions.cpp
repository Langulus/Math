#include "Main.hpp"
#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("Quaternions", "[quat]", REAL_TYPES) {
	GIVEN("An uninitialized quaternion") {
		using T = TestType;
		TQuaternion<T> x;

		WHEN("Creating a default quaternion") {
			THEN("The quaternion must be initialized to identity") {
				REQUIRE(x[0] == 0);
				REQUIRE(x[1] == 0);
				REQUIRE(x[2] == 0);
				REQUIRE(x[3] == 1);
			}
		}

		WHEN("Creating a quaternion from an axis and angle") {
			x = TQuaternion<T>::FromAxisAngle(Cardinal::Up<T>, Degrees(T(45)));

			THEN("The result should be correct") {
				REQUIRE(x[0] == 0);
				REQUIRE(x[1] == Approx(0.38268343236508978));
				REQUIRE(x[2] == 0);
				REQUIRE(x[3] == Approx(0.92387953251128674));
			}
		}

		WHEN("Creating a quaternion from an axis and angle, and then normalizing it") {
			x = TQuaternion<T>::FromAxisAngle(Cardinal::Up<T>, Degrees(T(45)));
			x = x.Normalize();

			THEN("The result should be correct") {
				REQUIRE(x[0] == 0);
				REQUIRE(x[1] == Approx(0.38268343236508978));
				REQUIRE(x[2] == 0);
				REQUIRE(x[3] == Approx(0.92387953251128674));
			}
		}

		WHEN("Creating a quaternion from an axis and angle, and then converting it to a 3x3 rotation matrix") {
			x = TQuaternion<T>::FromAxisAngle(Cardinal::Up<T>, Degrees(T(45)));
			auto as_mat = static_cast<TMatrix<T, 3, 3>>(x);

			THEN("The result should be correct") {
				REQUIRE(as_mat.Get(0, 0) == Approx(0.70710678118654746));
				REQUIRE(as_mat.Get(1, 0) == 0);
				REQUIRE(as_mat.Get(2, 0) == Approx(-0.70710678118654757));
				REQUIRE(as_mat.Get(0, 1) == 0);
				REQUIRE(as_mat.Get(1, 1) == 1);
				REQUIRE(as_mat.Get(2, 1) == 0);
				REQUIRE(as_mat.Get(0, 2) == Approx(0.70710678118654746));
				REQUIRE(as_mat.Get(1, 2) == 0);
				REQUIRE(as_mat.Get(2, 2) == Approx(0.70710678118654757));
			}
		}
	}

	GIVEN("Two quaternions and a resulting quaternion") {
		using T = TestType;
		TQuaternion<T> x, y, r;
		x = TQuaternion<T>::FromAxisAngle(Cardinal::Up<T>, Degrees(T(45)));
		y = TQuaternion<T>::FromAxisAngle(Cardinal::Right<T>, Degrees(T(45)));

		REQUIRE(y[0] == Approx(0.38268343236508978));
		REQUIRE(y[1] == 0);
		REQUIRE(y[2] == 0);
		REQUIRE(y[3] == Approx(0.92387953251128674));

		WHEN("Multiplying the quaternions") {
			r = x * y;

			THEN("The result should be correct") {
				REQUIRE(r[0] == Approx(0.35355339059327379));
				REQUIRE(r[1] == Approx(0.35355339059327379));
				REQUIRE(r[2] == Approx(-0.14644660940672624));
				REQUIRE(r[3] == Approx(0.85355339059327373));
			}
		}

		WHEN("Multiplying the quaternions in reverse order") {
			r = y * x;

			THEN("The result should be correct") {
				REQUIRE(r[0] == Approx(0.35355339059327379));
				REQUIRE(r[1] == Approx(0.35355339059327379));
				REQUIRE(r[2] == Approx(0.14644660940672624));
				REQUIRE(r[3] == Approx(0.85355339059327373));
			}
		}
	}

	GIVEN("An initialized quaternion and a point in space") {
		using T = TestType;
		TQuaternion<T> orientation;
		TVector<T, 3> point;

		orientation = TQuaternion<T>::FromAxisAngle(Cardinal::Up<T>, Degrees(T(45)));
		point = {0, 0, 50};

		WHEN("Doing a quaternion * point multiplication") {
			TVector<T, 3> r1 = orientation * point;
			TVector<T, 3> r2 = point * orientation;

			THEN("The point should be correctly transformed") {
				REQUIRE(r1 != r2);

				REQUIRE(r1.Length() == 50);
				REQUIRE(r1[0] == Approx(-35.355339059327378));
				REQUIRE(r1[1] == 0);
				REQUIRE(r1[2] == Approx(35.355339059327378));

				REQUIRE(r2.Length() == 50);
				REQUIRE(r2[0] == Approx(35.355339059327378));
				REQUIRE(r2[1] == 0);
				REQUIRE(r2[2] == Approx(35.355339059327378));
			}
		}

		WHEN("Doing a static_cast<mat3>(quaternion) * point multiplication") {
			TVector<T, 3> r1 = TMatrix<T, 3, 3>(orientation) * point;
			TVector<T, 3> r2 = point * TMatrix<T, 3, 3>(orientation);

			THEN("The point should be correctly transformed, and same as the previous test") {
				REQUIRE(r1 != r2);

				REQUIRE(r1.Length() == 50);
				REQUIRE(r1[0] == Approx(35.355339059327378));
				REQUIRE(r1[1] == 0);
				REQUIRE(r1[2] == Approx(35.355339059327378));

				REQUIRE(r2.Length() == 50);
				REQUIRE(r2[0] == Approx(-35.355339059327378));
				REQUIRE(r2[1] == 0);
				REQUIRE(r2[2] == Approx(35.355339059327378));
			}
		}

		WHEN("When doing a conversions matrix -> quat, and quat -> matrix") {
			auto matrix = TMatrix<T, 3, 3>(orientation);

			THEN("The state must be perfectly conserved") {
				auto back_to_quat = TQuaternion<T>(matrix);
				REQUIRE(back_to_quat == orientation);
			}
		}
	}
}