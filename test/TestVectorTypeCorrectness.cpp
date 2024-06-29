///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Math/Vector.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Vector interpretation", "[metadata]", 
	Vec2u8, Vec2u16, Vec2u32, Vec2u64, 
	Vec2i8, Vec2i16, Vec2i32, Vec2i64, 
	Vec2f, Vec2d
) {
	GIVEN("A 2D vector") {
		auto meta = MetaOf<TestType>();
		REQUIRE(meta);

		WHEN("Interpreted as number") {
			REQUIRE(		meta->template CastsTo<A::Number>( ));
			REQUIRE(not meta->template CastsTo<A::Number>(1));
			REQUIRE(		meta->template CastsTo<A::Number>(2));
			REQUIRE(not meta->template CastsTo<A::Number>(3));
			REQUIRE(not meta->template CastsTo<A::Number>(4));
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

TEST_CASE("CountOf checks", "[CountOf]") {
   using T = float;

   static_assert(CountOf<TVec<T, 1>> == 1);
   static_assert(CountOf<TVec<T, 2>> == 2);
   static_assert(CountOf<TVec<T, 3>> == 3);
   static_assert(CountOf<TVec<T, 4>> == 4);

   static_assert(CountOf<TVec<T, 1>[12]> == 12);
   static_assert(CountOf<TVec<T, 1>[12]> == 12);
   static_assert(CountOf<TVec<T, 1>[12]> == 12);
   static_assert(CountOf<TVec<T, 2>[12]> == 24);
   static_assert(CountOf<TVec<T, 2>[12]> == 24);
   static_assert(CountOf<TVec<T, 3>[ 8]> == 24);
}

TEST_CASE("OverlapCounts checks", "[OverlapCounts]") {
   int scalar {};
   int scalarArray[1] {};
   int smallArray[2] {};
   int bigArray[4] {};

   TVec<int, 1> v1;
   TVec<int, 2> v2;
   TVec<int, 4> v4;

   TVec<int, 1> v1x2[2];
   TVec<int, 2> v2x2[2];
   TVec<int, 4> v4x2[2];

   static_assert(OverlapCounts<decltype(scalar),      decltype(scalar)     >() == 1);
   static_assert(OverlapCounts<decltype(scalar),      decltype(scalarArray)>() == 1);
   static_assert(OverlapCounts<decltype(scalar),      decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(scalar),      decltype(bigArray)   >() == 4);
   static_assert(OverlapCounts<decltype(scalar),      decltype(v1)         >() == 1);
   static_assert(OverlapCounts<decltype(scalar),      decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(scalar),      decltype(v4)         >() == 4);
   static_assert(OverlapCounts<decltype(scalar),      decltype(v1x2)       >() == 1*2);
   static_assert(OverlapCounts<decltype(scalar),      decltype(v2x2)       >() == 2*2);
   static_assert(OverlapCounts<decltype(scalar),      decltype(v4x2)       >() == 4*2);

   static_assert(OverlapCounts<decltype(scalarArray), decltype(scalar)     >() == 1);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(scalarArray)>() == 1);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(bigArray)   >() == 4);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(v1)         >() == 1);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(v4)         >() == 4);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(v1x2)       >() == 1*2);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(v2x2)       >() == 2*2);
   static_assert(OverlapCounts<decltype(scalarArray), decltype(v4x2)       >() == 4*2);

   static_assert(OverlapCounts<decltype(smallArray),  decltype(scalar)     >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(scalarArray)>() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(bigArray)   >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(v1)         >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(v4)         >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(v1x2)       >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(v2x2)       >() == 2);
   static_assert(OverlapCounts<decltype(smallArray),  decltype(v4x2)       >() == 2);

   static_assert(OverlapCounts<decltype(bigArray),    decltype(scalar)     >() == 4);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(scalarArray)>() == 4);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(bigArray)   >() == 4);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(v1)         >() == 4);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(v4)         >() == 4);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(v1x2)       >() == 2);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(v2x2)       >() == 4);
   static_assert(OverlapCounts<decltype(bigArray),    decltype(v4x2)       >() == 4);

   static_assert(OverlapCounts<decltype(v1),          decltype(scalar)     >() == 1);
   static_assert(OverlapCounts<decltype(v1),          decltype(scalarArray)>() == 1);
   static_assert(OverlapCounts<decltype(v1),          decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(v1),          decltype(bigArray)   >() == 4);
   static_assert(OverlapCounts<decltype(v1),          decltype(v1)         >() == 1);
   static_assert(OverlapCounts<decltype(v1),          decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(v1),          decltype(v4)         >() == 4);
   static_assert(OverlapCounts<decltype(v1),          decltype(v1x2)       >() == 1*2);
   static_assert(OverlapCounts<decltype(v1),          decltype(v2x2)       >() == 2*2);
   static_assert(OverlapCounts<decltype(v1),          decltype(v4x2)       >() == 4*2);

   static_assert(OverlapCounts<decltype(v2),          decltype(scalar)     >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(scalarArray)>() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(bigArray)   >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(v1)         >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(v4)         >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(v1x2)       >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(v2x2)       >() == 2);
   static_assert(OverlapCounts<decltype(v2),          decltype(v4x2)       >() == 2);

   static_assert(OverlapCounts<decltype(v4),          decltype(scalar)     >() == 4);
   static_assert(OverlapCounts<decltype(v4),          decltype(scalarArray)>() == 4);
   static_assert(OverlapCounts<decltype(v4),          decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(v4),          decltype(bigArray)   >() == 4);
   static_assert(OverlapCounts<decltype(v4),          decltype(v1)         >() == 4);
   static_assert(OverlapCounts<decltype(v4),          decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(v4),          decltype(v4)         >() == 4);
   static_assert(OverlapCounts<decltype(v4),          decltype(v1x2)       >() == 2);
   static_assert(OverlapCounts<decltype(v4),          decltype(v2x2)       >() == 4);
   static_assert(OverlapCounts<decltype(v4),          decltype(v4x2)       >() == 4);

   static_assert(OverlapCounts<decltype(v1x2),        decltype(scalar)     >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(scalarArray)>() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(bigArray)   >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(v1)         >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(v4)         >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(v1x2)       >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(v2x2)       >() == 2);
   static_assert(OverlapCounts<decltype(v1x2),        decltype(v4x2)       >() == 2);

   static_assert(OverlapCounts<decltype(v2x2),        decltype(scalar)     >() == 4);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(scalarArray)>() == 4);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(bigArray)   >() == 4);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(v1)         >() == 4);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(v4)         >() == 4);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(v1x2)       >() == 2);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(v2x2)       >() == 4);
   static_assert(OverlapCounts<decltype(v2x2),        decltype(v4x2)       >() == 4);

   static_assert(OverlapCounts<decltype(v4x2),        decltype(scalar)     >() == 8);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(scalarArray)>() == 8);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(smallArray) >() == 2);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(bigArray)   >() == 4);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(v1)         >() == 8);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(v2)         >() == 2);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(v4)         >() == 4);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(v1x2)       >() == 2);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(v2x2)       >() == 4);
   static_assert(OverlapCounts<decltype(v4x2),        decltype(v4x2)       >() == 8);
}

TEST_CASE("Lossless checks", "[lossless]") {
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2u8 >, Vec2u8::ArrayType >);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2u16>, Vec2u16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2u32>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2i8 >, Vec2i8::ArrayType >);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2u8  , Vec2d  >, Vec2d::ArrayType  >);
                                            
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2u8 >, Vec2u16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2u16>, Vec2u16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2u32>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2i8 >, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2u16 , Vec2d  >, Vec2d::ArrayType  >);
                                            
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2u8 >, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2u16>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2u32>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2i8 >, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2i16>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2u32 , Vec2d  >, Vec2d::ArrayType  >);
                                            
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2u8 >, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2u16>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2u32>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2i8 >, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2i16>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2i32>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2u64 , Vec2d  >, Vec2d::ArrayType  >);


   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2u8 >, Vec2i8::ArrayType >);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2u16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2u32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2i8 >, Vec2i8::ArrayType >);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2i8  , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2u8 >, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2u16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2u32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2i8 >, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2i16 , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2u8 >, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2u16>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2u32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2i8 >, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2i16>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2i32 , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2u8 >, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2u16>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2u32>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2i8 >, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2i16>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2i32>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2i64 , Vec2d  >, Vec2d::ArrayType  >);


   static_assert(CT::Exact<Lossless<Vec2f   , Vec2u8 >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2u16>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2u32>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2u64>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2i8 >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2i16>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2i32>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2i64>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2f   , Vec2d  >, Vec2d::ArrayType  >);


   static_assert(CT::Exact<Lossless<Vec2d   , Vec2u8 >, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2u16>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2u32>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2u64>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2i8 >, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2i16>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2i32>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2i64>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2f  >, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<Vec2d   , Vec2d  >, Vec2d::ArrayType  >);
}

TEST_CASE("LosslessVector checks", "[lossless]") {
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2u8 >, Vec2u8 >);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2u16>, Vec2u16>);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2u32>, Vec2u32>);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2u64>, Vec2u64>);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2i8 >, Vec2i8 >);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2i16>, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2i32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2u8  , Vec2d  >, Vec2d  >);

   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2u8 >, Vec2u16>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2u16>, Vec2u16>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2u32>, Vec2u32>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2u64>, Vec2u64>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2i8 >, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2i16>, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2i32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2u16 , Vec2d  >, Vec2d  >);

   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2u8 >, Vec2u32>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2u16>, Vec2u32>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2u32>, Vec2u32>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2u64>, Vec2u64>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2i8 >, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2i16>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2i32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2u32 , Vec2d  >, Vec2d  >);

   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2u8 >, Vec2u64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2u16>, Vec2u64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2u32>, Vec2u64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2u64>, Vec2u64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2i8 >, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2i16>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2i32>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2u64 , Vec2d  >, Vec2d  >);


   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2u8 >, Vec2i8 >);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2u16>, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2u32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2u64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2i8 >, Vec2i8 >);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2i16>, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2i32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2i8  , Vec2d  >, Vec2d  >);

   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2u8 >, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2u16>, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2u32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2u64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2i8 >, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2i16>, Vec2i16>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2i32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2i16 , Vec2d  >, Vec2d  >);

   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2u8 >, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2u16>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2u32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2u64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2i8 >, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2i16>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2i32>, Vec2i32>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2i32 , Vec2d  >, Vec2d  >);

   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2u8 >, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2u16>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2u32>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2u64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2i8 >, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2i16>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2i32>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2i64>, Vec2i64>);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2i64 , Vec2d  >, Vec2d  >);


   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2u8 >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2u16>, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2u32>, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2u64>, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2i8 >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2i16>, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2i32>, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2i64>, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2f  >, Vec2f  >);
   static_assert(CT::Exact<LosslessVector<Vec2f   , Vec2d  >, Vec2d  >);


   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2u8 >, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2u16>, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2u32>, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2u64>, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2i8 >, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2i16>, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2i32>, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2i64>, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2f  >, Vec2d  >);
   static_assert(CT::Exact<LosslessVector<Vec2d   , Vec2d  >, Vec2d  >);
}