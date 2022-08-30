#include "TestMain.hpp"
#include <catch2/catch.hpp>


TEMPLATE_TEST_CASE("pcIsPowerOfTwo - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcIsPowerOfTwo(T(0)) == false);
	REQUIRE(pcIsPowerOfTwo(T(1)) == true);
	REQUIRE(pcIsPowerOfTwo(T(2)) == true);
	REQUIRE(pcIsPowerOfTwo(T(3)) == false);
	REQUIRE(pcIsPowerOfTwo(T(4)) == true);
	REQUIRE(pcIsPowerOfTwo(T(5)) == false);
	REQUIRE(pcIsPowerOfTwo(T(10)) == false);
	REQUIRE(pcIsPowerOfTwo(T(16)) == true);
}

TEMPLATE_TEST_CASE("pcNear - Integers", "[arithmetics]", INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(pcNear(T(0), T(1)) == false);
	REQUIRE(pcNear(T(1), T(1)) == true);
}

TEMPLATE_TEST_CASE("pcNear - Real", "[arithmetics]", REAL_TYPES) {
	// With epsilon																		
	using T = TestType;
	REQUIRE(pcNear(T(0.01), T(0.02), T(0.02)) == true);
	REQUIRE(pcNear(T(0.01), T(-0.02), T(0.02)) == false);
	REQUIRE(pcNear(T(0.01), T(0.02), T(0.0002)) == false);
}

TEMPLATE_TEST_CASE("pcAbs - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcAbs(T(1)) == T(1));
	REQUIRE(pcAbs(T(0)) == T(0));
	REQUIRE(pcAbs(T(-1)) == T(1));
}

TEMPLATE_TEST_CASE("pcAbs - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcAbs(T(1)) == T(1));
	REQUIRE(pcAbs(T(0)) == T(0));
}

TEMPLATE_TEST_CASE("pcSign - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcSign(T(5)) == T(1));
	REQUIRE(pcSign(T(1)) == T(1));
	REQUIRE(pcSign(T(0)) == T(1));
	REQUIRE(pcSign(T(-0)) == T(1));
	REQUIRE(pcSign(T(-1)) == T(-1));
	REQUIRE(pcSign(T(-5)) == T(-1));
}

TEMPLATE_TEST_CASE("pcSign - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcSign(T(5)) == T(1));
	REQUIRE(pcSign(T(1)) == T(1));
	REQUIRE(pcSign(T(0)) == T(1));
}

TEMPLATE_TEST_CASE("pcRoundi - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcRoundi(T(5.488)) == pci64(5));
	REQUIRE(pcRoundi(T(5.666)) == pci64(6));
	REQUIRE(pcRoundi(T(-5.488)) == pci64(-5));
	REQUIRE(pcRoundi(T(-5.666)) == pci64(-6));
	REQUIRE(pcRoundi(T(0)) == pci64(0));
	REQUIRE(pcRoundi(T(235266.52)) == pci64(235267));
	REQUIRE(pcRoundi(T(235266.49)) == pci64(235266));
	REQUIRE(pcRoundi(T(-235266.52)) == pci64(-235267));
	REQUIRE(pcRoundi(T(-235266.49)) == pci64(-235266));
}

TEMPLATE_TEST_CASE("pcRound - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear(pcRound(T(5.488)), T(5)));
	REQUIRE(pcNear(pcRound(T(5.666)), T(6)));
	REQUIRE(pcNear(pcRound(T(-5.488)), T(-5)));
	REQUIRE(pcNear(pcRound(T(-5.666)), T(-6)));
	REQUIRE(pcNear(pcRound(T(0)), T(0)));
	REQUIRE(pcNear(pcRound(T(235266.52)), T(235267)));
	REQUIRE(pcNear(pcRound(T(235266.49)), T(235266)));
	REQUIRE(pcNear(pcRound(T(-235266.52)), T(-235267)));
	REQUIRE(pcNear(pcRound(T(-235266.49)), T(-235266)));
}

TEMPLATE_TEST_CASE("pcFloori - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcFloori(T(5)) == pci64(5));
	REQUIRE(pcFloori(T(5.488)) == pci64(5));
	REQUIRE(pcFloori(T(5.666)) == pci64(5));
	REQUIRE(pcFloori(T(-5.488)) == pci64(-6));
	REQUIRE(pcFloori(T(-5.666)) == pci64(-6));
	REQUIRE(pcFloori(T(0)) == pci64(0));
	REQUIRE(pcFloori(T(235266.52)) == pci64(235266));
	REQUIRE(pcFloori(T(235266.49)) == pci64(235266));
	REQUIRE(pcFloori(T(-235266.52)) == pci64(-235267));
	REQUIRE(pcFloori(T(-235266.49)) == pci64(-235267));
}

TEMPLATE_TEST_CASE("pcFloor - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear(pcFloor(T(5)), T(5)));
	REQUIRE(pcNear(pcFloor(T(5.488)), T(5)));
	REQUIRE(pcNear(pcFloor(T(5.666)), T(5)));
	REQUIRE(pcNear(pcFloor(T(-5.488)), T(-6)));
	REQUIRE(pcNear(pcFloor(T(-5.666)), T(-6)));
	REQUIRE(pcNear(pcFloor(T(0)), T(0)));
	REQUIRE(pcNear(pcFloor(T(235266.52)), T(235266)));
	REQUIRE(pcNear(pcFloor(T(235266.49)), T(235266)));
	REQUIRE(pcNear(pcFloor(T(-235266.52)), T(-235267)));
	REQUIRE(pcNear(pcFloor(T(-235266.49)), T(-235267)));
}

TEMPLATE_TEST_CASE("pcCeili - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcCeili(T(5)) == pci64(5));
	REQUIRE(pcCeili(T(5.488)) == pci64(6));
	REQUIRE(pcCeili(T(5.666)) == pci64(6));
	REQUIRE(pcCeili(T(-5.488)) == pci64(-5));
	REQUIRE(pcCeili(T(-5.666)) == pci64(-5));
	REQUIRE(pcCeili(T(0)) == pci64(0));
	REQUIRE(pcCeili(T(235266.52)) == pci64(235267));
	REQUIRE(pcCeili(T(235266.49)) == pci64(235267));
	REQUIRE(pcCeili(T(-235266.52)) == pci64(-235266));
	REQUIRE(pcCeili(T(-235266.49)) == pci64(-235266));
}

TEMPLATE_TEST_CASE("pcCeil - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear(pcCeil(T(5)), T(5)));
	REQUIRE(pcNear(pcCeil(T(5.488)), T(6)));
	REQUIRE(pcNear(pcCeil(T(5.666)), T(6)));
	REQUIRE(pcNear(pcCeil(T(-5.488)), T(-5)));
	REQUIRE(pcNear(pcCeil(T(-5.666)), T(-5)));
	REQUIRE(pcNear(pcCeil(T(0)), T(0)));
	REQUIRE(pcNear(pcCeil(T(235266.52)), T(235267)));
	REQUIRE(pcNear(pcCeil(T(235266.49)), T(235267)));
	REQUIRE(pcNear(pcCeil(T(-235266.52)), T(-235266)));
	REQUIRE(pcNear(pcCeil(T(-235266.49)), T(-235266)));
}

TEMPLATE_TEST_CASE("pcSquare - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear(pcSq(T(-0)), T(0)));
	REQUIRE(pcNear(pcSq(T(-1)), T(1)));
	REQUIRE(pcNear(pcSq(T(-2)), T(4)));
	REQUIRE(pcNear(pcSq(T(-3)), T(9)));
	REQUIRE(pcNear(pcSq(T(-10)), T(100)));
}

TEMPLATE_TEST_CASE("pcSquare - All", "[arithmetics]", ALL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcSq(T(0)), T(0)));
	REQUIRE(pcNear<T>(pcSq(T(1)), T(1)));
	REQUIRE(pcNear<T>(pcSq(T(2)), T(4)));
	REQUIRE(pcNear<T>(pcSq(T(3)), T(9)));
	REQUIRE(pcNear<T>(pcSq(T(10)), T(100)));
}

TEMPLATE_TEST_CASE("pcSqrt - Integers", "[arithmetics]", INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcSqrt(T(0)), T(0)));
	REQUIRE(pcNear<T>(pcSqrt(T(1)), T(1)));
	REQUIRE(pcNear<T>(pcSqrt(T(4)), T(2)));
	REQUIRE(pcNear<T>(pcSqrt(T(9)), T(3)));
	REQUIRE(pcNear<T>(pcSqrt(T(100)), T(10)));
}

TEMPLATE_TEST_CASE("pcSqrt - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcSqrt(T(2)), T(1.41421356237), T(0.000001)));
	REQUIRE(pcNear<T>(pcSqrt(T(245.23)), T(15.6598211995), T(0.000001)));
}

TEMPLATE_TEST_CASE("pcLerp 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcLerp(T(0), T(1), T(0.5)), T(0.5)));
	REQUIRE(pcNear<T>(pcLerp(T(0), T(1), T(0.75)), T(0.75)));
	REQUIRE(pcNear<T>(pcLerp(T(1), T(0), T(0.5)), T(0.5)));
	REQUIRE(pcNear<T>(pcLerp(T(1), T(0), T(0.75)), T(0.25)));
	REQUIRE(pcNear<T>(pcLerp(T(0), T(0), T(555.5)), T(0)));
	REQUIRE(pcNear<T>(pcLerp(T(666), T(666), T(555.5)), T(666)));
}

TEMPLATE_TEST_CASE("pcFrac 1D - Unsigned Integers", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcFrac(T(0)), T(0)));
	REQUIRE(pcNear<T>(pcFrac(T(16)), T(0)));
}

TEMPLATE_TEST_CASE("pcFrac 1D - Signed Integers", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcFrac(T(0)), T(0)));
	REQUIRE(pcNear<T>(pcFrac(T(-16)), T(0)));
	REQUIRE(pcNear<T>(pcFrac(T(16)), T(0)));
}

TEMPLATE_TEST_CASE("pcFrac 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcFrac(T(0)), T(0)));
	REQUIRE(pcNear<T>(pcFrac(T(-16)), T(0)));
	REQUIRE(pcNear<T>(pcFrac(T(16)), T(0)));
	REQUIRE(pcNear<T>(pcFrac(T(-66.2)), T(0.8), T(0.001)));
	REQUIRE(pcNear<T>(pcFrac(T(66.55)), T(0.55), T(0.001)));
}

TEMPLATE_TEST_CASE("pcMod 1D - Unsigned Integers", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcMod(T(0), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(0), T(3)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(1), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(1), T(3)), T(1)));
	REQUIRE(pcNear<T>(pcMod(T(2), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(4), T(16)), T(4)));
}

TEMPLATE_TEST_CASE("pcMod 1D - Signed Integers", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcMod<T>(T(0), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod<T>(T(0), T(3)), T(0)));
	REQUIRE(pcNear<T>(pcMod<T>(T(1), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod<T>(T(1), T(3)), T(1)));
	REQUIRE(pcNear<T>(pcMod<T>(T(2), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod<T>(T(4), T(16)), T(4)));
	REQUIRE(pcNear<T>(pcMod<T>(T(0), T(-1)), T(0)));
	REQUIRE(pcNear<T>(pcMod<T>(T(5), T(-2)), T(-1)));
	REQUIRE(pcNear<T>(pcMod<T>(T(-5), T(2)), T(1)));
	REQUIRE(pcNear<T>(pcMod<T>(T(-50), T(-23)), T(-4)));
}

TEMPLATE_TEST_CASE("pcMod 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcMod(T(0), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(0), T(3)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(1), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(1), T(3)), T(1)));
	REQUIRE(pcNear<T>(pcMod(T(2), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(4), T(16)), T(4)));
	REQUIRE(pcNear<T>(pcMod(T(0), T(-1)), T(0)));
	REQUIRE(pcNear<T>(pcMod(T(5), T(-2)), T(-1)));
	REQUIRE(pcNear<T>(pcMod(T(-5), T(2)), T(1)));
	REQUIRE(pcNear<T>(pcMod(T(-50), T(-23)), T(-4)));
	REQUIRE(pcNear<T>(pcMod(T(-2.1), -T(0.2)), T(-0.1)));
	REQUIRE(pcNear<T>(pcMod(T(5.555), T(2)), T(1.555)));
	REQUIRE(pcNear<T>(pcMod(T(5.555), T(-2)), T(-0.445)));
}

TEMPLATE_TEST_CASE("pcMin 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcMin(T(0), T(5)), T(0)));
	REQUIRE(pcNear<T>(pcMin(T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcMin(T(-6), T(-10)), T(-10)));
}

TEMPLATE_TEST_CASE("pcMin 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcMin(T(0), T(5)), T(0)));
	REQUIRE(pcNear<T>(pcMin(T(0), T(0)), T(0)));
}

TEMPLATE_TEST_CASE("pcMax 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcMax(T(0), T(5)), T(5)));
	REQUIRE(pcNear<T>(pcMax(T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcMax(T(-6), T(-10)), T(-6)));
}

TEMPLATE_TEST_CASE("pcMax 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcMax(T(0), T(5)), T(5)));
	REQUIRE(pcNear<T>(pcMax(T(0), T(0)), T(0)));
}

TEMPLATE_TEST_CASE("pcClamp 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcClamp(T(0), T(5), T(10)), T(5)));
	REQUIRE(pcNear<T>(pcClamp(T(100), T(0), T(1)), T(1)));
	REQUIRE(pcNear<T>(pcClamp(T(0), T(-5), T(5)), T(0)));
	REQUIRE(pcNear<T>(pcClamp(T(0), T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcClamp(T(-6), T(-10), T(-9)), T(-9)));
	REQUIRE(pcNear<T>(pcClamp(T(12), T(10), T(15)), T(12)));
}

TEMPLATE_TEST_CASE("pcClamp 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcClamp(T(0), T(5), T(10)), T(5)));
	REQUIRE(pcNear<T>(pcClamp(T(100), T(0), T(1)), T(1)));
	REQUIRE(pcNear<T>(pcClamp(T(0), T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcClamp(T(12), T(10), T(15)), T(12)));
}

TEMPLATE_TEST_CASE("pcClampRev 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcClampRev(T(0), T(5), T(10)), T(0)));
	REQUIRE(pcNear<T>(pcClampRev(T(100), T(0), T(1)), T(100)));
	REQUIRE(pcNear<T>(pcClampRev(T(0), T(-5), T(5)), T(-5)));
	REQUIRE(pcNear<T>(pcClampRev(T(0), T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcClampRev(T(-6), T(-10), T(-9)), T(-6)));
	REQUIRE(pcNear<T>(pcClampRev(T(12), T(10), T(15)), T(10)));
}

TEMPLATE_TEST_CASE("pcClampRev 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcClampRev(T(0), T(5), T(10)), T(0)));
	REQUIRE(pcNear<T>(pcClampRev(T(100), T(0), T(1)), T(100)));
	REQUIRE(pcNear<T>(pcClampRev(T(0), T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcClampRev(T(12), T(10), T(15)), T(10)));
}

/*
//TODO
TEMPLATE_TEST_CASE("Testing algebra", "[pcSmoothStep 1D]", pcu8, pcu16, pcu32, pcu64, pci8, pci16, pci32, pci64, pcr32, pcr64) {
	REQUIRE(pcNear<T>(pcSmoothStep<T>(0, 1, 0.5), T(0.5)));
	REQUIRE(pcNear<T>(pcSmoothStep<T>(0, 1, 0.75), T(0.75)));
	REQUIRE(pcNear<T>(pcSmoothStep<T>(1, 0, 0.5), T(0.5)));
	REQUIRE(pcNear<T>(pcSmoothStep<T>(1, 0, 0.75), T(0.25)));
	REQUIRE(pcNear<T>(pcSmoothStep<T>(0, 0, 555.5), T(0)));
	REQUIRE(pcNear<T>(pcSmoothStep<T>(666, 666, 555.5), T(666)));
}
*/

TEMPLATE_TEST_CASE("pcStep 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcStep(T(0), T(0)), T(1)));
	REQUIRE(pcNear<T>(pcStep(T(1), T(1)), T(1)));
}
TEMPLATE_TEST_CASE("pcStep 1D - Signed", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcStep(T(0), T(0)), T(1)));
	REQUIRE(pcNear<T>(pcStep(T(1), T(1)), T(1)));
	REQUIRE(pcNear<T>(pcStep(T(-5), T(-16)), T(0)));
	REQUIRE(pcNear<T>(pcStep(T(-5), T(-4)), T(1)));
}
TEMPLATE_TEST_CASE("pcStep 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcStep(T(1), T(0.5)), T(0)));
	REQUIRE(pcNear<T>(pcStep(T(0), T(0)), T(1)));
	REQUIRE(pcNear<T>(pcStep(T(1), T(1)), T(1)));
	REQUIRE(pcNear<T>(pcStep(T(1), T(1.5)), T(1)));
	REQUIRE(pcNear<T>(pcStep(T(-5), T(-16)), T(0)));
	REQUIRE(pcNear<T>(pcStep(T(-5), T(-4)), T(1)));
}

TEMPLATE_TEST_CASE("pcDistance 1D - Integers", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcDistance(T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcDistance(T(1), T(1)), T(0)));
}

TEMPLATE_TEST_CASE("pcDistance 1D - Integers", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	const T zero{ 0 };
	REQUIRE(pcNear<T>(pcDistance<T>(zero, zero), zero));
	REQUIRE(pcNear<T>(pcDistance<T>(T(1), T(1)), zero));
	REQUIRE(pcNear<T>(pcDistance<T>(T(-5), T(-16)), T(11)));
	REQUIRE(pcNear<T>(pcDistance<T>(T(-5), T(-4)), T(1)));
	REQUIRE(pcNear<T>(pcDistance<T>(T(-5), T(7)), T(12)));
	REQUIRE(pcNear<T>(pcDistance<T>(T(5), T(-7)), T(12)));
}

TEMPLATE_TEST_CASE("pcDistance 1D - Reals", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(pcNear<T>(pcDistance(T(1), T(0.5)), T(0.5)));
	REQUIRE(pcNear<T>(pcDistance(T(0), T(0)), T(0)));
	REQUIRE(pcNear<T>(pcDistance(T(1), T(1)), T(0)));
	REQUIRE(pcNear<T>(pcDistance(T(1), T(1.5)), T(0.5)));
	REQUIRE(pcNear<T>(pcDistance(T(-5), T(-16)), T(11)));
	REQUIRE(pcNear<T>(pcDistance(T(-5), T(-4)), T(1)));
	REQUIRE(pcNear<T>(pcDistance(T(-5), T(7)), T(12)));
	REQUIRE(pcNear<T>(pcDistance(T(-7), T(5)), T(12)));
}


/*
TEMPLATE_TEST_CASE("Testing algebra", "[pcPow 1D]", pcu8, pcu16, pcu32, pcu64, pcr32, pcr64) {
	REQUIRE(pcNear<T>(pcPow<T>(1, 0), T(1)));
	REQUIRE(pcNear<T>(pcPow<T>(120, 0), T(1)));
	REQUIRE(pcNear<T>(pcPow<T>(120, 1), T(120)));
	REQUIRE(pcNear<T>(pcPow<T>(8, 2), T(64)));
}

TEMPLATE_TEST_CASE("Testing algebra", "[pcPow 1D]", pcr32, pcr64) {
	REQUIRE(pcNear<T>(pcPow<T>(16, -2), T(4)));
	REQUIRE(pcNear<T>(pcPow<T>(532, -1), T(532)));
	REQUIRE(pcNear<T>(pcPow<T>(-532, 1), T(-532)));
	REQUIRE(pcNear<T>(pcPow<T>(-532, -1), T(-532)));
	REQUIRE(pcNear<T>(pcPow<T>(-8, 2), T(64)));
	REQUIRE(pcNear<T>(pcPow<T>(16, -2), T(4)));
}

TEMPLATE_TEST_CASE("Testing algebra", "[pcExp 1D]", pcr32, pcr64) {
	REQUIRE(pcNear<T>(pcExp<T>(0), T(1)));
	REQUIRE(pcNear<T>(pcExp<T>(-1), T(0.36787944117)));
	REQUIRE(pcNear<T>(pcExp<T>(1), T(2.71828182846)));
	REQUIRE(pcNear<T>(pcExp<T>(-2), T(0.13533528323)));
	REQUIRE(pcNear<T>(pcExp<T>(2), T(7.38905609893)));
	REQUIRE(pcNear<T>(pcExp<T>(-16), T(1.12535175e-7)));
	REQUIRE(pcNear<T>(pcExp<T>(16), T(8886110.52051)));
}

//TODO
TEMPLATE_TEST_CASE("Testing algebra", "[pcExp2 1D]", pcu8, pcu16, pcu32, pcu64, pci8, pci16, pci32, pci64, pcr32, pcr64) {
	REQUIRE(pcNear<T>(pcExp2<T>(0), T(1)));
	REQUIRE(pcNear<T>(pcExp2<T>(-1), T(0.36787944117)));
	REQUIRE(pcNear<T>(pcExp2<T>(1), T(2.71828182846)));
	REQUIRE(pcNear<T>(pcExp2<T>(-2), T(0.13533528323)));
	REQUIRE(pcNear<T>(pcExp2<T>(2), T(7.38905609893)));
	REQUIRE(pcNear<T>(pcExp2<T>(-16), T(1.12535175e-7)));
	REQUIRE(pcNear<T>(pcExp2<T>(16), T(8886110.52051)));
}
*/
