///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Functions/Trigonometry.hpp"
#include "../Functions/Arithmetics.hpp"
#include "../Numbers/TNumber.hpp"
#include "../Dimensions.hpp"
#include <SIMD/SIMD.hpp>

#define TARGS(a) CT::ScalarBased a##T, Count a##S, int a##D
#define TVEC(a) TVector<a##T, a##S, a##D>
#define TEMPLATE() template<CT::ScalarBased T, Count S, int DEFAULT>
#define TME() TVector<T, S, DEFAULT>


namespace Langulus::Math
{

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
   template<Count S, CT::ScalarBased T>
   struct TVectorBase;

   template<CT::ScalarBased T>
   struct TVectorBase<1, T> {
      union {
         union { RTTI::Tag<T, Traits::X, Traits::R, Traits::U> x, first, r, red, u; };
         T all[1] {};
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

      constexpr TVectorBase& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr TVectorBase& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };

   template<CT::ScalarBased T>
   struct TVectorBase<2, T> {
      union {
         struct {
            union { RTTI::Tag<T, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<T, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
         };
         T all[2] {};
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

      constexpr TVectorBase& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr TVectorBase& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };

   template<CT::ScalarBased T>
   struct TVectorBase<3, T> {
      union {
         struct {
            union { RTTI::Tag<T, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<T, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
            union { RTTI::Tag<T, Traits::Z, Traits::B, Traits::S> z, third,  b, blue,  s; };
         };
         T all[3] {};
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

      constexpr TVectorBase& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr TVectorBase& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };

   template<CT::ScalarBased T>
   struct TVectorBase<4, T> {
      union {
         struct {
            union { RTTI::Tag<T, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<T, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
            union { RTTI::Tag<T, Traits::Z, Traits::B, Traits::S> z, third,  b, blue,  s; };
            union { RTTI::Tag<T, Traits::W, Traits::A, Traits::T> w, fourth, a, alpha, t; };
         };
         T all[4] {};
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

      constexpr TVectorBase& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr TVectorBase& operator = (TVectorBase&& other) noexcept {
         return *new (this) TVectorBase {Forward<TVectorBase>(other)};
      }
   };

   template<Count S, CT::ScalarBased T>
   struct TVectorBase {
      static_assert(S > 4, 
         "Smaller S should've been defined in specializations, "
         "something's wrong with your compiler");

      union {
         struct {
            union { RTTI::Tag<T, Traits::X, Traits::R, Traits::U> x, first,  r, red,   u; };
            union { RTTI::Tag<T, Traits::Y, Traits::G, Traits::V> y, second, g, green, v; };
            union { RTTI::Tag<T, Traits::Z, Traits::B, Traits::S> z, third,  b, blue,  s; };
            union { RTTI::Tag<T, Traits::W, Traits::A, Traits::T> w, fourth, a, alpha, t; };

            // The remaining elements, that don't have custom names     
            T tail[S - 4];
         };
         T all[S] {};
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

      constexpr TVectorBase& operator = (const TVectorBase& other) noexcept {
         return *new (this) TVectorBase {other};
      }

      constexpr TVectorBase& operator = (TVectorBase&& other) noexcept {
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
      static constexpr T DefaultMember = static_cast<T>(DEFAULT);
      using ArrayType = T[S];
      using Base = TVectorBase<S, T>;

   public:
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

   #if LANGULUS_SIMD(128BIT)
      TVector(const simde__m128&)  noexcept;
      TVector(const simde__m128d&) noexcept;
      TVector(const simde__m128i&) noexcept;
   #endif

   #if LANGULUS_SIMD(256BIT)
      TVector(const simde__m256&)  noexcept;
      TVector(const simde__m256d&) noexcept;
      TVector(const simde__m256i&) noexcept;
   #endif

   #if LANGULUS_SIMD(512BIT)
      TVector(const simde__m512&)  noexcept;
      TVector(const simde__m512d&) noexcept;
      TVector(const simde__m512i&) noexcept;
   #endif

      TVector(Describe&&);

      ///                                                                     
      ///   Assignment                                                        
      ///                                                                     
      constexpr TVector& operator = (const CT::Vector auto&) noexcept;
      constexpr TVector& operator = (const CT::Scalar auto&) noexcept;

      template<CT::ScalarBased N, CT::Dimension D>
      constexpr TVector& operator = (const TVectorComponent<N, D>&) noexcept;

      ///                                                                     
      ///   Interpretation                                                    
      ///                                                                     
      template<class TOKEN>
      Flow::Code Serialize() const;

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

      LANGULUS(INLINED)
      constexpr const T* GetRaw() const noexcept { return all; }
      LANGULUS(INLINED)
      constexpr       T* GetRaw()       noexcept { return all; }

      NOD() constexpr const T& Get(Offset) const noexcept;
      NOD() constexpr       T& Get(Offset)       noexcept;

      template<Offset I>
      NOD() constexpr const T& GetIdx() const noexcept;

      NOD() constexpr       T& operator [] (Offset)       noexcept;
      NOD() constexpr const T& operator [] (Offset) const noexcept;

      NOD() constexpr Count GetCount() const noexcept;
      NOD() constexpr T LengthSquared() const noexcept;
      NOD() constexpr T Length() const noexcept;
      NOD() constexpr bool IsDegenerate() const noexcept;

      template<Offset HEAD, Offset...TAIL>
      NOD()           decltype(auto) Swz()       noexcept;
      template<Offset HEAD, Offset...TAIL>
      NOD() constexpr decltype(auto) Swz() const noexcept;

      template<Offset... I>
      static constexpr bool SwzRequirements = S > Max(0U, I...);

      /// Generate all combinations of all swizzle functions up to 4D         
      #define LANGULUS_TVECTOR_SWIZZLER(name, ...) \
         NOD() decltype(auto) name() noexcept requires (SwzRequirements<__VA_ARGS__>) { \
            return Swz<__VA_ARGS__>(); \
         } \
         NOD() decltype(auto) name() const noexcept requires (SwzRequirements<__VA_ARGS__>) { \
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


      template<class AS, bool NORMALIZE = CT::Real<AS> and not CT::Real<T>>
      NOD() constexpr TVector<AS, S> AsCast() const noexcept;
      template<Count = Math::Min(S, 3u)>
      NOD() constexpr auto Volume() const noexcept;

      template<TARGS(ALT)>
      NOD() constexpr T Dot(const TVEC(ALT)&) const noexcept;

      template<TARGS(ALT)>
      NOD() constexpr TVector<T, 3> Cross(const TVEC(ALT)&) const noexcept requires (S >= 3 and ALTS >= 3);

      NOD() constexpr auto Normalize() const requires (S > 1);

      template<TARGS(MIN), TARGS(MAX)>
      NOD() constexpr auto Clamp(const TVEC(MIN)&, const TVEC(MAX)&) const noexcept;
      template<TARGS(MIN), TARGS(MAX)>
      NOD() constexpr auto ClampRev(const TVEC(MIN)&, const TVEC(MAX)&) const noexcept;

      NOD() constexpr auto Round() const noexcept;
      NOD() constexpr auto Floor() const noexcept;
      NOD() constexpr auto Ceil() const noexcept;
      NOD() constexpr auto Abs() const noexcept;
      NOD() constexpr auto Sign() const noexcept;
      NOD() constexpr auto Frac() const noexcept;
      NOD() constexpr auto Sqrt() const noexcept;
      NOD() constexpr auto Exp() const noexcept;
      NOD() constexpr auto Sin() const noexcept;
      NOD() constexpr auto Cos() const noexcept;
      NOD() constexpr auto Warp(const T&) const noexcept;

      NOD() static constexpr TVector Max() noexcept;
      NOD() constexpr auto Max(const T&) const noexcept;
      template<TARGS(ALT)>
      NOD() constexpr auto Max(const TVEC(ALT)&) const noexcept;
      NOD() constexpr auto HMax() const noexcept;

      NOD() static constexpr TVector Min() noexcept;
      NOD() constexpr auto Min(const T&) const noexcept;
      template<TARGS(ALT)>
      NOD() constexpr auto Min(const TVEC(ALT)&) const noexcept;
      NOD() constexpr auto HMin() const noexcept;

      NOD() constexpr auto HSum() const noexcept;
      NOD() constexpr auto HMul() const noexcept;

      NOD() constexpr auto Mod(const T&) const noexcept;
      template<TARGS(ALT)>
      NOD() constexpr auto Mod(const TVEC(ALT)&) const noexcept;

      NOD() constexpr auto Step(const T&) const noexcept;
      template<TARGS(ALT)>
      NOD() constexpr auto Step(const TVEC(ALT)&) const noexcept;

      template<class ALT>
      NOD() constexpr TME() Pow(const ALT&) const noexcept;

      auto& Sort() noexcept;

      NOD() constexpr operator       T& ()       noexcept requires (S == 1);
      NOD() constexpr operator const T& () const noexcept requires (S == 1);

      template<CT::ScalarBased N>
      NOD() explicit constexpr operator N () const noexcept requires (S == 1 and CT::Convertible<N, T>);

      template<Count ALTS>
      NOD() operator TVector<T, ALTS>& () noexcept requires (ALTS < S);
      template<Count ALTS>
      NOD() operator const TVector<T, ALTS>& () const noexcept requires (ALTS < S);

      ///                                                                     
      ///   Iteration                                                         
      ///                                                                     
      NOD() constexpr       T* begin() noexcept;
      NOD() constexpr       T* end() noexcept;
      NOD() constexpr       T* last() noexcept;
      NOD() constexpr const T* begin() const noexcept;
      NOD() constexpr const T* end() const noexcept;
      NOD() constexpr const T* last() const noexcept;
   };
   #pragma pack(pop)


   namespace Inner
   {

      ///                                                                     
      ///   Swizzled vector, intermediate type                                
      ///                                                                     
      /// Creates a shuffled representation of a source vector, and commits   
      /// any changes to it upon destruction                                  
      ///                                                                     
      template<TARGS(V), Offset...I>
      struct TProxyVector : TVector<VT, sizeof...(I), VD> {
      LANGULUS(UNINSERTABLE) true;
      private:
         using Base = TVector<VT, sizeof...(I), VD>;

         TVEC(V)& mSource;

      private:
         /// Commit the changes                                               
         template<Offset...I2>
         constexpr void Commit(::std::integer_sequence<Offset, I2...>&&) noexcept {
            ((mSource[I] = (*this)[I2]), ...);
         }

      public:
         TProxyVector() = delete;
         TProxyVector(const TProxyVector&) = delete;
         TProxyVector(TProxyVector&&) = delete;

         explicit TProxyVector(TVEC(V)& source) noexcept
            : mSource {source} {}

         ~TProxyVector() noexcept {
            Commit(::std::make_integer_sequence<Offset, sizeof...(I)>{});
         }

         using Base::operator =;
      };

   } // namespace Inner


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

   /// Returns the sum of two vectors                                         
   NOD() constexpr auto operator + (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   /// Returns the difference of two vectors                                  
   NOD() constexpr auto operator - (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   /// Returns the Hadamard product of two vectors                            
   NOD() constexpr auto operator * (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   /// Returns the division of two vectors                                    
   NOD() constexpr auto operator / (const CT::VectorBased auto&, const CT::VectorBased auto&);
   NOD() constexpr auto operator / (const CT::VectorBased auto&, const CT::ScalarBased auto&);
   NOD() constexpr auto operator / (const CT::ScalarBased auto&, const CT::VectorBased auto&);

   /// Returns the left-shift of two integer vectors                          
   template<CT::VectorBased LHS, CT::VectorBased RHS>
   NOD() constexpr auto operator << (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;
   template<CT::VectorBased LHS, CT::ScalarBased RHS>
   NOD() constexpr auto operator << (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;
   template<CT::VectorBased LHS, CT::ScalarBased RHS>
   NOD() constexpr auto operator << (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;

   /// Returns the right-shift of two integer vectors                         
   template<CT::VectorBased LHS, CT::VectorBased RHS>
   NOD() constexpr auto operator >> (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;
   template<CT::VectorBased LHS, CT::ScalarBased RHS>
   NOD() constexpr auto operator >> (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;
   template<CT::VectorBased LHS, CT::ScalarBased RHS>
   NOD() constexpr auto operator >> (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;

   /// Returns the xor of two integer vectors                                 
   template<CT::VectorBased LHS, CT::VectorBased RHS>
   NOD() constexpr auto operator ^ (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;
   template<CT::VectorBased LHS, CT::ScalarBased RHS>
   NOD() constexpr auto operator ^ (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;
   template<CT::VectorBased LHS, CT::ScalarBased RHS>
   NOD() constexpr auto operator ^ (const LHS&, const RHS&) noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>>;


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   constexpr auto& operator += (CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator += (CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;

   /// Subtract                                                               
   constexpr auto& operator -= (CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator -= (CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;

   /// Multiply                                                               
   constexpr auto& operator *= (CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator *= (CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;

   /// Divide                                                                 
   constexpr auto& operator /= (CT::VectorBased auto&, const CT::VectorBased auto&);
   constexpr auto& operator /= (CT::VectorBased auto&, const CT::ScalarBased auto&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   /// Bigger                                                                 
   NOD() constexpr auto operator >  (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   /// Bigger or equal                                                        
   NOD() constexpr auto operator >= (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   /// Smaller or equal                                                       
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   /// Equal                                                                  
   NOD() constexpr auto operator == (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator == (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator == (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

   NOD() constexpr auto operator != (const CT::VectorBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator != (const CT::VectorBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator != (const CT::ScalarBased auto&, const CT::VectorBased auto&) noexcept;

} // namespace Langulus::Math

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME