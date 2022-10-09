///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TNumber.hpp"

namespace Langulus::Math
{

	/// Returns an inverted number															
	template<TARGS(RHS)>
	constexpr RHSW operator - (const TNUM(RHS)& a) noexcept {
		return -a.mValue;
	}

	/// Returns the sum of two numbers														
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW operator + (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue + rhs.mValue;
	}

	template<TARGS(LHS)>
	constexpr LHSW operator + (const TNUM(LHS)& lhs, const LHST& rhs) noexcept {
		return lhs.mValue + rhs;
	}

	template<TARGS(RHS)>
	constexpr RHSW operator + (const RHST& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs + rhs.mValue;
	}

	/// Returns the difference of two numbers												
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW operator - (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue - rhs.mValue;
	}
	 
	template<TARGS(LHS)>
	constexpr LHSW operator - (const TNUM(LHS)& lhs, const LHST& rhs) noexcept {
		return lhs.mValue - rhs;
	}

	template<TARGS(RHS)>
	constexpr RHSW operator - (const RHST& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs - rhs.mValue;
	}

	/// Returns the product of two numbers													
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW operator * (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue * rhs.mValue;
	}

	template<TARGS(LHS)>
	constexpr LHSW operator * (const TNUM(LHS)& lhs, const LHST& rhs) noexcept {
		return lhs.mValue * rhs;
	}

	template<TARGS(RHS)>
	constexpr RHSW operator * (const RHST& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs * rhs.mValue;
	}

	/// Returns the division of two numbers												
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW operator / (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) requires CT::Same<LHSW, RHSW> {
		return lhs.mValue / rhs.mValue;
	}

	template<TARGS(LHS)>
	constexpr LHSW operator / (const TNUM(LHS)& lhs, const LHST& rhs) {
		return lhs.mValue / rhs;
	}

	template<TARGS(RHS)>
	constexpr RHSW operator / (const RHST& lhs, const TNUM(RHS)& rhs) {
		return lhs / rhs.mValue;
	}

	/// Returns the left-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW operator << (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST>&& CT::Same<LHSW, RHSW>) {
		return lhs.mValue << rhs.mValue;
	}

	template<TARGS(LHS)>
	constexpr LHSW operator << (const TNUM(LHS)& lhs, const LHST& rhs) noexcept requires (CT::Integer<LHST>) {
		return lhs.mValue << rhs;
	}

	template<TARGS(RHS)>
	constexpr RHSW operator << (const RHST& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<RHST>) {
		return lhs << rhs.mValue;
	}

	/// Returns the right-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW operator >> (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST>&& CT::Same<LHSW, RHSW>) {
		return lhs.mValue >> rhs.mValue;
	}

	template<TARGS(LHS)>
	constexpr LHSW operator >> (const TNUM(LHS)& lhs, const LHST& rhs) noexcept requires (CT::Integer<LHST>) {
		return lhs.mValue >> rhs;
	}

	template<TARGS(RHS)>
	constexpr RHSW operator >> (const RHST& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<RHST>) {
		return lhs >> rhs.mValue;
	}

	/// Returns the xor of two integer vectors											
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW operator ^ (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<LHST, RHST>&& CT::Same<LHSW, RHSW>) {
		return lhs.mValue ^ rhs.mValue;
	}

	template<TARGS(LHS)>
	constexpr LHSW operator ^ (const TNUM(LHS)& lhs, const LHST& rhs) noexcept requires (CT::Integer<LHST>) {
		return lhs.mValue ^ rhs;
	}

	template<TARGS(RHS)>
	constexpr RHSW operator ^ (const RHST& lhs, const TNUM(RHS)& rhs) noexcept requires (CT::Integer<RHST>) {
		return lhs ^ rhs.mValue;
	}


	///																								
	///	Mutators																					
	///																								
	/// Add																							
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator += (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		lhs.mValue += rhs.mValue;
		return reinterpret_cast<LHSW&>(lhs);
	}

	template<TARGS(LHS)>
	constexpr LHSW& operator += (TNUM(LHS)& lhs, const LHST& rhs) noexcept {
		lhs.mValue += rhs;
		return reinterpret_cast<LHSW&>(lhs);
	}

	/// Subtract																					
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator -= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		lhs.mValue -= rhs.mValue;
		return reinterpret_cast<LHSW&>(lhs);
	}

	template<TARGS(LHS)>
	constexpr LHSW& operator -= (TNUM(LHS)& lhs, const LHST& rhs) noexcept {
		lhs.mValue -= rhs;
		return reinterpret_cast<LHSW&>(lhs);
	}

	/// Multiply																					
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator *= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		lhs.mValue *= rhs.mValue;
		return reinterpret_cast<LHSW&>(lhs);
	}

	template<TARGS(LHS)>
	constexpr LHSW& operator *= (TNUM(LHS)& lhs, const LHST& rhs) noexcept {
		lhs.mValue *= rhs;
		return reinterpret_cast<LHSW&>(lhs);
	}

	/// Divide																						
	template<TARGS(LHS), TARGS(RHS)>
	constexpr LHSW& operator /= (TNUM(LHS)& lhs, const TNUM(RHS)& rhs) requires CT::Same<LHSW, RHSW> {
		lhs.mValue /= rhs.mValue;
		return reinterpret_cast<LHSW&>(lhs);
	}

	template<TARGS(LHS)>
	constexpr LHSW& operator /= (TNUM(LHS)& lhs, const LHST& rhs) {
		lhs.mValue /= rhs;
		return reinterpret_cast<LHSW&>(lhs);
	}


	///																								
	///	Comparing																				
	///																								
	/// Smaller																						
	template<TARGS(LHS), TARGS(RHS)>
	constexpr bool operator < (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue < rhs.mValue;
	}

	template<TARGS(LHS), CT::DenseNumber N>
	constexpr bool operator < (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue < rhs;
	}

	template<TARGS(LHS), CT::Character N>
	constexpr bool operator < (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue < rhs;
	}

	template<TARGS(RHS), CT::DenseNumber N>
	constexpr bool operator < (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs < rhs.mValue;
	}

	template<TARGS(RHS), CT::Character N>
	constexpr bool operator < (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs < rhs.mValue;
	}

	/// Bigger																						
	template<TARGS(LHS), TARGS(RHS)>
	constexpr bool operator > (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue > rhs.mValue;
	}

	template<TARGS(LHS), CT::DenseNumber N>
	constexpr bool operator > (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue > rhs;
	}

	template<TARGS(LHS), CT::Character N>
	constexpr bool operator > (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue > rhs;
	}

	template<TARGS(RHS), CT::DenseNumber N>
	constexpr bool operator > (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs > rhs.mValue;
	}

	template<TARGS(RHS), CT::Character N>
	constexpr bool operator > (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs > rhs.mValue;
	}

	/// Bigger or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	constexpr bool operator >= (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue >= rhs.mValue;
	}

	template<TARGS(LHS), CT::DenseNumber N>
	constexpr bool operator >= (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue >= rhs;
	}

	template<TARGS(LHS), CT::Character N>
	constexpr bool operator >= (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue >= rhs;
	}

	template<TARGS(RHS), CT::DenseNumber N>
	constexpr bool operator >= (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs >= rhs.mValue;
	}

	template<TARGS(RHS), CT::Character N>
	constexpr bool operator >= (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs >= rhs.mValue;
	}

	/// Smaller or equal																			
	template<TARGS(LHS), TARGS(RHS)>
	constexpr bool operator <= (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue <= rhs.mValue;
	}

	template<TARGS(LHS), CT::DenseNumber N>
	constexpr bool operator <= (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue <= rhs;
	}

	template<TARGS(LHS), CT::Character N>
	constexpr bool operator <= (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue <= rhs;
	}

	template<TARGS(RHS), CT::DenseNumber N>
	constexpr bool operator <= (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs <= rhs.mValue;
	}

	template<TARGS(RHS), CT::Character N>
	constexpr bool operator <= (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs <= rhs.mValue;
	}

	/// Equal																						
	template<TARGS(LHS), TARGS(RHS)>
	constexpr bool operator == (const TNUM(LHS)& lhs, const TNUM(RHS)& rhs) noexcept requires CT::Same<LHSW, RHSW> {
		return lhs.mValue == rhs.mValue;
	}

	template<TARGS(LHS), CT::DenseNumber N>
	constexpr bool operator == (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue == rhs;
	}

	template<TARGS(LHS), CT::Character N>
	constexpr bool operator == (const TNUM(LHS)& lhs, const N& rhs) noexcept {
		return lhs.mValue == rhs;
	}

	template<TARGS(RHS), CT::DenseNumber N>
	constexpr bool operator == (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs == rhs.mValue;
	}

	template<TARGS(RHS), CT::Character N>
	constexpr bool operator == (const N& lhs, const TNUM(RHS)& rhs) noexcept {
		return lhs == rhs.mValue;
	}

} // namespace Langulus::Math
