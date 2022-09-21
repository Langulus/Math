///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "APrimitive.hpp"

namespace Langulus::Math
{

	/// 3D cone with varying dimensions, centered around origin						
	/// SPACE determines the direction of the cone's pointy side					
	template<class T, Dimension SPACE = Dimension::Y>
	class TCone : POD {
	public:
		static_assert(pcHasBase<T, AVector>, "TCone base must inherit a vector");

		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr Dimension Space = SPACE;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(Space != Dimension::W, "Can't extend cone in W dimension");
		static_assert(MemberCount == 3, "Can't have a non-3D cone");

		REFLECT_MANUALLY(TCone) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Cone";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a cone of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mHeight),
				MEMBER_NOTRAIT(ME, mRadius));
			return reflection;
		}

	public:
		/// Check if cylinder is degenerate													
		///	@return true if at least one offset is zero								
		NOD() bool IsDegenerate() const noexcept {
			return mHeight == 0 || mAngle == 0;
		}

		/// Check if box is hollow																
		///	@return true if at least one of the offsets is negative				
		NOD() bool IsHollow() const noexcept {
			return mHeight < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const PointType& point) const {
			if constexpr (Space == Dimension::X) {
				const auto q = point.yz().Length();
				const auto c = vec2(pcSin(mAngle), pcCos(mAngle));
				return pcMax(c.Dot(vec2(q, point[0])), -mHeight - point[0]);
			}
			else if constexpr (Space == Dimension::Y) {
				const auto q = point.xz().Length();
				const auto c = vec2(pcSin(mAngle), pcCos(mAngle));
				return pcMax(c.Dot(vec2(q, point[1])), -mHeight - point[1]);
			}
			else {
				const auto q = point.xy().Length();
				const auto c = vec2(pcSin(mAngle), pcCos(mAngle));
				return pcMax(c.Dot(vec2(q, point[2])), -mHeight - point[2]);
			}
		}

	public:
		MemberType mHeight = MemberType(0.5);
		MemberType mAngle = HALFPI<MemberType>;
	};

} // namespace Langulus::Math

