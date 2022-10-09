///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"
#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("Vector interpretation", "[metadata]", vec2u8, vec2u16, vec2u32, vec2u64, vec2i8, vec2i16, vec2i32, vec2i64, vec2f, vec2d) {
	GIVEN("A 2D vector") {
		auto meta = MetaData::Of<TestType>();
		REQUIRE(meta != nullptr);

		WHEN("Interpreted as number") {
			THEN("Requirements should be met") {
				REQUIRE(meta->template CastsTo<Langulus::A::Number>());
				REQUIRE(!meta->template CastsTo<Langulus::A::Number>(1));
				REQUIRE(meta->template CastsTo<Langulus::A::Number>(2));
				REQUIRE(!meta->template CastsTo<Langulus::A::Number>(3));
				REQUIRE(!meta->template CastsTo<Langulus::A::Number>(4));
			}
		}
	}
}

TEMPLATE_TEST_CASE("Padding and alignment checks", "[sizes]", ALL_TYPES) {
	using T = TestType;

	REQUIRE(sizeof(TVector<T, 1>) == sizeof(T) * 1);
	REQUIRE(sizeof(TVector<T, 2>) == sizeof(T) * 2);
	REQUIRE(sizeof(TVector<T, 3>) == sizeof(T) * 3);
	REQUIRE(sizeof(TVector<T, 4>) == sizeof(T) * 4);

	REQUIRE(sizeof(TVector<T, 2>) == sizeof(T) * 4);
	REQUIRE(sizeof(TVector<T, 3>) == sizeof(T) * 9);
	REQUIRE(sizeof(TVector<T, 4>) == sizeof(T) * 16);

	REQUIRE(sizeof(TVector<T, 1>[12]) == sizeof(TVector<T, 4>[3]));
	REQUIRE(sizeof(TVector<T, 1>[12]) == sizeof(TVector<T, 3>[4]));
	REQUIRE(sizeof(TVector<T, 1>[12]) == sizeof(TVector<T, 2>[6]));
	REQUIRE(sizeof(TVector<T, 2>[12]) == sizeof(TVector<T, 3>[8]));
	REQUIRE(sizeof(TVector<T, 2>[12]) == sizeof(TVector<T, 4>[6]));
	REQUIRE(sizeof(TVector<T, 3>[8]) == sizeof(TVector<T, 4>[6]));
}