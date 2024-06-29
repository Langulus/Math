///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Functions/Trigonometry.hpp"
#include "../Functions/Arithmetics.hpp"
#include "../Numbers/TNumber.hpp"
#include "../Dimensions.hpp"
#include <SIMD/SIMD.hpp>
#include <Core/Sequences.hpp>

#define TARGS(a)     CT::ScalarBased a##T, Count a##S, int a##D
#define TVEC(a)      TVector<a##T, a##S, a##D>
#define TEMPLATE()   template<CT::ScalarBased T, Count S, int DEFAULT>
#define TME()        TVector<T, S, DEFAULT>


namespace Langulus::Math
{

   LANGULUS_API(MATH) extern void RegisterVectors();

   template<CT::ScalarBased T, CT::Dimension D>
   struct TVectorComponent;

   template<CT::ScalarBased T, Count S, int DEFAULT = 0>
   struct TVector;

   template<CT::ScalarBased T, Count S, int DEFAULT = 0>
   using TVec = TME();

   using Vec1     = TVector<Real, 1>;
   using Vec1f    = TVector<Float, 1>;
   using Vec1d    = TVector<Double, 1>;
   using Vec1i    = TVector<signed, 1>;
   using Vec1u    = TVector<unsigned, 1>;
   using Vec1i8   = TVector<::std::int8_t, 1>;
   using Vec1u8   = TVector<::std::uint8_t, 1>;
   using Vec1i16  = TVector<::std::int16_t, 1>;
   using Vec1u16  = TVector<::std::uint16_t, 1>;
   using Vec1i32  = TVector<::std::int32_t, 1>;
   using Vec1u32  = TVector<::std::uint32_t, 1>;
   using Vec1i64  = TVector<::std::int64_t, 1>;
   using Vec1u64  = TVector<::std::uint64_t, 1>;

   using Vec2     = TVector<Real, 2>;
   using Vec2f    = TVector<Float, 2>;
   using Vec2d    = TVector<Double, 2>;
   using Vec2i    = TVector<signed, 2>;
   using Vec2u    = TVector<unsigned, 2>;
   using Vec2i8   = TVector<::std::int8_t, 2>;
   using Vec2u8   = TVector<::std::uint8_t, 2>;
   using Vec2i16  = TVector<::std::int16_t, 2>;
   using Vec2u16  = TVector<::std::uint16_t, 2>;
   using Vec2i32  = TVector<::std::int32_t, 2>;
   using Vec2u32  = TVector<::std::uint32_t, 2>;
   using Vec2i64  = TVector<::std::int64_t, 2>;
   using Vec2u64  = TVector<::std::uint64_t, 2>;

   using Vec3     = TVector<Real, 3>;
   using Vec3f    = TVector<Float, 3>;
   using Vec3d    = TVector<Double, 3>;
   using Vec3i    = TVector<signed, 3>;
   using Vec3u    = TVector<unsigned, 3>;
   using Vec3i8   = TVector<::std::int8_t, 3>;
   using Vec3u8   = TVector<::std::uint8_t, 3>;
   using Vec3i16  = TVector<::std::int16_t, 3>;
   using Vec3u16  = TVector<::std::uint16_t, 3>;
   using Vec3i32  = TVector<::std::int32_t, 3>;
   using Vec3u32  = TVector<::std::uint32_t, 3>;
   using Vec3i64  = TVector<::std::int64_t, 3>;
   using Vec3u64  = TVector<::std::uint64_t, 3>;

   using Vec4     = TVector<Real, 4>;
   using Vec4f    = TVector<Float, 4>;
   using Vec4d    = TVector<Double, 4>;
   using Vec4i    = TVector<signed, 4>;
   using Vec4u    = TVector<unsigned, 4>;
   using Vec4i8   = TVector<::std::int8_t, 4>;
   using Vec4u8   = TVector<::std::uint8_t, 4>;
   using Vec4i16  = TVector<::std::int16_t, 4>;
   using Vec4u16  = TVector<::std::uint16_t, 4>;
   using Vec4i32  = TVector<::std::int32_t, 4>;
   using Vec4u32  = TVector<::std::uint32_t, 4>;
   using Vec4i64  = TVector<::std::int64_t, 4>;
   using Vec4u64  = TVector<::std::uint64_t, 4>;
   
   using Vec      = Vec4;
   using Vecf     = Vec4f;
   using Vecd     = Vec4d;
   using Veci     = Vec4i;
   using Vecu     = Vec4u;
   using Veci8    = Vec4i8;
   using Vecu8    = Vec4u8;
   using Veci16   = Vec4i16;
   using Vecu16   = Vec4u16;
   using Veci32   = Vec4i32;
   using Vecu32   = Vec4u32;
   using Veci64   = Vec4i64;
   using Vecu64   = Vec4u64;

} // namespace Langulus::Math

namespace Langulus
{
   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// vector                                                              
      struct Vector {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Vec4;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// vector of the same size                                             
      template<Count S>
      struct VectorOfSize : Vector {
         LANGULUS(CONCRETE) Math::TVector<::Langulus::Real, S>;
         LANGULUS_BASES(Vector);
         static constexpr Count MemberCount {S};
         static_assert(S > 0, "Vector size must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// vector of the same type                                             
      template<CT::ScalarBased T>
      struct VectorOfType : Vector {
         LANGULUS(CONCRETE) Math::TVector<T, 4>;
         LANGULUS(TYPED) T;
         LANGULUS_BASES(Vector);
      };

      using Point = Vector;

   } // namespace Langulus::A


   /// Custom name generator at compile-time for vectors                      
   TEMPLATE()
   consteval auto CustomName(Of<Math::TME()>&&) noexcept {
      constexpr auto defaultClassName = RTTI::LastCppNameOf<Math::TME()>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      if constexpr (S > 4) {
         for (auto i : defaultClassName)
            name[offset++] = i;
         return name;
      }

      // Write prefix                                                   
      for (auto i : "Vec")
         name[offset++] = i;

      // Write size                                                     
      --offset;
      name[offset++] = '0' + S;

      // Write suffix                                                   
      for (auto i : SuffixOf<T>())
         name[offset++] = i;

      return name;
   }

} // namespace Langulus

namespace Langulus::Math
{

   #pragma pack(push, 1)
   template<Count, CT::ScalarBased>
   struct TVectorBase;


   ///                                                                        
   /// 1D vector base                                                         
   template<CT::ScalarBased TYPE>
   struct TVectorBase<1, TYPE> {
      union {
         TYPE all[1] {};
         union { RTTI::Tag<TYPE, Traits::X, Traits::R, Traits::U> x, first, r, red, u; };
      };

      // Declare the rest as functions, so that they don't take up space
      // This is necessary to work around the dependent names in TVector
      // This will also error out, when missing (), but if you happen to
      // call them by accident, you will get a proper compile error     
      void y()       { LANGULUS_ERROR("1D vector doesn't have 'y' component"); }
      void second()  { LANGULUS_ERROR("1D vector doesn't have 'second' component"); }
      void g()       { LANGULUS_ERROR("1D vector doesn't have 'g' component"); }
      void green()   { LANGULUS_ERROR("1D vector doesn't have 'green' component"); }
      void v()       { LANGULUS_ERROR("1D vector doesn't have 'v' component"); }

      void z()       { LANGULUS_ERROR("1D vector doesn't have 'z' component"); }
      void third()   { LANGULUS_ERROR("1D vector doesn't have 'third' component"); }
      void b()       { LANGULUS_ERROR("1D vector doesn't have 'b' component"); }
      void blue()    { LANGULUS_ERROR("1D vector doesn't have 'blue' component"); }
      void s()       { LANGULUS_ERROR("1D vector doesn't have 's' component"); }

      void w()       { LANGULUS_ERROR("1D vector doesn't have 'w' component"); }
      void fourth()  { LANGULUS_ERROR("1D vector doesn't have 'fourth' component"); }
      void a()       { LANGULUS_ERROR("1D vector doesn't have 'a' component"); }
      void alpha()   { LANGULUS_ERROR("1D vector doesn't have 'alpha' component"); }
      void t()       { LANGULUS_ERROR("1D vector doesn't have 't' component"); }

      void tail()    { LANGULUS_ERROR("1D vector doesn't have a tail"); }

      LANGULUS_MEMBERS(&TVectorBase::x);

      constexpr TVectorBase() noexcept = default;

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         all[0] = other.all[0];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         all[0] = other.all[0];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };


   ///                                                                        
   /// 2D vector base                                                         
   template<CT::ScalarBased TYPE>
   struct TVectorBase<2, TYPE> {
      union {
         TYPE all[2] {};
         struct {
            union { RTTI::Tag<TYPE, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<TYPE, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
         };
      };

      // Declare the rest as functions, so that they don't take up space
      // This is necessary to work around the dependent names in TVector
      // This will also error out, when missing (), but if you happen to
      // call them by accident, you will get a proper compile error     
      void z()       { LANGULUS_ERROR("2D vector doesn't have 'z' component"); }
      void third()   { LANGULUS_ERROR("2D vector doesn't have 'third' component"); }
      void b()       { LANGULUS_ERROR("2D vector doesn't have 'b' component"); }
      void blue()    { LANGULUS_ERROR("2D vector doesn't have 'blue' component"); }
      void s()       { LANGULUS_ERROR("2D vector doesn't have 's' component"); }

      void w()       { LANGULUS_ERROR("2D vector doesn't have 'w' component"); }
      void fourth()  { LANGULUS_ERROR("2D vector doesn't have 'fourth' component"); }
      void a()       { LANGULUS_ERROR("2D vector doesn't have 'a' component"); }
      void alpha()   { LANGULUS_ERROR("2D vector doesn't have 'alpha' component"); }
      void t()       { LANGULUS_ERROR("2D vector doesn't have 't' component"); }

      void tail()    { LANGULUS_ERROR("2D vector doesn't have a tail"); }

      LANGULUS_MEMBERS(&TVectorBase::x, &TVectorBase::y);

      constexpr TVectorBase() noexcept = default;

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (int i = 0; i < 2; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (int i = 0; i < 2; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };


   ///                                                                        
   /// 3D vector base                                                         
   template<CT::ScalarBased TYPE>
   struct TVectorBase<3, TYPE> {
      union {
         TYPE all[3] {};
         struct {
            union { RTTI::Tag<TYPE, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<TYPE, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
            union { RTTI::Tag<TYPE, Traits::Z, Traits::B, Traits::S> z, third,  b, blue,  s; };
         };
      };

      // Declare the rest as functions, so that they don't take up space
      // This is necessary to work around the dependent names in TVector
      // This will also error out, when missing (), but if you happen to
      // call them by accident, you will get a proper compile error     
      void w()       { LANGULUS_ERROR("3D vector doesn't have 'w' component"); }
      void fourth()  { LANGULUS_ERROR("3D vector doesn't have 'fourth' component"); }
      void a()       { LANGULUS_ERROR("3D vector doesn't have 'a' component"); }
      void alpha()   { LANGULUS_ERROR("3D vector doesn't have 'alpha' component"); }
      void t()       { LANGULUS_ERROR("3D vector doesn't have 't' component"); }

      void tail()    { LANGULUS_ERROR("3D vector doesn't have a tail"); }

      LANGULUS_MEMBERS(&TVectorBase::x, &TVectorBase::y, &TVectorBase::z);

      constexpr TVectorBase() noexcept = default;

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (int i = 0; i < 3; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (int i = 0; i < 3; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };


   ///                                                                        
   /// 4D vector base                                                         
   template<CT::ScalarBased TYPE>
   struct TVectorBase<4, TYPE> {
      union {
         TYPE all[4] {};
         struct {
            union { RTTI::Tag<TYPE, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<TYPE, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
            union { RTTI::Tag<TYPE, Traits::Z, Traits::B, Traits::S> z, third,  b, blue,  s; };
            union { RTTI::Tag<TYPE, Traits::W, Traits::A, Traits::T> w, fourth, a, alpha, t; };
         };
      };

      void tail()    { LANGULUS_ERROR("4D vector doesn't have a tail"); }

      LANGULUS_MEMBERS(&TVectorBase::x, &TVectorBase::y, &TVectorBase::z, &TVectorBase::w);

      constexpr TVectorBase() noexcept = default;

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (int i = 0; i < 4; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (int i = 0; i < 4; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };


   ///                                                                        
   /// 5+D vector base                                                        
   template<Count S, CT::ScalarBased TYPE> requires (S > 4)
   struct TVectorBase<S, TYPE> {
      union {
         TYPE all[S] {};
         struct {
            union { RTTI::Tag<TYPE, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<TYPE, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
            union { RTTI::Tag<TYPE, Traits::Z, Traits::B, Traits::S> z, third,  b, blue,  s; };
            union { RTTI::Tag<TYPE, Traits::W, Traits::A, Traits::T> w, fourth, a, alpha, t; };

            // The remaining elements, that don't have custom names     
            TYPE tail[S - 4];
         };
      };

      LANGULUS_MEMBERS(&TVectorBase::x, &TVectorBase::y, &TVectorBase::z, &TVectorBase::w);

      constexpr TVectorBase() noexcept = default;

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (int i = 0; i < S; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (int i = 0; i < S; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };


   ///                                                                        
   ///   Templated vector                                                     
   ///                                                                        
   ///   This is a multipurpose vector that is used in numerous places, such  
   /// as: primitives, colors, forces, scalers, normals, samplers, etc...     
   ///   This vector template is designed to be mostly similar to GLSL        
   /// vectors. When swizzling, the template returns a similar vector with T  
   /// being a pointer (a so called proxy vector), in order to implement      
   /// swizzling. Proxy vectors eventually decay into conventional vectors.   
   ///                                                                        
   TEMPLATE()
   struct TVector : TVectorBase<S, T> {
      static_assert(S >= 1, "Can't have a vector of zero size");
      static constexpr Count MemberCount = S;
      static constexpr T Default = static_cast<T>(DEFAULT);
      using ArrayType = T[S];
      using Base = TVectorBase<S, T>;

      LANGULUS(NAME) CustomNameOf<TVector>::Generate();
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) DEFAULT == 0;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(
         A::VectorOfSize<S>, 
         A::VectorOfType<T>,
         Base, T
      );
      LANGULUS_CONVERTS_TO(Anyness::Text, Flow::Code);

      // Make TVector match the CT::VectorBased concept                 
      static constexpr bool CTTI_VectorTrait = true;

   public:
      ///                                                                     
      ///   Construction                                                      
      ///                                                                     
      constexpr TVector() noexcept;
      constexpr TVector(const CT::Vector auto&) noexcept;
      constexpr TVector(const CT::Scalar auto&) noexcept;

      template<class T1, class T2, class...TN>
      constexpr TVector(const T1&, const T2&, const TN&...) noexcept;

      template<CT::ScalarBased N, CT::Dimension D>
      constexpr TVector(const TVectorComponent<N, D>&) noexcept;

      TVector(const CT::SIMD auto&)  noexcept;
      TVector(Describe&&);

      ///                                                                     
      ///   Assignment                                                        
      ///                                                                     
      constexpr auto operator = (const CT::Vector auto&) noexcept -> TVector&;
      constexpr auto operator = (const CT::Scalar auto&) noexcept -> TVector&;

      template<CT::ScalarBased N, CT::Dimension D>
      constexpr auto operator = (const TVectorComponent<N, D>&) noexcept -> TVector&;

      ///                                                                     
      ///   Interpretation                                                    
      ///                                                                     
      template<CT::Serial AS, class TOKEN>
      AS Serialize() const;

      NOD() explicit operator Anyness::Text() const;
      NOD() explicit operator Flow::Code() const;

      NOD() static constexpr decltype(auto) Adapt(const CT::ScalarBased auto&) noexcept;

      ///                                                                     
      ///   Access                                                            
      ///                                                                     
      using TVectorBase<S, T>::x;
      using TVectorBase<S, T>::first;
      using TVectorBase<S, T>::r;
      using TVectorBase<S, T>::red;
      using TVectorBase<S, T>::u;

      using TVectorBase<S, T>::y;
      using TVectorBase<S, T>::second;
      using TVectorBase<S, T>::g;
      using TVectorBase<S, T>::green;
      using TVectorBase<S, T>::v;

      using TVectorBase<S, T>::z;
      using TVectorBase<S, T>::third;
      using TVectorBase<S, T>::b;
      using TVectorBase<S, T>::blue;
      using TVectorBase<S, T>::s;

      using TVectorBase<S, T>::w;
      using TVectorBase<S, T>::fourth;
      using TVectorBase<S, T>::a;
      using TVectorBase<S, T>::alpha;
      using TVectorBase<S, T>::t;

      using TVectorBase<S, T>::all;

      NOD() constexpr auto Get(Offset) const noexcept -> const T&;
      NOD() constexpr auto Get(Offset)       noexcept ->       T&;

      template<Offset I>
      NOD() constexpr auto GetIdx() const noexcept -> const T&;

      NOD() constexpr auto operator [] (Offset)       noexcept ->       T&;
      NOD() constexpr auto operator [] (Offset) const noexcept -> const T&;

      NOD() constexpr auto GetCount() const noexcept -> Count;
      NOD() constexpr auto LengthSquared() const noexcept -> T;
      NOD() constexpr auto Length() const noexcept -> T;
      NOD() constexpr bool IsDegenerate() const noexcept;

      template<Offset HEAD, Offset...TAIL>
      NOD()           decltype(auto) Swz()       noexcept;
      template<Offset HEAD, Offset...TAIL>
      NOD() constexpr decltype(auto) Swz() const noexcept;

      template<Offset...I>
      static constexpr bool SwzRequirements = ((S > I) and ...);

      /// Generate all combinations of all swizzle functions up to 4D         
      #define LANGULUS_TVECTOR_SWIZZLER(name, ...) \
         NOD() LANGULUS(INLINED) decltype(auto) name() noexcept \
         requires (SwzRequirements<__VA_ARGS__>) { \
            return Swz<__VA_ARGS__>(); \
         } \
         NOD() LANGULUS(INLINED) decltype(auto) name() const noexcept \
         requires (SwzRequirements<__VA_ARGS__>) { \
            return Swz<__VA_ARGS__>(); \
         }

      /// 2D Swizzlers                                                        
      #define LANGULUS_TVECTOR_SWIZZLER2(name, ...) \
         LANGULUS_TVECTOR_SWIZZLER(x##name, 0U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER(y##name, 1U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER(z##name, 2U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER(w##name, 3U, __VA_ARGS__)

      LANGULUS_TVECTOR_SWIZZLER2(x, 0U)
      LANGULUS_TVECTOR_SWIZZLER2(y, 1U)
      LANGULUS_TVECTOR_SWIZZLER2(z, 2U)
      LANGULUS_TVECTOR_SWIZZLER2(w, 3U)

      /// 3D Swizzlers                                                        
      #define LANGULUS_TVECTOR_SWIZZLER3(name, ...) \
         LANGULUS_TVECTOR_SWIZZLER2(x##name, 0U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER2(y##name, 1U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER2(z##name, 2U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER2(w##name, 3U, __VA_ARGS__)

      LANGULUS_TVECTOR_SWIZZLER3(x, 0U)
      LANGULUS_TVECTOR_SWIZZLER3(y, 1U)
      LANGULUS_TVECTOR_SWIZZLER3(z, 2U)
      LANGULUS_TVECTOR_SWIZZLER3(w, 3U)

      /// 4D Swizzlers                                                        
      #define LANGULUS_TVECTOR_SWIZZLER4(name, ...) \
         LANGULUS_TVECTOR_SWIZZLER3(x##name, 0U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER3(y##name, 1U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER3(z##name, 2U, __VA_ARGS__)\
         LANGULUS_TVECTOR_SWIZZLER3(w##name, 3U, __VA_ARGS__)

      LANGULUS_TVECTOR_SWIZZLER4(x, 0U)
      LANGULUS_TVECTOR_SWIZZLER4(y, 1U)
      LANGULUS_TVECTOR_SWIZZLER4(z, 2U)
      LANGULUS_TVECTOR_SWIZZLER4(w, 3U)

      #undef LANGULUS_TVECTOR_SWIZZLER
      #undef LANGULUS_TVECTOR_SWIZZLER2
      #undef LANGULUS_TVECTOR_SWIZZLER3
      #undef LANGULUS_TVECTOR_SWIZZLER4

      template<class AS, bool NORMALIZE = CT::Real<AS> and not CT::Real<T>>
      NOD() constexpr auto AsCast() const noexcept -> TVector<AS, S>;

      template<Count = Math::Min(S, 3u)>
      NOD() constexpr auto Volume() const noexcept;

      NOD() constexpr auto Dot(const CT::VectorBased auto&) const noexcept -> T;

      template<CT::VectorBased V> requires (S >= 3 and CountOf<V> >= 3)
      NOD() constexpr auto Cross(const V&) const noexcept -> TVector<T, 3>;

      NOD() constexpr auto Normalize() const -> TVector requires (S > 1);

      NOD() constexpr auto Clamp   (const auto&, const auto&) const noexcept -> TVector;
      NOD() constexpr auto ClampRev(const auto&, const auto&) const noexcept -> TVector;

      NOD() constexpr auto Round() const noexcept -> TVector;
      NOD() constexpr auto Floor() const noexcept -> TVector;
      NOD() constexpr auto Ceil () const noexcept -> TVector;
      NOD() constexpr auto Abs  () const noexcept -> TVector;
      NOD() constexpr auto Sign () const noexcept -> TVector;
      NOD() constexpr auto Frac () const noexcept -> TVector;
      NOD() constexpr auto Sqrt () const noexcept -> TVector;
      NOD() constexpr auto Exp  () const noexcept -> TVector;
      NOD() constexpr auto Sin  () const noexcept -> TVector;
      NOD() constexpr auto Cos  () const noexcept -> TVector;
      NOD() constexpr auto Warp(const T&) const noexcept -> TVector;

      NOD() static constexpr auto Max() noexcept -> TVector;
      NOD() static constexpr auto Min() noexcept -> TVector;

      NOD() constexpr auto Max(const auto&) const noexcept;
      NOD() constexpr auto Min(const auto&) const noexcept;

      NOD() constexpr auto HMax() const noexcept -> T;
      NOD() constexpr auto HMin() const noexcept -> T;
      NOD() constexpr auto HSum() const noexcept -> T;
      NOD() constexpr auto HMul() const noexcept -> T;

      NOD() constexpr auto Mod (const auto&) const noexcept -> TVector;
      NOD() constexpr auto Step(const auto&) const noexcept -> TVector;
      NOD() constexpr auto Pow (const auto&) const noexcept -> TVector;

      auto& Sort() noexcept;

      NOD() constexpr explicit operator T&   () const noexcept requires (S == 1);
      NOD() constexpr explicit operator bool () const noexcept;

      template<CT::ScalarBased N> requires (S == 1 and CT::Convertible<N, T>)
      NOD() explicit constexpr operator N () const noexcept;
      
      template<Count ALTS> requires (ALTS < S)
      NOD() operator TVector<T, ALTS>& () const noexcept;

      ///                                                                     
      ///   Iteration                                                         
      ///                                                                     
      NOD() constexpr auto begin()       noexcept -> T*;
      NOD() constexpr auto end()         noexcept -> T*;
      NOD() constexpr auto last()        noexcept -> T*;
      NOD() constexpr auto begin() const noexcept -> T const*;
      NOD() constexpr auto end()   const noexcept -> T const*;
      NOD() constexpr auto last()  const noexcept -> T const*;
   };
   #pragma pack(pop)


   namespace Inner
   {

      ///                                                                     
      ///   Proxy array (a.k.a. a swizzled vector, intermediate type)         
      ///                                                                     
      /// Creates a shuffled representation of a source vector, and commits   
      /// any changes to it upon destruction                                  
      ///                                                                     
      template<TARGS(V) = 0, Offset...I>
      struct TProxyArray : TVector<VT, sizeof...(I), VD> {
         LANGULUS(UNINSERTABLE) true;
         LANGULUS(REFLECTABLE) false;
         static_assert(sizeof...(I) > 1, "Invalid proxy array size");
         static constexpr bool CTTI_VectorTrait = false;
         static constexpr bool CTTI_ProxyArray = true;
         using Base = TVector<VT, sizeof...(I), VD>;

      private:
         // The original data source, will be changed upon destruction  
         VT (&mSource)[VS];

         /// Commit the changes                                               
         template<Offset...I2>
         constexpr void CommitInner(ExpandedSequence<I2...>) noexcept {
            static_assert(sizeof...(I) == sizeof...(I2));
            ((mSource[I] = Base::all[I2]), ...);
         }

      public:
         TProxyArray() = delete;
         TProxyArray(const TProxyArray&) = delete;
         TProxyArray(TProxyArray&&) = delete;

         /// Create a proxy array - copy relevant contents and save a ref for 
         /// later, when local changes have to be commited to the original    
         explicit TProxyArray(VT (&source)[VS]) noexcept
            : Base    {source[I]...}
            , mSource {source} {}

         /// Intermediate type destructor - commits any local changes to the  
         /// original array, making sure no information is lost               
         ~TProxyArray() noexcept { Commit(); }

         using Base::operator =;

         auto GetBase() noexcept -> Base& {
            return static_cast<Base&>(*this);
         }

         auto GetBase() const noexcept -> Base const& {
            return static_cast<Base const&>(*this);
         }

         void Commit() noexcept {
            CommitInner(Sequence<sizeof...(I)>::Expand);
         }
      };

   } // namespace Langulus::Math::Inner


   /// Generate a lossless vector type from provided LHS and RHS types        
   ///   @tparam LHS - left hand side, can be scalar/array/vector             
   ///   @tparam RHS - right hand side, can be scalar/array/vector            
   template<class LHS, class RHS>
   using LosslessVector = TVector<Decay<Lossless<LHS, RHS>>, OverlapCounts<LHS, RHS>()>;


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   /// Returns an inverted vector                                             
   NOD() constexpr auto operator - (const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::ProxyArray  auto&) noexcept;

   /// Returns the sum of two vectors                                         
   NOD() constexpr auto operator + (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator + (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator + (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Returns the difference of two vectors                                  
   NOD() constexpr auto operator - (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator - (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator - (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Returns the Hadamard product of two vectors                            
   NOD() constexpr auto operator * (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator * (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator * (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Returns the division of two vectors                                    
   NOD() constexpr auto operator / (const CT::VectorBased auto&, const CT::VectorBased auto&);
   NOD() constexpr auto operator / (const CT::VectorBased auto&, const CT::ScalarBased auto&);
   NOD() constexpr auto operator / (const CT::ScalarBased auto&, const CT::VectorBased auto&);

   NOD() constexpr auto operator / (const CT::ProxyArray  auto&, const CT::VectorBased auto&);
   NOD() constexpr auto operator / (const CT::VectorBased auto&, const CT::ProxyArray  auto&);
   NOD() constexpr auto operator / (const CT::ProxyArray  auto&, const CT::ScalarBased auto&);
   NOD() constexpr auto operator / (const CT::ScalarBased auto&, const CT::ProxyArray  auto&);

   /// Returns the left-shift of two integer vectors                          
   NOD() constexpr auto operator << (const CT::VectorBasedInt auto&, const CT::VectorBasedInt auto&) noexcept;
   NOD() constexpr auto operator << (const CT::VectorBasedInt auto&, const CT::ScalarBasedInt auto&) noexcept;
   NOD() constexpr auto operator << (const CT::ScalarBasedInt auto&, const CT::VectorBasedInt auto&) noexcept;

   NOD() constexpr auto operator << (const CT::ProxyArrayInt  auto&, const CT::VectorBasedInt auto&) noexcept;
   NOD() constexpr auto operator << (const CT::VectorBasedInt auto&, const CT::ProxyArrayInt  auto&) noexcept;
   NOD() constexpr auto operator << (const CT::ProxyArrayInt  auto&, const CT::ScalarBasedInt auto&) noexcept;
   NOD() constexpr auto operator << (const CT::ScalarBasedInt auto&, const CT::ProxyArrayInt  auto&) noexcept;

   /// Returns the right-shift of two integer vectors                         
   NOD() constexpr auto operator >> (const CT::VectorBasedInt auto&, const CT::VectorBasedInt auto&) noexcept;
   NOD() constexpr auto operator >> (const CT::VectorBasedInt auto&, const CT::ScalarBasedInt auto&) noexcept;
   NOD() constexpr auto operator >> (const CT::ScalarBasedInt auto&, const CT::VectorBasedInt auto&) noexcept;

   NOD() constexpr auto operator >> (const CT::ProxyArrayInt  auto&, const CT::VectorBasedInt auto&) noexcept;
   NOD() constexpr auto operator >> (const CT::VectorBasedInt auto&, const CT::ProxyArrayInt  auto&) noexcept;
   NOD() constexpr auto operator >> (const CT::ProxyArrayInt  auto&, const CT::ScalarBasedInt auto&) noexcept;
   NOD() constexpr auto operator >> (const CT::ScalarBasedInt auto&, const CT::ProxyArrayInt  auto&) noexcept;

   /// Returns the xor of two integer vectors                                 
   NOD() constexpr auto operator ^ (const CT::VectorBasedInt auto&, const CT::VectorBasedInt auto&) noexcept;
   NOD() constexpr auto operator ^ (const CT::VectorBasedInt auto&, const CT::ScalarBasedInt auto&) noexcept;
   NOD() constexpr auto operator ^ (const CT::ScalarBasedInt auto&, const CT::VectorBasedInt auto&) noexcept;

   NOD() constexpr auto operator ^ (const CT::ProxyArrayInt  auto&, const CT::VectorBasedInt auto&) noexcept;
   NOD() constexpr auto operator ^ (const CT::VectorBasedInt auto&, const CT::ProxyArrayInt  auto&) noexcept;
   NOD() constexpr auto operator ^ (const CT::ProxyArrayInt  auto&, const CT::ScalarBasedInt auto&) noexcept;
   NOD() constexpr auto operator ^ (const CT::ScalarBasedInt auto&, const CT::ProxyArrayInt  auto&) noexcept;


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   constexpr auto& operator += (CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator += (CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;

   constexpr auto& operator += (CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator += (CT::VectorBased auto&, const CT::ProxyArray auto&) noexcept;
   constexpr auto& operator += (CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;

   /// Subtract                                                               
   constexpr auto& operator -= (CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator -= (CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;

   constexpr auto& operator -= (CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator -= (CT::VectorBased auto&, const CT::ProxyArray auto&) noexcept;
   constexpr auto& operator -= (CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;

   /// Multiply                                                               
   constexpr auto& operator *= (CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator *= (CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;

   constexpr auto& operator *= (CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator *= (CT::VectorBased auto&, const CT::ProxyArray auto&) noexcept;
   constexpr auto& operator *= (CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;

   /// Divide                                                                 
   constexpr auto& operator /= (CT::VectorBased auto&, const CT::VectorBased auto&);
   constexpr auto& operator /= (CT::VectorBased auto&, const CT::ScalarBased auto&);

   constexpr auto& operator /= (CT::ProxyArray  auto&, const CT::VectorBased auto&);
   constexpr auto& operator /= (CT::VectorBased auto&, const CT::ProxyArray auto&);
   constexpr auto& operator /= (CT::ProxyArray  auto&, const CT::ScalarBased auto&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator <  (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Bigger                                                                 
   NOD() constexpr auto operator >  (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator >  (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Bigger or equal                                                        
   NOD() constexpr auto operator >= (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator >= (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Smaller or equal                                                       
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator <  (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Equal                                                                  
   NOD() constexpr auto operator == (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator == (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator == (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator == (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator == (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator == (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator == (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

   /// Not equal                                                              
   NOD() constexpr auto operator != (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator != (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator != (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator != (const CT::ProxyArray  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator != (const CT::VectorBased auto&, const CT::ProxyArray  auto&) noexcept;
   NOD() constexpr auto operator != (const CT::ProxyArray  auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator != (const CT::ScalarBased auto&, const CT::ProxyArray  auto&) noexcept;

} // namespace Langulus::Math

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME