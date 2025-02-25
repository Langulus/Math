///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Math/Vector.hpp>
#include <Langulus/Math/Normal.hpp>
#include <Langulus/Math/Range.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Ranges", "[range]",
   TRange<Vec1i64 >,
   TRange<Normal2f>,

   TRange<Vec1f   >,
   TRange<Vec1d   >,
   TRange<Vec1i   >,
   TRange<Vec1u   >,
   TRange<Vec1i8  >,
   TRange<Vec1u8  >,
   TRange<Vec1i16 >,
   TRange<Vec1u16 >,
   TRange<Vec1i32 >,
   TRange<Vec1u32 >,
   TRange<Vec1u64 >,
   TRange<Vec2f   >,
   TRange<Vec2d   >,
   TRange<Vec2i   >,
   TRange<Vec2u   >,
   TRange<Vec2i8  >,
   TRange<Vec2u8  >,
   TRange<Vec2i16 >,
   TRange<Vec2u16 >,
   TRange<Vec2i32 >,
   TRange<Vec2u32 >,
   TRange<Vec2i64 >,
   TRange<Vec2u64 >,
   TRange<Vec3f   >,
   TRange<Vec3d   >,
   TRange<Vec3i   >,
   TRange<Vec3u   >,
   TRange<Vec3i8  >,
   TRange<Vec3u8  >,
   TRange<Vec3i16 >,
   TRange<Vec3u16 >,
   TRange<Vec3i32 >,
   TRange<Vec3u32 >,
   TRange<Vec3i64 >,
   TRange<Vec3u64 >,
   TRange<Vec4f   >,
   TRange<Vec4d   >,
   TRange<Vec4i   >,
   TRange<Vec4u   >,
   TRange<Vec4i8  >,
   TRange<Vec4u8  >,
   TRange<Vec4i16 >,
   TRange<Vec4u16 >,
   TRange<Vec4i32 >,
   TRange<Vec4u32 >,
   TRange<Vec4i64 >,
   TRange<Vec4u64 >,

   TRange<Normal2d>,
   TRange<Normal3f>,
   TRange<Normal3d>,
   TRange<Normal4f>,
   TRange<Normal4d>
) {
   using Anyness::Text;
   using Flow::Code;
   using T = TestType;
   using P = typename T::PointType;
   using P2 = typename T::CoalescedType;
   using E = TypeOf<T>;
   constexpr auto C = CountOf<T>;
   static_assert(CT::Exact<E, TypeOf<P>>);
   static_assert(sizeof(E) * CountOf<P> * 2 == sizeof(P) * 2);
   static_assert(sizeof(T) == sizeof(P) * 2);

   GIVEN("A range") {
      if constexpr (not CT::Normalized<T>) {
         WHEN("Default-initialized") {
            T x;
            REQUIRE(x == 0);
            REQUIRE(x.mMin == 0);
            REQUIRE(x.mMax == 0);
         }
      }
      else static_assert(not CT::Defaultable<T>);

      WHEN("Constructing a non-scalar range with missing information (2D)") {
         T x {P {1, 0}, P {2, 0}};

         REQUIRE(x.mMin.x == 1);
         REQUIRE(x.mMax.x == (CT::Normalized<T> ? 1 : 2));

         if constexpr (C >= 4) {
            REQUIRE(x.mMin.y == 0);
            REQUIRE(x.mMax.y == 0);
         }

         if constexpr (C >= 6) {
            REQUIRE(x.mMin.z == 0);
            REQUIRE(x.mMax.z == 0);
         }

         if constexpr (C >= 8) {
            REQUIRE(x.mMin.w == 0);
            REQUIRE(x.mMax.w == 0);
         }
      }

      WHEN("Constructing a non-scalar range with missing information (3D)") {
         T x {P {1, 0, 0}, P {2, 0, 0}};

         REQUIRE(x.mMin.x == 1);
         REQUIRE(x.mMax.x == (CT::Normalized<T> ? 1 : 2));

         if constexpr (C >= 4) {
            REQUIRE(x.mMin.y == 0);
            REQUIRE(x.mMax.y == 0);
         }

         if constexpr (C >= 6) {
            REQUIRE(x.mMin.z == 0);
            REQUIRE(x.mMax.z == 0);
         }

         if constexpr (C >= 8) {
            REQUIRE(x.mMin.w == 0);
            REQUIRE(x.mMax.w == 0);
         }
      }

		WHEN("Assigning a range manually") {
         T x {P {1, 2, 3, 4}, P {1, 2, 3, 4}};
         x = T {P {0, 5, 12, 1}, P {1, 7, 19, 100}};
         
         if constexpr (not CT::Normalized<T>) {
            if constexpr (C == 8) {
               REQUIRE(x == T {P {0, 5, 12, 1}, P {1, 7, 19, 100}});
               REQUIRE(x == P2 {0, 5, 12, 1, 1, 7, 19, 100});
               REQUIRE(x.mMin == P {0, 5, 12, 1});
               REQUIRE(x.mMax == P {1, 7, 19, 100});
            }
            else if constexpr (C == 6) {
               REQUIRE(x == T {P {0, 5, 12}, P {1, 7, 19}});
               REQUIRE(x == P2 {0, 5, 12, 1, 7, 19});
               REQUIRE(x.mMin == P {0, 5, 12});
               REQUIRE(x.mMax == P {1, 7, 19});
            }
            else if constexpr (C == 4) {
               REQUIRE(x == T {P {0, 5}, P {1, 7}});
               REQUIRE(x == P2 {0, 5, 1, 7});
               REQUIRE(x.mMin == P {0, 5});
               REQUIRE(x.mMax == P {1, 7});
            }
            else if constexpr (C == 2) {
               REQUIRE(x == T {P {0}, P {1}});
               REQUIRE(x == P2 {0, 1});
               REQUIRE(x.mMin == 0);
               REQUIRE(x.mMax == 1);
            }
            else static_assert(false, "TODO");
         }
         else if constexpr (C == 8) {
            REQUIRE(x.mMin.x == Approx(0).margin(0.0001));
            REQUIRE(x.mMin.y == Approx(0.3835).margin(0.0001));
            REQUIRE(x.mMin.z == Approx(0.9204).margin(0.0001));
            REQUIRE(x.mMin.w == Approx(0.0767).margin(0.0001));

            REQUIRE(x.mMax.x == Approx(0.0098).margin(0.0001));
            REQUIRE(x.mMax.y == Approx(0.0686).margin(0.0001));
            REQUIRE(x.mMax.z == Approx(0.1862).margin(0.0001));
            REQUIRE(x.mMax.w == Approx(0.9801).margin(0.0001));
         }
         else if constexpr (C == 6) {
            REQUIRE(x.mMin.x == Approx(0).margin(0.0001));
            REQUIRE(x.mMin.y == Approx(0.3846).margin(0.0001));
            REQUIRE(x.mMin.z == Approx(0.9231).margin(0.0001));

            REQUIRE(x.mMax.x == Approx(0.0493).margin(0.0001));
            REQUIRE(x.mMax.y == Approx(0.3453).margin(0.0001));
            REQUIRE(x.mMax.z == Approx(0.9372).margin(0.0001));
         }
         else if constexpr (C == 4) {
            REQUIRE(x.mMin.x == Approx(0).margin(0.0001));
            REQUIRE(x.mMin.y == Approx(1).margin(0.0001));

            REQUIRE(x.mMax.x == Approx(0.1414).margin(0.0001));
            REQUIRE(x.mMax.y == Approx(0.9899).margin(0.0001));
         }
         else static_assert(false, "TODO");
		}

		WHEN("Assigning a vector manually") {
         T x {P2 {1, 2, 3, 4}};
         x = P2 {0, 5, 12, 1};

         if constexpr (not CT::Normalized<T>) {
            if constexpr (C == 8) {
               REQUIRE(x == T {P {0, 5, 12, 1}, P {0, 0, 0, 0}});
               REQUIRE(x == P2 {0, 5, 12, 1});
               REQUIRE(x.mMin == P {0, 5, 12, 1});
               REQUIRE(x.mMax == P {0, 0, 0, 0});
            }
            else if constexpr (C == 6) {
               REQUIRE(x == T {P {0, 5, 12}, P {1, 0, 0}});
               REQUIRE(x == P2 {0, 5, 12, 1});
               REQUIRE(x.mMin == P {0, 5, 12});
               REQUIRE(x.mMax == P {1, 0, 0});
            }
            else if constexpr (C == 4) {
               REQUIRE(x == T {P {0, 5}, P {12, 1}});
               REQUIRE(x == P2 {0, 5, 12, 1});
               REQUIRE(x.mMin == P {0, 5});
               REQUIRE(x.mMax == P {12, 1});
            }
            else if constexpr (C == 2) {
               REQUIRE(x == T {P {0}, P {5}});
               REQUIRE(x == P2 {0, 5});
               REQUIRE(x.mMin == 0);
               REQUIRE(x.mMax == 5);
            }
            else static_assert(false, "TODO");
         }
         else if constexpr (C == 8) {
            REQUIRE(x.mMin.x == Approx(0).margin(0.0001));
            REQUIRE(x.mMin.y == Approx(0.3835).margin(0.0001));
            REQUIRE(x.mMin.z == Approx(0.9204).margin(0.0001));
            REQUIRE(x.mMin.w == Approx(0.0767).margin(0.0001));

            REQUIRE(x.mMax.x == Approx(0).margin(0.0001));
            REQUIRE(x.mMax.y == Approx(0).margin(0.0001));
            REQUIRE(x.mMax.z == Approx(0).margin(0.0001));
            REQUIRE(x.mMax.w == Approx(0).margin(0.0001));
         }
         else if constexpr (C == 6) {
            REQUIRE(x.mMin.x == Approx(0).margin(0.0001));
            REQUIRE(x.mMin.y == Approx(0.3846).margin(0.0001));
            REQUIRE(x.mMin.z == Approx(0.9231).margin(0.0001));

            REQUIRE(x.mMax.x == Approx(1).margin(0.0001));
            REQUIRE(x.mMax.y == Approx(0).margin(0.0001));
            REQUIRE(x.mMax.z == Approx(0).margin(0.0001));
         }
         else if constexpr (C == 4) {
            REQUIRE(x.mMin.x == Approx(0).margin(0.0001));
            REQUIRE(x.mMin.y == Approx(1).margin(0.0001));

            REQUIRE(x.mMax.x == Approx(0.9965).margin(0.0001));
            REQUIRE(x.mMax.y == Approx(0.0830).margin(0.0001));
         }
         else static_assert(false, "TODO");
		}

		WHEN("Assigning a scalar manually") {
         T x {22};
         x = 23;

         if constexpr (CT::Normalized<T>) {
            if constexpr (C == 4) {
               REQUIRE(x.mMin.x == Approx(0.7071).margin(0.0001));
               REQUIRE(x.mMin.y == Approx(0.7071).margin(0.0001));
               REQUIRE(x.mMax.x == Approx(0.7071).margin(0.0001));
               REQUIRE(x.mMax.y == Approx(0.7071).margin(0.0001));
            }
            else if constexpr (C == 6) {
               REQUIRE(x.mMin.x == Approx(0.5774).margin(0.0001));
               REQUIRE(x.mMin.y == Approx(0.5774).margin(0.0001));
               REQUIRE(x.mMin.z == Approx(0.5774).margin(0.0001));
               REQUIRE(x.mMax.x == Approx(0.5774).margin(0.0001));
               REQUIRE(x.mMax.y == Approx(0.5774).margin(0.0001));
               REQUIRE(x.mMax.z == Approx(0.5774).margin(0.0001));
            }
            else if constexpr (C == 8) {
               REQUIRE(x.mMin.x == Approx(0.5).margin(0.0001));
               REQUIRE(x.mMin.y == Approx(0.5).margin(0.0001));
               REQUIRE(x.mMin.z == Approx(0.5).margin(0.0001));
               REQUIRE(x.mMin.w == Approx(0.5).margin(0.0001));
               REQUIRE(x.mMax.x == Approx(0.5).margin(0.0001));
               REQUIRE(x.mMax.y == Approx(0.5).margin(0.0001));
               REQUIRE(x.mMax.z == Approx(0.5).margin(0.0001));
               REQUIRE(x.mMax.w == Approx(0.5).margin(0.0001));
            }
         }
         else {
            REQUIRE(x == T {23});

            if constexpr (C == 2)
               REQUIRE(x == P {23});
            else
               REQUIRE(x != P {23});

            REQUIRE(x.mMin == P {23});
            REQUIRE(x.mMax == P {23});
         }

         REQUIRE(x.GetMin() == x.GetMax());
		}

		WHEN("Calculating length") {
         T x {P {1, 5, 12, 1}, P {1, 7, 19, 100}};

         if constexpr (not CT::Normalized<T>) {
            if constexpr (C == 2)
               REQUIRE(x.Length() == 0);
            else if constexpr (C == 4)
               REQUIRE(x.Length() == P {0, 2});
            else if constexpr (C == 6)
               REQUIRE(x.Length() == P {0, 2, 7});
            else if constexpr (C == 8)
               REQUIRE(x.Length() == P {0, 2, 7, 99});
            else
               static_assert(false, "TODO");
         }
         else {
            if constexpr (C == 2) {
               REQUIRE(x.Length() == Approx(0).margin(0.0001));
            }
            else if constexpr (C == 4) {
               REQUIRE(x.Length().x == Approx(0.1414 - 0.1961).margin(0.0001));
               REQUIRE(x.Length().y == Approx(0.9899 - 0.9806).margin(0.0001));
            }
            else if constexpr (C == 6) {
               REQUIRE(x.Length().x == Approx(0.0493 - 0.0767).margin(0.0001));
               REQUIRE(x.Length().y == Approx(0.3453 - 0.3835).margin(0.0001));
               REQUIRE(x.Length().z == Approx(0.9372 - 0.9204).margin(0.0001));
            }
            else if constexpr (C == 8) {
               REQUIRE(x.Length().x == Approx(0.0098 - 0.0765).margin(0.0001));
               REQUIRE(x.Length().y == Approx(0.0686 - 0.3824).margin(0.0001));
               REQUIRE(x.Length().z == Approx(0.1862 - 0.9177).margin(0.0001));
               REQUIRE(x.Length().w == Approx(0.9801 - 0.0765).margin(0.0001));
            }
            else static_assert(false, "TODO");
         }
      }
	}

	GIVEN("Two ranges and a resulting range") {
      T x {P {0, 5, 12, 1}, P {2, 7, 14, 3}};
      T y {P {2, 24, 4, 2}, P {6, 28, 8, 5}};

		WHEN("Adding the ranges (commutative)") {
         auto tester = [&](T sum) {
            T r = sum;

            if constexpr (not CT::Normalized<T>) {
               REQUIRE(r == T {P {0 + 2, 5 + 24, 12 + 4, 1 + 2},
                               P {2 + 6, 7 + 28, 14 + 8, 3 + 5}});
            }
            else if constexpr (C == 8) {
               REQUIRE(r.mMin.x == Approx(0.0466).margin(0.0001));
               REQUIRE(r.mMin.y == Approx(0.7787).margin(0.0001));
               REQUIRE(r.mMin.z == Approx(0.6190).margin(0.0001));
               REQUIRE(r.mMin.w == Approx(0.0904).margin(0.0001));

               REQUIRE(r.mMax.x == Approx(0.1759).margin(0.0001));
               REQUIRE(r.mMax.y == Approx(0.7418).margin(0.0001));
               REQUIRE(r.mMax.z == Approx(0.6181).margin(0.0001));
               REQUIRE(r.mMax.w == Approx(0.1917).margin(0.0001));
            }
            else if constexpr (C == 6) {
               REQUIRE(r.mMin.x == Approx(0.0468).margin(0.0001));
               REQUIRE(r.mMin.y == Approx(0.7820).margin(0.0001));
               REQUIRE(r.mMin.z == Approx(0.6214).margin(0.0001));

               REQUIRE(r.mMax.x == Approx(0.1791).margin(0.0001));
               REQUIRE(r.mMax.y == Approx(0.7553).margin(0.0001));
               REQUIRE(r.mMax.z == Approx(0.6304).margin(0.0001));
            }
            else if constexpr (C == 4) {
               REQUIRE(r.mMin.x == Approx(0.0415).margin(0.0001));
               REQUIRE(r.mMin.y == Approx(0.9991).margin(0.0001));

               REQUIRE(r.mMax.x == Approx(0.2422).margin(0.0001));
               REQUIRE(r.mMax.y == Approx(0.9702).margin(0.0001));
            }
            else static_assert(false, "TODO");
         };

         tester(x + y);
         tester(y + x);
      }

		WHEN("Subtracting the ranges") {
			T r = x - y;

         if constexpr (not CT::Normalized<T>) {
            REQUIRE(r == T {P {0 - 2, 5 - 24, 12 - 4, 1 - 2},
                            P {2 - 6, 7 - 28, 14 - 8, 3 - 5}});
         }
         else if constexpr (C == 8) {
            REQUIRE(r.mMin.x == Approx(-0.0844).margin(0.0001));
            REQUIRE(r.mMin.y == Approx(-0.6165).margin(0.0001));
            REQUIRE(r.mMin.z == Approx( 0.7827).margin(0.0001));
            REQUIRE(r.mMin.w == Approx(-0.0051).margin(0.0001));

            REQUIRE(r.mMax.x == Approx(-0.0949).margin(0.0001));
            REQUIRE(r.mMax.y == Approx(-0.6277).margin(0.0001));
            REQUIRE(r.mMax.z == Approx( 0.7722).margin(0.0001));
            REQUIRE(r.mMax.w == Approx( 0.0267).margin(0.0001));
         }
         else if constexpr (C == 6) {
            REQUIRE(r.mMin.x == Approx(-0.0844).margin(0.0001));
            REQUIRE(r.mMin.y == Approx(-0.6168).margin(0.0001));
            REQUIRE(r.mMin.z == Approx( 0.7825).margin(0.0001));

            REQUIRE(r.mMax.x == Approx(-0.0942).margin(0.0001));
            REQUIRE(r.mMax.y == Approx(-0.6247).margin(0.0001));
            REQUIRE(r.mMax.z == Approx( 0.7752).margin(0.0001));
         }
         else if constexpr (C == 4) {
            REQUIRE(r.mMin.x == Approx(-0.9991).margin(0.0001));
            REQUIRE(r.mMin.y == Approx( 0.0415).margin(0.0001));

            REQUIRE(r.mMax.x == Approx( 0.9702).margin(0.0001));
            REQUIRE(r.mMax.y == Approx(-0.2422).margin(0.0001));
         }
         else static_assert(false, "TODO");
      }

		WHEN("Subtracting the ranges in reverse order") {
			T r = y - x;

         if constexpr (not CT::Normalized<T>) {
            REQUIRE(r == T {P {2 - 0, 24 - 5, 4 - 12, 2 - 1},
                            P {6 - 2, 28 - 7, 8 - 14, 5 - 3}});
         }
         else if constexpr (C == 8) {
            REQUIRE(r.mMin.x == Approx( 0.0844).margin(0.0001));
            REQUIRE(r.mMin.y == Approx( 0.6165).margin(0.0001));
            REQUIRE(r.mMin.z == Approx(-0.7827).margin(0.0001));
            REQUIRE(r.mMin.w == Approx( 0.0051).margin(0.0001));

            REQUIRE(r.mMax.x == Approx( 0.0949).margin(0.0001));
            REQUIRE(r.mMax.y == Approx( 0.6277).margin(0.0001));
            REQUIRE(r.mMax.z == Approx(-0.7722).margin(0.0001));
            REQUIRE(r.mMax.w == Approx(-0.0267).margin(0.0001));
         }
         else if constexpr (C == 6) {
            REQUIRE(r.mMin.x == Approx( 0.0844).margin(0.0001));
            REQUIRE(r.mMin.y == Approx( 0.6168).margin(0.0001));
            REQUIRE(r.mMin.z == Approx(-0.7825).margin(0.0001));

            REQUIRE(r.mMax.x == Approx( 0.0942).margin(0.0001));
            REQUIRE(r.mMax.y == Approx( 0.6247).margin(0.0001));
            REQUIRE(r.mMax.z == Approx(-0.7752).margin(0.0001));
         }
         else if constexpr (C == 4) {
            REQUIRE(r.mMin.x == Approx( 0.9991).margin(0.0001));
            REQUIRE(r.mMin.y == Approx(-0.0415).margin(0.0001));

            REQUIRE(r.mMax.x == Approx(-0.9702).margin(0.0001));
            REQUIRE(r.mMax.y == Approx( 0.2422).margin(0.0001));
         }
         else static_assert(false, "TODO");
      }

		WHEN("Multiplying the ranges (commutative)") {
         auto tester = [&](T product) {
            T r = product;

            if constexpr (not CT::Normalized<T>) {
               REQUIRE(r == T {P {0 * 2, 5 * 24, 12 * 4, 1 * 2},
                               P {2 * 6, 7 * 28, 14 * 8, 3 * 5}});
            }
            else if constexpr (C == 8) {
               REQUIRE(r.mMin.x == 0);
               REQUIRE(r.mMin.y == Approx(0.9284).margin(0.0001));
               REQUIRE(r.mMin.z == Approx(0.3713).margin(0.0001));
               REQUIRE(r.mMin.w == Approx(0.0155).margin(0.0001));

               REQUIRE(r.mMax.x == Approx(0.053).margin(0.0001));
               REQUIRE(r.mMax.y == Approx(0.8652).margin(0.0001));
               REQUIRE(r.mMax.z == Approx(0.4943).margin(0.0001));
               REQUIRE(r.mMax.w == Approx(0.0662).margin(0.0001));
            }
            else if constexpr (C == 6) {
               REQUIRE(r.mMin.x == 0);
               REQUIRE(r.mMin.y == Approx(0.9284).margin(0.0001));
               REQUIRE(r.mMin.z == Approx(0.3713).margin(0.0001));

               REQUIRE(r.mMax.x == Approx(0.0531).margin(0.0001));
               REQUIRE(r.mMax.y == Approx(0.8670).margin(0.0001));
               REQUIRE(r.mMax.z == Approx(0.4955).margin(0.0001));
            }
            else if constexpr (C == 4) {
               REQUIRE(r.mMin.x == 0);
               REQUIRE(r.mMin.y == Approx(1));

               REQUIRE(r.mMax.x == Approx(0.0611).margin(0.0001));
               REQUIRE(r.mMax.y == Approx(0.9981).margin(0.0001));
            }
            else static_assert(false, "TODO");
         };

         tester(x * y);
         tester(y * x);
      }

		WHEN("Dividing the ranges") {
			T r = x / y;

         if constexpr (not CT::Normalized<T>) {
            REQUIRE(r.mMin.x == 0);
            REQUIRE(r.mMax.x == Approx(E(2) / E(6)));

            if constexpr (C >= 4) {
               REQUIRE(r.mMin.y == Approx(E(5) / E(24)));
               REQUIRE(r.mMax.y == Approx(E(7) / E(28)));
            }

            if constexpr (C >= 6) {
               REQUIRE(r.mMin.z == Approx(E(12) / E(4)));
               REQUIRE(r.mMax.z == Approx(E(14) / E(8)));
            }

            if constexpr (C >= 8) {
               REQUIRE(r.mMin.w == Approx(E(1) / E(2)));
               REQUIRE(r.mMax.w == Approx(E(3) / E(5)));
            }
         }
         else if constexpr (C == 8) {
            REQUIRE(r.mMin.x == 0);
            REQUIRE(r.mMin.y == Approx(0.0683).margin(0.0001));
            REQUIRE(r.mMin.z == Approx(0.9841).margin(0.0001));
            REQUIRE(r.mMin.w == Approx(0.1640).margin(0.0001));

            REQUIRE(r.mMax.x == Approx(0.1757).margin(0.0001));
            REQUIRE(r.mMax.y == Approx(0.1318).margin(0.0001));
            REQUIRE(r.mMax.z == Approx(0.9228).margin(0.0001));
            REQUIRE(r.mMax.w == Approx(0.3163).margin(0.0001));
         }
         else if constexpr (C == 6) {
            REQUIRE(r.mMin.x == 0);
            REQUIRE(r.mMin.y == Approx(0.0692).margin(0.0001));
            REQUIRE(r.mMin.z == Approx(0.9976).margin(0.0001));

            REQUIRE(r.mMax.x == Approx(0.1853).margin(0.0001));
            REQUIRE(r.mMax.y == Approx(0.1390).margin(0.0001));
            REQUIRE(r.mMax.z == Approx(0.9728).margin(0.0001));
         }
         else if constexpr (C == 4) {
            REQUIRE(r.mMin.x == 0);
            REQUIRE(r.mMin.y == Approx(1));

            REQUIRE(r.mMax.x == Approx(0.8).margin(0.0001));
            REQUIRE(r.mMax.y == Approx(0.6).margin(0.0001));
         }
         else static_assert(false, "TODO");
		}

		WHEN("Dividing the vectors in reverse order") {
         T r {1};
			REQUIRE_THROWS(r = y / x);
		}
	}

   if constexpr (not CT::Normalized<T>) {
      GIVEN("A preinitialized range") {
         T x {P {0, 5, 12, 1}, P {2, 7, 14, 3}};

         WHEN("Contained in type-erased container") {
            Many packed = x;

            REQUIRE(packed == x);
         }

         WHEN("Serialized as text") {
            if constexpr (C == 2) {
               const auto serialized = static_cast<Text>(x);
               REQUIRE(serialized == MetaDataOf<T>() + "(0; 2)"_text);
            }
            else if constexpr (C == 4) {
               const auto serialized = static_cast<Text>(x);
               const auto required = MetaDataOf<T>() + "((0, 5); (2, 7))"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 6) {
               const auto serialized = static_cast<Text>(x);
               const auto required = MetaDataOf<T>() + "((0, 5, 12); (2, 7, 14))"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 8) {
               const auto serialized = static_cast<Text>(x);
               const auto required = MetaDataOf<T>() + "((0, 5, 12, 1); (2, 7, 14, 3))"_text;
               REQUIRE(serialized == required);
            }
         }

         WHEN("Serialized as code") {
            if constexpr (C == 2) {
               const auto serialized = static_cast<Code>(x);
               REQUIRE(serialized == MetaDataOf<T>() + "(0, 2)"_text);
            }
            else if constexpr (C == 4) {
               const auto serialized = static_cast<Code>(x);
               const auto required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 5), " + MetaDataOf<P>() + "(2, 7))"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 6) {
               const auto serialized = static_cast<Code>(x);
               const auto required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 5, 12), " + MetaDataOf<P>() + "(2, 7, 14))"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 8) {
               const auto serialized = static_cast<Code>(x);
               const auto required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 5, 12, 1), " + MetaDataOf<P>() + "(2, 7, 14, 3))"_text;
               REQUIRE(serialized == required);
            }
         }
      }
   }

   if constexpr (CT::Float<E>) {
      GIVEN("A preinitialized float range") {
         T x {P {E {0.0f}, E {5.00001f}, E {-12.532f}, E {6666.1f}},
              P {E {2.0f}, E {7.00001f}, E {-14.532f}, E {3.1f}}};

         WHEN("Contained in type-erased container") {
            Many packed = x;
            Logger::Info(packed, " == ", static_cast<Code>(x));

            if constexpr (CT::Normalized<T>) {
               if constexpr (C == 6) {
                  REQUIRE(packed.As<T>().mMin.x == Approx( 0).margin(0.0001));
                  REQUIRE(packed.As<T>().mMin.y == Approx( 0.3705).margin(0.0001));
                  REQUIRE(packed.As<T>().mMin.z == Approx(-0.9288).margin(0.0001));

                  REQUIRE(packed.As<T>().mMax.x == Approx( 0.1230).margin(0.0001));
                  REQUIRE(packed.As<T>().mMax.y == Approx( 0.4307).margin(0.0001));
                  REQUIRE(packed.As<T>().mMax.z == Approx(-0.8941).margin(0.0001));
               }
               else if constexpr (C == 8) {
                  REQUIRE(packed.As<T>().mMin.x == Approx( 0).margin(0.0001));
                  REQUIRE(packed.As<T>().mMin.y == Approx( 0.0008).margin(0.0001));
                  REQUIRE(packed.As<T>().mMin.z == Approx(-0.0019).margin(0.0001));
                  REQUIRE(packed.As<T>().mMin.w == Approx( 1).margin(0.0001));

                  REQUIRE(packed.As<T>().mMax.x == Approx( 0.1209).margin(0.0001));
                  REQUIRE(packed.As<T>().mMax.y == Approx( 0.4230).margin(0.0001));
                  REQUIRE(packed.As<T>().mMax.z == Approx(-0.8782).margin(0.0001));
                  REQUIRE(packed.As<T>().mMax.w == Approx( 0.1873).margin(0.0001));
               }
            }
            else {
               REQUIRE(packed == x);
            }
         }

         WHEN("Serialized as text") {
            const auto serialized = static_cast<Text>(x);

            if constexpr (C == 2) {
               REQUIRE(serialized == MetaDataOf<T>() + "(0; 2)"_text);
            }
            else if constexpr (C == 4) {
               if constexpr (CT::Normalized<T>) {
                  const auto required = MetaDataOf<T>() + "((0, 1); (~0.27, ~0.96))"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const auto required = MetaDataOf<T>() + "((0, ~5); (2, ~7))"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 6) {
               if constexpr (CT::Normalized<T>) {
                  const auto required = MetaDataOf<T>() + "((0, ~0.37, ~-0.93); (~0.12, ~0.43, ~-0.89))"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const auto required = MetaDataOf<T>() + "((0, ~5, ~-12.53); (2, ~7, ~-14.53))"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 8) {
               if constexpr (CT::Normalized<T>) {
                  const auto required = MetaDataOf<T>() + "((0, ~0, ~-0, ~1); (~0.12, ~0.42, ~-0.88, ~0.19))"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const auto required = MetaDataOf<T>() + "((0, ~5, ~-12.53, 6666.1); (2, ~7, ~-14.53, 3.1))"_text;
                  REQUIRE(serialized == required);
               }
            }
         }

         WHEN("Serialized as code") {
            const auto serialized = static_cast<Code>(x);

            if constexpr (C == 1) {
               REQUIRE(serialized == MetaDataOf<T>() + "(0, 2)"_text);
            }
            else if constexpr (C == 4) {
               if constexpr (CT::Normalized<T>) {
                  const Code required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 1), " + MetaDataOf<P>() + "(0.27472076, 0.961524))"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const Code required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 5.00001), " + MetaDataOf<P>() + "(2, 7.00001))"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 6) {
               if constexpr (CT::Normalized<T>) {
                  const Code required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 0.37057337, -0.9288032), " + MetaDataOf<P>() + "(0.12304974, 0.43067473, -0.8940794))"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const Code required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 5.00001, -12.532), " + MetaDataOf<P>() + "(2, 7.00001, -14.532))"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 8) {
               if constexpr (CT::Normalized<T>) {
                  const Code required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 0.0007500637, -0.0018799558, 0.9999979), " + MetaDataOf<P>() + "(0.12087093, 0.42304888, -0.87824816, 0.18734995))"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const Code required = MetaDataOf<T>() + "(" + MetaDataOf<P>() + "(0, 5.00001, -12.532, 6666.1), " + MetaDataOf<P>() + "(2, 7.00001, -14.532, 3.1))"_text;
                  REQUIRE(serialized == required);
               }
            }
         }
      }
   }

   if constexpr (not CT::Normalized<T>) {
      GIVEN("A scalar descriptor with number literal") {
         const Code descriptor = NameOf<T>() + "(1)"_code;
         const auto parsed = descriptor.Parse();
         Logger::Info(parsed, " == ", static_cast<Code>(T {1}));
         REQUIRE(parsed == T {1});
      }
   }

   GIVEN("A component descriptor with number literals") {
      WHEN("Parsing the Range {{1, 2, 3, 4}, {2, 7, 14, 3}}") {
         const Code descriptor = NameOf<T>() + "(" + NameOf<P>() + "(1, 2, 3, 4), " + NameOf<P>() + "(2, 7, 14, 3))"_code;
         const auto parsed = descriptor.Parse();
         Logger::Info(parsed, " == ", static_cast<Code>(T {P {1, 2, 3, 4}, P {2, 7, 14, 3}}));

         if constexpr (CT::Normalized<T>) {
            if constexpr (C == 6) {
               REQUIRE(parsed.As<T>().mMin.x == Approx(0.26726).margin(0.0001));
               REQUIRE(parsed.As<T>().mMin.y == Approx(0.53452).margin(0.0001));
               REQUIRE(parsed.As<T>().mMin.z == Approx(0.80178).margin(0.0001));

               REQUIRE(parsed.As<T>().mMax.x == Approx(0.1267).margin(0.0001));
               REQUIRE(parsed.As<T>().mMax.y == Approx(0.4436).margin(0.0001));
               REQUIRE(parsed.As<T>().mMax.z == Approx(0.8872).margin(0.0001));
            }
            else if constexpr (C == 8) {
               REQUIRE(parsed.As<T>().mMin.x == Approx(0.18257).margin(0.0001));
               REQUIRE(parsed.As<T>().mMin.y == Approx(0.36515).margin(0.0001));
               REQUIRE(parsed.As<T>().mMin.z == Approx(0.54772).margin(0.0001));
               REQUIRE(parsed.As<T>().mMin.w == Approx(0.7303) .margin(0.0001));

               REQUIRE(parsed.As<T>().mMax.x == Approx(0.1245) .margin(0.0001));
               REQUIRE(parsed.As<T>().mMax.y == Approx(0.4358).margin(0.0001));
               REQUIRE(parsed.As<T>().mMax.z == Approx(0.8716).margin(0.0001));
               REQUIRE(parsed.As<T>().mMax.w == Approx(0.1868) .margin(0.0001));
            }
         }
         else {
            REQUIRE(parsed == T {P {1, 2, 3, 4}, P {2, 7, 14, 3}});
         }
      }

      if constexpr (CT::Signed<E>) {
         WHEN("Parsing the Range {{0, 0, -1}, {0, 0, 1}}") {
            const Code descriptor = NameOf<T>() + "(Vec3(0, 0, -1), Vec3(0, 0, 1))"_code;
            const auto parsed = descriptor.Parse();
            Logger::Info(parsed, " == ", static_cast<Code>(T {P {0, 0, -1}, P {0, 0, 1}}));

            REQUIRE(parsed == T {P {0, 0, -1}, P {0, 0, 1}});
         }
      }
   }

   GIVEN("Nested descriptors") {
      const Code descriptor = NameOf<T>() + "(Range4(" + NameOf<P>() + "(1, 2, 3, 4), " + NameOf<P>() + "(5, 5, 5, 6)))"_code;
      const auto parsed = descriptor.Parse();
      Logger::Info(parsed, " == ", static_cast<Code>(T {P {1, 2, 3, 4}, P {5, 5, 5, 6}}));

      if constexpr (CT::Normalized<T>) {
         if constexpr (C == 6) {
            REQUIRE(parsed.As<T>().mMin.x == Approx(0.26726).margin(0.0001));
            REQUIRE(parsed.As<T>().mMin.y == Approx(0.53452).margin(0.0001));
            REQUIRE(parsed.As<T>().mMin.z == Approx(0.80178).margin(0.0001));

            REQUIRE(parsed.As<T>().mMax.x == Approx(0.5774).margin(0.0001));
            REQUIRE(parsed.As<T>().mMax.y == Approx(0.5774).margin(0.0001));
            REQUIRE(parsed.As<T>().mMax.z == Approx(0.5774).margin(0.0001));
         }
         else if constexpr (C == 8) {
            REQUIRE(parsed.As<T>().mMin.x == Approx(0.18257).margin(0.0001));
            REQUIRE(parsed.As<T>().mMin.y == Approx(0.36515).margin(0.0001));
            REQUIRE(parsed.As<T>().mMin.z == Approx(0.54772).margin(0.0001));
            REQUIRE(parsed.As<T>().mMin.w == Approx(0.7303).margin(0.0001));

            REQUIRE(parsed.As<T>().mMax.x == Approx(0.4746).margin(0.0001));
            REQUIRE(parsed.As<T>().mMax.y == Approx(0.4746).margin(0.0001));
            REQUIRE(parsed.As<T>().mMax.z == Approx(0.4746).margin(0.0001));
            REQUIRE(parsed.As<T>().mMax.w == Approx(0.5695).margin(0.0001));
         }
      }
      else {
         REQUIRE(parsed == T {P {1, 2, 3, 4}, P {5, 5, 5, 6}});
      }
   }
}

TEST_CASE("Range constants", "[range]") {
   using T = Range3;

   GIVEN("Descriptors involving CMeta") {
      WHEN("Using Ranges::In") {
         const Code descriptor = NameOf<T>() + "(Ranges::In)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::In});
      }

      WHEN("Using Ranges::On") {
         const Code descriptor = NameOf<T>() + "(Ranges::On)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::On});
      }

      WHEN("Using Ranges::Under") {
         const Code descriptor = NameOf<T>() + "(Ranges::Under)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Under});
      }

      WHEN("Using Ranges::Above") {
         const Code descriptor = NameOf<T>() + "(Ranges::Above)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Above});
      }

      WHEN("Using Ranges::Below") {
         const Code descriptor = NameOf<T>() + "(Ranges::Below)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Below});
      }

      WHEN("Using Ranges::Center") {
         const Code descriptor = NameOf<T>() + "(Ranges::Center)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Center});
      }

      WHEN("Using Ranges::Middle") {
         const Code descriptor = NameOf<T>() + "(Ranges::Middle)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Middle});
      }

      WHEN("Using Ranges::Rear") {
         const Code descriptor = NameOf<T>() + "(Ranges::Rear)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Rear});
      }

      WHEN("Using Ranges::Behind") {
         const Code descriptor = NameOf<T>() + "(Ranges::Behind)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Behind});
      }

      WHEN("Using Ranges::Front") {
         const Code descriptor = NameOf<T>() + "(Ranges::Front)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Front});
      }

      WHEN("Using Ranges::Ahead") {
         const Code descriptor = NameOf<T>() + "(Ranges::Ahead)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Ahead});
      }

      WHEN("Using Ranges::Left") {
         const Code descriptor = NameOf<T>() + "(Ranges::Left)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Left});
      }

      WHEN("Using Ranges::Right") {
         const Code descriptor = NameOf<T>() + "(Ranges::Right)"_code;
         REQUIRE(descriptor.Parse() == T {Ranges::Right});
      }
   }
}