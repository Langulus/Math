///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TVectorComponent.hpp"
#include "../TGradient.hpp"

/*LANGULUS_DECLARE_TRAIT(Position, "Position trait");
LANGULUS_DECLARE_TRAIT(Velocity, "Velocity trait");
LANGULUS_DECLARE_TRAIT(Acceleration, "Acceleration trait");*/

namespace Langulus::Math
{

	template<CT::Vector> class TForce;
	template<CT::Vector> class TNormal;
	template<CT::Vector> class TSampler;
	template<CT::Vector> class TSizer;


	/// An abstract vector of specific size												
	/// Used as a common base for any type that can be interpretable as a		
	/// vector of the same size																
	template<pcptr S>
	struct EMPTY_BASE() TSizedVector {
		static constexpr pcptr MemberCount = S;
		static_assert(S > 0, "Vector size must be greater than zero");
		REFLECT_MANUALLY(TSizedVector);
	};

	/// An abstract vector of specific type												
	/// Used as a common base for any type that can be interpretable as a		
	/// vector of the same type																
	template<Number T>
	struct EMPTY_BASE() TTypedVector {
		using MemberType = T;
		REFLECT_MANUALLY(TTypedVector);
	};


	///																								
	///	Templated vector																		
	///																								
	/// This vector template is designed to be mostly similar to GLSL vectors	
	/// When swizzling, the template returns a similar vector with T being a	
	/// pointer (a so called proxy vector), in order to implement swizzling.	
	/// Proxy vectors eventually decay into conventional vectors.					
	///																								
	/// This is a multipurpose vector that is used in numerous places, such		
	/// as: primitives, colors, forces, scalers, normals, samplers, etc...		
	///																								
#pragma pack(push, 1)
	template<Number T, pcptr S>
	class EMPTY_BASE() TVector 
		: AVector
		, TSizedVector<S>
		, TTypedVector<pcDecay<T>>
		, POD, NULLIFIABLE {
	public:
		using DenseT = pcDecay<T>;
		using DenseME = TVector<DenseT, S>;
		using MemberType = DenseT;

		static constexpr pcptr MemberCount = S;
		static constexpr bool SparseVector = Sparse<T>;
		static constexpr bool DenseVector = Dense<T>;

		T mArray[MemberCount] = {};

	public:
		REFLECT_MANUALLY(TVector);

		///																							
		///	Construction																		
		///																							
		constexpr TVector() noexcept = default;

		template<Number ALTT, pcptr ALTS>
		constexpr TVector(const TVector<ALTT, ALTS>&) noexcept;

		template<class HEAD, class... TAIL>
		constexpr TVector(const HEAD&, const TAIL&...) noexcept requires (S > 1 && sizeof...(TAIL) > 0);

		template<class N>
		constexpr TVector(const N&) noexcept requires Convertible<pcDecay<N>, pcDecay<T>>;

		template<Number N, Dimension IDX>
		constexpr TVector(const TVectorComponent<N, IDX>&) noexcept requires (pcptr(IDX) < S);

		template<Number ALTT, pcptr ALTS, ALTT DEFAULT>
		constexpr void Initialize(const TVector<ALTT, ALTS>&) noexcept;

		void WriteBody(GASM&) const;

		NOD() explicit operator GASM() const;

		template<class N>
		NOD() constexpr decltype(auto) Adapt(const N&) const noexcept requires Convertible<pcDecay<N>, pcDecay<T>>;

		///																							
		///	Access																				
		///																							
		NOD() constexpr decltype(auto) Get(pcptr) const noexcept;

		template<pcptr I>
		NOD() constexpr decltype(auto) GetIdx() const noexcept requires (I < S);

		NOD() constexpr decltype(auto) operator [] (pcptr) noexcept;
		NOD() constexpr decltype(auto) operator [] (pcptr) const noexcept;

		NOD() constexpr auto GetRaw() const noexcept;
		NOD() constexpr auto GetRaw() noexcept;
		NOD() constexpr auto GetCount() const noexcept;
		NOD() constexpr auto GetCount() noexcept;

		PC_RANGED_FOR_INTEGRATION(T, GetRaw(), GetCount())

		NOD() constexpr auto operator () () noexcept requires DenseVector;
		NOD() constexpr auto operator () () const noexcept requires DenseVector;

		NOD() constexpr auto LengthSquared() const noexcept;
		NOD() constexpr auto Length() const noexcept;

		NOD() constexpr bool IsDegenerate() const noexcept;

		template <pcptr... I>
		NOD() constexpr decltype(auto) Swz() noexcept;

		template <pcptr... I>
		NOD() constexpr decltype(auto) Swz() const noexcept;

		template <pcptr... I>
		static constexpr bool SwzRequirements = S > pcMax(0U, I...);

		/// Generate all combinations of all swizzle functions up to 4D			
		#define PC_VSWIZZLE(name, ...) \
			NOD() decltype(auto) name() noexcept requires (SwzRequirements<__VA_ARGS__>) { return Swz<__VA_ARGS__>(); }\
			NOD() decltype(auto) name() const noexcept requires (SwzRequirements<__VA_ARGS__>) { return Swz<__VA_ARGS__>(); }

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


		NOD() constexpr decltype(auto) Real() const noexcept;
		NOD() constexpr auto Volume() const noexcept;

		///																							
		///	Compare																				
		///																							
		template<Number N>
		constexpr auto& operator = (const N&) noexcept;

		template<Number ALTT = T, pcptr ALTS = S>
		constexpr auto& operator = (const TVector<ALTT, ALTS>&) noexcept;

		template<Number N, Dimension IDX>
		constexpr auto& operator = (const TVectorComponent<N, IDX>&) noexcept requires (pcptr(IDX) < S);

		template<Number ALTT = T, pcptr ALTS = S>
		NOD() constexpr auto Dot(const TVector<ALTT, ALTS>&) const noexcept;

		template<Number N>
		NOD() constexpr auto Dot(const N&) const noexcept;

		template<Number ALTT = T, pcptr ALTS = S>
		NOD() constexpr auto Cross(const TVector<ALTT, ALTS>&) const noexcept requires (S > 2 && ALTS > 2);

		NOD() constexpr auto Normalize() const requires (S > 1);

		template<Number ALTT1 = T, pcptr ALTS1 = S, Number ALTT2 = T, pcptr ALTS2 = S>
		NOD() constexpr auto Clamp(const TVector<ALTT1, ALTS1>&, const TVector<ALTT2, ALTS2>&) const noexcept;
		template<Number ALTT1 = T, pcptr ALTS1 = S, Number ALTT2 = T, pcptr ALTS2 = S>
		NOD() constexpr auto ClampRev(const TVector<ALTT1, ALTS1>&, const TVector<ALTT2, ALTS2>&) const noexcept;

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
		NOD() constexpr auto Warp(const DenseT&) const noexcept;

		NOD() static constexpr ME Max() noexcept;
		NOD() constexpr auto Max(const DenseT&) const noexcept;
		template<Number ALTT = T, pcptr ALTS = S>
		NOD() constexpr auto Max(const TVector<ALTT, ALTS>&) const noexcept;
		NOD() constexpr auto HMax() const noexcept;

		NOD() static constexpr ME Min() noexcept;
		NOD() constexpr auto Min(const DenseT&) const noexcept;
		template<Number ALTT = T, pcptr ALTS = S>
		NOD() constexpr auto Min(const TVector<ALTT, ALTS>&) const noexcept;
		NOD() constexpr auto HMin() const noexcept;

		NOD() constexpr auto HSum() const noexcept;
		NOD() constexpr auto HMul() const noexcept;

		NOD() constexpr auto Mod(const DenseT&) const noexcept;
		template<Number ALTT = T, pcptr ALTS = S>
		NOD() constexpr auto Mod(const TVector<ALTT, ALTS>&) const noexcept;

		NOD() constexpr auto Step(const DenseT&) const noexcept;
		template<Number ALTT = T, pcptr ALTS = S>
		NOD() constexpr auto Step(const TVector<ALTT, ALTS>&) const noexcept;

		NOD() constexpr auto Pow(const DenseT&) const noexcept;
		template<Number ALTT = T, pcptr ALTS = S>
		NOD() constexpr auto Pow(const TVector<ALTT, ALTS>&) const noexcept;

		auto& Sort() noexcept;

		NOD() constexpr operator DenseME () const noexcept requires SparseVector;
		NOD() constexpr operator const DenseT& () const noexcept requires (S == 1);
		NOD() constexpr operator DenseT& () noexcept requires (S == 1);
		template<Number N>
		NOD() explicit constexpr operator N () const noexcept requires (S == 1);
	};
	#pragma pack(pop)

	/// Define the AVector here, because it requires vec4 as complete type		
	PC_DEFINE_ABSTRACT_DATA(Vector, "An abstract vector", vec4);


	///																								
	///	Operations																				
	///																								
	#define TARGS(a) Number a##T, pcptr a##S
	#define TVEC(a) TVector<a##T, a##S>
	#define TEMPLATE() template<Number T, pcptr S>
	#define TME() TVector<T, S>

	/// Returns an inverted vector															
	template<TARGS(RHS)>
	NOD() auto operator - (const TVEC(RHS)&) noexcept;

	/// Returns the sum of two vectors														
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator + (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), Number N>
	NOD() auto operator + (const TVEC(LHS)&, const N&) noexcept;

	template<TARGS(RHS), Number N>
	NOD() auto operator + (const N&, const TVEC(RHS)&) noexcept;

	/// Returns the difference of two vectors												
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator - (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), Number N>
	NOD() auto operator - (const TVEC(LHS)&, const N&) noexcept;

	template<TARGS(RHS), Number N>
	NOD() auto operator - (const N&, const TVEC(RHS)&) noexcept;

	/// Returns the product of two vectors													
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator * (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), Number N>
	NOD() auto operator * (const TVEC(LHS)&, const N&) noexcept;

	template<TARGS(RHS), Number N>
	NOD() auto operator * (const N&, const TVEC(RHS)&) noexcept;

	/// Returns the division of two vectors												
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator / (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), Number N>
	NOD() auto operator / (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), Number N>
	NOD() auto operator / (const N&, const TVEC(RHS)&);

	/// Returns the left-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator << (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires IntegerNumber<LHST, RHST>;

	template<TARGS(LHS), IntegerNumber N>
	NOD() auto operator << (const TVEC(LHS)&, const N&) noexcept requires IntegerNumber<LHST>;

	template<TARGS(RHS), IntegerNumber N>
	NOD() auto operator << (const N&, const TVEC(RHS)&) noexcept requires IntegerNumber<RHST>;

	/// Returns the right-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator >> (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires IntegerNumber<LHST, RHST>;

	template<TARGS(LHS), IntegerNumber N>
	NOD() auto operator >> (const TVEC(LHS)&, const N&) noexcept requires IntegerNumber<LHST>;

	template<TARGS(RHS), IntegerNumber N>
	NOD() auto operator >> (const N&, const TVEC(RHS)&) noexcept requires IntegerNumber<RHST>;

	/// Returns the xor of two integer vectors											
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator ^ (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires IntegerNumber<LHST, RHST>;

	template<TARGS(LHS), IntegerNumber N>
	NOD() auto operator ^ (const TVEC(LHS)&, const N&) noexcept requires IntegerNumber<LHST>;

	template<TARGS(RHS), IntegerNumber N>
	NOD() auto operator ^ (const N&, const TVEC(RHS)&) noexcept requires IntegerNumber<RHST>;


	///																								
	///	Mutators																					
	///																								
	/// Add																							
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator += (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator += (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires Sparse<LHST>;

	template<TARGS(LHS), Number N>
	auto& operator += (TVEC(LHS)&, const N&) noexcept;

	template<TARGS(LHS), Number N>
	auto& operator += (const TVEC(LHS)&, const N&) noexcept requires Sparse<LHST>;

	/// Subtract																					
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator -= (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator -= (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires Sparse<LHST>;

	template<TARGS(LHS), Number N>
	auto& operator -= (TVEC(LHS)&, const N&) noexcept;

	template<TARGS(LHS), Number N>
	auto& operator -= (const TVEC(LHS)&, const N&) noexcept requires Sparse<LHST>;

	/// Multiply																					
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator *= (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator *= (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires Sparse<LHST>;

	template<TARGS(LHS), Number N>
	auto& operator *= (TVEC(LHS)&, const N&) noexcept;

	template<TARGS(LHS), Number N>
	auto& operator *= (const TVEC(LHS)&, const N&) noexcept requires Sparse<LHST>;

	/// Divide																						
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator /= (TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator /= (const TVEC(LHS)&, const TVEC(RHS)&) requires Sparse<LHST>;

	template<TARGS(LHS), Number N>
	auto& operator /= (TVEC(LHS)&, const N&);

	template<TARGS(LHS), Number N>
	auto& operator /= (const TVEC(LHS)&, const N&) requires Sparse<LHST>;


	///																								
	///	Comparing																				
	///																								
	/// Smaller																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator < (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), Number N>
	NOD() auto operator < (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), Number N>
	NOD() auto operator < (const N&, const TVEC(RHS)&);

	/// Bigger																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator > (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), Number N>
	NOD() auto operator > (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), Number N>
	NOD() auto operator > (const N&, const TVEC(RHS)&);

	/// Bigger or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator >= (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), Number N>
	NOD() auto operator >= (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), Number N>
	NOD() auto operator >= (const N&, const TVEC(RHS)&);

	/// Smaller or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator <= (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), Number N>
	NOD() auto operator <= (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), Number N>
	NOD() auto operator <= (const N&, const TVEC(RHS)&);

	/// Equal																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator == (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), Number N>
	NOD() auto operator == (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), Number N>
	NOD() auto operator == (const N&, const TVEC(RHS)&);

	/// Not equal																					
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator != (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), Number N>
	NOD() auto operator != (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), Number N>
	NOD() auto operator != (const N&, const TVEC(RHS)&);

} // namespace Langulus::Math

#include "TVector.inl"

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME