///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"
#include <catch2/catch.hpp>


TEMPLATE_TEST_CASE("Matrices", "[mat]", REAL_TYPES) {
	using T = TestType;
	using testMat2 = TMatrix<T, 2, 2>;
	using testMat3 = TMatrix<T, 3, 3>;
	using testMat4 = TMatrix<T, 4, 4>;
	using testVec2 = TVector<T, 2>;
	using testVec3 = TVector<T, 3>;
	using testVec4 = TVector<T, 4>;

	GIVEN("An uninitialized matrix") {
		testMat2 x2;
		testMat3 x3;
		testMat4 x4;

		WHEN("Creating default matrices") {
			THEN("Matrices should be initialized to identity") {
				REQUIRE(x2[0] == 1);
				REQUIRE(x2[1] == 0);
				REQUIRE(x2[2] == 0);
				REQUIRE(x2[3] == 1);

				REQUIRE(x3[0] == 1);
				REQUIRE(x3[1] == 0);
				REQUIRE(x3[2] == 0);
				REQUIRE(x3[3] == 0);
				REQUIRE(x3[4] == 1);
				REQUIRE(x3[5] == 0);
				REQUIRE(x3[6] == 0);
				REQUIRE(x3[7] == 0);
				REQUIRE(x3[8] == 1);

				REQUIRE(x4[0] == 1);
				REQUIRE(x4[1] == 0);
				REQUIRE(x4[2] == 0);
				REQUIRE(x4[3] == 0);
				REQUIRE(x4[4] == 0);
				REQUIRE(x4[5] == 1);
				REQUIRE(x4[6] == 0);
				REQUIRE(x4[7] == 0);
				REQUIRE(x4[8] == 0);
				REQUIRE(x4[9] == 0);
				REQUIRE(x4[10] == 1);
				REQUIRE(x4[11] == 0);
				REQUIRE(x4[12] == 0);
				REQUIRE(x4[13] == 0);
				REQUIRE(x4[14] == 0);
				REQUIRE(x4[15] == 1);
			}
		}

		WHEN("Creating a translation matrix") {
			x4 = testMat4::Translation({5, 12, 2, 555});

			THEN("The result should be correct") {
				REQUIRE(x4.Row(3)[0] == T(5));
				REQUIRE(x4[12] == T(5));
				REQUIRE(x4.Get(0, 3) == T(5));
				REQUIRE(x4.Row(3)[1] == T(12));
				REQUIRE(x4[13] == T(12));
				REQUIRE(x4.Get(1, 3) == T(12));
				REQUIRE(x4.Row(3)[2] == T(2));
				REQUIRE(x4[14] == T(2));
				REQUIRE(x4.Get(2, 3) == T(2));
				REQUIRE(x4.Row(3)[3] == T(1));
				REQUIRE(x4[15] == T(1));
				REQUIRE(x4.Get(3, 3) == T(1));
			}
		}

		WHEN("Creating a rotation matrix") {
			x2 = testMat2::Rotation(DegToRad(45));
			x3 = testMat3::Rotation(DegToRad(45), DegToRad(45), 0);
			x4 = testMat4::Rotation(DegToRad(45), DegToRad(45), 0);
			testMat4 x4z = testMat4::Rotation(0, 0, DegToRad(45));

			THEN("The result should be correct") {
				REQUIRE(x2.Get(0, 0) == Approx(0.7071069));
				REQUIRE(x2.Get(1, 0) == Approx(-0.7071066));
				REQUIRE(x2.Get(0, 1) == Approx(0.7071066));
				REQUIRE(x2.Get(1, 1) == Approx(0.7071069));
				REQUIRE(x2[0] == Approx(0.7071069));
				REQUIRE(x2[1] == Approx(-0.7071066));
				REQUIRE(x2[2] == Approx(0.7071066));
				REQUIRE(x2[3] == Approx(0.7071069));

				REQUIRE(x4z.Get(0, 0) == Approx(0.7071069));
				REQUIRE(x4z.Get(1, 0) == Approx(-0.7071066));
				REQUIRE(x4z.Get(0, 1) == Approx(0.7071066));
				REQUIRE(x4z.Get(1, 1) == Approx(0.7071069));
				REQUIRE(x4z[0] == Approx(0.7071069));
				REQUIRE(x4z[1] == Approx(-0.7071066));
				REQUIRE(x4z[4] == Approx(0.7071066));
				REQUIRE(x4z[5] == Approx(0.7071069));

				REQUIRE(x3.Get(0, 0) == Approx(0.7071069));
				REQUIRE(x3.Get(1, 0) == 0);
				REQUIRE(x3.Get(2, 0) == Approx(0.7071066));
				REQUIRE(x3.Get(0, 1) == Approx(0.4999999));
				REQUIRE(x3.Get(1, 1) == Approx(0.7071069));
				REQUIRE(x3.Get(2, 1) == Approx(-0.5000000));
				REQUIRE(x3.Get(0, 2) == Approx(-0.5000000));
				REQUIRE(x3.Get(1, 2) == Approx(0.7071066));
				REQUIRE(x3.Get(2, 2) == Approx(0.5000000));
				REQUIRE(x3[0] == Approx(0.7071069));
				REQUIRE(x3[1] == 0);
				REQUIRE(x3[2] == Approx(0.7071066));
				REQUIRE(x3[3] == Approx(0.4999999));
				REQUIRE(x3[4] == Approx(0.7071069));
				REQUIRE(x3[5] == Approx(-0.5000000));
				REQUIRE(x3[6] == Approx(-0.5000000));
				REQUIRE(x3[7] == Approx(0.7071066));
				REQUIRE(x3[8] == Approx(0.5000000));

				REQUIRE(x4.Get(0, 0) == Approx(0.7071069));
				REQUIRE(x4.Get(1, 0) == 0);
				REQUIRE(x4.Get(2, 0) == Approx(0.7071066));
				REQUIRE(x4.Get(3, 0) == 0);
				REQUIRE(x4.Get(0, 1) == Approx(0.4999999));
				REQUIRE(x4.Get(1, 1) == Approx(0.7071069));
				REQUIRE(x4.Get(2, 1) == Approx(-0.5000000));
				REQUIRE(x4.Get(3, 1) == 0);
				REQUIRE(x4.Get(0, 2) == Approx(-0.5000000));
				REQUIRE(x4.Get(1, 2) == Approx(0.7071066));
				REQUIRE(x4.Get(2, 2) == Approx(0.5000000));
				REQUIRE(x4.Get(3, 2) == 0);
				REQUIRE(x4.Get(0, 3) == 0);
				REQUIRE(x4.Get(1, 3) == 0);
				REQUIRE(x4.Get(2, 3) == 0);
				REQUIRE(x4.Get(3, 3) == 1);
				REQUIRE(x4[0] == Approx(0.7071069));
				REQUIRE(x4[1] == 0);
				REQUIRE(x4[2] == Approx(0.7071066));
				REQUIRE(x4[3] == 0);
				REQUIRE(x4[4] == Approx(0.4999999));
				REQUIRE(x4[5] == Approx(0.7071069));
				REQUIRE(x4[6] == Approx(-0.5000000));
				REQUIRE(x4[7] == 0);
				REQUIRE(x4[8] == Approx(-0.5000000));
				REQUIRE(x4[9] == Approx(0.7071066));
				REQUIRE(x4[10] == Approx(0.5000000));
				REQUIRE(x4[11] == 0);
				REQUIRE(x4[12] == 0);
				REQUIRE(x4[13] == 0);
				REQUIRE(x4[14] == 0);
				REQUIRE(x4[15] == 1);
			}
		}

		WHEN("Creating a scalar matrix") {
			x2 = testMat2::Scalar(testVec2(1, 2));
			x3 = testMat3::Scalar(testVec3(1, 2, 3));
			x4 = testMat4::Scalar(testVec4(1, 2, 3, 4));

			THEN("The result should be correct") {
				REQUIRE((x2.Get(0, 0) == T(1) && x2[0] == T(1)));
				REQUIRE((x2.Get(1, 0) == T(0) && x2[1] == T(0)));
				REQUIRE((x2.Get(0, 1) == T(0) && x2[2] == T(0)));
				REQUIRE((x2.Get(1, 1) == T(2) && x2[3] == T(2)));
			}
		}
	}

	GIVEN("Given a 3x3 rotation matrix") {
		auto y3 = testMat3::Rotation(DegToRad(T(45)), DegToRad(T(45)), 0);

		WHEN("Getting the inverse") {
			auto r = y3.Invert();
			THEN("The result should be correct") {
				REQUIRE(r[0] == Approx(0.707106918439098));
				REQUIRE(r[1] == Approx(0.49999976286795883));
				REQUIRE(r[2] == Approx(-0.4999999749999469));

				REQUIRE(r[3] == 0);
				REQUIRE(r[4] == Approx(0.707106918439098));
				REQUIRE(r[5] == Approx(0.7071067063070499));

				REQUIRE(r[6] == Approx(0.7071067063070499));
				REQUIRE(r[7] == Approx(-0.4999999749999469));
				REQUIRE(r[8] == Approx(0.5000001871320249));
			}
		}
	}

	GIVEN("Given a 4x4 rotation and translation matrix") {
		auto y4 = testMat4::Rotation(DegToRad(T(45)), DegToRad(T(45)), 0)
			.SetPosition({15, 29, -5});

		WHEN("Getting the inverse") {
			auto r = y4.Invert();
			THEN("The result should be correct") {
				REQUIRE(r[0] == Approx(0.707106918439098));
				REQUIRE(r[1] == Approx(0.49999976286795883));
				REQUIRE(r[2] == Approx(-0.4999999749999469));
				REQUIRE(r[3] == 0);

				REQUIRE(r[4] == 0);
				REQUIRE(r[5] == Approx(0.707106918439098));
				REQUIRE(r[6] == Approx(0.7071067063070499));
				REQUIRE(r[7] == 0);

				REQUIRE(r[8] == Approx(0.7071067063070499));
				REQUIRE(r[9] == Approx(-0.4999999749999469));
				REQUIRE(r[10] == Approx(0.5000001871320249));
				REQUIRE(r[11] == 0);

				REQUIRE(r[12] == Approx(-7.071068795051746));
				REQUIRE(r[13] == Approx(-30.506096952752955));
				REQUIRE(r[14] == Approx(-10.506093922245118));
				REQUIRE(r[15] == 1);
			}
		}
	}

	GIVEN("Two matrices and a resulting matrix") {
		auto x2 = testMat2::Rotation(DegToRad(45));
		auto y2 = testMat2::Rotation(DegToRad(45));
		testMat2 r2;

		auto x3 = testMat3::Rotation(0, DegToRad(45), 0);
		auto y3 = testMat3::Rotation(DegToRad(45), DegToRad(45), 0);
		testMat3 r3;

		auto x4 = testMat4::Rotation(0, DegToRad(45), 0)
			.SetPosition({4, 13, 9});
		auto y4 = testMat4::Rotation(DegToRad(45), DegToRad(45), 0)
			.SetPosition({50, 25, 2});
		testMat4 r4;

		WHEN("Calculating determinants") {
			auto x2d = x2.Determinant();
			auto y2d = y2.Determinant();
			auto x3d = x3.Determinant();
			auto y3d = y3.Determinant();
			auto x4d = x4.Determinant();
			auto y4d = y4.Determinant();

			THEN("The result should be correct") {
				REQUIRE(x2d == 1);
				REQUIRE(y2d == 1);
				REQUIRE(x3d == 1);
				REQUIRE(y3d == 1);
				REQUIRE(x4d == 1);
				REQUIRE(y4d == 1);
			}
		}

		WHEN("Multiplying the matrices") {
			r2 = x2 * y2;
			r3 = x3 * y3;
			r4 = x4 * y4;

			THEN("The result should be correct") {
				REQUIRE(r2[0] == 0);
				REQUIRE(r2[1] == -1);
				REQUIRE(r2[2] == 1);
				REQUIRE(r2[3] == 0);

				REQUIRE(r3[0] == Approx(0.1464469));
				REQUIRE(r3[1] == Approx(0.4999997));
				REQUIRE(r3[2] == Approx(0.8535534));
				REQUIRE(r3[3] == Approx(0.4999999));
				REQUIRE(r3[4] == Approx(0.7071069));
				REQUIRE(r3[5] == Approx(-0.5));
				REQUIRE(r3[6] == Approx(-0.8535534));
				REQUIRE(r3[7] == Approx(0.5));
				REQUIRE(r3[8] == Approx(-0.1464462));

				REQUIRE(r4[0] == Approx(0.1464469));
				REQUIRE(r4[1] == Approx(0.4999997));
				REQUIRE(r4[2] == Approx(0.8535534));
				REQUIRE(r4[3] == 0);
				REQUIRE(r4[4] == Approx(0.4999999));
				REQUIRE(r4[5] == Approx(0.7071069));
				REQUIRE(r4[6] == Approx(-0.5));
				REQUIRE(r4[7] == 0);
				REQUIRE(r4[8] == Approx(-0.8535534));
				REQUIRE(r4[9] == Approx(0.5));
				REQUIRE(r4[10] == Approx(-0.1464462));
				REQUIRE(r4[11] == 0);
				REQUIRE(r4[12] == Approx(54.8284263));
				REQUIRE(r4[13] == Approx(40.5563491));
				REQUIRE(r4[14] == Approx(2.8284282));
				REQUIRE(r4[15] == 1);
			}
		}

		WHEN("Multiplying the matrices in reverse order") {
			r2 = y2 * x2;
			r3 = y3 * x3;
			r4 = y4 * x4;

			THEN("The result should be correct") {
				REQUIRE(r3[0] == 0);
				REQUIRE(r3[1] == 0);
				REQUIRE(r3[2] == 1);
				REQUIRE(r3[3] == Approx(0.7071067));
				REQUIRE(r3[4] == Approx(0.7071069));
				REQUIRE(r3[5] == 0);
				REQUIRE(r3[6] == Approx(-0.7071069));
				REQUIRE(r3[7] == Approx(0.7071066));
				REQUIRE(r3[8] == 0);

				REQUIRE(r4[0] == 0);
				REQUIRE(r4[1] == 0);
				REQUIRE(r4[2] == 1);
				REQUIRE(r4[3] == 0);
				REQUIRE(r4[4] == Approx(0.7071067));
				REQUIRE(r4[5] == Approx(0.7071069));
				REQUIRE(r4[6] == 0);
				REQUIRE(r4[7] == 0);
				REQUIRE(r4[8] == Approx(-0.7071069));
				REQUIRE(r4[9] == Approx(0.7071066));
				REQUIRE(r4[10] == 0);
				REQUIRE(r4[11] == 0);
				REQUIRE(r4[12] == Approx(37.9411318));
				REQUIRE(r4[13] == Approx(38));
				REQUIRE(r4[14] == Approx(45.7695438));
				REQUIRE(r4[15] == 1);
			}
		}
	}

	GIVEN("An initialized matrix and a point in space") {
		testMat2 matrix2 = testMat2::Rotation(DegToRad(T(45)));
		testVec2 point2 {0, 50};

		testMat3 matrix3 = testMat3::Rotation(DegToRad(T(45)), DegToRad(T(45)), 0);
		testVec3 point3 {0, 50, 0};

		testMat4 matrix4 = testMat4::Rotation(0, DegToRad(T(45)), 0).SetPosition({4, 13, 9});
		testVec4 point4 {0, 50, 0, 1};

		WHEN("Doing a matrix * point and point * matrix multiplication") {
			const testVec2 r2for = matrix2 * point2;
			const testVec2 r2rev = point2 * matrix2;
			const testVec3 r3for = matrix3 * point3;
			const testVec3 r3rev = point3 * matrix3;
			const testVec4 r4for = matrix4 * point4;
			const testVec4 r4rev = point4 * matrix4;

			THEN("The point should be correctly transformed") {
				REQUIRE(r2for != r2rev);
				REQUIRE(r3for != r3rev);
				REQUIRE(r4for != r4rev);

				REQUIRE(r2for.Length() == 50);
				REQUIRE(r2for[0] == Approx(-35.355339059327378));
				REQUIRE(r2for[1] == 0);
				REQUIRE(r2rev.Length() == 50);
				REQUIRE(r2rev[0] == Approx(35.355339059327378));
				REQUIRE(r2rev[1] == 0);

				REQUIRE(r3for.Length() == 50);
				REQUIRE(r3for[0] == Approx(-35.355339059327378));
				REQUIRE(r3for[1] == 0);
				REQUIRE(r3for[2] == Approx(35.355339059327378));
				REQUIRE(r3rev.Length() == 50);
				REQUIRE(r3rev[0] == Approx(35.355339059327378));
				REQUIRE(r3rev[1] == 0);
				REQUIRE(r3rev[2] == Approx(35.355339059327378));

				REQUIRE(r4for.Length() == 50);
				REQUIRE(r4for[0] == Approx(-35.355339059327378));
				REQUIRE(r4for[1] == 0);
				REQUIRE(r4for[2] == Approx(35.355339059327378));
				REQUIRE(r4for[3] == Approx(35.355339059327378));
				REQUIRE(r4rev.Length() == 50);
				REQUIRE(r4rev[0] == Approx(35.355339059327378));
				REQUIRE(r4rev[1] == 0);
				REQUIRE(r4rev[2] == Approx(35.355339059327378));
				REQUIRE(r4rev[3] == Approx(35.355339059327378));
			}
		}
	}
}
