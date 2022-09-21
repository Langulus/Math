///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Vectors.hpp"

namespace Langulus::Math
{

	template<Number T, pcptr S = 1>
	class TRange;


	///																								
	///	Abstract range																			
	///																								
	PC_DECLARE_ABSTRACT_DATA(Range);


	///																								
	///	Abstract range of specific size													
	///																								
	template<pcptr S>
	class EMPTY_BASE() TSizedRange {
	public:
		static constexpr pcptr MemberCount = S;
		using Concrete = TRange<real, S>;

		REFLECT_MANUALLY(TSizedRange) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Range";
				name += MemberCount;
				name = name.StandardToken();
				info += "an abstract range of a size ";
				info += MemberCount;
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mConcrete = DataID::Of<Concrete>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(ARange));
			reflection.MakeAbstract();
			return reflection;
		}
	};


	///																								
	///	Templated range																		
	///																								
	#pragma pack(push, 1)
	template<Number T, pcptr S>
	class TRange {
	public:
		static_assert(Dense<T>, "T must be dense");
		using PointType = TVec<T, S>;
		using MemberType = T;
		static constexpr pcptr MemberCount = S;

	public:
		PointType mMin;
		PointType mMax;

		REFLECT_MANUALLY(TRange) {
			static_assert(sizeof(T) * S * 2 == sizeof(ME), "Size mismatch");
			auto subtype = DataID::Reflect<TSizedRange<MemberCount>>();
			static GASM name, info;
			if (name.IsEmpty()) {
				name += subtype->GetToken();
				name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a range of a size ";
				info += MemberCount;
				info += " and type ";
				info += DataID::Reflect<MemberType>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mPOD = pcIsPOD<PointType>;
			reflection.mNullifiable = pcIsNullifiable<PointType>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(TSizedRange<MemberCount>));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mMin, Min),
				REFLECT_MEMBER_TRAIT(mMax, Max));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			return reflection;
		}

	public:
		constexpr TRange() noexcept = default;

		/// Copy constructor																		
		constexpr TRange(const TRange& a) noexcept
			: mMin {a.mMin}
			, mMax {a.mMax} {}

		/// Scalar construction (min == max)												
		constexpr TRange(const PointType& minmax) noexcept
			: mMin {minmax}
			, mMax {minmax} {}

		/// Manual construction from min & max												
		constexpr TRange(const PointType& min, const PointType& max) noexcept
			: mMin {min}
			, mMax {max} {}

		/// From dense data																		
		constexpr TRange(const PointType* a) noexcept
			: TRange {a[0], a[1]} {}

		/// From sparse data																		
		constexpr TRange(const PointType* const* a) noexcept
			: TRange {*a[0], *a[1]} {}

		~TRange() noexcept = default;

		/// Copy operator																			
		constexpr auto& operator = (const TRange& a) noexcept {
			mMin = a.mMin;
			mMax = a.mMax;
			return *this;
		}

		/// Convert any range to text															
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			result += GASM::OpenScope;
				result += Flow::pcSerialize<GASM>(mMin);
				result += GASM::AndSeparator;
				result += Flow::pcSerialize<GASM>(mMax);
			result += GASM::CloseScope;
			return result;
		}
		
		/// Arithmetics																			
		NOD() friend constexpr ME operator - (const ME& me) noexcept {
			return {-me.mMin, -me.mMax};
		}

		NOD() friend constexpr ME operator + (const ME& me, const ME& other) noexcept {
			return {me.mMin + other.mMin, me.mMax + other.mMax};
		}

		NOD() friend constexpr ME operator + (const ME& me, const T& other) noexcept {
			return {me.mMin + other, me.mMax + other};
		}

		NOD() friend constexpr ME operator - (const ME& me, const ME& other) noexcept {
			return {me.mMin - other.mMin, me.mMax - other.mMax};
		}

		NOD() friend constexpr ME operator - (const ME& me, const T& other) noexcept {
			return {me.mMin - other, me.mMax - other};
		}

		NOD() friend constexpr ME operator * (const ME& me, const ME& other) noexcept {
			return {me.mMin * other.mMin, me.mMax * other.mMax};
		}

		NOD() friend constexpr ME operator * (const ME& me, const T& other) noexcept {
			return {me.mMin * other, me.mMax * other};
		}

		NOD() friend constexpr ME operator / (const ME& me, const ME& other) noexcept {
			return {me.mMin / other.mMin, me.mMax / other.mMax};
		}

		NOD() friend constexpr ME operator / (const ME& me, const T& other) noexcept {
			return {me.mMin / other, me.mMax / other};
		}

		friend constexpr void operator += (ME& me, const ME& other) noexcept {
			me.mMin += other.mMin;
			me.mMax += other.mMax;
		}

		friend constexpr void operator += (ME& me, const T& other) noexcept {
			me.mMin += other;
			me.mMax += other;
		}

		friend constexpr void operator -= (ME& me, const ME& other) noexcept {
			me.mMin -= other.mMin;
			me.mMax -= other.mMax;
		}

		friend constexpr void operator -= (ME& me, const T& other) noexcept {
			me.mMin -= other;
			me.mMax -= other;
		}

		friend constexpr void operator *= (ME& me, const ME& other) noexcept {
			me.mMin *= other.mMin;
			me.mMax *= other.mMax;
		}

		friend constexpr void operator *= (ME& me, const T& other) noexcept {
			me.mMin *= other;
			me.mMax *= other;
		}

		friend constexpr void operator /= (ME& me, const ME& other) noexcept {
			me.mMin /= other.mMin;
			me.mMax /= other.mMax;
		}

		friend constexpr void operator /= (ME& me, const T& other) noexcept {
			me.mMin /= other;
			me.mMax /= other;
		}

		template<class N>
		constexpr TRange& Embrace(const N& other) noexcept {
			mMin = pcMin(mMin, other);
			mMax = pcMax(mMax, other);
			return *this;
		}

		template<class N>
		constexpr TRange& ConstrainBy(const N& limits) noexcept {
			mMin = pcClamp(mMin, limits.mMin, limits.mMax);
			mMax = pcClamp(mMax, limits.mMin, limits.mMax);
			return *this;
		}

		NOD() constexpr bool operator == (const ME& a) const noexcept {
			return mMin == a.mMin && mMax == a.mMax;
		}

		NOD() constexpr bool operator != (const ME& a) const noexcept {
			return !(*this == a);
		}

		NOD() constexpr bool operator >= (const ME& a) const noexcept {
			return mMin >= a.mMin || mMax >= a.mMax;
		}

		NOD() constexpr bool operator <= (const ME& a) const noexcept {
			return mMin <= a.mMin || mMax <= a.mMax;
		}

		NOD() constexpr bool operator <  (const ME& a) const noexcept {
			return mMin < a.mMin || mMax < a.mMax;
		}

		NOD() constexpr bool operator >  (const ME& a) const noexcept {
			return mMin > a.mMin || mMax > a.mMax;
		}

		NOD() PointType Length() const noexcept {
			return mMax - mMin;
		}

		NOD() PointType Center() const noexcept {
			return mMin + Length() * 0.5f;
		}

		NOD() constexpr bool IsDegenerate() const noexcept {
			return mMin == mMax;
		}

		NOD() constexpr bool Inside(const PointType& a) const noexcept {
			return a >= mMin && a <= mMax;
		}

		NOD() constexpr bool IsInsideHalfClosed(const PointType& x) const noexcept {
			return x >= mMin && x < mMax;
		}

		NOD() constexpr PointType ClampRev(const PointType& pos) const noexcept {
			return pos.ClampRev(mMin, mMax);
		}

		NOD() constexpr PointType Clamp(const PointType& pos) const noexcept {
			return pos.Clamp(mMin, mMax);
		}

		NOD() constexpr ME operator | (const ME& a) const noexcept {
			return {
				mMin.Clamp(a.mMin, a.mMax),
				mMax.Clamp(a.mMin, a.mMax)
			};
		}

		constexpr void operator |= (const ME& a) noexcept {
			*this = *this | a;
		}

		template<DenseNumber ALT_T = T, pcptr ALT_S = S>
		NOD() explicit constexpr operator TRange<ALT_T, ALT_S>() const noexcept {
			return {mMin, mMax};
		}
		template<pcptr ALT_S = S>
		NOD() constexpr operator TRange<T, ALT_S>() const noexcept {
			return {mMin, mMax};
		}
	};
	#pragma pack(pop)

	PC_DEFINE_ABSTRACT_DATA(Range, "An abstract range", void);

	template<ComplexNumber T>
	using TComplexRange = TRange<typename T::MemberType, T::MemberCount>;

} // namespace Langulus::Math
