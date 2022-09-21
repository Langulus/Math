///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Built-in primitives", "[builtin]") {
	REQUIRE(sizeof(pcu8) == 1);
	REQUIRE(sizeof(pcu16) == 2);
	REQUIRE(sizeof(pcu32) == 4);
	REQUIRE(sizeof(pcu64) == 8);
	REQUIRE(sizeof(pci8) == 1);
	REQUIRE(sizeof(pci16) == 2);
	REQUIRE(sizeof(pci32) == 4);
	REQUIRE(sizeof(pci64) == 8);
	REQUIRE(sizeof(pcr32) == 4);
	REQUIRE(sizeof(pcr64) == 8);
}

TEMPLATE_TEST_CASE("Signed integers", "[builtin]", SIGNED_INTEGER_TYPES) {
	REQUIRE(SignedInteger<TestType>);
	REQUIRE(!UnsignedInteger<TestType>);
}

TEMPLATE_TEST_CASE("Unsigned integers", "[builtin]", UNSIGNED_TYPES) {
	REQUIRE(UnsignedInteger<TestType>);
	REQUIRE(!SignedInteger<TestType>);
}

TEMPLATE_TEST_CASE("Integers", "[builtin]", INTEGER_TYPES) {
	REQUIRE(IntegerNumber<TestType>);
	REQUIRE(!RealNumber<TestType>);
}

TEMPLATE_TEST_CASE("Reals", "[builtin]", REAL_TYPES) {
	REQUIRE(RealNumber<TestType>);
	REQUIRE(!IntegerNumber<TestType>);
}

TEMPLATE_TEST_CASE("Signed numbers", "[builtin]", SIGNED_TYPES) {
	REQUIRE(Signed<TestType>);
}

TEMPLATE_TEST_CASE("Unsigned numbers", "[builtin]", UNSIGNED_TYPES) {
	REQUIRE(!Signed<TestType>);
}

TEMPLATE_TEST_CASE("Numbers", "[builtin]", ALL_TYPES) {
	REQUIRE(Number<TestType>);
}

TEMPLATE_TEST_CASE("Padding and alignment checks", "[sizes]", ALL_TYPES) {
	using T = TestType;

	REQUIRE(sizeof(TVec<T, 1>) == sizeof(T) * 1);
	REQUIRE(sizeof(TVec<T, 2>) == sizeof(T) * 2);
	REQUIRE(sizeof(TVec<T, 3>) == sizeof(T) * 3);
	REQUIRE(sizeof(TVec<T, 4>) == sizeof(T) * 4);

	REQUIRE(sizeof(TMat<T, 2>) == sizeof(T) * 4);
	REQUIRE(sizeof(TMat<T, 3>) == sizeof(T) * 9);
	REQUIRE(sizeof(TMat<T, 4>) == sizeof(T) * 16);

	REQUIRE(sizeof(TVec<T, 1>[12]) == sizeof(TVec<T, 4>[3]));
	REQUIRE(sizeof(TVec<T, 1>[12]) == sizeof(TVec<T, 3>[4]));
	REQUIRE(sizeof(TVec<T, 1>[12]) == sizeof(TVec<T, 2>[6]));
	REQUIRE(sizeof(TVec<T, 2>[12]) == sizeof(TVec<T, 3>[8]));
	REQUIRE(sizeof(TVec<T, 2>[12]) == sizeof(TVec<T, 4>[6]));
	REQUIRE(sizeof(TVec<T, 3>[8]) == sizeof(TVec<T, 4>[6]));
}