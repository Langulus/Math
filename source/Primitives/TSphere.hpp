///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Primitive.hpp"

namespace Langulus::Math
{

	///																								
	/// 2D circle, or 3D sphere, centered around origin								
	///																								
	template<CT::Vector T>
	struct TSphere {
		LANGULUS(POD) CT::POD<T>;
		LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
		LANGULUS_BASES(A::Primitive);

		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount > 1, "Roundness doesn't exist below two dimensions");

		MemberType mRadius {.5};

	public:
		/// Check if sphere is degenerate													
		///	@return true if radius is zero												
		NOD() constexpr bool IsDegenerate() const noexcept {
			return mRadius == 0;
		}

		/// Check if sphere is hollow															
		///	@return true if radius is negative											
		NOD() constexpr bool IsHollow() const noexcept {
			return mRadius < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() auto SignedDistance(const T& point) const {
			return point.Length() - mRadius;
		}
	};


	///																								
	/// 2D/3D ellipsoid, centered around origin											
	///																								
	template<CT::Vector T>
	struct TEllipsoid {
	public:
		LANGULUS(POD) CT::POD<T>;
		LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
		LANGULUS_BASES(A::Primitive);

		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount > 1, "Roundness doesn't exist below two dimensions");

		// A radius for each cardinal direction									
		T mRadii {.5};

	public:
		/// Check if ellipsoid is degenerate												
		///	@return true if any radius is zero											
		NOD() constexpr bool IsDegenerate() const noexcept {
			return mRadii == 0;
		}

		/// Check if ellipsoid is hollow														
		///	@return true if any radius is negative										
		NOD() constexpr bool IsHollow() const noexcept {
			return mRadii < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() auto SignedDistance(const T& point) const {
			const auto k0 = (point / mRadii).Length();
			const auto k1 = (point / (mRadii * mRadii)).Length();
			return k0 * (k0 - MemberType {1}) / k1;
		}
	};

} // namespace Langulus::Math

