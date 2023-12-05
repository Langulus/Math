///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Math/Matrix.hpp>
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

		REQUIRE(x2[0][0] == 1);
		REQUIRE(x2[0][1] == 0);
		REQUIRE(x2[1][0] == 0);
		REQUIRE(x2[1][1] == 1);
		REQUIRE(x2.IsIdentity());

		REQUIRE(x3[0][0] == 1);
		REQUIRE(x3[0][1] == 0);
		REQUIRE(x3[0][2] == 0);
		REQUIRE(x3[1][0] == 0);
		REQUIRE(x3[1][1] == 1);
		REQUIRE(x3[1][2] == 0);
		REQUIRE(x3[2][0] == 0);
		REQUIRE(x3[2][1] == 0);
		REQUIRE(x3[2][2] == 1);
		REQUIRE(x3.IsIdentity());

		REQUIRE(x4[0][0] == 1);
		REQUIRE(x4[0][1] == 0);
		REQUIRE(x4[0][2] == 0);
		REQUIRE(x4[0][3] == 0);
		REQUIRE(x4[1][0] == 0);
		REQUIRE(x4[1][1] == 1);
		REQUIRE(x4[1][2] == 0);
		REQUIRE(x4[1][3] == 0);
		REQUIRE(x4[2][0] == 0);
		REQUIRE(x4[2][1] == 0);
		REQUIRE(x4[2][2] == 1);
		REQUIRE(x4[2][3] == 0);
		REQUIRE(x4[3][0] == 0);
		REQUIRE(x4[3][1] == 0);
		REQUIRE(x4[3][2] == 0);
		REQUIRE(x4[3][3] == 1);
		REQUIRE(x4.IsIdentity());

		WHEN("Creating a 4x4 translation matrix") {
			x4 = testMat4::Translate(testVec4 {5, 12, 2, 555});
         Logger::Special(x4);

			REQUIRE(x4.GetColumn(3)[0] == T(5));
			REQUIRE(x4[3][0] == T(5));
			REQUIRE(x4.GetColumn(3)[1] == T(12));
			REQUIRE(x4[3][1] == T(12));
			REQUIRE(x4.GetColumn(3)[2] == T(2));
			REQUIRE(x4[3][2] == T(2));
			REQUIRE(x4.GetColumn(3)[3] == T(1));
			REQUIRE(x4[3][3] == T(1));
		}

		WHEN("Creating a rotation matrix") {
			x2 = testMat2::Rotate(Degrees(45));
			x3 = testMat3::Rotate(Degrees(45), Degrees(45));
			x4 = testMat4::Rotate(Degrees(45), Degrees(45));
			testMat4 x4z = testMat4::Rotate(Radians(0), Radians(0), Degrees(45));

			REQUIRE(x2[0][0] == Approx(0.70711));
			REQUIRE(x2[1][0] == Approx(-0.70711));
			REQUIRE(x2[0][1] == Approx(0.70711));
			REQUIRE(x2[1][1] == Approx(0.70711));

			REQUIRE(x4z[0][0] == Approx(0.70711));
			REQUIRE(x4z[1][0] == Approx(-0.70711));
			REQUIRE(x4z[0][1] == Approx(0.70711));
			REQUIRE(x4z[1][1] == Approx(0.70711));

			REQUIRE(x3[0][0] == Approx(0.70711));
			REQUIRE(x3[1][0] == Approx(0.5));
			REQUIRE(x3[2][0] == Approx(0.5));
			REQUIRE(x3[0][1] == Approx(0));
			REQUIRE(x3[1][1] == Approx(0.70711));
			REQUIRE(x3[2][1] == Approx(-0.70711));
			REQUIRE(x3[0][2] == Approx(-0.70711));
			REQUIRE(x3[1][2] == Approx(0.5));
			REQUIRE(x3[2][2] == Approx(0.5));

			REQUIRE(x4[0][0] == Approx(0.70711));
			REQUIRE(x4[1][0] == Approx(0.5));
			REQUIRE(x4[2][0] == Approx(0.5));
			REQUIRE(x4[3][0] == 0);
			REQUIRE(x4[0][1] == 0);
			REQUIRE(x4[1][1] == Approx(0.70711));
			REQUIRE(x4[2][1] == Approx(-0.70711));
			REQUIRE(x4[3][1] == 0);
			REQUIRE(x4[0][2] == Approx(-0.70711));
			REQUIRE(x4[1][2] == Approx(0.5));
			REQUIRE(x4[2][2] == Approx(0.5));
			REQUIRE(x4[3][2] == 0);
			REQUIRE(x4[0][3] == 0);
			REQUIRE(x4[1][3] == 0);
			REQUIRE(x4[2][3] == 0);
			REQUIRE(x4[3][3] == Approx(1));
		}

		WHEN("Creating a scalar matrix") {
			x2 = testMat2::Scale(testVec2(1, 2));
			x3 = testMat3::Scale(testVec3(1, 2, 3));
			x4 = testMat4::Scale(testVec4(1, 2, 3, 4));

			REQUIRE(x2[0][0] == T(1));
			REQUIRE(x2[1][0] == T(0));
			REQUIRE(x2[0][1] == T(0));
			REQUIRE(x2[1][1] == T(2));
		}
	}

	GIVEN("Given a 3x3 rotation matrix") {
		auto y3 = testMat3::Rotate(Degrees(45), Degrees(45));

		WHEN("Getting the inverse") {
			auto r = y3.Invert();

			REQUIRE(r[0][0] == Approx(0.70711));
			REQUIRE(r[0][1] == Approx(0.5));
			REQUIRE(r[0][2] == Approx(0.5));

			REQUIRE(r[1][0] == Approx(0).margin(0.001));
			REQUIRE(r[1][1] == Approx(0.70711));
			REQUIRE(r[1][2] == Approx(-0.70711));

			REQUIRE(r[2][0] == Approx(-0.70711));
			REQUIRE(r[2][1] == Approx(0.5));
			REQUIRE(r[2][2] == Approx(0.5));
		}
	}

	GIVEN("Given a 4x4 rotation and translation matrix") {
		auto y4 = testMat4::Rotate(Degrees(45), Degrees(45))
			.SetPosition(testVec3 {15, 29, -5});

		WHEN("Getting the inverse") {
			auto r = y4.Invert();

			REQUIRE(r[0][0] == Approx(0.70711));
			REQUIRE(r[0][1] == Approx(0.5));
			REQUIRE(r[0][2] == Approx(0.5));
			REQUIRE(r[0][3] == Approx(0).margin(0.001));

			REQUIRE(r[1][0] == Approx(0).margin(0.001));
			REQUIRE(r[1][1] == Approx(0.70711));
			REQUIRE(r[1][2] == Approx(-0.70711));
			REQUIRE(r[1][3] == Approx(0).margin(0.001));

			REQUIRE(r[2][0] == Approx(-0.70711));
			REQUIRE(r[2][1] == Approx(0.5));
			REQUIRE(r[2][2] == Approx(0.5));
			REQUIRE(r[2][3] == Approx(0).margin(0.001));

			REQUIRE(r[3][0] == Approx(-14.14214));
			REQUIRE(r[3][1] == Approx(-25.5061));
			REQUIRE(r[3][2] == Approx(15.5061));
			REQUIRE(r[3][3] == Approx(1));
		}
	}

	GIVEN("Two matrices and a resulting matrix") {
		auto x2 = testMat2::Rotate(Degrees(45));
		auto y2 = testMat2::Rotate(Degrees(45));
		testMat2 r2;

		auto x3 = testMat3::Rotate(Degrees(0), Degrees(45));
		auto y3 = testMat3::Rotate(Degrees(45), Degrees(45));
		testMat3 r3;

		auto x4 = testMat4::Rotate(Degrees(0), Degrees(45))
			.SetPosition(testVec3 {4, 13, 9});
		auto y4 = testMat4::Rotate(Degrees(45), Degrees(45))
			.SetPosition(testVec3 {50, 25, 2});

		testMat4 r4;

		WHEN("Calculating determinants") {
			auto x2d = x2.Determinant();
			auto y2d = y2.Determinant();
			auto x3d = x3.Determinant();
			auto y3d = y3.Determinant();
			auto x4d = x4.Determinant();
			auto y4d = y4.Determinant();

			REQUIRE(x2d == Approx(1));
			REQUIRE(y2d == Approx(1));
			REQUIRE(x3d == Approx(1));
			REQUIRE(y3d == Approx(1));
			REQUIRE(x4d == Approx(1));
			REQUIRE(y4d == Approx(1));
		}

		WHEN("Multiplying the matrices") {
		#if LANGULUS_SIMD(128BIT)
			Logger::Info("LANGULUS_SIMD(BIT)");
		#endif
		#if LANGULUS_SIMD(256BIT)
			Logger::Info("LANGULUS_SIMD(256BIT)");
		#endif
			r4 = x4 * y4;
			Logger::Info("Multiplying the matrices r4 = x4 * y4 done");
			r3 = x3 * y3;
			Logger::Info("Multiplying the matrices r3 = x3 * y3 done");
			r2 = x2 * y2;
			Logger::Info("Multiplying the matrices r2 = x2 * y2 done");

			REQUIRE(r2[0][0] == Approx(0).margin(0.001));
			REQUIRE(r2[0][1] == Approx(1));
			REQUIRE(r2[1][0] == Approx(-1));
			REQUIRE(r2[1][1] == Approx(0).margin(0.001));

			REQUIRE(r3[0][0] == Approx(0).margin(0.001));
			REQUIRE(r3[0][1] == Approx(0).margin(0.001));
			REQUIRE(r3[0][2] == Approx(-1));
			REQUIRE(r3[1][0] == Approx(0.70711));
			REQUIRE(r3[1][1] == Approx(0.7071069));
			REQUIRE(r3[1][2] == Approx(0).margin(0.001));
			REQUIRE(r3[2][0] == Approx(0.70711));
			REQUIRE(r3[2][1] == Approx(-0.70711));
			REQUIRE(r3[2][2] == Approx(0).margin(0.001));

			REQUIRE(r4[0][0] == Approx(0).margin(0.001));
			REQUIRE(r4[0][1] == Approx(0).margin(0.001));
			REQUIRE(r4[0][2] == Approx(-1));
			REQUIRE(r4[0][3] == Approx(0).margin(0.001));
			REQUIRE(r4[1][0] == Approx(0.70711));
			REQUIRE(r4[1][1] == Approx(0.70711));
			REQUIRE(r4[1][2] == Approx(0).margin(0.001));
			REQUIRE(r4[1][3] == Approx(0).margin(0.001));
			REQUIRE(r4[2][0] == Approx(0.70711));
			REQUIRE(r4[2][1] == Approx(-0.70711));
			REQUIRE(r4[2][2] == Approx(0).margin(0.001));
			REQUIRE(r4[2][3] == Approx(0).margin(0.001));
			REQUIRE(r4[3][0] == Approx(40.76955));
			REQUIRE(r4[3][1] == Approx(38.0));
			REQUIRE(r4[3][2] == Approx(-24.94113));
			REQUIRE(r4[3][3] == Approx(1));
		}

		WHEN("Multiplying the matrices in reverse order") {
			r2 = y2 * x2;
			Logger::Info("Multiplying the matrices r2 = x2 * y2 done");
			r3 = y3 * x3;
			Logger::Info("Multiplying the matrices r3 = x3 * y3 done");
			r4 = y4 * x4;
			Logger::Info("Multiplying the matrices r4 = x4 * y4 done");

			REQUIRE(r3[0][0] == Approx(0.1464469));
			REQUIRE(r3[0][1] == Approx(0.5));
			REQUIRE(r3[0][2] == Approx(-0.85355));
			REQUIRE(r3[1][0] == Approx(0.5));
			REQUIRE(r3[1][1] == Approx(0.7071069));
			REQUIRE(r3[1][2] == Approx(0.5));
			REQUIRE(r3[2][0] == Approx(0.85355));
			REQUIRE(r3[2][1] == Approx(-0.5));
			REQUIRE(r3[2][2] == Approx(-0.146446));

			REQUIRE(r4[0][0] == Approx(0.146446));
			REQUIRE(r4[0][1] == Approx(0.5));
			REQUIRE(r4[0][2] == Approx(-0.85355));
			REQUIRE(r4[0][3] == Approx(0).margin(0.001));
			REQUIRE(r4[1][0] == Approx(0.5));
			REQUIRE(r4[1][1] == Approx(0.7071069));
			REQUIRE(r4[1][2] == Approx(0.5));
			REQUIRE(r4[1][3] == Approx(0).margin(0.001));
			REQUIRE(r4[2][0] == Approx(0.85355));
			REQUIRE(r4[2][1] == Approx(-0.5));
			REQUIRE(r4[2][2] == Approx(-0.146446));
			REQUIRE(r4[2][3] == Approx(0).margin(0.001));
			REQUIRE(r4[3][0] == Approx(63.82843));
			REQUIRE(r4[3][1] == Approx(27.82843));
			REQUIRE(r4[3][2] == Approx(10.17157));
			REQUIRE(r4[3][3] == Approx(1));
		}
	}

	GIVEN("An initialized matrix and a point in space") {
		testMat2 matrix2 = testMat2::Rotate(Degrees(45));
		testVec2 point2 {0, 50};

		testMat3 matrix3 = testMat3::Rotate(Degrees(45), Degrees(45));
		testVec3 point3 {0, 50, 0};

		testMat4 matrix4 = testMat4::Rotate(Degrees(0), Degrees(45)).SetPosition(testVec3 {4, 13, 9});
		testVec4 point4 {0, 50, 0, 1};

		WHEN("Doing a matrix * point and point * matrix multiplication") {
			const testVec2 r2for = matrix2 * point2;
			const testVec2 r2rev = point2 * matrix2;
			const testVec3 r3for = matrix3 * point3;
			const testVec3 r3rev = point3 * matrix3;
			const testVec4 r4for = matrix4 * point4;
			const testVec4 r4rev = point4 * matrix4;

			REQUIRE(r2for != r2rev);
			REQUIRE(r3for != r3rev);
			REQUIRE(r4for != r4rev);

			REQUIRE(r2for.Length() == Approx(50));
			REQUIRE(r2for[0] == Approx(-35.35534));
			REQUIRE(r2for[1] == Approx(35.35534));
			REQUIRE(r2rev.Length() == Approx(50));
			REQUIRE(r2rev[0] == Approx(35.35534));
			REQUIRE(r2rev[1] == Approx(35.35534));

			REQUIRE(r3for.Length() == Approx(50));
			REQUIRE(r3for[0] == Approx(25));
			REQUIRE(r3for[1] == Approx(35.35534));
			REQUIRE(r3for[2] == Approx(25));
			REQUIRE(r3rev.Length() == Approx(50));
			REQUIRE(r3rev[0] == Approx(0.0).margin(0.001));
			REQUIRE(r3rev[1] == Approx(35.35534));
			REQUIRE(r3rev[2] == Approx(-35.35534f));

			REQUIRE(r4for.Length() == Approx(63.77303));
			REQUIRE(r4for[0] == Approx(4));
			REQUIRE(r4for[1] == Approx(63));
			REQUIRE(r4for[2] == Approx(9));
			REQUIRE(r4for[3] == Approx(1));
			REQUIRE(r4rev.Length() == Approx(652.9173));
			REQUIRE(r4rev[0] == Approx(0));
			REQUIRE(r4rev[1] == Approx(50));
			REQUIRE(r4rev[2] == Approx(0.0).margin(0.001));
			REQUIRE(r4rev[3] == Approx(651));
		}
	}
}
