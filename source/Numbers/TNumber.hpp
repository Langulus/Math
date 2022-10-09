///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Common.hpp"

namespace Langulus::Math
{

	///																								
	///	Templated number																		
	///																								
	/// Serves various kinds of purposes:													
	///	1. Provides a safety layer, that asserts underflows/overflows			
	///		when building in safe-mode														
	///	2. Provides consistent handling of infinities across all arithmetic	
	///		types																					
	///	3. Allows for types, such as std::int8_t and std::uint8_t to be		
	///		considered CT::Number, without suffering the usual implicit			
	///		conversion-to-text-hell															
	///	4. Gives a layer for integration with langulus flows and verbs			
	///	5. Makes all numbers equivalent to 1D vectors, and thus compatible	
	///		with the CT::Vector concept													
	///																								
	template<CT::Dense T, CT::Dense WRAPPER = T>
	struct TNumber {
		LANGULUS(NUMBER) T;
		LANGULUS(POD) CT::POD<T>;
		LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
		using MemberType = T;
		static constexpr Count MemberCount {1};

		T mValue {};

	public:
		constexpr TNumber() noexcept = default;
		constexpr TNumber(const TNumber&) noexcept = default;
		constexpr TNumber(TNumber&&) noexcept = default;
		constexpr TNumber(const T& a) noexcept
			: mValue {a} {}
		constexpr TNumber(const WRAPPER& a) noexcept requires (!CT::Same<T, WRAPPER>)
			: mValue {a.mValue} {}

		TNumber& operator = (const TNumber&) noexcept = default;
		TNumber& operator = (TNumber&&) noexcept = default;
		TNumber& operator = (const T& a) noexcept {
			mValue = a;
			return *this;
		}
		TNumber& operator = (const WRAPPER& a) noexcept requires (!CT::Same<T, WRAPPER>) {
			mValue = a.mValue;
			return *this;
		}

		constexpr explicit operator const T& () const noexcept {
			return mValue;
		}
		constexpr explicit operator T& () noexcept {
			return mValue;
		}

		//WRAPPER Length() const;
		WRAPPER Sqrt() const;
		WRAPPER Frac() const;
		WRAPPER Mod(const TNumber<T>&) const;
	};

	using uint8 = TNumber<::std::uint8_t>;


	///																								
	///	Operations on numbers																
	///																								
	#define TARGS(a) CT::Dense a##T, CT::Dense a##W
	#define TNUM(a) TNumber<a##T, a##W>
	#define TEMPLATE() template<CT::Dense T, CT::Dense W>
	#define TME() TNumber<T, W>

	/// Returns an inverted number															
	template<TARGS(RHS)>
	NOD() constexpr RHSW operator - (const TNUM(RHS)&) noexcept;

	/// Returns the sum of two numbers														
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr LHSW operator + (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS)>
	NOD() constexpr LHSW operator + (const TNUM(LHS)&, const LHST&) noexcept;

	template<TARGS(RHS)>
	NOD() constexpr RHSW operator + (const RHST&, const TNUM(RHS)&) noexcept;

	/// Returns the difference of two numbers												
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr LHSW operator - (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;
	 
	template<TARGS(LHS)>
	NOD() constexpr LHSW operator - (const TNUM(LHS)&, const LHST&) noexcept;

	template<TARGS(RHS)>
	NOD() constexpr RHSW operator - (const RHST&, const TNUM(RHS)&) noexcept;

	/// Returns the product of two numbers													
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr LHSW operator * (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS)>
	NOD() constexpr LHSW operator * (const TNUM(LHS)&, const LHST&) noexcept;

	template<TARGS(RHS)>
	NOD() constexpr RHSW operator * (const RHST&, const TNUM(RHS)&) noexcept;

	/// Returns the division of two numbers												
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr LHSW operator / (const TNUM(LHS)&, const TNUM(RHS)&) requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS)>
	NOD() constexpr LHSW operator / (const TNUM(LHS)&, const LHST&);

	template<TARGS(RHS)>
	NOD() constexpr RHSW operator / (const RHST&, const TNUM(RHS)&);

	/// Returns the left-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr LHSW operator << (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires (CT::Integer<LHST, RHST> && CT::Same<LHSW, RHSW>);

	template<TARGS(LHS)>
	NOD() constexpr LHSW operator << (const TNUM(LHS)&, const LHST&) noexcept requires (CT::Integer<LHST>);

	template<TARGS(RHS)>
	NOD() constexpr RHSW operator << (const RHST&, const TNUM(RHS)&) noexcept requires (CT::Integer<RHST>);

	/// Returns the right-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr LHSW operator >> (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires (CT::Integer<LHST, RHST>&& CT::Same<LHSW, RHSW>);

	template<TARGS(LHS)>
	NOD() constexpr LHSW operator >> (const TNUM(LHS)&, const LHST&) noexcept requires (CT::Integer<LHST>);

	template<TARGS(RHS)>
	NOD() constexpr RHSW operator >> (const RHST&, const TNUM(RHS)&) noexcept requires (CT::Integer<RHST>);

	/// Returns the xor of two integer vectors											
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr LHSW operator ^ (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires (CT::Integer<LHST, RHST>&& CT::Same<LHSW, RHSW>);

	template<TARGS(LHS)>
	NOD() constexpr LHSW operator ^ (const TNUM(LHS)&, const LHST&) noexcept requires (CT::Integer<LHST>);

	template<TARGS(RHS)>
	NOD() constexpr RHSW operator ^ (const RHST&, const TNUM(RHS)&) noexcept requires (CT::Integer<RHST>);


	///																								
	///	Mutators																					
	///																								
	/// Add																							
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator += (TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS)>
	constexpr LHSW& operator += (TNUM(LHS)&, const LHST&) noexcept;

	/// Subtract																					
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator -= (TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS)>
	constexpr LHSW& operator -= (TNUM(LHS)&, const LHST&) noexcept;

	/// Multiply																					
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator *= (TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS)>
	constexpr LHSW& operator *= (TNUM(LHS)&, const LHST&) noexcept;

	/// Divide																						
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator /= (TNUM(LHS)&, const TNUM(RHS)&) requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS)>
	constexpr LHSW& operator /= (TNUM(LHS)&, const LHST&);


	///																								
	///	Comparing																				
	///																								
	/// Smaller																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr bool operator < (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS), CT::DenseNumber N>
	NOD() constexpr bool operator < (const TNUM(LHS)&, const N&) noexcept;
	template<TARGS(LHS), CT::Character N>
	NOD() constexpr bool operator < (const TNUM(LHS)&, const N&) noexcept;

	template<TARGS(RHS), CT::DenseNumber N>
	NOD() constexpr bool operator < (const N&, const TNUM(RHS)&) noexcept;
	template<TARGS(RHS), CT::Character N>
	NOD() constexpr bool operator < (const N&, const TNUM(RHS)&) noexcept;

	/// Bigger																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr bool operator > (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS), CT::DenseNumber N>
	NOD() constexpr bool operator > (const TNUM(LHS)&, const N&) noexcept;
	template<TARGS(LHS), CT::Character N>
	NOD() constexpr bool operator > (const TNUM(LHS)&, const N&) noexcept;

	template<TARGS(RHS), CT::DenseNumber N>
	NOD() constexpr bool operator > (const N&, const TNUM(RHS)&) noexcept;
	template<TARGS(RHS), CT::Character N>
	NOD() constexpr bool operator > (const N&, const TNUM(RHS)&) noexcept;

	/// Bigger or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr bool operator >= (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS), CT::DenseNumber N>
	NOD() constexpr bool operator >= (const TNUM(LHS)&, const N&) noexcept;
	template<TARGS(LHS), CT::Character N>
	NOD() constexpr bool operator >= (const TNUM(LHS)&, const N&) noexcept;

	template<TARGS(RHS), CT::DenseNumber N>
	NOD() constexpr bool operator >= (const N&, const TNUM(RHS)&) noexcept;
	template<TARGS(RHS), CT::Character N>
	NOD() constexpr bool operator >= (const N&, const TNUM(RHS)&) noexcept;

	/// Smaller or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr bool operator <= (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS), CT::DenseNumber N>
	NOD() constexpr bool operator <= (const TNUM(LHS)&, const N&) noexcept;
	template<TARGS(LHS), CT::Character N>
	NOD() constexpr bool operator <= (const TNUM(LHS)&, const N&) noexcept;

	template<TARGS(RHS), CT::DenseNumber N>
	NOD() constexpr bool operator <= (const N&, const TNUM(RHS)&) noexcept;
	template<TARGS(RHS), CT::Character N>
	NOD() constexpr bool operator <= (const N&, const TNUM(RHS)&) noexcept;

	/// Equal																						
	template<TARGS(LHS), TARGS(RHS)>
	NOD() constexpr bool operator == (const TNUM(LHS)&, const TNUM(RHS)&) noexcept requires CT::Same<LHSW, RHSW>;

	template<TARGS(LHS), CT::DenseNumber N>
	NOD() constexpr bool operator == (const TNUM(LHS)&, const N&) noexcept;
	template<TARGS(LHS), CT::Character N>
	NOD() constexpr bool operator == (const TNUM(LHS)&, const N&) noexcept;

	template<TARGS(RHS), CT::DenseNumber N>
	NOD() constexpr bool operator == (const N&, const TNUM(RHS)&) noexcept;
	template<TARGS(RHS), CT::Character N>
	NOD() constexpr bool operator == (const N&, const TNUM(RHS)&) noexcept;

} // namespace Langulus::Math

#include "TNumber.inl"

#undef TARGS
#undef TNUM
#undef TEMPLATE
#undef TME
