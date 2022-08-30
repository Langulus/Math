#pragma once
#include "APrimitive.hpp"
#include "../Dimensions.hpp"

namespace PCFW::Math
{

	/// 3D torus																					
	template<class T, Dimension SPACE = Dimension::Y>
	class TTorus : POD {
	public:
		static_assert(pcHasBase<T, AVector>, "TTorus base must inherit a vector");

		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static constexpr Dimension Space = SPACE;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(Space != Dimension::W, "Can't extend torus in W dimension");
		static_assert(MemberCount == 3, "Can't have a non-3D torus");

		REFLECT_MANUALLY(TTorus) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Torus";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a torus of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mOuterRadius),
				MEMBER_NOTRAIT(ME, mInnerRadius));
			return reflection;
		}

	public:
		/// Check if cylinder is degenerate													
		///	@return true if at least one offset is zero								
		NOD() bool IsDegenerate() const noexcept {
			return mInnerRadius == 0 || mOuterRadius == 0;
		}

		/// Check if box is hollow																
		///	@return true if at least one of the offsets is negative				
		NOD() bool IsHollow() const noexcept {
			return mInnerRadius * mOuterRadius < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const PointType& point) const {
			if constexpr (Space == Dimension::X) {
				const auto q = TVec<MemberType, 2>(point.yz().Length() - mOuterRadius, point[0]);
				return q.Length() - mInnerRadius;
			}
			else if constexpr (Space == Dimension::Y) {
				const auto q = TVec<MemberType, 2>(point.xz().Length() - mOuterRadius, point[1]);
				return q.Length() - mInnerRadius;
			}
			else {
				const auto q = TVec<MemberType, 2>(point.yz().Length() - mOuterRadius, point[2]);
				return q.Length() - mInnerRadius;
			}
		}

	public:
		MemberType mOuterRadius = .5;
		MemberType mInnerRadius = .5;
	};

} // namespace PCFW::Math

