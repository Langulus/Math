///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Math/Vector.hpp>
#include <catch2/catch.hpp>


TEMPLATE_TEST_CASE("Vector interpretation", "[metadata]", 
	Vec2u8, Vec2u16, Vec2u32, Vec2u64, 
	Vec2i8, Vec2i16, Vec2i32, Vec2i64, 
	Vec2f, Vec2d
) {
	GIVEN("A 2D vector") {
		auto meta = MetaOf<TestType>();
		REQUIRE(meta);

		WHEN("Interpreted as number") {
			THEN("Requirements should be met") {
				REQUIRE(		meta->template CastsTo<A::Number>( ));
				REQUIRE(not meta->template CastsTo<A::Number>(1));
				REQUIRE(		meta->template CastsTo<A::Number>(2));
				REQUIRE(not meta->template CastsTo<A::Number>(3));
				REQUIRE(not meta->template CastsTo<A::Number>(4));
			}
		}
	}
}

TEMPLATE_TEST_CASE("Padding and alignment checks", "[sizes]", ALL_TYPES) {
	using T = TestType;

	REQUIRE(sizeof(TVec<T, 1>) == sizeof(T) * 1);
	REQUIRE(sizeof(TVec<T, 2>) == sizeof(T) * 2);
	REQUIRE(sizeof(TVec<T, 3>) == sizeof(T) * 3);
	REQUIRE(sizeof(TVec<T, 4>) == sizeof(T) * 4);

	REQUIRE(sizeof(TVec<T, 1>[12]) == sizeof(TVec<T, 4>[3]));
	REQUIRE(sizeof(TVec<T, 1>[12]) == sizeof(TVec<T, 3>[4]));
	REQUIRE(sizeof(TVec<T, 1>[12]) == sizeof(TVec<T, 2>[6]));
	REQUIRE(sizeof(TVec<T, 2>[12]) == sizeof(TVec<T, 3>[8]));
	REQUIRE(sizeof(TVec<T, 2>[12]) == sizeof(TVec<T, 4>[6]));
	REQUIRE(sizeof(TVec<T, 3>[ 8]) == sizeof(TVec<T, 4>[6]));
}
