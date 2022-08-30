#pragma once
#include "TPlane.hpp"

namespace PCFW::Math
{

	/// 3D frustum, centered around origin													
	/// or a 2D frustum, centered around origin											
	template<ComplexNumber T>
	class TFrustum : POD {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(MemberCount > 1, "Can't have 1D frustum");

		REFLECT_MANUALLY(TFrustum) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Frustum";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a frustum of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mPlanes));
			return reflection;
		}

	public:
		/// Default unit frustum construction												
		TFrustum() noexcept {
			if constexpr (MemberCount == 3) {
				// 3D frustum																
				const PointType right = { 0.5, 0, 0 };
				const PointType top   = { 0, 0.5, 0 };
				const PointType far   = { 0, 0, 0.5 };

				// Left clipping plane													
				mPlanes[0] = TPlane<T>(right);
				// Right clipping plane													
				mPlanes[1] = TPlane<T>(-right);
				// Top clipping plane													
				mPlanes[2] = TPlane<T>(-top);
				// Bottom clipping plane												
				mPlanes[3] = TPlane<T>(top);
				// Near clipping plane													
				mPlanes[4] = TPlane<T>(far);
				// Far clipping plane													
				mPlanes[5] = TPlane<T>(-far);
			}
			else if constexpr (MemberCount == 2) {
				// 2D frustum																
				const PointType right = { 0.5, 0 };
				const PointType top = { 0, 0.5 };

				// Left clipping plane													
				mPlanes[0] = TPlane<T>(right);
				// Right clipping plane													
				mPlanes[1] = TPlane<T>(-right);
				// Top clipping plane													
				mPlanes[2] = TPlane<T>(-top);
				// Bottom clipping plane												
				mPlanes[3] = TPlane<T>(top);
			}
		}

		/// Create a frustum by deconstructing a view*projection matrix			
		///	@param projectedView - projected view matrix								
		TFrustum(const TMat<MemberType, MemberCount + 1>& projectedView) noexcept {
			if constexpr (MemberCount == 3) {
				// 3D frustum																
				const auto right = projectedView.Column(0);
				const auto top = projectedView.Column(1);
				const auto far = projectedView.Column(2);
				const auto eye = projectedView.Column(3) * (-1);

				// Left clipping plane													
				mPlanes[0] = TPlane<T>(eye + right);
				// Right clipping plane													
				mPlanes[1] = TPlane<T>(eye - right);
				// Top clipping plane													
				mPlanes[2] = TPlane<T>(eye - top);
				// Bottom clipping plane												
				mPlanes[3] = TPlane<T>(eye + top);
				// Near clipping plane													
				mPlanes[4] = TPlane<T>(eye + far);
				// Far clipping plane													
				mPlanes[5] = TPlane<T>(eye - far);
			}
			else if constexpr (MemberCount == 2) {
				// 2D frustum																
				const auto right = projectedView.Column(0);
				const auto top = projectedView.Column(1);
				const auto eye = projectedView.Column(2) * (-1);

				// Left clipping plane													
				mPlanes[0] = TPlane<T>(eye + right);
				// Right clipping plane													
				mPlanes[1] = TPlane<T>(eye - right);
				// Top clipping plane													
				mPlanes[2] = TPlane<T>(eye - top);
				// Bottom clipping plane												
				mPlanes[3] = TPlane<T>(eye + top);
			}
		}

		/// Check if frustum is degenerate													
		///	@return true if at least one offset is zero								
		NOD() bool IsDegenerate() const noexcept {
			TODO();
			return false;
		}

		/// Check if frustum is hollow														
		///	@return true if at least one of the offsets is negative				
		NOD() bool IsHollow() const noexcept {
			TODO();
			return false;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const PointType& point) const {
			return pcMin(pcMin(pcMin(pcMin(pcMin(
								mPlanes[0].SD(point), 
								mPlanes[1].SD(point)
							), mPlanes[2].SD(point)
						), mPlanes[3].SD(point)
					), mPlanes[4].SD(point)
				), mPlanes[5].SD(point)
			);
		}

		/// Intersect with an AABB																
		bool Intersects(const range3& box) const noexcept {
			if (box.IsDegenerate() || box.Length().IsDegenerate())
				return false;

			// Not quite as fast, but wastes less space							
			for (const auto& plane : mPlanes) {
				const auto& normal = plane.mNormal;
				const PointType point = {
					normal[0] >= 0 ? box.mMin[0] : box.mMax[0],
					normal[1] >= 0 ? box.mMin[1] : box.mMax[1],
					normal[2] >= 0 ? box.mMin[2] : box.mMax[2]
				};

				if (point.Dot(normal) > -plane.mOffset)
					return false;
			}

			return true;
		}

	public:
		TPlane<T> mPlanes[MemberCount * 2];
	};

} // namespace PCFW::Math