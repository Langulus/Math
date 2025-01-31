///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Math/Color.hpp>
#include "Common.hpp"


TEMPLATE_TEST_CASE("Colors", "[color]",
   RGB24,
   RGBA32,
   RGBA,
   RGB,
   RGB96,
   RGBA128,
   RGBAf,
   RGBf
) {
   using Anyness::Text;
   using Flow::Code;
   using T = TestType;
   using E = TypeOf<T>;
   constexpr auto C = CountOf<T>;

   auto RequireMax = [](const auto& x) {
      if constexpr (T::IsReal)
         REQUIRE(x == 1);
      else
         REQUIRE(x == 255);
   };

   GIVEN("A color") {
      WHEN("Default-initialized") {
         T x;
         RequireMax(x);
      }

      WHEN("Constructing a non-scalar color with missing information (RG)") {
         T x {1, 0};

         if constexpr (T::IsReal)
            REQUIRE(x.x == Approx(E {1} / E {255}));
         else
            REQUIRE(x.x == 1);

         if constexpr (C >= 2)
            REQUIRE(x.y == 0);
         if constexpr (C >= 3)
            REQUIRE(x.z == 0);
         if constexpr (C >= 4)
            RequireMax(x.w);
      }

      WHEN("Constructing a non-scalar color with missing information (RGB)") {
         T x {1, 0, 0};

         if constexpr (T::IsReal)
            REQUIRE(x.x == Approx(E {1} / E {255}));
         else
            REQUIRE(x.x == 1);

         if constexpr (C >= 2)
            REQUIRE(x.y == 0);
         if constexpr (C >= 3)
            REQUIRE(x.z == 0);
         if constexpr (C >= 4)
            RequireMax(x.w);
      }

		WHEN("Assigning a color manually") {
         T x {1, 2, 3, 4};
         x = T {0, 5, 12, 1};

         if constexpr (T::IsReal)
            REQUIRE(x == T {0, 5, 12, 1});
         else
            REQUIRE(x == T {0, 5, 12, 1});
      }

		WHEN("Horizontally adding a color") {
         T x {1, 5, 12, 1};

         if constexpr (T::IsReal) {
            if constexpr (C == 1)
               REQUIRE(x.HSum() == Approx(E {1} / E {255}));
            else if constexpr (C == 2)
               REQUIRE(x.HSum() == Approx(E {1+5} / E {255}));
            else if constexpr (C == 3)
               REQUIRE(x.HSum() == Approx(E {1+5+12} / E {255}));
            else if constexpr (C == 4)
               REQUIRE(x.HSum() == Approx(E {1+5+12+1} / E {255}));
            else
               static_assert(false, "TODO");
         }
         else {
            if constexpr (C == 1)
               REQUIRE(x.HSum() == 1);
            else if constexpr (C == 2)
               REQUIRE(x.HSum() == (1+5));
            else if constexpr (C == 3)
               REQUIRE(x.HSum() == (1+5+12));
            else if constexpr (C == 4)
               REQUIRE(x.HSum() == (1+5+12+1));
            else
               static_assert(false, "TODO");
         }
      }

		WHEN("Horizontally multiplying a color") {
         T x {1, 5, 12, 1};

         if constexpr (T::IsReal) {
            if constexpr (C == 1)
               REQUIRE(x.HMul() == Approx(E {1} / E {255}));
            else if constexpr (C == 2)
               REQUIRE(x.HMul() == Approx(E {1} / E {255} * E {5} / E {255}));
            else if constexpr (C == 3)
               REQUIRE(x.HMul() == Approx(E {1} / E {255} * E {5} / E {255} * E {12} / E {255}));
            else if constexpr (C == 4)
               REQUIRE(x.HMul() == Approx(E {1} / E {255} * E {5} / E {255} * E {12} / E {255} * E {1} / E {255}));
            else
               static_assert(false, "TODO");
         }
         else {
            if constexpr (C == 1)
               REQUIRE(x.HMul() == 1);
            else if constexpr (C == 2)
               REQUIRE(x.HMul() == (1*5));
            else if constexpr (C == 3)
               REQUIRE(x.HMul() == (1*5*12));
            else if constexpr (C == 4)
               REQUIRE(x.HMul() == (1*5*12*1));
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
               if constexpr (T::IsReal) {
                  REQUIRE(cx.xy() == T {E {1} / E {255}, E {5} / E {255}});
                  REQUIRE(cx.yx() == T {E {5} / E {255}, E {1} / E {255}});
               }
               else {
                  REQUIRE(cx.xy() == T {1, 5});
                  REQUIRE(cx.yx() == T {5, 1});
               }
            }
            else if constexpr (C == 3) {
               if constexpr (T::IsReal) {
                  REQUIRE(cx.xy()  == TVector<E, 2> {E { 1} / E {255}, E {5} / E {255}});
                  REQUIRE(cx.yx()  == TVector<E, 2> {E { 5} / E {255}, E {1} / E {255}});
                  REQUIRE(cx.xyz() == TVector<E, 3> {E { 1} / E {255}, E {5} / E {255}, E {12} / E {255}});
                  REQUIRE(cx.yxz() == TVector<E, 3> {E { 5} / E {255}, E {1} / E {255}, E {12} / E {255}});
                  REQUIRE(cx.zyx() == TVector<E, 3> {E {12} / E {255}, E {5} / E {255}, E { 1} / E {255}});
               }
               else {
                  REQUIRE(cx.xy()  == TVector<E, 2> { 1, 5});
                  REQUIRE(cx.yx()  == TVector<E, 2> { 5, 1});
                  REQUIRE(cx.xyz() == TVector<E, 3> { 1, 5, 12});
                  REQUIRE(cx.yxz() == TVector<E, 3> { 5, 1, 12});
                  REQUIRE(cx.zyx() == TVector<E, 3> {12, 5, 1});
               }
            }
            else if constexpr (C == 4) {
               if constexpr (T::IsReal) {
                  REQUIRE(cx.xy()   == TVector<E, 2> {E { 1} / E {255}, E {5} / E {255}});
                  REQUIRE(cx.yx()   == TVector<E, 2> {E { 5} / E {255}, E {1} / E {255}});
                  REQUIRE(cx.xyz()  == TVector<E, 3> {E { 1} / E {255}, E {5} / E {255}, E {12} / E {255}});
                  REQUIRE(cx.yxz()  == TVector<E, 3> {E { 5} / E {255}, E {1} / E {255}, E {12} / E {255}});
                  REQUIRE(cx.zyx()  == TVector<E, 3> {E {12} / E {255}, E {5} / E {255}, E { 1} / E {255}});
                  REQUIRE(cx.xyzw() == TVector<E, 4> {E { 1} / E {255}, E {5} / E {255}, E {12} / E {255}, E {1} / E {255}});
                  REQUIRE(cx.yxzw() == TVector<E, 4> {E { 5} / E {255}, E {1} / E {255}, E {12} / E {255}, E {1} / E {255}});
                  REQUIRE(cx.zyxw() == TVector<E, 4> {E {12} / E {255}, E {5} / E {255}, E { 1} / E {255}, E {1} / E {255}});
                  REQUIRE(cx.wyzx() == TVector<E, 4> {E { 1} / E {255}, E {5} / E {255}, E {12} / E {255}, E {1} / E {255}});
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

	GIVEN("Two colors") {
		T x {0, 5, 12, 1};
      T y {2, 24, 4, 2};

		WHEN("Adding the colors (commutative, saturated)") {
         auto tester = [&](T sum) {
            T r = sum;

            if constexpr (T::IsReal) {
               REQUIRE(r.x    == Approx(E { 0 +  2} / E {255}));
               if constexpr (C == 2)
                  REQUIRE(r.y == Approx(E { 5 + 24} / E {255}));
               if constexpr (C == 3)
                  REQUIRE(r.z == Approx(E {12 +  4} / E {255}));
               if constexpr (C == 4)
                  REQUIRE(r.w == Approx(E { 1 +  2} / E {255}));
            }
            else REQUIRE(r == T {0 + 2, 5 + 24, 12 + 4, 1 + 2});
         };

         tester(x + y);
         tester(y + x);
      }

		WHEN("Subtracting the colors (saturated)") {
			T r = x - y;

         if constexpr (T::IsReal) {
            REQUIRE(r.x == 0);
            if constexpr (C == 2)
               REQUIRE(r.y == 0);
            if constexpr (C == 3)
               REQUIRE(r.z == Approx(E {12 - 4} / E {255}));
            if constexpr (C == 4)
               REQUIRE(r.w == 0);
         }
         else REQUIRE(r == T {0 - 2, 5 - 24, 12 - 4, 1 - 2});
      }

		WHEN("Subtracting the colors in reverse order (saturated)") {
			T r = y - x;

         REQUIRE(r == T {2 - 0, 24 - 5, 4 - 12, 2 - 1});
      }

		WHEN("Multiplying the colors (commutative, saturated)") {
         auto tester = [&](T product) {
            T r = product;

            if constexpr (T::IsReal) {
               REQUIRE(r.x == 0);
               if constexpr (C == 2)
                  REQUIRE(r.y == Approx(E { 5} / E {255} * E {24} / E {255}));
               if constexpr (C == 3)
                  REQUIRE(r.z == Approx(E {12} / E {255} * E { 4} / E {255}));
               if constexpr (C == 4)
                  REQUIRE(r.w == Approx(E { 1} / E {255} * E { 2} / E {255}));
            }
            else REQUIRE(r == T {0 * 2, 5 * 24, 12 * 4, 1 * 2});
         };

         tester(x * y);
         tester(y * x);
      }

		WHEN("Dividing the colors") {
			T r = x / y;

         REQUIRE(r.x == 0);
         if constexpr (C >= 2)
            REQUIRE(r.y == Approx(E( 5) / E(24)));
         if constexpr (C >= 3)
            REQUIRE(r.z == Approx(E(12) / E( 4)));
         if constexpr (C >= 4)
            REQUIRE(r.w == Approx(E( 1) / E( 2)));
		}

		WHEN("Dividing the colors in reverse order") {
         T r {1, 2, 3, 4};
			REQUIRE_THROWS(r = y / x);
		}
	}

   GIVEN("A preinitialized integer color") {
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
            const auto required = MetaDataOf<T>() + (T::IsReal ? "(0, ~0.02)"_text : "(0, 5)"_text);
            REQUIRE(serialized == required);
         }
         else if constexpr (C == 3) {
            const auto serialized = static_cast<Text>(x);
            const auto required = MetaDataOf<T>() + (T::IsReal ? "(0, ~0.02, ~0.05)"_text : "(0, 5, 12)"_text);
            REQUIRE(serialized == required);
         }
         else if constexpr (C == 4) {
            const auto serialized = static_cast<Text>(x);
            const auto required = MetaDataOf<T>() + (T::IsReal ? "(0, ~0.02, ~0.05, ~0)"_text : "(0, 5, 12, 1)"_text);
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
            const Code required = MetaDataOf<T>() + (T::IsReal ? "(0, 0.019607844)"_text : "(0, 5)"_text);
            REQUIRE(serialized == required);
         }
         else if constexpr (C == 3) {
            const auto serialized = static_cast<Code>(x);
            const Code required = MetaDataOf<T>() + (T::IsReal ? "(0, 0.019607844, 0.047058824)"_text : "(0, 5, 12)"_text);
            REQUIRE(serialized == required);
         }
         else if constexpr (C == 4) {
            const auto serialized = static_cast<Code>(x);
            const Code required = MetaDataOf<T>() + (T::IsReal ? "(0, 0.019607844, 0.047058824, 0.003921569)"_text : "(0, 5, 12, 1)"_text);
            REQUIRE(serialized == required);
         }
      }
   }

   if constexpr (CT::Float<E>) {
      GIVEN("A preinitialized float color") {
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
               const auto required = MetaDataOf<T>() + "(0, ~5)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 3) {
               const auto required = MetaDataOf<T>() + "(0, ~5, 0)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 4) {
               const auto required = MetaDataOf<T>() + "(0, ~5, 0, 6666.1)"_text;
               REQUIRE(serialized == required);
            }
         }

         WHEN("Serialized as code") {
            const auto serialized = static_cast<Code>(x);

            if constexpr (C == 1) {
               REQUIRE(serialized == "0");
            }
            else if constexpr (C == 2) {
               const Code required = MetaDataOf<T>() + "(0, 5.00001)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 3) {
               const Code required = MetaDataOf<T>() + "(0, 5.00001, 0)"_text;
               REQUIRE(serialized == required);
            }
            else if constexpr (C == 4) {
               const Code required = MetaDataOf<T>() + "(0, 5.00001, 0, 6666.1)"_text;
               REQUIRE(serialized == required);
            }
         }
      }
   }

   GIVEN("A scalar descriptor with number literal") {
      const Code descriptor = NameOf<T>() + "(1)"_code;
      if constexpr (T::IsReal)
         REQUIRE(descriptor.Parse() == T {E {1}});
      else
         REQUIRE(descriptor.Parse() == T {255});
   }

   GIVEN("A component descriptor with number literals") {
      WHEN("Parsing the vector {1, 2, 3, 4}") {
         const Code descriptor = NameOf<T>() + "(1, 2, 3, 4)"_code;
         if constexpr (T::IsReal)
            REQUIRE(descriptor.Parse() == T {E {1}});
         else
            REQUIRE(descriptor.Parse() == T {255});
      }
   }

   GIVEN("Nested descriptors") {
      const Code descriptor = NameOf<T>() + "(Vec4(1, 2, 3, 4))"_code;
      if constexpr (T::IsReal)
         REQUIRE(descriptor.Parse() == T {E {1}});
      else
         REQUIRE(descriptor.Parse() == T {255});
   }

   GIVEN("Descriptors involving CMeta") {
      WHEN("Using Colors::Red") {
         const Code descriptor = NameOf<T>() + "(Colors::Red)"_code;
         REQUIRE(descriptor.Parse() == T {Colors::Red});
      }

      WHEN("Using Colors::Green") {
         const Code descriptor = NameOf<T>() + "(Colors::Green)"_code;
         REQUIRE(descriptor.Parse() == T {Colors::Green});
      }

      WHEN("Using Colors::Blue") {
         const Code descriptor = NameOf<T>() + "(Colors::Blue)"_code;
         REQUIRE(descriptor.Parse() == T {Colors::Blue});
      }
   }
}
