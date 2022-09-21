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

	/// 3D sphere, centered around origin													
	/// or a 2D circle, centered around origin											
	template<class T>
	class TSphere : POD {
	public:
		static_assert(pcHasBase<T, AVector>, "TSphere base must inherit a vector");

		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(MemberCount > 1, "Roundness doesn't exist in 1D");

		REFLECT_MANUALLY(TSphere) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Sphere";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a sphere of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mRadius));
			return reflection;
		}

	public:
		/// Check if sphere is degenerate													
		///	@return true if radius is zero												
		NOD() bool IsDegenerate() const noexcept {
			return mRadius == 0;
		}

		/// Check if sphere is hollow															
		///	@return true if radius is negative											
		NOD() bool IsHollow() const noexcept {
			return mRadius < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const PointType& point) const {
			return point.Length() - mRadius;
		}

	public:
		MemberType mRadius = 0.5;
	};


	/// 3D sphere, centered around origin													
	/// or a 2D circle, centered around origin											
	template<class T>
	class TEllipsoid : POD {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(MemberCount > 1, "Roundness doesn't exist in 1D");

		REFLECT_MANUALLY(TEllipsoid) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Ellipsoid";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "an ellipsoid of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mRadii));
			return reflection;
		}

	public:
		/// Check if ellipsoid is degenerate												
		///	@return true if any radius is zero											
		NOD() bool IsDegenerate() const noexcept {
			return mRadii == 0;
		}

		/// Check if ellipsoid is hollow														
		///	@return true if any radius is negative										
		NOD() bool IsHollow() const noexcept {
			return mRadii < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const PointType& point) const {
			const auto k0 = (point / mRadii).Length();
			const auto k1 = (point / (mRadii * mRadii)).Length();
			return k0 * (k0 - MemberType(1)) / k1;
		}

	public:
		PointType mRadii = 0.5;
	};

} // namespace Langulus::Math

