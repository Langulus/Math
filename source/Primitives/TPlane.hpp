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

	/// Templated plane																			
	template<ComplexNumber T>
	class TPlane : POD {
	public:
		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr pcptr MemberCount = T::MemberCount;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(MemberCount > 1, "Planes don't exist in 1D");

		REFLECT_MANUALLY(TPlane) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Plane";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a plane of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mPlane));
			return reflection;
		}

	public:
		constexpr TPlane() noexcept = default;

		/// Construction from normal and offset											
		///	@param normal - the plane normal												
		///	@param offset - the plane distance from origin							
		constexpr TPlane(const T& normal, MemberType offset) noexcept
			: mNormal(normal)
			, mOffset(offset) {
			Normalize();
		}

		/// Construction from a matrix column												
		///	@param column - the column														
		constexpr TPlane(const TVec<MemberType, MemberCount + 1>& column) noexcept
			: mNormal(column)
			, mOffset(column[3]) {
			Normalize();
		}

		/// Construction from distance times direction									
		///	@param offset - the offset														
		constexpr TPlane(const T& offset) noexcept {
			const auto d = offset.Length();
			mNormal = offset / d;
			mOffset = d;
		}

		/// Flip the plane																		
		///	@return a reference to this plane											
		ME& Flip() noexcept {
			mNormal *= MemberType(-1);
			mOffset *= MemberType(-1);
			return *this;
		}

		/// Normalize the plane																	
		///	@return a normalized plane														
		ME& Normalize() noexcept {
			const auto length = mNormal.Length();
			if (0 != length) {
				mNormal /= length;
				mOffset /= length;
			}
			return *this;
		}

		/// Check if plane is degenerate														
		///	@return true if at least one offset is zero								
		NOD() bool IsDegenerate() const noexcept {
			return 0 == mNormal.Length();
		}

		/// Check if plane is hollow															
		///	@return always false, because planes aren't volumes					
		NOD() bool IsHollow() const noexcept {
			return false;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const T& point) const {
			return point.Dot(mNormal) + mOffset;
		}

	public:
		T mNormal = Vectors::Backward<MemberType>;
		MemberType mOffset = 0;
	};

} // namespace Langulus::Math

