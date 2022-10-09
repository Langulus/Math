///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TNumber.hpp"
#include "../Vectors.hpp"
#include "../Dimensions.hpp"

namespace Langulus::CT
{

	template<class T>
	concept Angle = DenseNumber<T> && requires { {Decay<T>::Radians} -> Bool; };

} // namespace Langulus::CT


namespace Langulus::Math
{

	/// Type used for representing angles in degrees									
	template<CT::DenseNumber T>
	struct TDegrees : public TNumber<T, TDegrees<T>> {
		using Base = TNumber<T, TDegrees<T>>;
		using Base::Base;
		using Base::mValue;
		static constexpr bool Radians = false;
	};

	/// Type used for representing angles in radians									
	template<CT::DenseNumber T>
	struct TRadians : public TNumber<T, TRadians<T>> {
		using Base = TNumber<T, TRadians<T>>;
		using Base::Base;
		using Base::mValue;
		static constexpr bool Radians = true;
	};

	using Degrees = TDegrees<Real>;
	using Radians = TRadians<Real>;

	template<CT::Angle T, CT::Dimension D>
	struct TAngle;

	template<CT::Angle T>
	using TYaw = TAngle<T, Traits::Y>;
	template<CT::Angle T>
	using TPitch = TAngle<T, Traits::X>;
	template<CT::Angle T>
	using TRoll = TAngle<T, Traits::Z>;

	using Yawdf = TYaw<TDegrees<RealSP>>;
	using Yawdd = TYaw<TDegrees<RealDP>>;
	using Yawrf = TYaw<TRadians<RealSP>>;
	using Yawrd = TYaw<TRadians<RealDP>>;

	using Pitchdf = TPitch<TDegrees<RealSP>>;
	using Pitchdd = TPitch<TDegrees<RealDP>>;
	using Pitchrf = TPitch<TRadians<RealSP>>;
	using Pitchrd = TPitch<TRadians<RealDP>>;

	using Rolldf = TRoll<TDegrees<RealSP>>;
	using Rolldd = TRoll<TDegrees<RealDP>>;
	using Rollrf = TRoll<TRadians<RealSP>>;
	using Rollrd = TRoll<TRadians<RealDP>>;

	using Yawd = TYaw<Degrees>;
	using Yawr = TYaw<Radians>;
	using Pitchd = TPitch<Degrees>;
	using Pitchr = TPitch<Radians>;
	using Rolld = TRoll<Degrees>;
	using Rollr = TRoll<Radians>;


	namespace A
	{

		/// Used as an imposed base for any type that can be interpretable as	
		/// an angle																				
		struct Angle {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) Radians;
		};

		/// Used as an imposed base for any type that can be interpretable as	
		/// an angle of the same dimension													
		template<CT::Dimension D>
		struct AngleOfDimension : public Angle {
			LANGULUS(CONCRETE) TAngle<Radians, D>;
			LANGULUS_BASES(Angle);
		};

		/// Used as an imposed base for any type that can be interpretable as	
		/// an angle of the same type															
		template<CT::Angle T>
		struct AngleOfType : public Angle {
			LANGULUS(CONCRETE) T;
			LANGULUS_BASES(Angle);
			using MemberType = T;
		};

	} // namespace Langulus::Math::A


	///																								
	///	Templated angle																		
	///																								
	template<CT::Angle T, CT::Dimension D>
	struct TAngle : public T {
		using Dimension = D;
		using T::T;
		using T::mValue;

		NOD() constexpr decltype(auto) GetRadians() const noexcept {
			if constexpr (T::Radians)
				return mValue;
			else
				return DegToRad(mValue);
		}

		NOD() constexpr decltype(auto) GetDegrees() const noexcept {
			if constexpr (T::Radians)
				return RadToDeg(mValue);
			else
				return mValue;
		}

		/// Convert from any angle to text													
		NOD() explicit operator Flow::Code() const {
			Flow::Code result;
			result += MetaOf<TAngle>();
			result += Flow::Code::OpenScope;
			result += Text {mValue};
			result += Flow::Code::CloseScope;
			return result;
		}
	};


	/// Add two similar angles																	
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	NOD() constexpr TAngle<LHST, D> operator + (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
		if constexpr (CT::Same<LHST, RHST>)
			return lhs.mValue + rhs.mValue;
		else if constexpr (LHST::Radians)
			return lhs.mValue + DegToRad(rhs.mValue);
		else 
			return lhs.mValue + RadToDeg(rhs.mValue);
	}

	/// Subtract two similar angles															
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	NOD() constexpr TAngle<LHST, D> operator - (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
		if constexpr (CT::Same<LHST, RHST>)
			return lhs.mValue - rhs.mValue;
		else if constexpr (LHST::Radians)
			return lhs.mValue - DegToRad(rhs.mValue);
		else
			return lhs.mValue - RadToDeg(rhs.mValue);
	}

	/// Multiply two similar angles															
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	NOD() constexpr TAngle<LHST, D> operator * (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
		if constexpr (CT::Same<LHST, RHST>)
			return lhs.mValue * rhs.mValue;
		else if constexpr (LHST::Radians)
			return lhs.mValue * DegToRad(rhs.mValue);
		else
			return lhs.mValue * RadToDeg(rhs.mValue);
	}
		
	/// Divide two similar angles																
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	NOD() constexpr TAngle<LHST, D> operator / (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) {
		if constexpr (CT::Same<LHST, RHST>)
			return lhs.mValue / rhs.mValue;
		else if constexpr (LHST::Radians)
			return lhs.mValue / DegToRad(rhs.mValue);
		else
			return lhs.mValue / RadToDeg(rhs.mValue);
	}

	/// Destructively add two similar angles												
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	constexpr TAngle<LHST, D>& operator += (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
		lhs = lhs + rhs;
		return lhs;
	}
		
	/// Destructively subtract two similar angles										
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	constexpr TAngle<LHST, D>& operator -= (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
		lhs = lhs - rhs;
		return lhs;
	}
		
	/// Destructively multiply two similar angles										
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	constexpr TAngle<LHST, D>& operator *= (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
		lhs = lhs * rhs;
		return lhs;
	}

	/// Destructively divide two similar angles											
	template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
	constexpr TAngle<LHST, D>& operator /= (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) {
		lhs = lhs / rhs;
		return lhs;
	}

} // namespace Langulus::Math