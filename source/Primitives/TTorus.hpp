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
	/// 3D torus																					
	///																								
	template<CT::Vector T, CT::Dimension D = Traits::Y>
	struct TTorus {
		LANGULUS(POD) true;
		LANGULUS_BASES(A::Primitive);

		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount == 3, "Can't have a non-three-dimensional torus");
		static_assert(D::Index < 3, "Can't extend torus in that dimension");

		MemberType mOuterRadius {.5};
		MemberType mInnerRadius {.5};

	public:
		/// Check if torus is degenerate														
		///	@return true if at least one radius is zero								
		NOD() constexpr bool IsDegenerate() const noexcept {
			return mInnerRadius == 0 || mOuterRadius == 0;
		}

		/// Check if torus is hollow															
		///	@return true if at least one of the radii is negative					
		NOD() constexpr bool IsHollow() const noexcept {
			return mInnerRadius * mOuterRadius < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() auto SignedDistance(const T& point) const {
			if constexpr (CT::Same<D, Traits::X>) {
				const auto q = TVector<MemberType, 2>(point.yz().Length() - mOuterRadius, point[0]);
				return q.Length() - mInnerRadius;
			}
			else if constexpr (CT::Same<D, Traits::Y>) {
				const auto q = TVector<MemberType, 2>(point.xz().Length() - mOuterRadius, point[1]);
				return q.Length() - mInnerRadius;
			}
			else if constexpr (CT::Same<D, Traits::Z>) {
				const auto q = TVector<MemberType, 2>(point.xy().Length() - mOuterRadius, point[2]);
				return q.Length() - mInnerRadius;
			}
			else LANGULUS_ERROR("Unsupported dimension");
		}
	};

} // namespace Langulus::Math

