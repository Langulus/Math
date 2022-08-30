#include "TestMain.hpp"
#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("Vector interpretation", "[metadata]", vec2u8, vec2u16, vec2u32, vec2u64, vec2i8, vec2i16, vec2i32, vec2i64, vec2f, vec2d) {
	GIVEN("A 2D vector") {
		auto meta = MetaData::Of<TestType>();
		REQUIRE(meta != nullptr);

		WHEN("Interpreted as number") {
			THEN("Requirements should be met") {
				REQUIRE(meta->template InterpretsAs<ANumber>());
				REQUIRE(!meta->template InterpretsAs<ANumber>(1));
				REQUIRE(meta->template InterpretsAs<ANumber>(2));
				REQUIRE(!meta->template InterpretsAs<ANumber>(3));
				REQUIRE(!meta->template InterpretsAs<ANumber>(4));
			}
		}
	}
}
