///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Math/Number.hpp>
#include <catch2/catch.hpp>


TEMPLATE_TEST_CASE("Abs - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Abs(T(1)) == T(1));
	REQUIRE(Abs(T(0)) == T(0));
	REQUIRE(Abs(T(-1)) == T(1));
}

TEMPLATE_TEST_CASE("Abs - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Abs(T(1)) == T(1));
	REQUIRE(Abs(T(0)) == T(0));
}

TEMPLATE_TEST_CASE("Sign - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Sign(T(5)) == T(1));
	REQUIRE(Sign(T(1)) == T(1));
	REQUIRE(Sign(T(0)) == T(1));
	REQUIRE(Sign(T(-0)) == T(1));
	REQUIRE(Sign(T(-1)) == T(-1));
	REQUIRE(Sign(T(-5)) == T(-1));
}

TEMPLATE_TEST_CASE("Sign - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Sign(T(5)) == T(1));
	REQUIRE(Sign(T(1)) == T(1));
	REQUIRE(Sign(T(0)) == T(1));
}

TEMPLATE_TEST_CASE("Roundi - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Roundi(T(5.488)) == 5);
	REQUIRE(Roundi(T(5.666)) == 6);
	REQUIRE(Roundi(T(-5.488)) == -5);
	REQUIRE(Roundi(T(-5.666)) == -6);
	REQUIRE(Roundi(T(0)) == 0);
	REQUIRE(Roundi(T(235266.52)) == 235267);
	REQUIRE(Roundi(T(235266.49)) == 235266);
	REQUIRE(Roundi(T(-235266.52)) == -235267);
	REQUIRE(Roundi(T(-235266.49)) == -235266);
}

TEMPLATE_TEST_CASE("Round - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Round(T(5.488)) == T(5));
	REQUIRE(Round(T(5.666)) == T(6));
	REQUIRE(Round(T(-5.488)) == T(-5));
	REQUIRE(Round(T(-5.666)) == T(-6));
	REQUIRE(Round(T(0)) == T(0));
	REQUIRE(Round(T(235266.52)) == T(235267));
	REQUIRE(Round(T(235266.49)) == T(235266));
	REQUIRE(Round(T(-235266.52)) == T(-235267));
	REQUIRE(Round(T(-235266.49)) == T(-235266));
}

TEMPLATE_TEST_CASE("Floori - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Floori(T(5)) == 5);
	REQUIRE(Floori(T(5.488)) == 5);
	REQUIRE(Floori(T(5.666)) == 5);
	REQUIRE(Floori(T(-5.488)) == -6);
	REQUIRE(Floori(T(-5.666)) == -6);
	REQUIRE(Floori(T(0)) == 0);
	REQUIRE(Floori(T(235266.52)) == 235266);
	REQUIRE(Floori(T(235266.49)) == 235266);
	REQUIRE(Floori(T(-235266.52)) == -235267);
	REQUIRE(Floori(T(-235266.49)) == -235267);
}

TEMPLATE_TEST_CASE("Floor - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Floor(T(5)) == T(5));
	REQUIRE(Floor(T(5.488)) == T(5));
	REQUIRE(Floor(T(5.666)) == T(5));
	REQUIRE(Floor(T(-5.488)) == T(-6));
	REQUIRE(Floor(T(-5.666)) == T(-6));
	REQUIRE(Floor(T(0)) == T(0));
	REQUIRE(Floor(T(235266.52)) == T(235266));
	REQUIRE(Floor(T(235266.49)) == T(235266));
	REQUIRE(Floor(T(-235266.52)) == T(-235267));
	REQUIRE(Floor(T(-235266.49)) == T(-235267));
}

TEMPLATE_TEST_CASE("Ceili - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Ceili(T(5)) == 5);
	REQUIRE(Ceili(T(5.488)) == 6);
	REQUIRE(Ceili(T(5.666)) == 6);
	REQUIRE(Ceili(T(-5.488)) == -5);
	REQUIRE(Ceili(T(-5.666)) == -5);
	REQUIRE(Ceili(T(0)) == 0);
	REQUIRE(Ceili(T(235266.52)) == 235267);
	REQUIRE(Ceili(T(235266.49)) == 235267);
	REQUIRE(Ceili(T(-235266.52)) == -235266);
	REQUIRE(Ceili(T(-235266.49)) == -235266);
}

TEMPLATE_TEST_CASE("Ceil - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Ceil(T(5)) == T(5));
	REQUIRE(Ceil(T(5.488)) == T(6));
	REQUIRE(Ceil(T(5.666)) == T(6));
	REQUIRE(Ceil(T(-5.488)) == T(-5));
	REQUIRE(Ceil(T(-5.666)) == T(-5));
	REQUIRE(Ceil(T(0)) == T(0));
	REQUIRE(Ceil(T(235266.52)) == T(235267));
	REQUIRE(Ceil(T(235266.49)) == T(235267));
	REQUIRE(Ceil(T(-235266.52)) == T(-235266));
	REQUIRE(Ceil(T(-235266.49)) == T(-235266));
}

TEMPLATE_TEST_CASE("Square - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Sq(T(-0)) == T(0));
	REQUIRE(Sq(T(-1)) == T(1));
	REQUIRE(Sq(T(-2)) == T(4));
	REQUIRE(Sq(T(-3)) == T(9));
	REQUIRE(Sq(T(-10)) == T(100));
}

TEMPLATE_TEST_CASE("Square - All", "[arithmetics]", ALL_TYPES) {
	using T = TestType;
	REQUIRE(Sq(T(0)) == T(0));
	REQUIRE(Sq(T(1)) == T(1));
	REQUIRE(Sq(T(2)) == T(4));
	REQUIRE(Sq(T(3)) == T(9));
	REQUIRE(Sq(T(10)) == T(100));
}

TEMPLATE_TEST_CASE("Sqrt - Integers", "[arithmetics]", INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(Sqrt(T(0)) == T(0));
	REQUIRE(Sqrt(T(1)) == T(1));
	REQUIRE(Sqrt(T(4)) == T(2));
	REQUIRE(Sqrt(T(9)) == T(3));
	REQUIRE(Sqrt(T(100)) == T(10));
}

TEMPLATE_TEST_CASE("Sqrt - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Sqrt(T(2)) == Approx(1.41421356237));
	REQUIRE(Sqrt(T(245.23)) == Approx(15.6598211995));
}

TEMPLATE_TEST_CASE("Lerp 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Lerp(T(0), T(1), T(0.5)) == Approx(0.5));
	REQUIRE(Lerp(T(0), T(1), T(0.75)) == Approx(0.75));
	REQUIRE(Lerp(T(1), T(0), T(0.5)) == Approx(0.5));
	REQUIRE(Lerp(T(1), T(0), T(0.75)) == Approx(0.25));
	REQUIRE(Lerp(T(0), T(0), T(555.5)) == Approx(0));
	REQUIRE(Lerp(T(666), T(666), T(555.5)) == Approx(666));
}

TEMPLATE_TEST_CASE("Frac 1D - Unsigned Integers", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Frac(T(0)) == 0);
	REQUIRE(Frac(T(16)) == 0);
}

TEMPLATE_TEST_CASE("Frac 1D - Signed Integers", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(Frac(T(0)) == 0);
	REQUIRE(Frac(T(-16)) == 0);
	REQUIRE(Frac(T(16)) == 0);
}

TEMPLATE_TEST_CASE("Frac 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Frac(T(0)) == 0);
	REQUIRE(Frac(T(-16)) == 0);
	REQUIRE(Frac(T(16)) == 0);
	REQUIRE(Frac(T(-66.2)) == Approx(0.8));
	REQUIRE(Frac(T(66.55)) == Approx(0.55));
}

TEMPLATE_TEST_CASE("Mod 1D - Unsigned Integers", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Mod(T(0), T(1)) == 0);
	REQUIRE(Mod(T(0), T(3)) == 0);
	REQUIRE(Mod(T(1), T(1)) == 0);
	REQUIRE(Mod(T(1), T(3)) == 1);
	REQUIRE(Mod(T(2), T(1)) == 0);
	REQUIRE(Mod(T(4), T(16)) == 4);
}

TEMPLATE_TEST_CASE("Mod 1D - Signed Integers", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(Mod<T>(T(0), T(1)) == 0);
	REQUIRE(Mod<T>(T(0), T(3)) == 0);
	REQUIRE(Mod<T>(T(1), T(1)) == 0);
	REQUIRE(Mod<T>(T(1), T(3)) == 1);
	REQUIRE(Mod<T>(T(2), T(1)) == 0);
	REQUIRE(Mod<T>(T(4), T(16)) == 4);
	REQUIRE(Mod<T>(T(0), T(-1)) == 0);
	REQUIRE(Mod<T>(T(5), T(-2)) == 1);
	REQUIRE(Mod<T>(T(-5), T(2)) == -1);
	REQUIRE(Mod<T>(T(-50), T(-23)) == -4);
}

TEMPLATE_TEST_CASE("Mod 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Mod(T(0), T(1)) == 0);
	REQUIRE(Mod(T(0), T(3)) == 0);
	REQUIRE(Mod(T(1), T(1)) == 0);
	REQUIRE(Mod(T(1), T(3)) == 1);
	REQUIRE(Mod(T(2), T(1)) == 0);
	REQUIRE(Mod(T(4), T(16)) == 4);
	REQUIRE(Mod(T(0), T(-1)) == 0);
	REQUIRE(Mod(T(5), T(-2)) == -1);
	REQUIRE(Mod(T(-5), T(2)) == 1);
	REQUIRE(Mod(T(-50), T(-23)) == -4);
	REQUIRE(Mod(T(-2.1), -T(0.2)) == Approx(-0.1));
	REQUIRE(Mod(T(5.555), T(2)) == Approx(1.555));
	REQUIRE(Mod(T(5.555), T(-2)) == Approx(-0.445));
}

TEMPLATE_TEST_CASE("Min 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Min(T(0), T(5)) == 0);
	REQUIRE(Min(T(0), T(0)) == 0);
	REQUIRE(Min(T(-6), T(-10)) == -10);
}

TEMPLATE_TEST_CASE("Min 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Min(T(0), T(5)) == 0);
	REQUIRE(Min(T(0), T(0)) == 0);
}

TEMPLATE_TEST_CASE("Max 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Max(T(0), T(5)) == 5);
	REQUIRE(Max(T(0), T(0)) == 0);
	REQUIRE(Max(T(-6), T(-10)) == -6);
}

TEMPLATE_TEST_CASE("Max 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Max(T(0), T(5)) == 5);
	REQUIRE(Max(T(0), T(0)) == 0);
}

TEMPLATE_TEST_CASE("Clamp 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Clamp(T(0), T(5), T(10)) == 5);
	REQUIRE(Clamp(T(100), T(0), T(1)) == 1);
	REQUIRE(Clamp(T(0), T(-5), T(5)) == 0);
	REQUIRE(Clamp(T(0), T(0), T(0)) == 0);
	REQUIRE(Clamp(T(-6), T(-10), T(-9)) == -9);
	REQUIRE(Clamp(T(12), T(10), T(15)) == 12);
}

TEMPLATE_TEST_CASE("Clamp 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Clamp(T(0), T(5), T(10)) == 5);
	REQUIRE(Clamp(T(100), T(0), T(1)) == 1);
	REQUIRE(Clamp(T(0), T(0), T(0)) == 0);
	REQUIRE(Clamp(T(12), T(10), T(15)) == 12);
}

TEMPLATE_TEST_CASE("ClampRev 1D - Signed", "[arithmetics]", SIGNED_TYPES) {
	using T = TestType;
	REQUIRE(ClampRev(T(0), T(5), T(10)) == 0);
	REQUIRE(ClampRev(T(100), T(0), T(1)) == 100);
	REQUIRE(ClampRev(T(0), T(-5), T(5)) == -5);
	REQUIRE(ClampRev(T(0), T(0), T(0)) == 0);
	REQUIRE(ClampRev(T(-6), T(-10), T(-9)) == -6);
	REQUIRE(ClampRev(T(12), T(10), T(15)) == 10);
}

TEMPLATE_TEST_CASE("ClampRev 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(ClampRev(T(0), T(5), T(10)) == 0);
	REQUIRE(ClampRev(T(100), T(0), T(1)) == 100);
	REQUIRE(ClampRev(T(0), T(0), T(0)) == 0);
	REQUIRE(ClampRev(T(12), T(10), T(15)) == 10);
	REQUIRE(ClampRev(T(13), T(10), T(15)) == 15);
}

/*
//TODO
TEMPLATE_TEST_CASE("Testing algebra", "[pcSmoothStep 1D]", pcu8, pcu16, pcu32, pcu64, pci8, pci16, pci32, pci64, pcr32, pcr64) {
	REQUIRE(Approx<T>(pcSmoothStep<T>(0, 1, 0.5), T(0.5)));
	REQUIRE(Approx<T>(pcSmoothStep<T>(0, 1, 0.75), T(0.75)));
	REQUIRE(Approx<T>(pcSmoothStep<T>(1, 0, 0.5), T(0.5)));
	REQUIRE(Approx<T>(pcSmoothStep<T>(1, 0, 0.75), T(0.25)));
	REQUIRE(Approx<T>(pcSmoothStep<T>(0, 0, 555.5), T(0)));
	REQUIRE(Approx<T>(pcSmoothStep<T>(666, 666, 555.5), T(666)));
}
*/

TEMPLATE_TEST_CASE("Step 1D - Unsigned", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Step(T(0), T(0)) == 1);
	REQUIRE(Step(T(1), T(1)) == 1);
}
TEMPLATE_TEST_CASE("Step 1D - Signed", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(Step(T(0), T(0)) == 1);
	REQUIRE(Step(T(1), T(1)) == 1);
	REQUIRE(Step(T(-5), T(-16)) == 0);
	REQUIRE(Step(T(-5), T(-4)) == 1);
}
TEMPLATE_TEST_CASE("Step 1D - Real", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Step(T(1), T(0.5)) == 0);
	REQUIRE(Step(T(0), T(0)) == 1);
	REQUIRE(Step(T(1), T(1)) == 1);
	REQUIRE(Step(T(1), T(1.5)) == 1);
	REQUIRE(Step(T(-5), T(-16)) == 0);
	REQUIRE(Step(T(-5), T(-4)) == 1);
}

TEMPLATE_TEST_CASE("Distance 1D - Integers", "[arithmetics]", UNSIGNED_TYPES) {
	using T = TestType;
	REQUIRE(Distance(T(0), T(0)) == 0);
	REQUIRE(Distance(T(1), T(1)) == 0);
}

TEMPLATE_TEST_CASE("Distance 1D - Integers", "[arithmetics]", SIGNED_INTEGER_TYPES) {
	using T = TestType;
	REQUIRE(Distance(T(0), T(0)) == 0);
	REQUIRE(Distance(T(1), T(1)) == 0);
	REQUIRE(Distance(T(-5), T(-16)) == 11);
	REQUIRE(Distance(T(-5), T(-4)) == 1);
	REQUIRE(Distance(T(-5), T(7)) == 12);
	REQUIRE(Distance(T(5), T(-7)) == 12);
}

TEMPLATE_TEST_CASE("Distance 1D - Reals", "[arithmetics]", REAL_TYPES) {
	using T = TestType;
	REQUIRE(Distance(T(1), T(0.5)) == 0.5);
	REQUIRE(Distance(T(0), T(0)) == 0);
	REQUIRE(Distance(T(1), T(1)) == 0);
	REQUIRE(Distance(T(1), T(1.5)) == 0.5);
	REQUIRE(Distance(T(-5), T(-16)) == 11);
	REQUIRE(Distance(T(-5), T(-4)) == 1);
	REQUIRE(Distance(T(-5), T(7)) == 12);
	REQUIRE(Distance(T(-7), T(5)) == 12);
}


/*
TEMPLATE_TEST_CASE("Testing algebra", "[pcPow 1D]", pcu8, pcu16, pcu32, pcu64, pcr32, pcr64) {
	REQUIRE(Approx<T>(pcPow<T>(1, 0), T(1)));
	REQUIRE(Approx<T>(pcPow<T>(120, 0), T(1)));
	REQUIRE(Approx<T>(pcPow<T>(120, 1), T(120)));
	REQUIRE(Approx<T>(pcPow<T>(8, 2), T(64)));
}

TEMPLATE_TEST_CASE("Testing algebra", "[pcPow 1D]", pcr32, pcr64) {
	REQUIRE(Approx<T>(pcPow<T>(16, -2), T(4)));
	REQUIRE(Approx<T>(pcPow<T>(532, -1), T(532)));
	REQUIRE(Approx<T>(pcPow<T>(-532, 1), T(-532)));
	REQUIRE(Approx<T>(pcPow<T>(-532, -1), T(-532)));
	REQUIRE(Approx<T>(pcPow<T>(-8, 2), T(64)));
	REQUIRE(Approx<T>(pcPow<T>(16, -2), T(4)));
}

TEMPLATE_TEST_CASE("Testing algebra", "[pcExp 1D]", pcr32, pcr64) {
	REQUIRE(Approx<T>(pcExp<T>(0), T(1)));
	REQUIRE(Approx<T>(pcExp<T>(-1), T(0.36787944117)));
	REQUIRE(Approx<T>(pcExp<T>(1), T(2.71828182846)));
	REQUIRE(Approx<T>(pcExp<T>(-2), T(0.13533528323)));
	REQUIRE(Approx<T>(pcExp<T>(2), T(7.38905609893)));
	REQUIRE(Approx<T>(pcExp<T>(-16), T(1.12535175e-7)));
	REQUIRE(Approx<T>(pcExp<T>(16), T(8886110.52051)));
}

//TODO
TEMPLATE_TEST_CASE("Testing algebra", "[pcExp2 1D]", pcu8, pcu16, pcu32, pcu64, pci8, pci16, pci32, pci64, pcr32, pcr64) {
	REQUIRE(Approx<T>(pcExp2<T>(0), T(1)));
	REQUIRE(Approx<T>(pcExp2<T>(-1), T(0.36787944117)));
	REQUIRE(Approx<T>(pcExp2<T>(1), T(2.71828182846)));
	REQUIRE(Approx<T>(pcExp2<T>(-2), T(0.13533528323)));
	REQUIRE(Approx<T>(pcExp2<T>(2), T(7.38905609893)));
	REQUIRE(Approx<T>(pcExp2<T>(-16), T(1.12535175e-7)));
	REQUIRE(Approx<T>(pcExp2<T>(16), T(8886110.52051)));
}
*/
