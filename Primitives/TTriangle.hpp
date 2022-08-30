#pragma once
#include "TPoint.hpp"

namespace PCFW::Math
{

	template<class T> class TTriangle;
	template<class T> class TTriangleStrip;
	template<class T> class TTriangleFan;

	using Triangle2 = TTriangle<Point2>;
	using Triangle3 = TTriangle<Point3>;
	using TriangleStrip2 = TTriangleStrip<Point2>;
	using TriangleStrip3 = TTriangleStrip<Point3>;
	using TriangleFan2 = TTriangleFan<Point2>;
	using TriangleFan3 = TTriangleFan<Point3>;


	///																								
	///	An abstract triangle topologies													
	///																								
	PC_DECLARE_ABSTRACT_DATA(Triangle);
	PC_DECLARE_ABSTRACT_DATA(TriangleStrip);
	PC_DECLARE_ABSTRACT_DATA(TriangleFan);


	///																								
	///	A templated triangle																	
	///																								
	#pragma pack(push, 1)
	template<class T>
	class EMPTY_BASE() TTriangle {
	public:
		static_assert(pcHasBase<T, AVector>, "TTriangle base must inherit a vector");

		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TTriangle) {
			static_assert(sizeof(PointType) == sizeof(MemberType) * MemberCount,
				"Size mismatch");
			static_assert(sizeof(ME) == sizeof(PointType) * 3,
				"Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Tri";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a triangle of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mPOD = pcIsPOD<T>;
			reflection.mNullifiable = pcIsNullifiable<T>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(ATriangle),
				REFLECT_BASE_MAP(PointType, 3));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mPoints, Position));
			return reflection;
		}

	public:
		/// Construction																			
		constexpr TTriangle() = default;

		/// Manual construction																	
		///	@param p1 - first point															
		///	@param p2 - second point														
		///	@param p3 - third point															
		template<class ALT_T = T>
		constexpr TTriangle(const ALT_T& p1, const ALT_T& p2, const ALT_T& p3) noexcept
			: mPoints{ p1, p2, p3 } {}

		/// Manual construction from three points of any type							
		///	@param points - pointer to the three points								
		template<class ALT_T = T>
		constexpr TTriangle(const ALT_T* points) noexcept
			: mPoints{ points[0], points[1], points[2] } {}

		/// Manual construction from dense memory of any type, indexed				
		///	@param points - pointer to the point array								
		///	@param indices - three indices for the points array					
		template<class ALT_T = T>
		constexpr TTriangle(const ALT_T* points, const pcu32(&indices)[3]) noexcept
			: mPoints{ points[indices[0]], points[indices[1]], points[indices[2]] } {}

		/// Check if triangle is degenerate													
		///	@return true if any of the points overlap									
		NOD() bool IsDegenerate() const noexcept {
			return mPoints[0] == mPoints[1]
				 || mPoints[0] == mPoints[2]
				 || mPoints[1] == mPoints[2];
		}

		/// Subdivide triangle																	
		///	@return the four new triangles												
		NOD() std::array<ME, 4> Subdivide() const noexcept {
			const PointType m01 = mPoints[0] + (mPoints[1] - mPoints[0]) / MemberType(2);
			const PointType m12 = mPoints[1] + (mPoints[2] - mPoints[1]) / MemberType(2);
			const PointType m20 = mPoints[2] + (mPoints[0] - mPoints[2]) / MemberType(2);
			return { 
				ME(mPoints[0], m01, m20),
				ME(m01, mPoints[1], m12),
				ME(m20, m12, mPoints[2]),
				ME(m01, m12, m20)
			};
		}

		/// Calculate signed distance															
		///	@param point - the point from which distance is calculated			
		///	@return the distance																
		NOD() MemberType SD(const PointType& point) const {
			if constexpr (MemberCount < 3) {
				// 2D signed distance field											
				const auto p = PointType(point);
				const auto e0 = mPoints[1] - mPoints[0];
				const auto e1 = mPoints[2] - mPoints[1];
				const auto e2 = mPoints[0] - mPoints[2];
				const auto v0 = p - mPoints[0];
				const auto v1 = p - mPoints[1];
				const auto v2 = p - mPoints[2];

				const auto pq0 = v0 - e0 * pcClamp01(v0.Dot(e0) / e0.Dot(e0));
				const auto pq1 = v1 - e1 * pcClamp01(v1.Dot(e1) / e1.Dot(e1));
				const auto pq2 = v2 - e2 * pcClamp01(v2.Dot(e2) / e2.Dot(e2));

				const auto s = pcSign(e0[0] * e2[1] - e0[1] * e2[0]);
				PointType d =
					pcMin(
						pcMin(
							PointType(pq0.Dot(pq0), s * (v0[0] * e0[1] - v0[1] * e0[0])),
							PointType(pq1.Dot(pq1), s * (v1[0] * e1[1] - v1[1] * e1[0]))
						),
						PointType(pq2.Dot(pq2), s * (v2[0] * e2[1] - v2[1] * e2[0]))
					);

				return -pcSqrt(d[0]) * pcSign(d[1]);
			}
			else {
				// 3D signed distance field											
				const auto ba = mPoints[1] - mPoints[0];
				const auto pa = point - mPoints[0];
				const auto cb = mPoints[2] - mPoints[1];
				const auto pb = point - mPoints[1];
				const auto ac = mPoints[0] - mPoints[2];
				const auto pc = point - mPoints[2];
				const auto nor = ba.Cross(ac);

				return pcSqrt(
					(
						pcSign(ba.Cross(nor).Dot(pa)) +
						pcSign(cb.Cross(nor).Dot(pb)) +
						pcSign(ac.Cross(nor).Dot(pc)) < real(2)
						)
					?
					pcMin(
						pcMin(
							pcDot2(ba * pcClamp01(ba.Dot(pa) / ba.Dot(ba)) - pa),
							pcDot2(cb * pcClamp01(cb.Dot(pb) / cb.Dot(cb)) - pb)
						),
						pcDot2(ac * pcClamp01(ac.Dot(pc) / ac.Dot(ac)) - pc)
					)
					:
					nor.Dot(pa) * nor.Dot(pa) / pcDot2(nor)
				);
			}
		}

		/// Access points																			
		NOD() auto& operator [] (pcptr index) const noexcept {
			return mPoints[index];
		}
		NOD() auto& operator [] (pcptr index) noexcept {
			return mPoints[index];
		}

		/// Convert to other kinds of triangles											
		template<class ALT>
		NOD() explicit operator TTriangle<ALT>() const noexcept {
			return { 
				static_cast<ALT>(mPoints[0]), 
				static_cast<ALT>(mPoints[1]),
				static_cast<ALT>(mPoints[2]) 
			};
		}

		/// Modify the triangle																	
		ME operator + (const PointType& rhs) const noexcept {
			return { mPoints[0] + rhs, mPoints[1] + rhs, mPoints[2] + rhs };
		}
		ME operator - (const PointType& rhs) const noexcept {
			return { mPoints[0] - rhs, mPoints[1] - rhs, mPoints[2] - rhs };
		}
		ME operator * (const PointType& rhs) const noexcept {
			return { mPoints[0] * rhs, mPoints[1] * rhs, mPoints[2] * rhs };
		}
		ME operator / (const PointType& rhs) const {
			return { mPoints[0] / rhs, mPoints[1] / rhs, mPoints[2] / rhs };
		}

	protected:
		PointType mPoints[3];
	};
	#pragma pack(pop)


	///																								
	///	A templated triangle strip															
	///																								
	template<class T>
	class TTriangleStrip : public TAny<T> {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TTriangleStrip) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "TriStrip";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a triangle strip of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ATriangleStrip));
			return reflection;
		}

		/// Check if cone is degenerate														
		NOD() bool IsDegenerate() const noexcept {
			//TODO
			return false;
		}

		/// Check if cone is hollow															
		NOD() bool IsHollow() const noexcept {
			return false;
		}

		/// Calculate signed distance for 2D triangle									
		NOD() MemberType SD(const PointType& point) const {
			//TODO
			return 0;
		}

		NOD() ME Clone() const {
			ME cloned;
			static_cast<TAny<T>&>(cloned) = TAny<T>::Clone();
			return cloned;
		}
	};


	///																								
	///	A templated triangle fan															
	///																								
	template<class T>
	class TTriangleFan : public TAny<T> {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TTriangleFan) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "TriFan";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a triangle fan of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ATriangleFan));
			return reflection;
		}

		/// Check if fan is degenerate														
		NOD() bool IsDegenerate() const noexcept {
			//TODO
			return false;
		}

		/// Check if fan is hollow																
		NOD() bool IsHollow() const noexcept {
			return false;
		}

		/// Calculate signed distance for 2D triangle									
		NOD() MemberType SD(const PointType& point) const {
			//TODO
			return 0;
		}

		NOD() ME Clone() const {
			ME cloned;
			static_cast<TAny<T>&>(cloned) = TAny<T>::Clone();
			return cloned;
		}
	};

	PC_DEFINE_ABSTRACT_DATA(Triangle, "An abstract triangle primitive",
		Triangle3, REFLECT_BASE(ATopology));

	PC_DEFINE_ABSTRACT_DATA(TriangleStrip, "An abstract triangle strip primitive",
		TriangleStrip3, REFLECT_BASE(ATriangle));

	PC_DEFINE_ABSTRACT_DATA(TriangleFan, "An abstract triangle fan primitive",
		TriangleFan3, REFLECT_BASE(ATriangle));

} // namespace PCFW::Math

