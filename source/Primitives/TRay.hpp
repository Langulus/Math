///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TPoint.hpp"

namespace Langulus::Math
{

	template<class T> class TRay;

	using Ray2 = TRay<Point2>;
	using Ray3 = TRay<Point3>;


	///																								
	///	An abstract ray																		
	///																								
	PC_DECLARE_ABSTRACT_DATA(Ray);


	///																								
	///	A concrete ray																			
	///																								
	template<class T>
	class TRay {
	public:
		static_assert(pcHasBase<T, AVector>, "TRay base must inherit a vector");

		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr pcptr MemberCount = T::MemberCount;

		REFLECT_MANUALLY(TRay) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Ray";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a ray of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ARay));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mOrigin, Position), 
				REFLECT_MEMBER_TRAIT(mNormal, Aim));
			return reflection;
		}

	public:
		/// Construction																			
		constexpr TRay() = default;
		constexpr TRay(const T& position, const T& normal) noexcept
			: mOrigin(position)
			, mNormal(normal.Normalize()) {}

		/// Check if ray is degenerate														
		constexpr bool IsDegenerate() const noexcept {
			return mNormal.Length() == 0;
		}

		/// Get a point along the ray															
		constexpr T Point(const MemberType& distance) const noexcept {
			const T offset = mNormal * distance;
			return mOrigin + offset;
		}

		/// Move the ray origin 																
		constexpr ME& Step(const MemberType& distance) noexcept {
			mOrigin += mNormal * distance;
			return *this;
		}

		constexpr ME Stepped(const MemberType& distance) const noexcept {
			ME copy = *this;
			return copy.Step(distance);
		}

		/// Self-dot the ray																		
		constexpr float Dot() const noexcept {
			return pcDot(mOrigin, mNormal);
		}

	public:
		T mOrigin = {};
		T mNormal = {};
	};

	PC_DEFINE_ABSTRACT_DATA(Ray, "An abstract ray primitive",
		Ray3, REFLECT_BASE(APrimitive));

} // namespace Langulus::Math
