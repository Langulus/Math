///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
/*#include "../Functions/Trigonometry.hpp"
#include "../Functions/Arithmetics.hpp"
#include "../Numbers/TNumber.hpp"
#include "../Verbs/Multiply.hpp"*/

#include "../Numbers/Dimension.hpp"
#include <Langulus/CT/Scalar.hpp>
#include <Langulus/SIMD/SIMD.hpp>
#include <Langulus/Utils/Sequence.hpp>
#include <Langulus/Utils/Literal.hpp>
#include <Langulus/TOwn.hpp>

#define TARGS(a)     CT::Scalar a##T, size_t a##S, int a##D
#define TVEC(a)      TVector<a##T, a##S, a##D>
#define TEMPLATE()   template<CT::Scalar T, size_t S, int DEFAULT>
#define TME()        TVector<T, S, DEFAULT>


namespace Langulus::Math
{
   template<CT::Scalar T, CT::Dimension D>
   struct TVectorComponent;

   template<CT::Scalar T, size_t S, int DEFAULT = 0>
   struct TVector;

   template<CT::Scalar T, size_t S, int DEFAULT = 0>
   using TVec = TME();

   using Vec1     = TVector<Real, 1>;
   using Vec1f    = TVector<float, 1>;
   using Vec1d    = TVector<double, 1>;
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
   using Vec2f    = TVector<float, 2>;
   using Vec2d    = TVector<double, 2>;
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
   using Vec3f    = TVector<float, 3>;
   using Vec3d    = TVector<double, 3>;
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
   using Vec4f    = TVector<float, 4>;
   using Vec4d    = TVector<double, 4>;
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


   /// Abstract vector that relies on the context to pick the proper type.    
   /// A 2D world will work with Vec2, while a 3D world will work with Vec3.  
   /// Some contexts will demand integer vectors, while others will require   
   /// real ones. If context lacks definition, this will default to Vec4, as  
   /// it's the most versatile type, albeit a bit bigger.                     
   struct Vector {
      using CTTI_Abstract = Yup;
      using CTTI_Concrete = Vec4;
   };

   /// Similar as the above, but the size is explicitly defined.              
   /// Only the type is decided by the context, defaulting to real.           
   template<size_t S> requires (S>0)
   struct VectorOfSize : Vector {
      using CTTI_Concrete = TVector<Real, S>;
      using CTTI_Bases    = Vector;
      using CTTI_Array    = Yes<S>;
   };

   /// Similar as the above, but the type is explicitly defined.              
   /// Only the size is decided by the context, defaulting to 4.              
   template<CT::Scalar T>
   struct VectorOfType : Vector {
      using CTTI_Concrete = Math::TVector<T, 4>;
      using CTTI_Bases    = Vector;
      using CTTI_Typed    = T;
   };

   /// Points be just vectors, man                                            
   using Point = Vector;
   
   #pragma pack(push, 1)

   template<size_t, CT::Scalar, int DEFAULT>
   struct TVectorBase;


   ///                                                                        
   /// 1D vector base                                                         
   template<CT::Scalar TYPE, int DEFAULT>
   struct TVectorBase<1, TYPE, DEFAULT> {
      union {
         TYPE all[1] {};
         union {
            Own<TYPE, Tags::X, Tags::R, Tags::U> x, first, r, red, u;
         };
      };
      using CTTI_Members = Members<&TVectorBase::x>;

      static constexpr TYPE y       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE second  = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE g       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE green   = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE v       = static_cast<TYPE>(DEFAULT);

      static constexpr TYPE z       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE third   = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE b       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE blue    = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE s       = static_cast<TYPE>(DEFAULT);

      static constexpr TYPE w       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE fourth  = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE a       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE alpha   = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE t       = static_cast<TYPE>(DEFAULT);

      void tail() { static_assert(false, "1D vector doesn't have a tail"); }

      constexpr TVectorBase() noexcept {
         all[0] = static_cast<TYPE>(DEFAULT);
      }

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         all[0] = other.all[0];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         all[0] = other.all[0];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         all[0] = other.all[0];
         return *this;
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         all[0] = other.all[0];
         return *this;
      }
   };


   ///                                                                        
   /// 2D vector base                                                         
   template<CT::Scalar TYPE, int DEFAULT>
   struct TVectorBase<2, TYPE, DEFAULT> {
      union {
         TYPE all[2] {};
         struct {
            union {
               Own<TYPE, Tags::X, Tags::R, Tags::U> x, first,  r, red,   u;
            };
            union {
               Own<TYPE, Tags::Y, Tags::G, Tags::V> y, second, g, green, v;
            };
         };
      };
      using CTTI_Members = Members<&TVectorBase::x, &TVectorBase::y>;

      static constexpr TYPE z       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE third   = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE b       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE blue    = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE s       = static_cast<TYPE>(DEFAULT);

      static constexpr TYPE w       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE fourth  = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE a       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE alpha   = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE t       = static_cast<TYPE>(DEFAULT);

      void tail() { static_assert(false, "2D vector doesn't have a tail"); }

      constexpr TVectorBase() noexcept {
         for (int i = 0; i < 2; ++i)
            all[i] = static_cast<TYPE>(DEFAULT);
      }

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (int i = 0; i < 2; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (int i = 0; i < 2; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         for (int i = 0; i < 2; ++i)
            all[i] = other.all[i];
         return *this;
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         for (int i = 0; i < 2; ++i)
            all[i] = other.all[i];
         return *this;
      }
   };


   ///                                                                        
   /// 3D vector base                                                         
   template<CT::Scalar TYPE, int DEFAULT>
   struct TVectorBase<3, TYPE, DEFAULT> {
      union {
         TYPE all[3] {};
         struct {
            union {
               Own<TYPE, Tags::X, Tags::R, Tags::U> x, first,  r, red,   u;
            };
            union {
               Own<TYPE, Tags::Y, Tags::G, Tags::V> y, second, g, green, v;
            };
            union {
               Own<TYPE, Tags::Z, Tags::B, Tags::S> z, third,  b, blue,  s;
            };
         };
      };
      using CTTI_Members = Members<
         &TVectorBase::x,
         &TVectorBase::y, 
         &TVectorBase::z
      >;

      static constexpr TYPE w       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE fourth  = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE a       = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE alpha   = static_cast<TYPE>(DEFAULT);
      static constexpr TYPE t       = static_cast<TYPE>(DEFAULT);

      void tail() { static_assert(false, "3D vector doesn't have a tail"); }

      constexpr TVectorBase() noexcept {
         for (int i = 0; i < 3; ++i)
            all[i] = static_cast<TYPE>(DEFAULT);
      }

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (int i = 0; i < 3; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (int i = 0; i < 3; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         for (int i = 0; i < 3; ++i)
            all[i] = other.all[i];
         return *this;
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         for (int i = 0; i < 3; ++i)
            all[i] = other.all[i];
         return *this;
      }
   };


   ///                                                                        
   /// 4D vector base                                                         
   template<CT::Scalar TYPE, int DEFAULT>
   struct TVectorBase<4, TYPE, DEFAULT> {
      union {
         TYPE all[4] {};
         struct {
            union { Own<TYPE, Tags::X, Tags::R, Tags::U> x, first,  r, red,   u; };
            union { Own<TYPE, Tags::Y, Tags::G, Tags::V> y, second, g, green, v; };
            union { Own<TYPE, Tags::Z, Tags::B, Tags::S> z, third,  b, blue,  s; };
            union { Own<TYPE, Tags::W, Tags::A, Tags::T> w, fourth, a, alpha, t; };
         };
      };
      using CTTI_Members = Members<
         &TVectorBase::x,
         &TVectorBase::y, 
         &TVectorBase::z,
         &TVectorBase::w
      >;

      void tail() { static_assert(false, "4D vector doesn't have a tail"); }

      constexpr TVectorBase() noexcept {
         for (int i = 0; i < 4; ++i)
            all[i] = static_cast<TYPE>(DEFAULT);
      }

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (int i = 0; i < 4; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (int i = 0; i < 4; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         for (int i = 0; i < 4; ++i)
            all[i] = other.all[i];
         return *this;
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         for (int i = 0; i < 4; ++i)
            all[i] = other.all[i];
         return *this;
      }
   };


   ///                                                                        
   /// 5+D vector base                                                        
   template<size_t S, CT::Scalar TYPE, int DEFAULT> requires (S > 4)
   struct TVectorBase<S, TYPE, DEFAULT> {
      union {
         TYPE all[S] {};
         struct {
            union { Own<TYPE, Tags::X, Tags::R, Tags::U> x, first,  r, red,   u; };
            union { Own<TYPE, Tags::Y, Tags::G, Tags::V> y, second, g, green, v; };
            union { Own<TYPE, Tags::Z, Tags::B, Tags::S> z, third,  b, blue,  s; };
            union { Own<TYPE, Tags::W, Tags::A, Tags::T> w, fourth, a, alpha, t; };

            // The remaining elements, that don't have custom names     
            TYPE tail[S - 4];
         };
      };
      using CTTI_Members = Members<
         &TVectorBase::x,
         &TVectorBase::y, 
         &TVectorBase::z,
         &TVectorBase::w,
         &TVectorBase::tail
      >;

      constexpr TVectorBase() noexcept {
         for (size_t i = 0; i < S; ++i)
            all[i] = static_cast<TYPE>(DEFAULT);
      }

      constexpr TVectorBase(const TVectorBase& other) noexcept {
         for (size_t i = 0; i < S; ++i)
            all[i] = other.all[i];
      }

      constexpr TVectorBase(TVectorBase&& other) noexcept {
         for (size_t i = 0; i < S; ++i)
            all[i] = other.all[i];
      }

      constexpr auto& operator = (const TVectorBase& other) noexcept {
         for (size_t i = 0; i < S; ++i)
            all[i] = other.all[i];
         return *this;
      }

      constexpr auto& operator = (TVectorBase&& other) noexcept {
         for (size_t i = 0; i < S; ++i)
            all[i] = other.all[i];
         return *this;
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
   struct TVector : TVectorBase<S, T, DEFAULT> {
      static_assert(S > 0, "Can't have a vector of zero size");
      static constexpr size_t MemberCount = S;
      static constexpr T Default = static_cast<T>(DEFAULT);
      using ArrayType = T[S];
      using Base = TVectorBase<S, T, DEFAULT>;

   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TVector>();
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

   public:
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Abstract  = No;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Nullable  = Maybe<DEFAULT == 0>;
      using CTTI_Typed     = T;
      using CTTI_Bases     = Types<VectorOfSize<S>, VectorOfType<T>, Base, T>;

      // Make TVector match the CT::VectorBased concept                 
      static constexpr bool CTTI_VectorTrait = true;
      static constexpr bool IsReal = CT::Real<T>;

   public:
      ///                                                                     
      ///   Construction                                                      
      ///                                                                     
      constexpr TVector() noexcept;
      constexpr TVector(const CT::Vector auto&) noexcept;
      constexpr TVector(const CT::Scalar auto&) noexcept;

      template<class T1, class T2, class...TN>
      constexpr TVector(const T1&, const T2&, const TN&...) noexcept;

      template<CT::Scalar N, CT::Dimension D>
      constexpr TVector(const TVectorComponent<N, D>&) noexcept;

      TVector(const CT::SIMD auto&)  noexcept;
      TVector(Describe&&);

      ///                                                                     
      ///   Assignment                                                        
      ///                                                                     
      constexpr auto operator = (const CT::Vector auto&) noexcept -> TVector&;
      constexpr auto operator = (const CT::Scalar auto&) noexcept -> TVector&;

      template<CT::Scalar N, CT::Dimension D>
      constexpr auto operator = (const TVectorComponent<N, D>&) noexcept -> TVector&;

      ///                                                                     
      ///   Verbs                                                             
      ///                                                                     
      //void Multiply(Verb&) const;
      //void Multiply(Verb&);

      ///                                                                     
      ///   Interpretation                                                    
      ///                                                                     
      //template<CT::Serial AS, class TOKEN>
      //AS Serialize() const;

      //explicit operator Annies::Text() const;
      //explicit operator Flow::Code() const;

      static constexpr decltype(auto) Adapt(const CT::Scalar auto&) noexcept;

      ///                                                                     
      ///   Access                                                            
      ///                                                                     
      using Base::x;
      using Base::first;
      using Base::r;
      using Base::red;
      using Base::u;

      using Base::y;
      using Base::second;
      using Base::g;
      using Base::green;
      using Base::v;

      using Base::z;
      using Base::third;
      using Base::b;
      using Base::blue;
      using Base::s;

      using Base::w;
      using Base::fourth;
      using Base::a;
      using Base::alpha;
      using Base::t;

      using Base::all;

      constexpr auto Get(size_t) const noexcept -> const T&;
      constexpr auto Get(size_t)       noexcept ->       T&;

      template<size_t I>
      constexpr auto GetIdx() const noexcept -> const T&;

      constexpr auto operator [] (size_t)       noexcept ->       T&;
      constexpr auto operator [] (size_t) const noexcept -> const T&;

      constexpr auto GetCount() const noexcept -> size_t;
      constexpr auto LengthSquared() const noexcept -> T;
      constexpr auto Length() const noexcept -> T;
      constexpr bool IsDegenerate() const noexcept;

      template<size_t HEAD, size_t...TAIL>
      decltype(auto) Swz() noexcept;
      template<size_t HEAD, size_t...TAIL>
      constexpr decltype(auto) Swz() const noexcept;

      template<size_t...I>
      static constexpr bool SwzRequirements = ((S > I) and ...);

      /// Generate all combinations of all swizzle functions up to 4D         
      #define LANGULUS_TVECTOR_SWIZZLER(name, ...) \
         LANGULUS(INLINED) decltype(auto) name() noexcept \
         requires (SwzRequirements<__VA_ARGS__>) { \
            return Swz<__VA_ARGS__>(); \
         } \
         LANGULUS(INLINED) decltype(auto) name() const noexcept \
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
      constexpr auto AsCast() const noexcept -> TVector<AS, S>;

      template<size_t = S < 3u ? S : 3u>
      constexpr auto Volume() const noexcept;

      constexpr auto Dot(const CT::Vector auto&) const noexcept -> T;

      template<CT::Vector V> requires (S >= 3 and ExtentOf<V> >= 3)
      constexpr auto Cross(const V&) const noexcept -> TVector<T, 3>;

      constexpr auto Normalize() const noexcept -> TVector requires (S > 1);

      constexpr auto Clamp   (const auto&, const auto&) const noexcept -> TVector;
      constexpr auto ClampRev(const auto&, const auto&) const noexcept -> TVector;

      constexpr auto Round   () const noexcept -> TVector;
      constexpr auto Floor   () const noexcept -> TVector;
      constexpr auto Ceil    () const noexcept -> TVector;
      constexpr auto Abs     () const noexcept -> TVector;
      constexpr auto Sign    () const noexcept -> TVector;
      constexpr auto Frac    () const noexcept -> TVector;
      constexpr auto Sqrt    () const noexcept -> TVector;
      constexpr auto Exp     () const noexcept -> TVector;
      constexpr auto Sin     () const noexcept -> TVector;
      constexpr auto Cos     () const noexcept -> TVector;
      constexpr auto Warp(const T&) const noexcept -> TVector;

      static constexpr auto Max() noexcept -> TVector;
      static constexpr auto Min() noexcept -> TVector;

      constexpr auto Max(const auto&) const noexcept;
      constexpr auto Min(const auto&) const noexcept;

      constexpr auto HMax() const noexcept -> T;
      constexpr auto HMin() const noexcept -> T;
      constexpr auto HSum() const noexcept -> T;
      constexpr auto HMul() const noexcept -> T;

      constexpr auto Mod (const auto&) const noexcept -> TVector;
      constexpr auto Step(const auto&) const noexcept -> TVector;
      constexpr auto Pow (const auto&) const noexcept -> TVector;

      auto& Sort() noexcept;

      constexpr explicit operator T&   () const noexcept requires (S == 1);
      constexpr explicit operator bool () const noexcept;

      template<CT::Scalar N> requires (S == 1 and CT::Convertible<N, T>)
      /*explicit*/ constexpr operator N () const noexcept;
      
      template<size_t ALTS> requires (ALTS < S)
      operator TVector<T, ALTS>& () const noexcept;

      ///                                                                     
      ///   Iteration                                                         
      ///                                                                     
      constexpr auto begin()       noexcept -> T*;
      constexpr auto end()         noexcept -> T*;
      constexpr auto last()        noexcept -> T*;
      constexpr auto begin() const noexcept -> T const*;
      constexpr auto end()   const noexcept -> T const*;
      constexpr auto last()  const noexcept -> T const*;
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
      template<TARGS(V) = 0, size_t...I>
      struct TProxyArray : TVector<VT, sizeof...(I), VD> {
         using CTTI_ReflectAs = void;
         static_assert(sizeof...(I) > 1, "Invalid proxy array size");
         static constexpr bool CTTI_VectorTrait = false;
         static constexpr bool CTTI_ProxyArray = true;
         using Base = TVector<VT, sizeof...(I), VD>;

      private:
         // The original data source, will be changed upon destruction  
         VT (&mSource)[VS];

         /// Commit the changes                                               
         template<size_t...I2>
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
   }

   /// Generate a lossless vector type from provided LHS and RHS types        
   ///   @tparam LHS - left hand side, can be scalar/array/vector             
   ///   @tparam RHS - right hand side, can be scalar/array/vector            
   template<class LHS, class RHS>
   using LosslessVector = TVector<Decay<Lossless<LHS, RHS>>, OverlapCounts<LHS, RHS>()>;
}

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME