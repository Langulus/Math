#include "TestMain.hpp"
#include <catch2/catch.hpp>


TEMPLATE_TEST_CASE("Matrices", "[mat]", REAL_TYPES) {
	using T = TestType;
	using testMat2 = TMat<T, 2, 2>;
	using testMat3 = TMat<T, 3, 3>;
	using testMat4 = TMat<T, 4, 4>;
	using testVec2 = TVec<T, 2>;
	using testVec3 = TVec<T, 3>;
	using testVec4 = TVec<T, 4>;

	GIVEN("An uninitialized matrix") {
		testMat2 x2;
		testMat3 x3;
		testMat4 x4;

		WHEN("Creating default matrices") {
			THEN("Matrices should be initialized to identity") {
				REQUIRE(pcNear(x2[0], T(1)));
				REQUIRE(pcNear(x2[1], T(0)));
				REQUIRE(pcNear(x2[2], T(0)));
				REQUIRE(pcNear(x2[3], T(1)));

				REQUIRE(pcNear(x3[0], T(1)));
				REQUIRE(pcNear(x3[1], T(0)));
				REQUIRE(pcNear(x3[2], T(0)));
				REQUIRE(pcNear(x3[3], T(0)));
				REQUIRE(pcNear(x3[4], T(1)));
				REQUIRE(pcNear(x3[5], T(0)));
				REQUIRE(pcNear(x3[6], T(0)));
				REQUIRE(pcNear(x3[7], T(0)));
				REQUIRE(pcNear(x3[8], T(1)));

				REQUIRE(pcNear(x4[0], T(1)));
				REQUIRE(pcNear(x4[1], T(0)));
				REQUIRE(pcNear(x4[2], T(0)));
				REQUIRE(pcNear(x4[3], T(0)));
				REQUIRE(pcNear(x4[4], T(0)));
				REQUIRE(pcNear(x4[5], T(1)));
				REQUIRE(pcNear(x4[6], T(0)));
				REQUIRE(pcNear(x4[7], T(0)));
				REQUIRE(pcNear(x4[8], T(0)));
				REQUIRE(pcNear(x4[9], T(0)));
				REQUIRE(pcNear(x4[10], T(1)));
				REQUIRE(pcNear(x4[11], T(0)));
				REQUIRE(pcNear(x4[12], T(0)));
				REQUIRE(pcNear(x4[13], T(0)));
				REQUIRE(pcNear(x4[14], T(0)));
				REQUIRE(pcNear(x4[15], T(1)));
			}
		}

		WHEN("Creating a translation matrix") {
			x4 = testMat4::Translation({ 5, 12, 2, 555 });

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
			x2 = testMat2::Rotation(pcD2R(T(45)));
			x3 = testMat3::Rotation(pcD2R(T(45)), pcD2R(T(45)), 0);
			x4 = testMat4::Rotation(pcD2R(T(45)), pcD2R(T(45)), 0);
			testMat4 x4z = testMat4::Rotation(0, 0, pcD2R(T(45)));

			THEN("The result should be correct") {
				REQUIRE(pcNear(x2.Get(0, 0), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x2[0], T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x2.Get(1, 0), T(-0.7071066), T(0.001)));
				REQUIRE(pcNear(x2[1], T(-0.7071066), T(0.001)));
				REQUIRE(pcNear(x2.Get(0, 1), T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x2[2], T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x2.Get(1, 1), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x2[3], T(0.7071069), T(0.001)));

				REQUIRE(pcNear(x4z.Get(0, 0), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x4z[0], T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x4z.Get(1, 0), T(-0.7071066), T(0.001)));
				REQUIRE(pcNear(x4z[1], T(-0.7071066), T(0.001)));
				REQUIRE(pcNear(x4z.Get(0, 1), T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x4z[4], T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x4z.Get(1, 1), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x4z[5], T(0.7071069), T(0.001)));

				REQUIRE(pcNear(x3.Get(0, 0), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x3[0], T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x3.Get(1, 0), T(0), T(0.001)));
				REQUIRE(pcNear(x3[1], T(0), T(0.001)));
				REQUIRE(pcNear(x3.Get(2, 0), T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x3[2], T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x3.Get(0, 1), T(0.4999999), T(0.001)));
				REQUIRE(pcNear(x3[3], T(0.4999999), T(0.001)));
				REQUIRE(pcNear(x3.Get(1, 1), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x3[4], T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x3.Get(2, 1), T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x3[5], T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x3.Get(0, 2), T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x3[6], T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x3.Get(1, 2), T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x3[7], T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x3.Get(2, 2), T(0.5000000), T(0.001)));
				REQUIRE(pcNear(x3[8], T(0.5000000), T(0.001)));

				REQUIRE(pcNear(x4.Get(0, 0), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x4[0], T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x4.Get(1, 0), T(0), T(0.001)));
				REQUIRE(pcNear(x4[1], T(0), T(0.001)));
				REQUIRE(pcNear(x4.Get(2, 0), T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x4[2], T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x4.Get(3, 0), T(0), T(0.001)));
				REQUIRE(pcNear(x4[3], T(0), T(0.001)));
				REQUIRE(pcNear(x4.Get(0, 1), T(0.4999999), T(0.001)));
				REQUIRE(pcNear(x4[4], T(0.4999999), T(0.001)));
				REQUIRE(pcNear(x4.Get(1, 1), T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x4[5], T(0.7071069), T(0.001)));
				REQUIRE(pcNear(x4.Get(2, 1), T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x4[6], T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x4.Get(3, 1), T(0), T(0.001)));
				REQUIRE(pcNear(x4[7], T(0)));
				REQUIRE(pcNear(x4.Get(0, 2), T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x4[8], T(-0.5000000), T(0.001)));
				REQUIRE(pcNear(x4.Get(1, 2), T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x4[9], T(0.7071066), T(0.001)));
				REQUIRE(pcNear(x4.Get(2, 2), T(0.5000000), T(0.001)));
				REQUIRE(pcNear(x4[10], T(0.5000000), T(0.001)));
				REQUIRE(pcNear(x4.Get(3, 2), T(0), T(0.001)));
				REQUIRE(pcNear(x4[11], T(0), T(0.001)));
				REQUIRE(pcNear(x4.Get(0, 3), T(0), T(0.001)));
				REQUIRE(pcNear(x4[12], T(0), T(0.001)));
				REQUIRE(pcNear(x4.Get(1, 3), T(0), T(0.001)));
				REQUIRE(pcNear(x4[13], T(0), T(0.001)));
				REQUIRE(pcNear(x4.Get(2, 3), T(0), T(0.001)));
				REQUIRE(pcNear(x4[14], T(0), T(0.001)));
				REQUIRE(pcNear(x4.Get(3, 3), T(1), T(0.001)));
				REQUIRE(pcNear(x4[15], T(1), T(0.001)));
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
		auto y3 = testMat3::Rotation(pcD2R(T(45)), pcD2R(T(45)), 0);
		WHEN("Getting the inverse") {
			auto r = y3.Invert();
			THEN("The result should be correct") {
				REQUIRE(pcNear(r[0], T(0.707106918439098), T(0.0001)));
				REQUIRE(pcNear(r[1], T(0.49999976286795883), T(0.0001)));
				REQUIRE(pcNear(r[2], T(-0.4999999749999469), T(0.0001)));

				REQUIRE(pcNear(r[3], T(0), T(0.0001)));
				REQUIRE(pcNear(r[4], T(0.707106918439098), T(0.0001)));
				REQUIRE(pcNear(r[5], T(0.7071067063070499), T(0.0001)));

				REQUIRE(pcNear(r[6], T(0.7071067063070499), T(0.0001)));
				REQUIRE(pcNear(r[7], T(-0.4999999749999469), T(0.0001)));
				REQUIRE(pcNear(r[8], T(0.5000001871320249), T(0.0001)));
			}
		}
	}

	GIVEN("Given a 4x4 rotation and translation matrix") {
		auto y4 = testMat4::Rotation(pcD2R(T(45)), pcD2R(T(45)), 0).SetPosition({ 15, 29, -5 });
		WHEN("Getting the inverse") {
			auto r = y4.Invert();
			THEN("The result should be correct") {
				REQUIRE(pcNear(r[0], T(0.707106918439098), T(0.0001)));
				REQUIRE(pcNear(r[1], T(0.49999976286795883), T(0.0001)));
				REQUIRE(pcNear(r[2], T(-0.4999999749999469), T(0.0001)));
				REQUIRE(pcNear(r[3], T(0), T(0.0001)));

				REQUIRE(pcNear(r[4], T(0), T(0.0001)));
				REQUIRE(pcNear(r[5], T(0.707106918439098), T(0.0001)));
				REQUIRE(pcNear(r[6], T(0.7071067063070499), T(0.0001)));
				REQUIRE(pcNear(r[7], T(0), T(0.0001)));

				REQUIRE(pcNear(r[8], T(0.7071067063070499), T(0.0001)));
				REQUIRE(pcNear(r[9], T(-0.4999999749999469), T(0.0001)));
				REQUIRE(pcNear(r[10], T(0.5000001871320249), T(0.0001)));
				REQUIRE(pcNear(r[11], T(0), T(0.0001)));

				REQUIRE(pcNear(r[12], T(-7.071068795051746), T(0.0001)));
				REQUIRE(pcNear(r[13], T(-30.506096952752955), T(0.0001)));
				REQUIRE(pcNear(r[14], T(-10.506093922245118), T(0.0001)));
				REQUIRE(pcNear(r[15], T(1), T(0.0001)));
			}
		}
	}

	GIVEN("Two matrices and a resulting matrix") {
		auto x2 = testMat2::Rotation(pcD2R(T(45)));
		auto y2 = testMat2::Rotation(pcD2R(T(45)));
		testMat2 r2;

		auto x3 = testMat3::Rotation(0, pcD2R(T(45)), 0);
		auto y3 = testMat3::Rotation(pcD2R(T(45)), pcD2R(T(45)), 0);
		testMat3 r3;

		auto x4 = testMat4::Rotation(0, pcD2R(T(45)), 0).SetPosition({ 4, 13, 9 });
		auto y4 = testMat4::Rotation(pcD2R(T(45)), pcD2R(T(45)), 0).SetPosition({ 50, 25, 2 });
		testMat4 r4;

		WHEN("Calculating determinants") {
			auto x2d = x2.Determinant();
			auto y2d = y2.Determinant();
			auto x3d = x3.Determinant();
			auto y3d = y3.Determinant();
			auto x4d = x4.Determinant();
			auto y4d = y4.Determinant();

			THEN("The result should be correct") {
				REQUIRE(pcNear(x2d, T(1), T(0.0001)));
				REQUIRE(pcNear(y2d, T(1), T(0.0001)));
				REQUIRE(pcNear(x3d, T(1), T(0.0001)));
				REQUIRE(pcNear(y3d, T(1), T(0.0001)));
				REQUIRE(pcNear(x4d, T(1), T(0.0001)));
				REQUIRE(pcNear(y4d, T(1), T(0.0001)));
			}
		}

		WHEN("Multiplying the matrices") {
			r2 = x2 * y2;
			r3 = x3 * y3;
			r4 = x4 * y4;

			THEN("The result should be correct") {
				REQUIRE(pcNear(r2[0], T(0), T(0.0001)));
				REQUIRE(pcNear(r2[1], T(-1), T(0.0001)));
				REQUIRE(pcNear(r2[2], T(1), T(0.0001)));
				REQUIRE(pcNear(r2[3], T(0), T(0.0001)));

				REQUIRE(pcNear(r3[0], T(0.1464469), T(0.0001)));
				REQUIRE(pcNear(r3[1], T(0.4999997), T(0.0001)));
				REQUIRE(pcNear(r3[2], T(0.8535534), T(0.0001)));
				REQUIRE(pcNear(r3[3], T(0.4999999), T(0.0001)));
				REQUIRE(pcNear(r3[4], T(0.7071069), T(0.0001)));
				REQUIRE(pcNear(r3[5], T(-0.5), T(0.0001)));
				REQUIRE(pcNear(r3[6], T(-0.8535534), T(0.0001)));
				REQUIRE(pcNear(r3[7], T(0.5), T(0.0001)));
				REQUIRE(pcNear(r3[8], T(-0.1464462), T(0.0001)));

				REQUIRE(pcNear(r4[0], T(0.1464469), T(0.0001)));
				REQUIRE(pcNear(r4[1], T(0.4999997), T(0.0001)));
				REQUIRE(pcNear(r4[2], T(0.8535534), T(0.0001)));
				REQUIRE(pcNear(r4[3], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[4], T(0.4999999), T(0.0001)));
				REQUIRE(pcNear(r4[5], T(0.7071069), T(0.0001)));
				REQUIRE(pcNear(r4[6], T(-0.5), T(0.0001)));
				REQUIRE(pcNear(r4[7], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[8], T(-0.8535534), T(0.0001)));
				REQUIRE(pcNear(r4[9], T(0.5), T(0.0001)));
				REQUIRE(pcNear(r4[10], T(-0.1464462), T(0.0001)));
				REQUIRE(pcNear(r4[11], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[12], T(54.8284263), T(0.0001)));
				REQUIRE(pcNear(r4[13], T(40.5563491), T(0.0001)));
				REQUIRE(pcNear(r4[14], T(2.8284282), T(0.0001)));
				REQUIRE(pcNear(r4[15], T(1), T(0.0001)));
			}
		}

		WHEN("Multiplying the matrices in reverse order") {
			r2 = y2 * x2;
			r3 = y3 * x3;
			r4 = y4 * x4;

			THEN("The result should be correct") {
				REQUIRE(pcNear(r3[0], T(0), T(0.0001)));
				REQUIRE(pcNear(r3[1], T(0), T(0.0001)));
				REQUIRE(pcNear(r3[2], T(1), T(0.0001)));
				REQUIRE(pcNear(r3[3], T(0.7071067), T(0.0001)));
				REQUIRE(pcNear(r3[4], T(0.7071069), T(0.0001)));
				REQUIRE(pcNear(r3[5], T(0), T(0.0001)));
				REQUIRE(pcNear(r3[6], T(-0.7071069), T(0.0001)));
				REQUIRE(pcNear(r3[7], T(0.7071066), T(0.0001)));
				REQUIRE(pcNear(r3[8], T(0), T(0.0001)));

				REQUIRE(pcNear(r4[0], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[1], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[2], T(1), T(0.0001)));
				REQUIRE(pcNear(r4[3], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[4], T(0.7071067), T(0.0001)));
				REQUIRE(pcNear(r4[5], T(0.7071069), T(0.0001)));
				REQUIRE(pcNear(r4[6], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[7], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[8], T(-0.7071069), T(0.0001)));
				REQUIRE(pcNear(r4[9], T(0.7071066), T(0.0001)));
				REQUIRE(pcNear(r4[10], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[11], T(0), T(0.0001)));
				REQUIRE(pcNear(r4[12], T(37.9411318), T(0.0001)));
				REQUIRE(pcNear(r4[13], T(38), T(0.0001)));
				REQUIRE(pcNear(r4[14], T(45.7695438), T(0.0001)));
				REQUIRE(pcNear(r4[15], T(1), T(0.0001)));
			}
		}
	}

	GIVEN("An initialized matrix and a point in space") {
		testMat2 matrix2 = testMat2::Rotation(pcD2R(T(45)));
		testVec2 point2 = { 0, 50 };

		testMat3 matrix3 = testMat3::Rotation(pcD2R(T(45)), pcD2R(T(45)), 0);
		testVec3 point3 = { 0, 50, 0 };

		testMat4 matrix4 = testMat4::Rotation(0, pcD2R(T(45)), 0).SetPosition({ 4, 13, 9 });
		testVec4 point4 = { 0, 50, 0, 1 };

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

				REQUIRE(pcNear(r2for.Length(), T(50)));
				REQUIRE(pcNear(r2for[0], T(-35.355339059327378)));
				REQUIRE(pcNear(r2for[1], T(0)));
				REQUIRE(pcNear(r2rev.Length(), T(50)));
				REQUIRE(pcNear(r2rev[0], T(35.355339059327378)));
				REQUIRE(pcNear(r2rev[1], T(0)));

				REQUIRE(pcNear(r3for.Length(), T(50)));
				REQUIRE(pcNear(r3for[0], T(-35.355339059327378)));
				REQUIRE(pcNear(r3for[1], T(0)));
				REQUIRE(pcNear(r3for[2], T(35.355339059327378)));
				REQUIRE(pcNear(r3rev.Length(), T(50)));
				REQUIRE(pcNear(r3rev[0], T(35.355339059327378)));
				REQUIRE(pcNear(r3rev[1], T(0)));
				REQUIRE(pcNear(r3rev[2], T(35.355339059327378)));

				REQUIRE(pcNear(r4for.Length(), T(50)));
				REQUIRE(pcNear(r4for[0], T(-35.355339059327378)));
				REQUIRE(pcNear(r4for[1], T(0)));
				REQUIRE(pcNear(r4for[2], T(35.355339059327378)));
				REQUIRE(pcNear(r4for[3], T(35.355339059327378)));
				REQUIRE(pcNear(r4rev.Length(), T(50)));
				REQUIRE(pcNear(r4rev[0], T(35.355339059327378)));
				REQUIRE(pcNear(r4rev[1], T(0)));
				REQUIRE(pcNear(r4rev[2], T(35.355339059327378)));
				REQUIRE(pcNear(r4rev[3], T(35.355339059327378)));
			}
		}
	}
}
