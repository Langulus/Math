///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include <Math/Range.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Range interpretation", "[metadata]", 
	Range2u8,
   Range2u16,
   Range2u32,
   Range2u64, 
	Range2i8,
   Range2i16,
   Range2i32,
   Range2i64, 
	Range2f,
   Range2d
) {
	GIVEN("Range interpreted as A::Number") {
		auto meta = MetaOf<TestType>();

		REQUIRE(meta);
		REQUIRE(		meta->template CastsTo<A::Number>( ));
		REQUIRE(not meta->template CastsTo<A::Number>(1));
		REQUIRE(not meta->template CastsTo<A::Number>(2));
		REQUIRE(not meta->template CastsTo<A::Number>(3));
		REQUIRE(    meta->template CastsTo<A::Number>(4));
	}
}

TEMPLATE_TEST_CASE("Padding and alignment checks for ranges", "[sizes]", ALL_TYPES) {
	using T = TestType;

	REQUIRE(sizeof(TRange<TVec<T, 1>>) == sizeof(T) * 1 * 2);
	REQUIRE(sizeof(TRange<TVec<T, 2>>) == sizeof(T) * 2 * 2);
	REQUIRE(sizeof(TRange<TVec<T, 3>>) == sizeof(T) * 3 * 2);
	REQUIRE(sizeof(TRange<TVec<T, 4>>) == sizeof(T) * 4 * 2);

	REQUIRE(sizeof(TRange<TVec<T, 1>>[12]) == sizeof(TRange<TVec<T, 4>>[3]));
	REQUIRE(sizeof(TRange<TVec<T, 1>>[12]) == sizeof(TRange<TVec<T, 3>>[4]));
	REQUIRE(sizeof(TRange<TVec<T, 1>>[12]) == sizeof(TRange<TVec<T, 2>>[6]));
	REQUIRE(sizeof(TRange<TVec<T, 2>>[12]) == sizeof(TRange<TVec<T, 3>>[8]));
	REQUIRE(sizeof(TRange<TVec<T, 2>>[12]) == sizeof(TRange<TVec<T, 4>>[6]));
	REQUIRE(sizeof(TRange<TVec<T, 3>>[ 8]) == sizeof(TRange<TVec<T, 4>>[6]));
}

TEST_CASE("CountOf checks for ranges", "[CountOf]") {
   using T = float;

   static_assert(CountOf<TRange<TVec<T, 1>>> == 2);
   static_assert(CountOf<TRange<TVec<T, 2>>> == 4);
   static_assert(CountOf<TRange<TVec<T, 3>>> == 6);
   static_assert(CountOf<TRange<TVec<T, 4>>> == 8);

   static_assert(CountOf<TRange<TVec<T, 1>>[12]> == 12*2);
   static_assert(CountOf<TRange<TVec<T, 1>>[12]> == 12*2);
   static_assert(CountOf<TRange<TVec<T, 1>>[12]> == 12*2);
   static_assert(CountOf<TRange<TVec<T, 2>>[12]> == 24*2);
   static_assert(CountOf<TRange<TVec<T, 2>>[12]> == 24*2);
   static_assert(CountOf<TRange<TVec<T, 3>>[ 8]> == 24*2);
}

TEST_CASE("Lossless checks for ranges against vectors", "[lossless]") {
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2u8 >, Vec2u8::ArrayType >);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2u16>, Vec2u16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2u32>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2i8 >, Vec2i8::ArrayType >);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2u8>  , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2u8 >, Vec2u16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2u16>, Vec2u16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2u32>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2i8 >, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2u16> , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2u8 >, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2u16>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2u32>, Vec2u32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2i8 >, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2i16>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2u32> , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2u8 >, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2u16>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2u32>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2u64>, Vec2u64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2i8 >, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2i16>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2i32>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2u64> , Vec2d  >, Vec2d::ArrayType  >);


   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2u8 >, Vec2i8::ArrayType >);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2u16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2u32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2i8 >, Vec2i8::ArrayType >);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2i8>  , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2u8 >, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2u16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2u32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2i8 >, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2i16>, Vec2i16::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2i16> , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2u8 >, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2u16>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2u32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2i8 >, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2i16>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2i32>, Vec2i32::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2i32> , Vec2d  >, Vec2d::ArrayType  >);

   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2u8 >, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2u16>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2u32>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2u64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2i8 >, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2i16>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2i32>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2i64>, Vec2i64::ArrayType>);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2i64> , Vec2d  >, Vec2d::ArrayType  >);


   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2u8 >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2u16>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2u32>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2u64>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2i8 >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2i16>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2i32>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2i64>, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2f  >, Vec2f::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2f>   , Vec2d  >, Vec2d::ArrayType  >);


   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2u8 >, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2u16>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2u32>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2u64>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2i8 >, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2i16>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2i32>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2i64>, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2f  >, Vec2d::ArrayType  >);
   static_assert(CT::Exact<Lossless<TRange<Vec2d>   , Vec2d  >, Vec2d::ArrayType  >);
}

TEST_CASE("LosslessRange checks", "[lossless]") {
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2u8 >, TRange<Vec2u8 >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2u16>, TRange<Vec2u16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2u32>, TRange<Vec2u32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2u64>, TRange<Vec2u64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2i8 >, TRange<Vec2i8 >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2i16>, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2i32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u8> , Vec2d  >, TRange<Vec2d  >>);

   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2u8 >, TRange<Vec2u16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2u16>, TRange<Vec2u16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2u32>, TRange<Vec2u32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2u64>, TRange<Vec2u64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2i8 >, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2i16>, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2i32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u16>, Vec2d  >, TRange<Vec2d  >>);

   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2u8 >, TRange<Vec2u32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2u16>, TRange<Vec2u32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2u32>, TRange<Vec2u32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2u64>, TRange<Vec2u64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2i8 >, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2i16>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2i32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u32>, Vec2d  >, TRange<Vec2d  >>);

   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2u8 >, TRange<Vec2u64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2u16>, TRange<Vec2u64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2u32>, TRange<Vec2u64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2u64>, TRange<Vec2u64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2i8 >, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2i16>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2i32>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2u64>, Vec2d  >, TRange<Vec2d  >>);


   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2u8 >, TRange<Vec2i8 >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2u16>, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2u32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2u64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2i8 >, TRange<Vec2i8 >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2i16>, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2i32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i8> , Vec2d  >, TRange<Vec2d  >>);

   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2u8 >, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2u16>, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2u32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2u64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2i8 >, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2i16>, TRange<Vec2i16>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2i32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i16>, Vec2d  >, TRange<Vec2d  >>);

   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2u8 >, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2u16>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2u32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2u64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2i8 >, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2i16>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2i32>, TRange<Vec2i32>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i32>, Vec2d  >, TRange<Vec2d  >>);

   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2u8 >, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2u16>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2u32>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2u64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2i8 >, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2i16>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2i32>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2i64>, TRange<Vec2i64>>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2i64>, Vec2d  >, TRange<Vec2d  >>);


   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2u8 >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2u16>, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2u32>, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2u64>, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2i8 >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2i16>, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2i32>, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2i64>, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2f  >, TRange<Vec2f  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2f>  , Vec2d  >, TRange<Vec2d  >>);


   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2u8 >, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2u16>, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2u32>, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2u64>, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2i8 >, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2i16>, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2i32>, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2i64>, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2f  >, TRange<Vec2d  >>);
   static_assert(CT::Exact<LosslessRange<TRange<Vec2d>  , Vec2d  >, TRange<Vec2d  >>);
}