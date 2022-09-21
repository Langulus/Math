///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "APrimitive.hpp"
#include "../Dimensions.hpp"

namespace Langulus::Math
{

	/// 3D uncapped cylinder with varying dimensions, centered around origin	
	/// SPACE determines the direction of the cylinder's height						
	template<ComplexNumber T, bool CAPPED = true, Dimension SPACE = Dimension::Y>
	class TCylinder : POD {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr Dimension Space = SPACE;
		static constexpr bool Capped = CAPPED;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(Space != Dimension::W, "Can't extend cylinder in W dimension");
		static_assert(MemberCount == 3, "Can't have a non-3D cylinder");

		REFLECT_MANUALLY(TCylinder) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				if constexpr (Capped)
					name += "Cylinder";
				else
					name += "CylinderUncapped";

				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				
				name = name.StandardToken();

				if constexpr (Capped)
					info += "a capped ";
				else
					info += "an uncapped ";
				info += "cylinder of type ";
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
			return mHeight == 0 || mRadius == 0;
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
			if constexpr (!CAPPED) {
				if constexpr (Space == Dimension::X)
					return point.yz().Length() - mRadius;
				else if constexpr (Space == Dimension::Y)
					return point.xz().Length() - mRadius;
				else
					return point.xy().Length() - mRadius;
			}
			else {
				if constexpr (Space == Dimension::X) {
					const auto d = TVec<MemberType, 2>(point.yz().Length(), point[0]).Abs() 
						- TVec<MemberType, 2>(mRadius, mHeight);
					return d.Max(0).Length() + pcMin(pcMax(d[0], d[1]), MemberType(0));
				}
				else if constexpr (Space == Dimension::Y) {
					const auto d = TVec<MemberType, 2>(point.xz().Length(), point[1]).Abs() 
						- TVec<MemberType, 2>(mRadius, mHeight);
					return d.Max(0).Length() + pcMin(pcMax(d[0], d[1]), MemberType(0));
				}
				else {
					const auto d = TVec<MemberType, 2>(point.xy().Length(), point[2]).Abs() 
						- TVec<MemberType, 2>(mRadius, mHeight);
					return d.Max(0).Length() + pcMin(pcMax(d[0], d[1]), MemberType(0));
				}
			}
		}

	public:
		MemberType mHeight = 0.5;
		MemberType mRadius = 0.5;
	};

} // namespace Langulus::Math

