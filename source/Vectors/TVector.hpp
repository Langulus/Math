///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Functions/Arithmetics.hpp"
#include "../Functions/Trigonometry.hpp"
#include "../Numbers/TNumber.hpp"
#include "../Dimensions.hpp"

#define TARGS(a) CT::DenseNumber a##T, Count a##S, int a##D
#define TVEC(a) TVector<a##T, a##S, a##D>
#define TEMPLATE() template<CT::DenseNumber T, Count S, int DEFAULT>
#define TME() TVector<T, S, DEFAULT>

namespace Langulus::Math
{

   template<CT::DenseNumber T, CT::Dimension D>
   struct TVectorComponent;

   template<CT::DenseNumber T, Count C, int DEFAULT = 0>
   struct TVector;

   template<CT::Vector> struct TForce;
   template<CT::Vector> struct TNormal;
   template<CT::ScalarOrVector> struct TSampler;
   template<CT::ScalarOrVector> struct TSize;

   using vec1 = TVector<Real, 1>;
   using vec1f = TVector<Float, 1>;
   using vec1d = TVector<Double, 1>;
   using vec1i = TVector<signed, 1>;
   using vec1u = TVector<unsigned, 1>;
   using vec1i8 = TVector<::std::int8_t, 1>;
   using vec1u8 = TVector<uint8, 1>;
   using vec1i16 = TVector<::std::int16_t, 1>;
   using vec1u16 = TVector<::std::uint16_t, 1>;
   using vec1i32 = TVector<::std::int32_t, 1>;
   using vec1u32 = TVector<::std::uint32_t, 1>;
   using vec1i64 = TVector<::std::int64_t, 1>;
   using vec1u64 = TVector<::std::uint64_t, 1>;

   using vec2 = TVector<Real, 2>;
   using vec2f = TVector<Float, 2>;
   using vec2d = TVector<Double, 2>;
   using vec2i = TVector<signed, 2>;
   using vec2u = TVector<unsigned, 2>;
   using vec2i8 = TVector<::std::int8_t, 2>;
   using vec2u8 = TVector<uint8, 2>;
   using vec2i16 = TVector<::std::int16_t, 2>;
   using vec2u16 = TVector<::std::uint16_t, 2>;
   using vec2i32 = TVector<::std::int32_t, 2>;
   using vec2u32 = TVector<::std::uint32_t, 2>;
   using vec2i64 = TVector<::std::int64_t, 2>;
   using vec2u64 = TVector<::std::uint64_t, 2>;

   using vec3 = TVector<Real, 3>;
   using vec3f = TVector<Float, 3>;
   using vec3d = TVector<Double, 3>;
   using vec3i = TVector<signed, 3>;
   using vec3u = TVector<unsigned, 3>;
   using vec3i8 = TVector<::std::int8_t, 3>;
   using vec3u8 = TVector<uint8, 3>;
   using vec3i16 = TVector<::std::int16_t, 3>;
   using vec3u16 = TVector<::std::uint16_t, 3>;
   using vec3i32 = TVector<::std::int32_t, 3>;
   using vec3u32 = TVector<::std::uint32_t, 3>;
   using vec3i64 = TVector<::std::int64_t, 3>;
   using vec3u64 = TVector<::std::uint64_t, 3>;

   using vec4 = TVector<Real, 4>;
   using vec4f = TVector<Float, 4>;
   using vec4d = TVector<Double, 4>;
   using vec4i = TVector<signed, 4>;
   using vec4u = TVector<unsigned, 4>;
   using vec4i8 = TVector<::std::int8_t, 4>;
   using vec4u8 = TVector<uint8, 4>;
   using vec4i16 = TVector<::std::int16_t, 4>;
   using vec4u16 = TVector<::std::uint16_t, 4>;
   using vec4i32 = TVector<::std::int32_t, 4>;
   using vec4u32 = TVector<::std::uint32_t, 4>;
   using vec4i64 = TVector<::std::int64_t, 4>;
   using vec4u64 = TVector<::std::uint64_t, 4>;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as a    
   /// vector                                                                 
   struct Vector {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::vec4;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// vector of the same size                                                
   template<Count S>
   struct VectorOfSize : public Vector {
      LANGULUS(CONCRETE) Math::TVector<Langulus::Real, S>;
      LANGULUS_BASES(Vector);
      static constexpr Count MemberCount {S};
      static_assert(S > 0, "Vector size must be greater than zero");
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// vector of the same type                                                
   template<CT::DenseNumber T>
   struct VectorOfType : public Vector {
      LANGULUS(CONCRETE) Math::TVector<T, 4>;
      LANGULUS_BASES(Vector);
      using MemberType = T;
   };

} // namespace Langulus::A

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
      using MemberType = T;
      static constexpr Count MemberCount = S;
      static constexpr T DefaultMember {static_cast<T>(DEFAULT)};
      template<CT::DenseNumber N>
      static constexpr bool IsCompatible = CT::Convertible<N, T>;

      T mArray[S];

      static constexpr Token GenerateClassName() noexcept;
      LANGULUS(NAME) GenerateClassName();
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) DEFAULT == 0;
      LANGULUS_BASES(A::VectorOfSize<S>, A::VectorOfType<T>, T);

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
      #define PC_VSWIZZLE(name, ...) \
         NOD() decltype(auto) name() noexcept requires (SwzRequirements<__VA_ARGS__>) { \
            return Swz<__VA_ARGS__>(); \
         } \
         NOD() decltype(auto) name() const noexcept requires (SwzRequirements<__VA_ARGS__>) { \
            return Swz<__VA_ARGS__>(); \
         }

      /// 1D Swizzlers                                                        
      PC_VSWIZZLE(x, 0U)
      PC_VSWIZZLE(y, 1U)
      PC_VSWIZZLE(z, 2U)
      PC_VSWIZZLE(w, 3U)

      /// 2D Swizzlers                                                        
      #define PC_VSWIZZLE2(name, ...) \
         PC_VSWIZZLE(x##name, 0U, __VA_ARGS__)\
         PC_VSWIZZLE(y##name, 1U, __VA_ARGS__)\
         PC_VSWIZZLE(z##name, 2U, __VA_ARGS__)\
         PC_VSWIZZLE(w##name, 3U, __VA_ARGS__)

      PC_VSWIZZLE2(x, 0U)
      PC_VSWIZZLE2(y, 1U)
      PC_VSWIZZLE2(z, 2U)
      PC_VSWIZZLE2(w, 3U)

      /// 3D Swizzlers                                                        
      #define PC_VSWIZZLE3(name, ...) \
         PC_VSWIZZLE2(x##name, 0U, __VA_ARGS__)\
         PC_VSWIZZLE2(y##name, 1U, __VA_ARGS__)\
         PC_VSWIZZLE2(z##name, 2U, __VA_ARGS__)\
         PC_VSWIZZLE2(w##name, 3U, __VA_ARGS__)

      PC_VSWIZZLE3(x, 0U)
      PC_VSWIZZLE3(y, 1U)
      PC_VSWIZZLE3(z, 2U)
      PC_VSWIZZLE3(w, 3U)

      /// 4D Swizzlers                                                        
      #define PC_VSWIZZLE4(name, ...) \
         PC_VSWIZZLE3(x##name, 0U, __VA_ARGS__)\
         PC_VSWIZZLE3(y##name, 1U, __VA_ARGS__)\
         PC_VSWIZZLE3(z##name, 2U, __VA_ARGS__)\
         PC_VSWIZZLE3(w##name, 3U, __VA_ARGS__)

      PC_VSWIZZLE4(x, 0U)
      PC_VSWIZZLE4(y, 1U)
      PC_VSWIZZLE4(z, 2U)
      PC_VSWIZZLE4(w, 3U)


      template<class AS, bool NORMALIZE = CT::Real<AS> && !CT::Real<T>>
      NOD() constexpr TVector<AS, S> AsCast() const noexcept;
      template<Count = Math::Min(S, 3)>
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
      class TProxyVector : public TVector<VT, sizeof...(I), VD> {
      LANGULUS(UNINSERTABLE) true;
      private:
         using Base = TVector<VT, sizeof...(I), VD>;
         using Base::mArray;

         TVEC(V)& mSource;

      private:
         /// Commit the changes                                               
         template<Offset FROM, Offset TO, Offset... TAIL>
         void Commit() noexcept {
            mSource.mArray[TO] = mArray[FROM];
            if constexpr (sizeof...(TAIL))
               Commit<FROM + 1, TAIL...>();
         }

      public:
         TProxyVector() = delete;
         TProxyVector(const TProxyVector&) = delete;
         TProxyVector(TProxyVector&&) = delete;

         TProxyVector(TVEC(V)& source) noexcept
            : mSource {source} {}

         ~TProxyVector() noexcept {
            Commit<0, I...>();
         }
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
      template<CT::DenseNumber T>
      constexpr TVector<T, 4> Origin {0, 0, 0, 0};

      /// Canonical forward vector, pointing towards the screen, positive Z   
      template<CT::DenseNumber T>
      constexpr TVector<T, 4> Forward {0, 0, 1, 0};

      /// Canonical backward vector, pointing towards user, in negative Z     
      template<CT::DenseNumber T>
      constexpr TVector<T, 4> Backward {0, 0, -1, 0};

      /// Canonical up vector, pointing from the ground up, in positive Y     
      template<CT::DenseNumber T>
      constexpr TVector<T, 4> Up {0, 1, 0, 0};

      /// Canonical down vector, pointing in gravity's direction, negative Y  
      template<CT::DenseNumber T>
      constexpr TVector<T, 4> Down {0, -1, 0, 0};

      /// Canonical right vector, pointing to right hand, positive X          
      template<CT::DenseNumber T>
      constexpr TVector<T, 4> Right {1, 0, 0, 0};

      /// Canonical left vector, pointing to left hand, negative X            
      template<CT::DenseNumber T>
      constexpr TVector<T, 4> Left {-1, 0, 0, 0};

   } // Langulus::Math::Cardinal

} // namespace Langulus::Math

#include "TVector.inl"

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME
