///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Math/Vectors.hpp>
#include <Math/Colors.hpp>
#include <catch2/catch.hpp>

LANGULUS_EXCEPTION_HANDLER

SCENARIO("Testing vector names", "[rtti]") {
   GIVEN("All vector types") {
      THEN("The names should match") {
         REQUIRE(NameOf<Vec1>()                 == "Vec1");
         if constexpr (!CT::Same<float, Real>)
            REQUIRE(NameOf<Vec1f>()             == "Vec1f");
         if constexpr (!CT::Same<double, Real>)
            REQUIRE(NameOf<Vec1d>()             == "Vec1d");
         REQUIRE(NameOf<Vec1i>()                == "Vec1i");
         REQUIRE(NameOf<Vec1u>()                == "Vec1u");
         REQUIRE(NameOf<Vec1i8>()               == "Vec1i8");
         REQUIRE(NameOf<Vec1u8>()               == "Vec1u8");
         REQUIRE(NameOf<Vec1i16>()              == "Vec1i16");
         REQUIRE(NameOf<Vec1u16>()              == "Vec1u16");
         if constexpr (!CT::Same<signed, ::std::int32_t>)
            REQUIRE(NameOf<Vec1i32>()           == "Vec1i32");
         if constexpr (!CT::Same<unsigned, ::std::uint32_t>)
            REQUIRE(NameOf<Vec1u32>()           == "Vec1u32");
         REQUIRE(NameOf<Vec1i64>()              == "Vec1i64");
         REQUIRE(NameOf<Vec1u64>()              == "Vec1u64");

         REQUIRE(NameOf<Vec2>()                 == "Vec2");
         if constexpr (!CT::Same<float, Real>)
            REQUIRE(NameOf<Vec2f>()             == "Vec2f");
         if constexpr (!CT::Same<double, Real>)
            REQUIRE(NameOf<Vec2d>()             == "Vec2d");
         REQUIRE(NameOf<Vec2i>()                == "Vec2i");
         REQUIRE(NameOf<Vec2u>()                == "Vec2u");
         REQUIRE(NameOf<Vec2i8>()               == "Vec2i8");
         REQUIRE(NameOf<Vec2u8>()               == "Vec2u8");
         REQUIRE(NameOf<Vec2i16>()              == "Vec2i16");
         REQUIRE(NameOf<Vec2u16>()              == "Vec2u16");
         if constexpr (!CT::Same<signed, ::std::int32_t>)
            REQUIRE(NameOf<Vec2i32>()           == "Vec2i32");
         if constexpr (!CT::Same<unsigned, ::std::uint32_t>)
            REQUIRE(NameOf<Vec2u32>()           == "Vec2u32");
         REQUIRE(NameOf<Vec2i64>()              == "Vec2i64");
         REQUIRE(NameOf<Vec2u64>()              == "Vec2u64");
         
         REQUIRE(NameOf<Vec3>()                 == "Vec3");
         if constexpr (!CT::Same<float, Real>)
            REQUIRE(NameOf<Vec3f>()             == "Vec3f");
         if constexpr (!CT::Same<double, Real>)
            REQUIRE(NameOf<Vec3d>()             == "Vec3d");
         REQUIRE(NameOf<Vec3i>()                == "Vec3i");
         REQUIRE(NameOf<Vec3u>()                == "Vec3u");
         REQUIRE(NameOf<Vec3i8>()               == "Vec3i8");
         REQUIRE(NameOf<Vec3u8>()               == "Vec3u8");
         REQUIRE(NameOf<Vec3i16>()              == "Vec3i16");
         REQUIRE(NameOf<Vec3u16>()              == "Vec3u16");
         if constexpr (!CT::Same<signed, ::std::int32_t>)
            REQUIRE(NameOf<Vec3i32>()           == "Vec3i32");
         if constexpr (!CT::Same<unsigned, ::std::uint32_t>)
            REQUIRE(NameOf<Vec3u32>()           == "Vec3u32");
         REQUIRE(NameOf<Vec3i64>()              == "Vec3i64");
         REQUIRE(NameOf<Vec3u64>()              == "Vec3u64");

         REQUIRE(NameOf<Vec4>()                 == "Vec4");
         if constexpr (!CT::Same<float, Real>)
            REQUIRE(NameOf<Vec4f>()             == "Vec4f");
         if constexpr (!CT::Same<double, Real>)
            REQUIRE(NameOf<Vec4d>()             == "Vec4d");
         REQUIRE(NameOf<Vec4i>()                == "Vec4i");
         REQUIRE(NameOf<Vec4u>()                == "Vec4u");
         REQUIRE(NameOf<Vec4i8>()               == "Vec4i8");
         REQUIRE(NameOf<Vec4u8>()               == "Vec4u8");
         REQUIRE(NameOf<Vec4i16>()              == "Vec4i16");
         REQUIRE(NameOf<Vec4u16>()              == "Vec4u16");
         if constexpr (!CT::Same<signed, ::std::int32_t>)
            REQUIRE(NameOf<Vec4i32>()           == "Vec4i32");
         if constexpr (!CT::Same<unsigned, ::std::uint32_t>)
            REQUIRE(NameOf<Vec4u32>()           == "Vec4u32");
         REQUIRE(NameOf<Vec4i64>()              == "Vec4i64");
         REQUIRE(NameOf<Vec4u64>()              == "Vec4u64");
      }
   }

   GIVEN("All color types") {
      THEN("The names should match") {
         REQUIRE(NameOf<TColor<Vec2f>>()        == "Grayscalef");
         REQUIRE(NameOf<TColor<Vec2d>>()        == "Grayscaled");
         REQUIRE(NameOf<TColor<Vec2i>>()        == "Grayscalei");
         REQUIRE(NameOf<TColor<Vec2u>>()        == "Grayscaleu");
         REQUIRE(NameOf<TColor<Vec2i8>>()       == "Grayscalei8");
         REQUIRE(NameOf<TColor<Vec2u8>>()       == "Grayscale");
         REQUIRE(NameOf<TColor<Vec2i16>>()      == "Grayscalei16");
         REQUIRE(NameOf<TColor<Vec2u16>>()      == "Grayscaleu16");
         if constexpr (!CT::Same<signed, ::std::int32_t>)
            REQUIRE(NameOf<TColor<Vec2i32>>()   == "Grayscalei32");
         if constexpr (!CT::Same<unsigned, ::std::uint32_t>)
            REQUIRE(NameOf<TColor<Vec2u32>>()   == "Grayscaleu32");
         REQUIRE(NameOf<TColor<Vec2i64>>()      == "Grayscalei64");
         REQUIRE(NameOf<TColor<Vec2u64>>()      == "Grayscaleu64");

         REQUIRE(NameOf<TColor<Vec3f>>()        == "RGBf");
         REQUIRE(NameOf<TColor<Vec3d>>()        == "RGBd");
         REQUIRE(NameOf<TColor<Vec3i>>()        == "RGBi");
         REQUIRE(NameOf<TColor<Vec3u>>()        == "RGBu");
         REQUIRE(NameOf<TColor<Vec3i8>>()       == "RGBi8");
         REQUIRE(NameOf<TColor<Vec3u8>>()       == "RGB");
         REQUIRE(NameOf<TColor<Vec3i16>>()      == "RGBi16");
         REQUIRE(NameOf<TColor<Vec3u16>>()      == "RGBu16");
         if constexpr (!CT::Same<signed, ::std::int32_t>)
            REQUIRE(NameOf<TColor<Vec3i32>>()   == "RGBi32");
         if constexpr (!CT::Same<unsigned, ::std::uint32_t>)
            REQUIRE(NameOf<TColor<Vec3u32>>()   == "RGBu32");
         REQUIRE(NameOf<TColor<Vec3i64>>()      == "RGBi64");
         REQUIRE(NameOf<TColor<Vec3u64>>()      == "RGBu64");

         REQUIRE(NameOf<TColor<Vec4f>>()        == "RGBAf");
         REQUIRE(NameOf<TColor<Vec4d>>()        == "RGBAd");
         REQUIRE(NameOf<TColor<Vec4i>>()        == "RGBAi");
         REQUIRE(NameOf<TColor<Vec4u>>()        == "RGBAu");
         REQUIRE(NameOf<TColor<Vec4i8>>()       == "RGBAi8");
         REQUIRE(NameOf<TColor<Vec4u8>>()       == "RGBA");
         REQUIRE(NameOf<TColor<Vec4i16>>()      == "RGBAi16");
         REQUIRE(NameOf<TColor<Vec4u16>>()      == "RGBAu16");
         if constexpr (!CT::Same<signed, ::std::int32_t>)
            REQUIRE(NameOf<TColor<Vec4i32>>()   == "RGBAi32");
         if constexpr (!CT::Same<unsigned, ::std::uint32_t>)
            REQUIRE(NameOf<TColor<Vec4u32>>()   == "RGBAu32");
         REQUIRE(NameOf<TColor<Vec4i64>>()      == "RGBAi64");
         REQUIRE(NameOf<TColor<Vec4u64>>()      == "RGBAu64");
      }
   }
}
