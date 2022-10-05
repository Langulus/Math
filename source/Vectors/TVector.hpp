///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Numbers/TVectorComponent.hpp"
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

	namespace A
	{

		///																							
		/// An abstract vector																	
		/// Used as an imposed base for any type that can be interpretable as a	
		/// vector																					
		///																							
		struct Vector {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) vec4;
		};

		///																							
		/// An abstract vector of specific size											
		/// Used as an imposed base for any type that can be interpretable as a	
		/// vector of the same size															
		///																							
		template<Count S>
		struct VectorOfSize : public Vector {
			LANGULUS(CONCRETE) TVector<Real, S>;
			LANGULUS_BASES(Vector);
			static constexpr Count MemberCount {S};
			static_assert(S > 0, "Vector size must be greater than zero");
		};

		///																							
		/// An abstract vector of specific type											
		/// Used as an imposed base for any type that can be interpretable as a	
		/// vector of the same type															
		///																							
		template<CT::DenseNumber T>
		struct VectorOfType : public Vector {
			LANGULUS(CONCRETE) TVector<T, 4>;
			LANGULUS_BASES(Vector);
			using MemberType = T;
		};

	} // namespace Langulus::Math::A


	/// See my thread here:																		
	/// https://stackoverflow.com/questions/56585548/									
	#define LANGULUS_CONDITIONAL_MEMBER(CONDITION, TYPE, NAME) \
		[[no_unique_address]] Conditional<(CONDITION), TYPE, decltype([]{})> NAME;


	///																								
	///	Templated vector																		
	///																								
	///	This is a multipurpose vector that is used in numerous places, such	
	/// as: primitives, colors, forces, scalers, normals, samplers, etc...		
	///	This vector template is designed to be mostly similar to GLSL			
	/// vectors. When swizzling, the template returns a similar vector with T	
	/// being a pointer (a so called proxy vector), in order to implement		
	/// swizzling. Proxy vectors eventually decay into conventional vectors.	
	///																								
	#pragma pack(push, 1)
	template<CT::DenseNumber T, Count S>
	class TVector {
	public:
		LANGULUS(POD) true;
		LANGULUS(NULLIFIABLE) true;
		LANGULUS_BASES(A::VectorOfSize<S>, A::VectorOfType<T>);

		static_assert(S >= 1, "Can't have a vector of zero size");
		using MemberType = T;
		static constexpr Count MemberCount = S;
		template<CT::DenseNumber N>
		static constexpr bool IsCompatible = CT::Convertible<N, T>;

		union {
			// Array representation														
			T mArray[S] = {};

			struct {
				// xyzw-tail representation											
				T x;
				LANGULUS_CONDITIONAL_MEMBER(S > 1, T, y);
				LANGULUS_CONDITIONAL_MEMBER(S > 2, T, z);
				LANGULUS_CONDITIONAL_MEMBER(S > 3, T, w);
			};

			struct {
				// uvst representation													
				T u;
				LANGULUS_CONDITIONAL_MEMBER(S > 1, T, v);
				LANGULUS_CONDITIONAL_MEMBER(S > 2, T, s);
				LANGULUS_CONDITIONAL_MEMBER(S > 3, T, t);
			};

			struct {
				// rgba representation													
				T r;
				LANGULUS_CONDITIONAL_MEMBER(S > 1, T, g);
				LANGULUS_CONDITIONAL_MEMBER(S > 2, T, b);
				LANGULUS_CONDITIONAL_MEMBER(S > 3, T, a);
			};
		};

	public:
		constexpr TVector() noexcept = default;

		template<CT::DenseNumber ALTT, Count ALTS>
		constexpr TVector(const TVector<ALTT, ALTS>&) noexcept;

		template<class HEAD, class... TAIL>
		constexpr TVector(const HEAD&, const TAIL&...) noexcept requires (S > 1 && sizeof...(TAIL) > 0);

		template<CT::DenseNumber N>
		constexpr TVector(const N&) noexcept requires IsCompatible<N>;

		template<CT::SparseNumber N>
		constexpr TVector(Deref<N>) noexcept requires IsCompatible<Decay<N>>;

		template<CT::Array N>
		constexpr TVector(const N&) noexcept requires IsCompatible<Decay<N>>;

		template<CT::DenseNumber N, CT::Dimension D>
		constexpr TVector(const TVectorComponent<N, D>&) noexcept;

		template<CT::DenseNumber ALTT, Count ALTS, ALTT DEFAULT>
		constexpr void Initialize(const TVector<ALTT, ALTS>&) noexcept;

		void WriteBody(Flow::Code&) const;

		NOD() explicit operator Flow::Code() const;

		template<CT::DenseNumber N>
		NOD() constexpr decltype(auto) Adapt(const N&) const noexcept requires IsCompatible<N>;


		///																							
		///	Access																				
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

		template<Offset... I>
		NOD() auto Swz() noexcept;
		template<Offset... I>
		NOD() constexpr auto Swz() const noexcept;

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
		/*PC_VSWIZZLE(x, 0U)
		PC_VSWIZZLE(y, 1U)
		PC_VSWIZZLE(z, 2U)
		PC_VSWIZZLE(w, 3U)*/

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
		template<Count = Min(S, 3)>
		NOD() constexpr auto Volume() const noexcept;


		///																							
		///	Compare																				
		///																							
		template<CT::DenseNumber N>
		constexpr auto& operator = (const N&) noexcept;

		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		constexpr auto& operator = (const TVector<ALTT, ALTS>&) noexcept;

		template<CT::DenseNumber N, CT::Dimension D>
		constexpr auto& operator = (const TVectorComponent<N, D>&) noexcept;

		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		NOD() constexpr T Dot(const TVector<ALTT, ALTS>&) const noexcept;

		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		NOD() constexpr TVector<T, 3> Cross(const TVector<ALTT, ALTS>&) const noexcept requires (S >= 3 && ALTS >= 3);

		NOD() constexpr auto Normalize() const requires (S > 1);

		template<CT::DenseNumber ALTT1 = T, Count ALTS1 = S, CT::DenseNumber ALTT2 = T, Count ALTS2 = S>
		NOD() constexpr auto Clamp(const TVector<ALTT1, ALTS1>&, const TVector<ALTT2, ALTS2>&) const noexcept;
		template<CT::DenseNumber ALTT1 = T, Count ALTS1 = S, CT::DenseNumber ALTT2 = T, Count ALTS2 = S>
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
		NOD() constexpr auto Warp(const T&) const noexcept;

		NOD() static constexpr TVector Max() noexcept;
		NOD() constexpr auto Max(const T&) const noexcept;
		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		NOD() constexpr auto Max(const TVector<ALTT, ALTS>&) const noexcept;
		NOD() constexpr auto HMax() const noexcept;

		NOD() static constexpr TVector Min() noexcept;
		NOD() constexpr auto Min(const T&) const noexcept;
		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		NOD() constexpr auto Min(const TVector<ALTT, ALTS>&) const noexcept;
		NOD() constexpr auto HMin() const noexcept;

		NOD() constexpr auto HSum() const noexcept;
		NOD() constexpr auto HMul() const noexcept;

		NOD() constexpr auto Mod(const T&) const noexcept;
		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		NOD() constexpr auto Mod(const TVector<ALTT, ALTS>&) const noexcept;

		NOD() constexpr auto Step(const T&) const noexcept;
		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		NOD() constexpr auto Step(const TVector<ALTT, ALTS>&) const noexcept;

		NOD() constexpr auto Pow(const T&) const noexcept;
		template<CT::DenseNumber ALTT = T, Count ALTS = S>
		NOD() constexpr auto Pow(const TVector<ALTT, ALTS>&) const noexcept;

		auto& Sort() noexcept;

		NOD() constexpr operator T& () noexcept requires (S == 1);
		NOD() constexpr operator const T& () const noexcept requires (S == 1);

		template<CT::DenseNumber N>
		NOD() explicit constexpr operator N () const noexcept requires (S == 1 && IsCompatible<N>);
	};
	#pragma pack(pop)

	namespace Inner
	{

		///																							
		///	Swizzled vector, intermediate type											
		///																							
		/// Creates a shuffled representation of a source vector, and commits	
		/// any changes to it upon destruction												
		template<CT::DenseNumber T, Count S, Offset... I>
		class TProxyVector : public TVector<T, sizeof...(I)> {
		LANGULUS(UNINSERTABLE) true;
		private:
			using Base = TVector<T, sizeof...(I)>;
			using Base::mArray;

			TVector<T, S>& mSource;

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

			TProxyVector(TVector<T,S>& source) noexcept
				: mSource {source} {}

			~TProxyVector() noexcept {
				Commit<0, I...>();
			}
		};

	} // namespace Inner


	///																								
	///	Operations																				
	///																								
	#define TARGS(a) CT::DenseNumber a##T, Count a##S
	#define TVEC(a) TVector<a##T, a##S>
	#define TEMPLATE() template<CT::DenseNumber T, Count S>
	#define TME() TVector<T, S>

	/// Returns an inverted vector															
	template<TARGS(RHS)>
	NOD() auto operator - (const TVEC(RHS)&) noexcept;

	/// Returns the sum of two vectors														
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator + (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), class N>
	NOD() auto operator + (const TVEC(LHS)&, const N&) noexcept;

	template<TARGS(RHS), class N>
	NOD() auto operator + (const N&, const TVEC(RHS)&) noexcept;

	/// Returns the difference of two vectors												
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator - (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), class N>
	NOD() auto operator - (const TVEC(LHS)&, const N&) noexcept;

	template<TARGS(RHS), class N>
	NOD() auto operator - (const N&, const TVEC(RHS)&) noexcept;

	/// Returns the product of two vectors													
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator * (const TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), class N>
	NOD() auto operator * (const TVEC(LHS)&, const N&) noexcept;

	template<TARGS(RHS), class N>
	NOD() auto operator * (const N&, const TVEC(RHS)&) noexcept;

	/// Returns the division of two vectors												
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator / (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), class N>
	NOD() auto operator / (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), class N>
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
	///	Mutators																					
	///																								
	/// Add																							
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator += (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator += (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires CT::Sparse<LHST>;

	template<TARGS(LHS), class N>
	auto& operator += (TVEC(LHS)&, const N&) noexcept;

	template<TARGS(LHS), class N>
	auto& operator += (const TVEC(LHS)&, const N&) noexcept requires CT::Sparse<LHST>;

	/// Subtract																					
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator -= (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator -= (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires CT::Sparse<LHST>;

	template<TARGS(LHS), class N>
	auto& operator -= (TVEC(LHS)&, const N&) noexcept;

	template<TARGS(LHS), class N>
	auto& operator -= (const TVEC(LHS)&, const N&) noexcept requires CT::Sparse<LHST>;

	/// Multiply																					
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator *= (TVEC(LHS)&, const TVEC(RHS)&) noexcept;

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator *= (const TVEC(LHS)&, const TVEC(RHS)&) noexcept requires CT::Sparse<LHST>;

	template<TARGS(LHS), class N>
	auto& operator *= (TVEC(LHS)&, const N&) noexcept;

	template<TARGS(LHS), class N>
	auto& operator *= (const TVEC(LHS)&, const N&) noexcept requires CT::Sparse<LHST>;

	/// Divide																						
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator /= (TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), TARGS(RHS)>
	auto& operator /= (const TVEC(LHS)&, const TVEC(RHS)&) requires CT::Sparse<LHST>;

	template<TARGS(LHS), class N>
	auto& operator /= (TVEC(LHS)&, const N&);

	template<TARGS(LHS), class N>
	auto& operator /= (const TVEC(LHS)&, const N&) requires CT::Sparse<LHST>;


	///																								
	///	Comparing																				
	///																								
	/// Smaller																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator < (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), class N>
	NOD() auto operator < (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), class N>
	NOD() auto operator < (const N&, const TVEC(RHS)&);

	/// Bigger																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator > (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), class N>
	NOD() auto operator > (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), class N>
	NOD() auto operator > (const N&, const TVEC(RHS)&);

	/// Bigger or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator >= (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), class N>
	NOD() auto operator >= (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), class N>
	NOD() auto operator >= (const N&, const TVEC(RHS)&);

	/// Smaller or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator <= (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), class N>
	NOD() auto operator <= (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), class N>
	NOD() auto operator <= (const N&, const TVEC(RHS)&);

	/// Equal																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator == (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), class N>
	NOD() auto operator == (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), class N>
	NOD() auto operator == (const N&, const TVEC(RHS)&);

	/// Not equal																					
	template<TARGS(LHS), TARGS(RHS)>
	NOD() auto operator != (const TVEC(LHS)&, const TVEC(RHS)&);

	template<TARGS(LHS), class N>
	NOD() auto operator != (const TVEC(LHS)&, const N&);

	template<TARGS(RHS), class N>
	NOD() auto operator != (const N&, const TVEC(RHS)&);

} // namespace Langulus::Math

#include "TVector.inl"

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME
