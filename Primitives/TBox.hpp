#pragma once
#include "APrimitive.hpp"

namespace PCFW::Math
{

	/// 3D box with varying dimensions, centered around origin						
	/// or a 2D quad with varying dimensions, centered around origin				
	template<class T>
	class TBox : POD {
	public:
		static_assert(pcHasBase<T, AVector>, "TBox base must inherit a vector");

		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static_assert(RealNumber<MemberType>, "Must be composed of real numbers");
		static_assert(MemberCount > 1, "Can't have a box in 1D");

		REFLECT_MANUALLY(TBox) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Box";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a box primitive of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mOffsets));
			return reflection;
		}

	public:
		/// Check if box is degenerate														
		///	@return true if at least one offset is zero								
		NOD() bool IsDegenerate() const noexcept {
			return mOffsets.IsDegenerate();
		}

		/// Check if box is hollow																
		///	@return true if at least one of the offsets is negative				
		NOD() bool IsHollow() const noexcept {
			return mOffsets[0] < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const PointType& point) const {
			const PointType d = point.Abs() - mOffsets;
			if constexpr (MemberCount == 3)
				return d.Max(0).Length() + pcMin(pcMax(d[0], pcMax(d[1], d[2])), MemberType(0));
			else if constexpr (MemberCount == 2)
				return d.Max(0).Length() + pcMin(pcMax(d[0], d[1]), MemberType(0));
			else LANGULUS_ASSERT("Bad T::MemberCount for signed distance function");
		}

		/// Get code for the SD function														
		///	@return the code																	
		template<class CODE>
		NOD() static CODE GetDefinition() {
			if constexpr (MemberCount == 3) {
				if constexpr (Same<MemberType, pcr32>) {
					return
						"float sdBox(in vec3 point, in vec3 box) {\n"
						"   const vec3 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);\n"
						"}\n\n";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return
						"double sdBox(in dvec3 point, in dvec3 box) {\n"
						"   const dvec3 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);\n"
						"}\n\n";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else if constexpr (MemberCount == 2) {
				if constexpr (Same<MemberType, pcr32>) {
					return
						"float sdBox(in vec2 point, in vec2 box) {\n"
						"   const vec2 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);\n"
						"}\n\n";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return
						"double sdBox(in dvec2 point, in dvec2 box) {\n"
						"   const dvec2 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0);\n"
						"}\n\n";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else LANGULUS_ASSERT("Bad T::MemberCount for GLSL signed distance function");
		}

		/// Get code for the usage of the SD function									
		///	@return the code																	
		template<class CODE>
		NOD() CODE GetUse() const {
			if constexpr (MemberCount == 3) {
				if constexpr (Same<MemberType, pcr32>) {
					return CODE("sdBox(point, vec3(")
						+ mOffsets[0] + ", " 
						+ mOffsets[1] + ", " 
						+ mOffsets[2] 
						+ "))";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return CODE("sdBox(point, dvec3(")
						+ mOffsets[0] + ", "
						+ mOffsets[1] + ", "
						+ mOffsets[2]
						+ "))";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else if constexpr (MemberCount == 2) {
				if constexpr (Same<MemberType, pcr32>) {
					return CODE("sdBox(point, vec2(")
						+ mOffsets[0] + ", "
						+ mOffsets[1]
						+ "))";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return CODE("sdBox(point, dvec2(")
						+ mOffsets[0] + ", "
						+ mOffsets[1]
						+ "))";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else LANGULUS_ASSERT("Bad T::MemberCount for GLSL signed distance function");
		}

	public:
		PointType mOffsets = 0.5;
	};


	/// 3D rounded box with varying dimensions, centered around origin			
	/// or a 2D rounded quad with varying dimensions, centered around origin	
	template<class T>
	class TBoxRound : public TBox<T> {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TBoxRound) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name;
			if (name.IsEmpty()) {
				name += "BoxRound";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
			}

			auto reflection = RTTI::ReflectData::From<ME>(
				name, "A rounded box primitive");
			reflection.template SetBases<ME>(
				REFLECT_BASE(APrimitive));
			reflection.template SetMembers<ME>(
				MEMBER_NOTRAIT(ME, mRadius));
			return reflection;
		}

	public:
		/// Check if box is degenerate														
		///	@return true if at least one offset is zero								
		NOD() bool IsDegenerate() const noexcept {
			return pcNear(TBox<T>::mOffsets.Length() - mRadius, MemberType(0));
		}

		/// Check if box is hollow																
		///	@return true if at least one of the offsets is negative				
		NOD() bool IsHollow() const noexcept {
			return TBox<T>::mOffsets[0] - mRadius < 0;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const PointType& point) const {
			const PointType d = point.Abs() - TBox<T>::mOffsets;
			if constexpr (MemberCount == 3)
				return d.Max(0).Length() - mRadius + pcMin(pcMax(d[0], pcMax(d[1], d[2])), MemberType(0));
			else if constexpr (MemberCount == 2)
				return d.Max(0).Length() - mRadius + pcMin(pcMax(d[0], d[1]), MemberType(0));
			else LANGULUS_ASSERT("Bad T::MemberCount for signed distance function");
		}

		/// Get code for the SD function														
		///	@return the code																	
		template<class CODE>
		NOD() static CODE GetDefinition() {
			if constexpr (MemberCount == 3) {
				if constexpr (Same<MemberType, pcr32>) {
					return
						"float sdBoxRound(in vec3 point, in vec3 box, in float radius) {\n"
						"   const vec3 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0) - radius;\n"
						"}\n\n";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return
						"double sdBoxRound(in dvec3 point, in dvec3 box, in double radius) {\n"
						"   const dvec3 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0) - radius;\n"
						"}\n\n";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else if constexpr (MemberCount == 2) {
				if constexpr (Same<MemberType, pcr32>) {
					return
						"float sdBoxRound(in vec2 point, in vec2 box, in float radius) {\n"
						"   const vec2 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0) - radius;\n"
						"}\n\n";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return
						"double sdBoxRound(in dvec2 point, in dvec2 box, in double radius) {\n"
						"   const dvec2 d = abs(point) - box;\n"
						"   return length(max(d, 0.0)) + min(max(d.x, d.y), 0.0) - radius;\n"
						"}\n\n";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else LANGULUS_ASSERT("Bad T::MemberCount for GLSL signed distance function");
		}

		/// Get code for the usage of the SD function									
		///	@return the code																	
		template<class CODE>
		NOD() CODE GetUse() const {
			if constexpr (MemberCount == 3) {
				if constexpr (Same<MemberType, pcr32>) {
					return CODE("sdBoxRound(point, vec3(")
						+ TBox<T>::mOffsets[0] + ", "
						+ TBox<T>::mOffsets[1] + ", "
						+ TBox<T>::mOffsets[2]
						+ "), " + mRadius + ")";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return CODE("sdBoxRound(point, dvec3(")
						+ TBox<T>::mOffsets[0] + ", "
						+ TBox<T>::mOffsets[1] + ", "
						+ TBox<T>::mOffsets[2]
						+ "), " + mRadius + ")";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else if constexpr (MemberCount == 2) {
				if constexpr (Same<MemberType, pcr32>) {
					return CODE("sdBoxRound(point, vec2(")
						+ TBox<T>::mOffsets[0] + ", "
						+ TBox<T>::mOffsets[1]
						+ "), " + mRadius + ")";
				}
				else if constexpr (Same<MemberType, pcr64>) {
					return CODE("sdBoxRound(point, dvec2(")
						+ TBox<T>::mOffsets[0] + ", "
						+ TBox<T>::mOffsets[1]
						+ "), " + mRadius + ")";
				}
				else LANGULUS_ASSERT("Bad T::MemberType for GLSL signed distance function");
			}
			else LANGULUS_ASSERT("Bad T::MemberCount for GLSL signed distance function");
		}

	public:
		MemberType mRadius;
	};

} // namespace PCFW::Math

