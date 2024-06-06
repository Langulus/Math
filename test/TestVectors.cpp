///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include <Math/Vector.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Vectors", "[vec]",
   // Signed vectors                                                    
   (TVector<::std::int8_t,  1>),
   (TVector<::std::int16_t, 1>),
   (TVector<::std::int32_t, 1>),
   (TVector<::std::int64_t, 1>),
   (TVector<Float,          1>),
   (TVector<Double,         1>),
   (TVector<::std::int8_t,  2>),
   (TVector<::std::int16_t, 2>),
   (TVector<::std::int32_t, 2>),
   (TVector<::std::int64_t, 2>),
   (TVector<Float,          2>),
   (TVector<Double,         2>),
   (TVector<::std::int8_t,  3>),
   (TVector<::std::int16_t, 3>),
   (TVector<::std::int32_t, 3>),
   (TVector<::std::int64_t, 3>),
   (TVector<Float,          3>),
   (TVector<Double,         3>),
   (TVector<::std::int8_t,  4>),
   (TVector<::std::int16_t, 4>),
   (TVector<::std::int32_t, 4>),
   (TVector<::std::int64_t, 4>),
   (TVector<Float,          4>),
   (TVector<Double,         4>),
   // Unsigned vectors                                                  
   (TVector<::std::uint8_t,  1>),
   (TVector<::std::uint16_t, 1>),
   (TVector<::std::uint32_t, 1>),
   (TVector<::std::uint64_t, 1>)

) {
   using T = TestType;
   using E = TypeOf<T>;
   constexpr auto C = CountOf<T>;

   GIVEN("A default-initialized vector") {
		T x;

   	REQUIRE(x == 0);

		WHEN("Assigning a vector manually") {
         x = T {0, 5, 12, 1};

         REQUIRE(x == T {0, 5, 12, 1});
		}

		WHEN("Horizontally adding a vector") {
         x = T {1, 5, 12, 1};

         if      constexpr (C == 1)
            REQUIRE(x.HSum() == 1);
         else if constexpr (C == 2)
            REQUIRE(x.HSum() == (1 + 5));
         else if constexpr (C == 3)
            REQUIRE(x.HSum() == (1 + 5 + 12));
         else if constexpr (C == 4)
            REQUIRE(x.HSum() == (1 + 5 + 12 + 1));
         else
            LANGULUS_ERROR("TODO");
      }

		WHEN("Horizontally multiplying a vector") {
         x = T {1, 5, 12, 1};

         if      constexpr (C == 1)
            REQUIRE(x.HMul() == 1);
         else if constexpr (C == 2)
            REQUIRE(x.HMul() == (1 * 5));
         else if constexpr (C == 3)
            REQUIRE(x.HMul() == (1 * 5 * 12));
         else if constexpr (C == 4)
            REQUIRE(x.HMul() == (1 * 5 * 12 * 1));
         else
            LANGULUS_ERROR("TODO");
		}

		WHEN("Testing swizzling (const)") {
         x = T {1, 5, 12, 1};
         const T& cx = x;

         if constexpr (C == 1)
            REQUIRE(cx == 1);
         else if constexpr (C == 2) {
            REQUIRE(cx.xy()   == T {1, 5});
            REQUIRE(cx.yx()   == T {5, 1});
         }
         else if constexpr (C == 3) {
            REQUIRE(cx.xy()   == TVector<E, 2> { 1, 5});
            REQUIRE(cx.yx()   == TVector<E, 2> { 5, 1});
            REQUIRE(cx.xyz()  == TVector<E, 3> { 1, 5, 12});
            REQUIRE(cx.yxz()  == TVector<E, 3> { 5, 1, 12});
            REQUIRE(cx.zyx()  == TVector<E, 3> {12, 5,  1});
         }
         else if constexpr (C == 4) {
            REQUIRE(cx.xy()   == TVector<E, 2> { 1, 5});
            REQUIRE(cx.yx()   == TVector<E, 2> { 5, 1});
            REQUIRE(cx.xyz()  == TVector<E, 3> { 1, 5, 12});
            REQUIRE(cx.yxz()  == TVector<E, 3> { 5, 1, 12});
            REQUIRE(cx.zyx()  == TVector<E, 3> {12, 5,  1});
            REQUIRE(cx.xyzw() == TVector<E, 4> { 1, 5, 12, 1});
            REQUIRE(cx.yxzw() == TVector<E, 4> { 5, 1, 12, 1});
            REQUIRE(cx.zyxw() == TVector<E, 4> {12, 5,  1, 1});
            REQUIRE(cx.wyzx() == TVector<E, 4> { 1, 5, 12, 1});
         }
         else LANGULUS_ERROR("TODO");
      }

		WHEN("Testing swizzling (mutable, using proxy arrays)") {
         x = T {1, 5, 12, 1};

         if constexpr (C == 1)
            REQUIRE(x == 1);
         else if constexpr (C == 2) {
            REQUIRE(x.xy()   == T {1, 5});
            REQUIRE(x.yx()   == T {5, 1});
         }
         else if constexpr (C == 3) {
            REQUIRE(x.xy()   == TVector<E, 2> { 1, 5});
            REQUIRE(x.yx()   == TVector<E, 2> { 5, 1});
            REQUIRE(x.xyz()  == TVector<E, 3> { 1, 5, 12});
            REQUIRE(x.yxz()  == TVector<E, 3> { 5, 1, 12});
            REQUIRE(x.zyx()  == TVector<E, 3> {12, 5,  1});
         }
         else if constexpr (C == 4) {
            REQUIRE(x.xy()   == TVector<E, 2> { 1, 5});
            REQUIRE(x.yx()   == TVector<E, 2> { 5, 1});
            REQUIRE(x.xyz()  == TVector<E, 3> { 1, 5, 12});
            REQUIRE(x.yxz()  == TVector<E, 3> { 5, 1, 12});
            REQUIRE(x.zyx()  == TVector<E, 3> {12, 5,  1});
            REQUIRE(x.xyzw() == TVector<E, 4> { 1, 5, 12, 1});
            REQUIRE(x.yxzw() == TVector<E, 4> { 5, 1, 12, 1});
            REQUIRE(x.zyxw() == TVector<E, 4> {12, 5,  1, 1});
            REQUIRE(x.wyzx() == TVector<E, 4> { 1, 5, 12, 1});
         }
         else LANGULUS_ERROR("TODO");
      }
	}

	GIVEN("Two vectors and a resulting vector") {
		T x {0, 5, 12, 1};
      T y {2, 24, 4, 2};
		T r;

		WHEN("Adding the vectors") {
			r = x + y;

         REQUIRE(r == T {0 + 2, 5 + 24, 12 + 4, 1 + 2});
      }

		WHEN("Adding the vectors in reverse order") {
			r = y + x;

         REQUIRE(r == T {0 + 2, 5 + 24, 12 + 4, 1 + 2});
      }

		WHEN("Subtracting the vectors") {
			r = x - y;

         REQUIRE(r == T {0 - 2, 5 - 24, 12 - 4, 1 - 2});
		}

		WHEN("Subtracting the vectors in reverse order") {
			r = y - x;

         REQUIRE(r == T {2 - 0, 24 - 5, 4 - 12, 2 - 1});
		}

		WHEN("Multiplying the vectors") {
			r = x * y;

         REQUIRE(r == T {0 * 2, 5 * 24, 12 * 4, 1 * 2});
      }

		WHEN("Multiplying the vectors in reverse order") {
			r = y * x;

         REQUIRE(r == T {0 * 2, 5 * 24, 12 * 4, 1 * 2});
      }

		WHEN("Dividing the vectors") {
			r = x / y;

			REQUIRE(r[0] == 0);

         if constexpr (C == 2)
			   REQUIRE(r[1] == Approx(E( 5) / E(24)));
         if constexpr (C == 3)
            REQUIRE(r[2] == Approx(E(12) / E( 4)));
         if constexpr (C == 4)
            REQUIRE(r[3] == Approx(E( 1) / E( 2)));
		}

		WHEN("Dividing the vectors in reverse order") {
			REQUIRE_THROWS(r = y / x);
		}
	}
}
