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

	template<CT::Vector> struct TRay;

	using Ray2 = TRay<Point2>;
	using Ray3 = TRay<Point3>;
	using Ray = Ray3;

	namespace A
	{

		///																							
		///	An abstract ray																	
		///																							
		struct Ray {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::Ray;
			LANGULUS_BASES(Primitive);
		};

	} // namespace Langulus::Math::A


	///																								
	///	A ray																						
	/// A line segment with a discrete starting point, but no ending point		
	///																								
	template<CT::Vector T>
	struct TRay {
		LANGULUS(POD) CT::POD<T>;
		LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
		LANGULUS_BASES(A::Ray);

		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount > 1, "Rays don't exist below two dimensions");

		T mOrigin {};
		T mNormal {};

	public:
		constexpr TRay() = default;

		constexpr TRay(const T& position, const T& normal) noexcept
			: mOrigin {position}
			, mNormal {normal.Normalize()} {}

		/// Check if ray is degenerate														
		NOD() constexpr bool IsDegenerate() const noexcept {
			return mNormal.Length() == 0;
		}

		/// Get a point along the ray															
		NOD() constexpr T Point(const MemberType& distance) const noexcept {
			return mOrigin + mNormal * distance;
		}

		/// Move the ray origin 																
		NOD() constexpr TRay& Step(const MemberType& distance) noexcept {
			mOrigin += mNormal * distance;
			return *this;
		}

		NOD() constexpr TRay Stepped(const MemberType& distance) const noexcept {
			TRay copy = *this;
			return copy.Step(distance);
		}

		/// Self-dot the ray																		
		NOD() constexpr MemberType Dot() const noexcept {
			return Dot(mOrigin, mNormal);
		}
	};

} // namespace Langulus::Math
