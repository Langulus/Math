///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Math/Vector.hpp>
#include <Math/Normal.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Vectors", "[vec]",
   Normal2,

   Vec1   ,
   Vec1f  ,
   Vec1d  ,
   Vec1i  ,
   Vec1u  ,
   Vec1i8 ,
   Vec1u8 ,
   Vec1i16,
   Vec1u16,
   Vec1i32,
   Vec1u32,
   Vec1i64,
   Vec1u64,
   Vec2   ,
   Vec2f  ,
   Vec2d  ,
   Vec2i  ,
   Vec2u  ,
   Vec2i8 ,
   Vec2u8 ,
   Vec2i16,
   Vec2u16,
   Vec2i32,
   Vec2u32,
   Vec2i64,
   Vec2u64,
   Vec3   ,
   Vec3f  ,
   Vec3d  ,
   Vec3i  ,
   Vec3u  ,
   Vec3i8 ,
   Vec3u8 ,
   Vec3i16,
   Vec3u16,
   Vec3i32,
   Vec3u32,
   Vec3i64,
   Vec3u64,
   Vec4   ,
   Vec4f  ,
   Vec4d  ,
   Vec4i  ,
   Vec4u  ,
   Vec4i8 ,
   Vec4u8 ,
   Vec4i16,
   Vec4u16,
   Vec4i32,
   Vec4u32,
   Vec4i64,
   Vec4u64,

   Normal2f,
   Normal2d,
   Normal3 ,
   Normal3f,
   Normal3d,
   Normal4 ,
   Normal4f,
   Normal4d
) {
   using Anyness::Text;
   using Flow::Code;
   using T = TestType;
   using E = TypeOf<T>;
   constexpr auto C = CountOf<T>;

   GIVEN("A vector") {
      if constexpr (not CT::Normalized<T>) {
         WHEN("Default-initialized") {
            T x;
            REQUIRE(x == 0);
         }
      }
      else static_assert(not CT::Defaultable<T>);

      WHEN("Constructing a non-scalar vector with missing information (2D)") {
         T x {1, 0};

         REQUIRE(x.x == 1);

         if constexpr (C >= 2)
            REQUIRE(x.y == 0);
         if constexpr (C >= 3)
            REQUIRE(x.z == 0);
         if constexpr (C >= 4)
            REQUIRE(x.w == 0);
      }

      WHEN("Constructing a non-scalar vector with missing information (3D)") {
         T x {1, 0, 0};

         REQUIRE(x.x == 1);

         if constexpr (C >= 2)
            REQUIRE(x.y == 0);
         if constexpr (C >= 3)
            REQUIRE(x.z == 0);
         if constexpr (C >= 4)
            REQUIRE(x.w == 0);
      }

		WHEN("Assigning a vector manually") {
         T x {1, 2, 3, 4};
         x = T {0, 5, 12, 1};

         REQUIRE(x == T {0, 5, 12, 1});
		}

		WHEN("Horizontally adding a vector") {
         T x {1, 5, 12, 1};

         if constexpr (not CT::Normalized<T>) {
            if constexpr (C == 1)
               REQUIRE(x.HSum() == 1);
            else if constexpr (C == 2)
               REQUIRE(x.HSum() == (1 + 5));
            else if constexpr (C == 3)
               REQUIRE(x.HSum() == (1 + 5 + 12));
            else if constexpr (C == 4)
               REQUIRE(x.HSum() == (1 + 5 + 12 + 1));
            else
               static_assert(false, "TODO");
         }
         else {
            if constexpr (C == 2)
               REQUIRE(x.HSum() == Approx(1.1767).margin(0.0001));
            else if constexpr (C == 3)
               REQUIRE(x.HSum() == Approx(1.3805).margin(0.0001));
            else if constexpr (C == 4)
               REQUIRE(x.HSum() == Approx(1.4529).margin(0.0001));
            else
               static_assert(false, "TODO");
         }
      }

		WHEN("Horizontally multiplying a vector") {
         T x {1, 5, 12, 1};

         if constexpr (not CT::Normalized<T>) {
            if      constexpr (C == 1)
               REQUIRE(x.HMul() == 1);
            else if constexpr (C == 2)
               REQUIRE(x.HMul() == (1 * 5));
            else if constexpr (C == 3)
               REQUIRE(x.HMul() == (1 * 5 * 12));
            else if constexpr (C == 4)
               REQUIRE(x.HMul() == (1 * 5 * 12 * 1));
            else
               static_assert(false, "TODO");
         }
         else {
            if constexpr (C == 2)
               REQUIRE(x.HMul() == Approx(0.19231).margin(0.0001));
            else if constexpr (C == 3)
               REQUIRE(x.HMul() == Approx(0.02707).margin(0.0001));
            else if constexpr (C == 4)
               REQUIRE(x.HMul() == Approx(0.00205).margin(0.0001));
            else
               static_assert(false, "TODO");
         }
		}

		WHEN("Testing swizzling") {
         T x {1, 5, 12, 1};

         auto tester = []<class TEST>(TEST cx) {
            if constexpr (C == 1)
               REQUIRE(cx == 1);
            else if constexpr (C == 2) {
               if constexpr (CT::Normalized<T>) {
                  REQUIRE(cx.xy().x == Approx(0.19611).margin(0.0001));
                  REQUIRE(cx.xy().y == Approx(0.98058).margin(0.0001));

                  REQUIRE(cx.yx().x == Approx(0.98058).margin(0.0001));
                  REQUIRE(cx.yx().y == Approx(0.19611).margin(0.0001));
               }
               else {
                  REQUIRE(cx.xy()   == T {1, 5});
                  REQUIRE(cx.yx()   == T {5, 1});
               }
            }
            else if constexpr (C == 3) {
               if constexpr (CT::Normalized<T>) {
                  REQUIRE(cx.xy().x  == Approx(0.0767).margin(0.0001));
                  REQUIRE(cx.xy().y  == Approx(0.3834).margin(0.0001));
                                     
                  REQUIRE(cx.yx().x  == Approx(0.3834).margin(0.0001));
                  REQUIRE(cx.yx().y  == Approx(0.0767).margin(0.0001));

                  REQUIRE(cx.xyz().x == Approx(0.0767).margin(0.0001));
                  REQUIRE(cx.xyz().y == Approx(0.3834).margin(0.0001));
                  REQUIRE(cx.xyz().z == Approx(0.9203).margin(0.0001));

                  REQUIRE(cx.yxz().x == Approx(0.3834).margin(0.0001));
                  REQUIRE(cx.yxz().y == Approx(0.0767).margin(0.0001));
                  REQUIRE(cx.yxz().z == Approx(0.9203).margin(0.0001));

                  REQUIRE(cx.zyx().x == Approx(0.9203).margin(0.0001));
                  REQUIRE(cx.zyx().y == Approx(0.3834).margin(0.0001));
                  REQUIRE(cx.zyx().z == Approx(0.0767).margin(0.0001));
               }
               else {
                  REQUIRE(cx.xy()   == TVector<E, 2> { 1, 5});
                  REQUIRE(cx.yx()   == TVector<E, 2> { 5, 1});
                  REQUIRE(cx.xyz()  == TVector<E, 3> { 1, 5, 12});
                  REQUIRE(cx.yxz()  == TVector<E, 3> { 5, 1, 12});
                  REQUIRE(cx.zyx()  == TVector<E, 3> {12, 5, 1});
               }
            }
            else if constexpr (C == 4) {
               if constexpr (CT::Normalized<T>) {
                  REQUIRE(cx.xy().x == Approx(0.0765).margin(0.0001));
                  REQUIRE(cx.xy().y == Approx(0.3824).margin(0.0001));

                  REQUIRE(cx.yx().x == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.yx().y == Approx(0.0765).margin(0.0001));

                  REQUIRE(cx.xyz().x == Approx(0.0765).margin(0.0001));
                  REQUIRE(cx.xyz().y == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.xyz().z == Approx(0.9177).margin(0.0001));

                  REQUIRE(cx.yxz().x == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.yxz().y == Approx(0.0765).margin(0.0001));
                  REQUIRE(cx.yxz().z == Approx(0.9177).margin(0.0001));

                  REQUIRE(cx.zyx().x == Approx(0.9177).margin(0.0001));
                  REQUIRE(cx.zyx().y == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.zyx().z == Approx(0.0765).margin(0.0001));

                  REQUIRE(cx.xyzw().x == Approx(0.0765).margin(0.0001));
                  REQUIRE(cx.xyzw().y == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.xyzw().z == Approx(0.9177).margin(0.0001));
                  REQUIRE(cx.xyzw().w == Approx(0.0765).margin(0.0001));

                  REQUIRE(cx.yxzw().x == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.yxzw().y == Approx(0.0765).margin(0.0001));
                  REQUIRE(cx.yxzw().z == Approx(0.9177).margin(0.0001));
                  REQUIRE(cx.yxzw().w == Approx(0.0765).margin(0.0001));

                  REQUIRE(cx.zyxw().x == Approx(0.9177).margin(0.0001));
                  REQUIRE(cx.zyxw().y == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.zyxw().z == Approx(0.0765).margin(0.0001));
                  REQUIRE(cx.zyxw().w == Approx(0.0765).margin(0.0001));

                  REQUIRE(cx.wyzx().x == Approx(0.0765).margin(0.0001));
                  REQUIRE(cx.wyzx().y == Approx(0.3824).margin(0.0001));
                  REQUIRE(cx.wyzx().z == Approx(0.9177).margin(0.0001));
                  REQUIRE(cx.wyzx().w == Approx(0.0765).margin(0.0001));
               }
               else {
                  REQUIRE(cx.xy()   == TVector<E, 2> { 1, 5});
                  REQUIRE(cx.yx()   == TVector<E, 2> { 5, 1});
                  REQUIRE(cx.xyz()  == TVector<E, 3> { 1, 5, 12});
                  REQUIRE(cx.yxz()  == TVector<E, 3> { 5, 1, 12});
                  REQUIRE(cx.zyx()  == TVector<E, 3> {12, 5, 1});
                  REQUIRE(cx.xyzw() == TVector<E, 4> { 1, 5, 12, 1});
                  REQUIRE(cx.yxzw() == TVector<E, 4> { 5, 1, 12, 1});
                  REQUIRE(cx.zyxw() == TVector<E, 4> {12, 5, 1, 1});
                  REQUIRE(cx.wyzx() == TVector<E, 4> { 1, 5, 12, 1});
               }
            }
            else static_assert(false, "TODO");
         };

         tester.template operator() <const T&> (x);
         tester.template operator() <      T&> (x);
      }
	}

	GIVEN("Two vectors and a resulting vector") {
		T x {0, 5, 12, 1};
      T y {2, 24, 4, 2};

		WHEN("Adding the vectors (commutative)") {
         auto tester = [&](T sum) {
            T r = sum;

            if constexpr (not CT::Normalized<T>) {
               REQUIRE(r == T {0 + 2, 5 + 24, 12 + 4, 1 + 2});
            }
            else if constexpr (C == 4) {
               REQUIRE(r.x == Approx(0.0466).margin(0.0001));
               REQUIRE(r.y == Approx(0.7787).margin(0.0001));
               REQUIRE(r.z == Approx(0.6190).margin(0.0001));
               REQUIRE(r.w == Approx(0.0904).margin(0.0001));
            }
            else if constexpr (C == 3) {
               REQUIRE(r.x == Approx(0.0468).margin(0.0001));
               REQUIRE(r.y == Approx(0.7820).margin(0.0001));
               REQUIRE(r.z == Approx(0.6214).margin(0.0001));
            }
            else if constexpr (C == 2) {
               REQUIRE(r.x == Approx(0.0415).margin(0.0001));
               REQUIRE(r.y == Approx(0.9991).margin(0.0001));
            }
            else static_assert(false, "TODO");
         };

         tester(x + y);
         tester(y + x);
      }

		WHEN("Subtracting the vectors") {
			T r = x - y;

         if constexpr (not CT::Normalized<T>) {
            REQUIRE(r == T {0 - 2, 5 - 24, 12 - 4, 1 - 2});
         }
         else if constexpr (C == 4) {
            REQUIRE(r.x == Approx(-0.0844).margin(0.0001));
            REQUIRE(r.y == Approx(-0.6165).margin(0.0001));
            REQUIRE(r.z == Approx( 0.7827).margin(0.0001));
            REQUIRE(r.w == Approx(-0.0051).margin(0.0001));
         }
         else if constexpr (C == 3) {
            REQUIRE(r.x == Approx(-0.0844).margin(0.0001));
            REQUIRE(r.y == Approx(-0.6168).margin(0.0001));
            REQUIRE(r.z == Approx( 0.7825).margin(0.0001));
         }
         else if constexpr (C == 2) {
            REQUIRE(r.x == Approx(-0.9991).margin(0.0001));
            REQUIRE(r.y == Approx( 0.0415).margin(0.0001));
         }
         else static_assert(false, "TODO");
      }

		WHEN("Subtracting the vectors in reverse order") {
			T r = y - x;

         if constexpr (not CT::Normalized<T>) {
            REQUIRE(r == T {2 - 0, 24 - 5, 4 - 12, 2 - 1});
         }
         else if constexpr (C == 4) {
            REQUIRE(r.x == Approx( 0.0844).margin(0.0001));
            REQUIRE(r.y == Approx( 0.6165).margin(0.0001));
            REQUIRE(r.z == Approx(-0.7827).margin(0.0001));
            REQUIRE(r.w == Approx( 0.0051).margin(0.0001));
         }
         else if constexpr (C == 3) {
            REQUIRE(r.x == Approx( 0.0844).margin(0.0001));
            REQUIRE(r.y == Approx( 0.6168).margin(0.0001));
            REQUIRE(r.z == Approx(-0.7825).margin(0.0001));
         }
         else if constexpr (C == 2) {
            REQUIRE(r.x == Approx( 0.9991).margin(0.0001));
            REQUIRE(r.y == Approx(-0.0415).margin(0.0001));
         }
         else static_assert(false, "TODO");
      }

		WHEN("Multiplying the vectors (commutative)") {
         auto tester = [&](T product) {
            T r = product;

            if constexpr (not CT::Normalized<T>) {
               REQUIRE(r == T {0 * 2, 5 * 24, 12 * 4, 1 * 2});
            }
            else if constexpr (C == 4) {
               REQUIRE(r.x == 0);
               REQUIRE(r.y == Approx(0.9284).margin(0.0001));
               REQUIRE(r.z == Approx(0.3713).margin(0.0001));
               REQUIRE(r.w == Approx(0.0155).margin(0.0001));
            }
            else if constexpr (C == 3) {
               REQUIRE(r.x == 0);
               REQUIRE(r.y == Approx(0.9284).margin(0.0001));
               REQUIRE(r.z == Approx(0.3713).margin(0.0001));
            }
            else if constexpr (C == 2) {
               REQUIRE(r.x == 0);
               REQUIRE(r.y == Approx(1));
            }
            else static_assert(false, "TODO");
         };

         tester(x * y);
         tester(y * x);
      }

		WHEN("Dividing the vectors") {
			T r = x / y;

         if constexpr (not CT::Normalized<T>) {
            REQUIRE(r.x == 0);
            if constexpr (C >= 2)
               REQUIRE(r.y == Approx(E(5) / E(24)));
            if constexpr (C >= 3)
               REQUIRE(r.z == Approx(E(12) / E(4)));
            if constexpr (C >= 4)
               REQUIRE(r.w == Approx(E(1) / E(2)));
         }
         else if constexpr (C == 4) {
            REQUIRE(r.x == 0);
            REQUIRE(r.y == Approx(0.0683).margin(0.0001));
            REQUIRE(r.z == Approx(0.9841).margin(0.0001));
            REQUIRE(r.w == Approx(0.1640).margin(0.0001));
         }
         else if constexpr (C == 3) {
            REQUIRE(r.x == 0);
            REQUIRE(r.y == Approx(0.0692).margin(0.0001));
            REQUIRE(r.z == Approx(0.9976).margin(0.0001));
         }
         else if constexpr (C == 2) {
            REQUIRE(r.x == 0);
            REQUIRE(r.y == Approx(1));
         }
         else static_assert(false, "TODO");
		}

		WHEN("Dividing the vectors in reverse order") {
         T r {1, 2, 3, 4};
			REQUIRE_THROWS(r = y / x);
		}
	}

   if constexpr (not CT::Normalized<T>) {
      GIVEN("A preinitialized integer vector") {
         T x {0, 5, 12, 1};

         WHEN("Contained in type-erased container") {
            Many packed = x;

            REQUIRE(packed == x);
         }

         WHEN("Serialized as text") {
            if constexpr (C == 1) {
               const auto serialized = static_cast<Text>(x);
               REQUIRE(serialized == "0");
            }
            else if constexpr (C == 2) {
               const auto serialized = static_cast<Text>(x);
               const auto required = MetaDataOf<T>() + "(0, 5)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 3) {
               const auto serialized = static_cast<Text>(x);
               const auto required = MetaDataOf<T>() + "(0, 5, 12)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 4) {
               const auto serialized = static_cast<Text>(x);
               const auto required = MetaDataOf<T>() + "(0, 5, 12, 1)"_text;
               REQUIRE(serialized == required);
            }
         }

         WHEN("Serialized as code") {
            if constexpr (C == 1) {
               const auto serialized = static_cast<Code>(x);
               REQUIRE(serialized == "0");
            }
            else if constexpr (C == 2) {
               const auto serialized = static_cast<Code>(x);
               const Code required = MetaDataOf<T>() + "(0, 5)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 3) {
               const auto serialized = static_cast<Code>(x);
               const Code required = MetaDataOf<T>() + "(0, 5, 12)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 4) {
               const auto serialized = static_cast<Code>(x);
               const Code required = MetaDataOf<T>() + "(0, 5, 12, 1)"_text;
               REQUIRE(serialized == required);
            }
         }
      }
   }

   if constexpr (CT::Float<E>) {
      GIVEN("A preinitialized float vector") {
         T x {E {0.0f}, E {5.00001f}, E {-12.532f}, E {6666.1f}};

         WHEN("Contained in type-erased container") {
            Many packed = x;

            REQUIRE(packed == x);
         }

         WHEN("Serialized as text") {
            const auto serialized = static_cast<Text>(x);

            if constexpr (C == 1) {
               REQUIRE(serialized == "0");
            }
            else if constexpr (C == 2) {
               if constexpr (CT::Normalized<T>) {
                  const auto required = MetaDataOf<T>() + "(0, 1)"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const auto required = MetaDataOf<T>() + "(0, ~5)"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 3) {
               if constexpr (CT::Normalized<T>) {
                  const auto required = MetaDataOf<T>() + "(0, ~0.37, ~-0.92)"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const auto required = MetaDataOf<T>() + "(0, ~5, ~-12.53)"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 4) {
               if constexpr (CT::Normalized<T>) {
                  const auto required = MetaDataOf<T>() + "(0, ~0, ~-0, ~0.99)"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const auto required = MetaDataOf<T>() + "(0, ~5, ~-12.53, 6666.1)"_text;
                  REQUIRE(serialized == required);
               }
            }
         }

         WHEN("Serialized as code") {
            const auto serialized = static_cast<Code>(x);

            if constexpr (C == 1) {
               REQUIRE(serialized == "0");
            }
            else if constexpr (C == 2) {
               if constexpr (CT::Normalized<T>) {
                  const Code required = MetaDataOf<T>() + "(0, 1)"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const Code required = MetaDataOf<T>() + "(0, 5.00001)"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 3) {
               if constexpr (CT::Normalized<T>) {
                  const Code required = MetaDataOf<T>() + "(0, 0.37057337, -0.9288032)"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const Code required = MetaDataOf<T>() + "(0, 5.00001, -12.532)"_text;
                  REQUIRE(serialized == required);
               }
            }
            else if constexpr (C == 4) {
               if constexpr (CT::Normalized<T>) {
                  const Code required = MetaDataOf<T>() + "(0, 0.0007500637, -0.0018799558, 0.9999979)"_text;
                  REQUIRE(serialized == required);
               }
               else {
                  const Code required = MetaDataOf<T>() + "(0, 5.00001, -12.532, 6666.1)"_text;
                  REQUIRE(serialized == required);
               }
            }
         }
      }
   }

   GIVEN("A scalar descriptor with number literal") {
      const Code descriptor = NameOf<T>() + "(1)"_code;
      REQUIRE(descriptor.Parse() == T {1});
   }

   GIVEN("A component descriptor with number literals") {
      WHEN("Parsing the vector {1, 2, 3, 4}") {
         const Code descriptor = NameOf<T>() + "(1, 2, 3, 4)"_code;
         REQUIRE(descriptor.Parse() == T {1, 2, 3, 4});
      }

      if constexpr (CT::Signed<E>) {
         WHEN("Parsing the vector {0, 0, -1}") {
            const Code descriptor = NameOf<T>() + "(0, 0, -1)"_code;
            REQUIRE(descriptor.Parse() == T {0, 0, -1});
         }
      }
   }

   GIVEN("Nested descriptors") {
      const Code descriptor = NameOf<T>() + "(Vec4(1, 2, 3, 4))"_code;
      REQUIRE(descriptor.Parse() == T {1, 2, 3, 4});
   }

   GIVEN("Descriptors involving CMeta") {
      WHEN("Using Axes::Forward") {
         const Code descriptor = NameOf<T>() + "(Axes::Forward)"_code;
         REQUIRE(descriptor.Parse() == T {Axes::Forward<E>});
      }

      WHEN("Using Axes::Right") {
         const Code descriptor = NameOf<T>() + "(Axes::Right)"_code;
         REQUIRE(descriptor.Parse() == T {Axes::Right<E>});
      }

      if constexpr (CT::Signed<E>) {
         WHEN("Using Axes::Backward") {
            const Code descriptor = NameOf<T>() + "(Axes::Backward)"_code;
            REQUIRE(descriptor.Parse() == T {Axes::Backward<E>});
         }
         WHEN("Using Axes::Left") {
            const Code descriptor = NameOf<T>() + "(Axes::Left)"_code;
            REQUIRE(descriptor.Parse() == T {Axes::Left<E>});
         }
      }
   }
}
