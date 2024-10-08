///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Math/Quaternion.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Quaternions", "[quat]", REAL_TYPES) {
	GIVEN("An uninitialized quaternion") {
		using T = TestType;
		TQuaternion<T> x;

		WHEN("Creating a default quaternion") {
			REQUIRE(x[0] == 0);
			REQUIRE(x[1] == 0);
			REQUIRE(x[2] == 0);
			REQUIRE(x[3] == 1);
		}

		WHEN("Creating a quaternion from an axis and angle") {
			x = TQuaternion<T>::FromAxis(Axes::Up<T>, Degrees(45));

			REQUIRE(x[0] == 0);
			REQUIRE(x[1] == Approx(0.3826834323));
			REQUIRE(x[2] == 0);
			REQUIRE(x[3] == Approx(0.9238795325));
		}

		WHEN("Creating a quaternion from an axis and angle, and then normalizing it") {
			x = TQuaternion<T>::FromAxis(Axes::Up<T>, Degrees(45));
			x = x.Normalize();

			REQUIRE(x[0] == 0);
			REQUIRE(x[1] == Approx(0.3826834323));
			REQUIRE(x[2] == 0);
			REQUIRE(x[3] == Approx(0.9238795325));
		}

		WHEN("Creating a quaternion from an axis and angle, and then converting it to a 3x3 rotation matrix") {
			x = TQuaternion<T>::FromAxis(Axes::Up<T>, Degrees(45));
			auto as_mat = static_cast<TMatrix<T, 3, 3>>(x);

			REQUIRE(as_mat[0][0] == Approx(0.70710678));
			REQUIRE(as_mat[1][0] == 0);
			REQUIRE(as_mat[2][0] == Approx(0.70710678));
			REQUIRE(as_mat[0][1] == 0);
			REQUIRE(as_mat[1][1] == 1);
			REQUIRE(as_mat[2][1] == 0);
			REQUIRE(as_mat[0][2] == Approx(-0.70710678));
			REQUIRE(as_mat[1][2] == 0);
			REQUIRE(as_mat[2][2] == Approx(0.70710678));
		}
	}

	GIVEN("Two quaternions and a resulting quaternion") {
		using T = TestType;
		TQuaternion<T> x, y, r;
		x = TQuaternion<T>::FromAxis(Axes::Up<T>, Degrees(45));
		y = TQuaternion<T>::FromAxis(Axes::Right<T>, Degrees(45));

		REQUIRE(y[0] == Approx(0.3826834324));
		REQUIRE(y[1] == 0);
		REQUIRE(y[2] == 0);
		REQUIRE(y[3] == Approx(0.9238795325));

		WHEN("Multiplying the quaternions") {
			r = x * y;

			REQUIRE(r[0] == Approx(0.3535533906));
			REQUIRE(r[1] == Approx(0.3535533906));
			REQUIRE(r[2] == Approx(-0.1464466094));
			REQUIRE(r[3] == Approx(0.8535533906));
		}

		WHEN("Multiplying the quaternions in reverse order") {
			r = y * x;

			REQUIRE(r[0] == Approx(0.3535533906));
			REQUIRE(r[1] == Approx(0.3535533906));
			REQUIRE(r[2] == Approx(0.1464466094));
			REQUIRE(r[3] == Approx(0.8535533906));
		}
	}

	GIVEN("An initialized quaternion and a point in space") {
		using T = TestType;
		TQuaternion<T> orientation;
		TVector<T, 3> point;

		orientation = TQuaternion<T>::FromAxis(Axes::Up<T>, Degrees(45));
		point = {0, 0, 50};

		WHEN("Doing a quaternion * point multiplication") {
			TVector<T, 3> r1 = orientation * point;
			TVector<T, 3> r2 = point * orientation;

			REQUIRE(r1 != r2);

			REQUIRE(r1.Length() == Approx(50));
			REQUIRE(r1[0] == Approx(-35.35533906));
			REQUIRE(r1[1] == 0);
			REQUIRE(r1[2] == Approx(35.35533906));

			REQUIRE(r2.Length() == Approx(50));
			REQUIRE(r2[0] == Approx(35.35533906));
			REQUIRE(r2[1] == 0);
			REQUIRE(r2[2] == Approx(35.35533906));
		}

		WHEN("Doing a static_cast<mat3>(quaternion) * point multiplication") {
			TVector<T, 3> r1 = TMatrix<T, 3, 3>(orientation) * point;
			TVector<T, 3> r2 = point * TMatrix<T, 3, 3>(orientation);

			REQUIRE(r1 != r2);

			REQUIRE(r1.Length() == Approx(50));
			REQUIRE(r1[0] == Approx(35.35533906));
			REQUIRE(r1[1] == 0);
			REQUIRE(r1[2] == Approx(35.35533906));

			REQUIRE(r2.Length() == Approx(50));
			REQUIRE(r2[0] == Approx(-35.35533906));
			REQUIRE(r2[1] == 0);
			REQUIRE(r2[2] == Approx(35.35533906));
		}

		WHEN("When doing a conversions matrix -> quat, and quat -> matrix") {
			auto matrix = TMatrix<T, 3, 3>(orientation);
			auto back_to_quat = TQuaternion<T>(matrix);
			REQUIRE(back_to_quat[0] == Approx(orientation[0]));
			REQUIRE(back_to_quat[1] == Approx(orientation[1]));
			REQUIRE(back_to_quat[2] == Approx(orientation[2]));
			REQUIRE(back_to_quat[3] == Approx(orientation[3]));
		}
	}
}