///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Functions/Trigonometry.hpp"
#include "../Functions/Arithmetics.hpp"
#include "../Numbers/TNumber.hpp"
#include "../Dimensions.hpp"

namespace Langulus::Math
{

   template<CT::DenseNumber T, CT::Dimension D>
   struct TVectorComponent;

   template<CT::DenseNumber T, Count C, int DEFAULT = 0>
   struct TVector;

   using Vec1     = TVector<Real, 1>;
   using Vec1f    = TVector<Float, 1>;
   using Vec1d    = TVector<Double, 1>;
   using Vec1i    = TVector<signed, 1>;
   using Vec1u    = TVector<unsigned, 1>;
   using Vec1i8   = TVector<::std::int8_t, 1>;
   using Vec1u8   = TVector<uint8, 1>;
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
   using Vec2u8   = TVector<uint8, 2>;
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
   using Vec3u8   = TVector<uint8, 3>;
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
   using Vec4u8   = TVector<uint8, 4>;
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

namespace Langulus::A
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
   template<CT::DenseNumber T>
   struct VectorOfType : Vector {
      LANGULUS(CONCRETE) Math::TVector<T, 4>;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(Vector);
   };

} // namespace Langulus::A

#define TARGS(a) CT::DenseNumber a##T, Count a##S, int a##D
#define TVEC(a) TVector<a##T, a##S, a##D>
#define TEMPLATE() template<CT::DenseNumber T, Count S, int DEFAULT>
#define TME() TVector<T, S, DEFAULT>


namespace Langulus::Math
{

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
   #pragma pack(push, 1)
   TEMPLATE()
   struct TVector {
      static_assert(S >= 1, "Can't have a vector of zero size");
      static constexpr Count MemberCount = S;
      static constexpr T DefaultMember {static_cast<T>(DEFAULT)};
      template<CT::DenseNumber N>
      static constexpr bool IsCompatible = CT::Convertible<N, T>;

      T mArray[S];

   private:
      static constexpr auto DefaultClassName = RTTI::LastCppNameOf<TVector>();
      using ClassName = ::std::array<char, DefaultClassName.size() + 1>;
      static constexpr ClassName GenerateClassName() noexcept;
      static constexpr ClassName GeneratedClassName = GenerateClassName();

   public:
      LANGULUS(NAME) GeneratedClassName.data();
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) DEFAULT == 0;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(
         A::VectorOfSize<S>, 
         A::VectorOfType<T>,
         T
      );
      LANGULUS_CONVERSIONS(Flow::Code);

   public:
      constexpr TVector() noexcept;

      template<TARGS(ALT)>
      constexpr TVector(const TVEC(ALT)&) noexcept;

      template<class HEAD, class... TAIL>
      constexpr TVector(const HEAD&, const TAIL&...) noexcept requires (S > 1 && sizeof...(TAIL) > 0);

      template<CT::DenseNumber N>
      constexpr TVector(const N&) noexcept requires IsCompatible<N>;

      template<CT::DenseNumber N>
      constexpr TVector(const N*) noexcept requires IsCompatible<N>;

      template<CT::Array N>
      constexpr TVector(const N&) noexcept requires IsCompatible<Decay<N>>;

      template<CT::DenseNumber N, CT::Dimension D>
      constexpr TVector(const TVectorComponent<N, D>&) noexcept;

      TVector(const Descriptor&);

      template<class TOKEN>
      Flow::Code Serialize() const;

      NOD() explicit operator Flow::Code() const;

      template<CT::DenseNumber N>
      NOD() constexpr decltype(auto) Adapt(const N&) const noexcept requires IsCompatible<N>;


      ///                                                                     
      ///   Access                                                            
      ///                                                                     
      NOD() constexpr const T& Get(Offset) const noexcept;

      template<Offset I>
      NOD() constexpr const T& GetIdx() const noexcept;

      NOD() constexpr T& operator [] (Offset) noexcept;
      NOD() constexpr const T& operator [] (Offset) const noexcept;

      NOD() constexpr const T* GetRaw() const noexcept;
      NOD() constexpr T* GetRaw() noexcept;
      NOD() constexpr Count GetCount() const noexcept;
      NOD() constexpr T LengthSquared() const noexcept;
      NOD() constexpr T Length() const noexcept;
      NOD() constexpr bool IsDegenerate() const noexcept;

      template<Offset HEAD, Offset... TAIL>
      NOD() decltype(auto) Swz() noexcept;
      template<Offset HEAD, Offset... TAIL>
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

      /// 1D Swizzlers                                                        
      LANGULUS_TVECTOR_SWIZZLER(x, 0U)
      LANGULUS_TVECTOR_SWIZZLER(y, 1U)
      LANGULUS_TVECTOR_SWIZZLER(z, 2U)
      LANGULUS_TVECTOR_SWIZZLER(w, 3U)

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


      template<class AS, bool NORMALIZE = CT::Real<AS> && !CT::Real<T>>
      NOD() constexpr TVector<AS, S> AsCast() const noexcept;
      template<Count = Math::Min(S, 3u)>
      NOD() constexpr auto Volume() const noexcept;


      ///                                                                     
      ///   Compare                                                           
      ///                                                                     
      template<CT::DenseNumber N>
      constexpr auto& operator = (const N&) noexcept;

      template<TARGS(ALT)>
      constexpr auto& operator = (const TVEC(ALT)&) noexcept;

      template<CT::DenseNumber N, CT::Dimension D>
      constexpr auto& operator = (const TVectorComponent<N, D>&) noexcept;

      template<TARGS(ALT)>
      NOD() constexpr T Dot(const TVEC(ALT)&) const noexcept;

      template<TARGS(ALT)>
      NOD() constexpr TVector<T, 3> Cross(const TVEC(ALT)&) const noexcept requires (S >= 3 && ALTS >= 3);

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

      NOD() constexpr auto Pow(const T&) const noexcept;
      template<TARGS(ALT)>
      NOD() constexpr auto Pow(const TVEC(ALT)&) const noexcept;

      auto& Sort() noexcept;

      NOD() constexpr operator T& () noexcept requires (S == 1);
      NOD() constexpr operator const T& () const noexcept requires (S == 1);

      template<CT::DenseNumber N>
      NOD() explicit constexpr operator N () const noexcept requires (S == 1 && IsCompatible<N>);

      template<Count ALTS>
      NOD() operator TVector<T, ALTS>& () noexcept requires (ALTS < S);
      template<Count ALTS>
      NOD() operator const TVector<T, ALTS>& () const noexcept requires (ALTS < S);

      ///                                                                     
      ///   Iteration                                                         
      ///                                                                     
      NOD() constexpr T* begin() noexcept;
      NOD() constexpr T* end() noexcept;
      NOD() constexpr T* last() noexcept;
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
      template<TARGS(V), Offset... I>
      struct TProxyVector : TVector<VT, sizeof...(I), VD> {
      LANGULUS(UNINSERTABLE) true;
      private:
         using Base = TVector<VT, sizeof...(I), VD>;
         using Base::mArray;

         TVEC(V)& mSource;

      private:
         /// Commit the changes                                               
         void Commit() noexcept {
            constexpr Offset sequence [] {I...};
            auto from = mArray;
            for (auto& to : sequence)
               mSource.mArray[to] = *(++from);
         }

      public:
         TProxyVector() = delete;
         TProxyVector(const TProxyVector&) = delete;
         TProxyVector(TProxyVector&&) = delete;

         explicit TProxyVector(TVEC(V)& source) noexcept
            : mSource {source} {}

         ~TProxyVector() noexcept {
            Commit();
         }

         using Base::operator =;
      };

   } // namespace Inner


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   /// Returns an inverted vector                                             
   template<TARGS(RHS)>
   NOD() auto operator - (const TVEC(RHS)&) noexcept;

   /// Returns the sum of two vectors                                         
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator + (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator + (const TVEC(LHS)&, const N&) noexcept;

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator + (const N&, const TVEC(RHS)&) noexcept;

   /// Returns the difference of two vectors                                  
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator - (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator - (const TVEC(LHS)&, const N&) noexcept;

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator - (const N&, const TVEC(RHS)&) noexcept;

   /// Returns the product of two vectors                                     
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator * (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator * (const TVEC(LHS)&, const N&) noexcept;

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator * (const N&, const TVEC(RHS)&) noexcept;

   /// Returns the division of two vectors                                    
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator / (const TVEC(LHS)&, const TVEC(RHS)&);

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator / (const TVEC(LHS)&, const N&);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator / (const N&, const TVEC(RHS)&);

   /// Returns the left-shift of two integer vectors                          
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator << (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires CT::Integer<LHST, RHST>;

   template<TARGS(LHS), CT::Integer N>
   NOD() auto operator << (const TVEC(LHS)&, const N&) noexcept requires CT::Integer<LHST>;

   template<TARGS(RHS), CT::Integer N>
   NOD() auto operator << (const N&, const TVEC(RHS)&) noexcept requires CT::Integer<RHST>;

   /// Returns the right-shift of two integer vectors                         
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator >> (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires CT::Integer<LHST, RHST>;

   template<TARGS(LHS), CT::Integer N>
   NOD() auto operator >> (const TVEC(LHS)&, const N&) noexcept requires CT::Integer<LHST>;

   template<TARGS(RHS), CT::Integer N>
   NOD() auto operator >> (const N&, const TVEC(RHS)&) noexcept requires CT::Integer<RHST>;

   /// Returns the xor of two integer vectors                                 
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator ^ (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires CT::Integer<LHST, RHST>;

   template<TARGS(LHS), CT::Integer N>
   NOD() auto operator ^ (const TVEC(LHS)&, const N&) noexcept requires CT::Integer<LHST>;

   template<TARGS(RHS), CT::Integer N>
   NOD() auto operator ^ (const N&, const TVEC(RHS)&) noexcept requires CT::Integer<RHST>;


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator += (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator += (TVEC(LHS)&, const N&) noexcept;

   /// Subtract                                                               
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator -= (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator -= (TVEC(LHS)&, const N&) noexcept;

   /// Multiply                                                               
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator *= (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator *= (TVEC(LHS)&, const N&) noexcept;

   /// Divide                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator /= (TVEC(LHS)&, const TVEC(RHS)&);

   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator /= (TVEC(LHS)&, const N&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator < (const TVEC(LHS)&, const TVEC(RHS)&);

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator < (const TVEC(LHS)&, const N&);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator < (const N&, const TVEC(RHS)&);

   /// Bigger                                                                 
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator > (const TVEC(LHS)&, const TVEC(RHS)&);

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator > (const TVEC(LHS)&, const N&);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator > (const N&, const TVEC(RHS)&);

   /// Bigger or equal                                                        
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator >= (const TVEC(LHS)&, const TVEC(RHS)&);

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator >= (const TVEC(LHS)&, const N&);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator >= (const N&, const TVEC(RHS)&);

   /// Smaller or equal                                                       
   template<TARGS(LHS), TARGS(RHS)>
   NOD() auto operator <= (const TVEC(LHS)&, const TVEC(RHS)&);

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() auto operator <= (const TVEC(LHS)&, const N&);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() auto operator <= (const N&, const TVEC(RHS)&);

   /// Equal                                                                  
   template<TARGS(LHS), TARGS(RHS)>
   NOD() bool operator == (const TVEC(LHS)&, const TVEC(RHS)&);

   template<TARGS(LHS), CT::DenseNumber N>
   NOD() bool operator == (const TVEC(LHS)&, const N&);

   template<TARGS(RHS), CT::DenseNumber N>
   NOD() bool operator == (const N&, const TVEC(RHS)&);


   ///                                                                        
   /// Cardinal vectors                                                       
   ///                                                                        
   namespace Cardinal
   {

      /// Canonical world origin                                              
      template<CT::DenseNumber T = Real>
      constexpr TVector<T, 4> Origin {0, 0, 0, 0};

      /// Canonical forward vector, pointing towards the screen, positive Z   
      template<CT::DenseNumber T = Real>
      constexpr TVector<T, 4> Forward {0, 0, 1, 0};

      /// Canonical backward vector, pointing towards user, in negative Z     
      template<CT::DenseNumber T = Real>
      constexpr TVector<T, 4> Backward {0, 0, -1, 0};

      /// Canonical up vector, pointing from the ground up, in positive Y     
      template<CT::DenseNumber T = Real>
      constexpr TVector<T, 4> Up {0, 1, 0, 0};

      /// Canonical down vector, pointing in gravity's direction, negative Y  
      template<CT::DenseNumber T = Real>
      constexpr TVector<T, 4> Down {0, -1, 0, 0};

      /// Canonical right vector, pointing to right hand, positive X          
      template<CT::DenseNumber T = Real>
      constexpr TVector<T, 4> Right {1, 0, 0, 0};

      /// Canonical left vector, pointing to left hand, negative X            
      template<CT::DenseNumber T = Real>
      constexpr TVector<T, 4> Left {-1, 0, 0, 0};

   } // Langulus::Math::Cardinal

} // namespace Langulus::Math

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME

#include "TVector.inl"
