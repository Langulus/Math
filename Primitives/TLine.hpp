#pragma once
#include "TPoint.hpp"

namespace PCFW::Math
{

	template<class T> class TLine;
	template<class T> class TLineLoop;
	template<class T> class TLineStrip;

	using Line2 = TLine<Point2>;
	using Line3 = TLine<Point3>;
	using LineLoop2 = TLineLoop<Point2>;
	using LineLoop3 = TLineLoop<Point3>;
	using LineStrip2 = TLineStrip<Point2>;
	using LineStrip3 = TLineStrip<Point3>;


	///																								
	///	Abstract lines																			
	///																								
	PC_DECLARE_ABSTRACT_DATA(Line);
	PC_DECLARE_ABSTRACT_DATA(LineLoop);
	PC_DECLARE_ABSTRACT_DATA(LineStrip);


	///																								
	///	Templated line segment																
	///																								
	#pragma pack(push, 1)
	template<class T>
	class TLine {
	public:
		static_assert(pcHasBase<T, AVector>, "TLine base must inherit a vector");

		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;
		static_assert(MemberCount > 1, "Lines don't exist in 1D");

		REFLECT_MANUALLY(TLine) {
			static_assert(sizeof(ME) == sizeof(T) * 2, "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Line";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a line of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mPOD = pcIsPOD<T>;
			reflection.mNullifiable = pcIsNullifiable<T>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(ALine),
				REFLECT_BASE_MAP(PointType, 2));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mAB, Position));
			return reflection;
		}

	public:
		/// Default construction (along x)													
		constexpr TLine() noexcept {
			mAB[0] = {};
			if constexpr (MemberCount == 2)
				mAB[1] = { 0.5, 0.0 };
			else if constexpr (MemberCount == 3)
				mAB[1] = { 0.5, 0.0, 0.0 };
			else
				LANGULUS_ASSERT("Unsupported line dimension");
		}

		/// Manual construction																	
		///	@param p1 - first point															
		///	@param p2 - second point														
		template<class ALT_T = T>
		constexpr TLine(const ALT_T& p1, const ALT_T& p2) noexcept
			: mAB { p1, p2 } {}

		/// Manual construction from two points of any type							
		///	@param points - pointer to the two points									
		template<class ALT_T = T>
		constexpr TLine(const ALT_T* points) noexcept
			: mAB { points[0], points[1] } {}

		/// Manual construction from two points of any type, indexed				
		///	@param points - pointer to the two points									
		///	@param indices - indices for the points array							
		template<class ALT_T = T>
		constexpr TLine(const ALT_T* points, const pcu32(&indices)[2]) noexcept
			: mAB { points[indices[0]], points[indices[1]] } {}

		/// Check if line is degenerate														
		///	@param radius - the line radius used for tolerance						
		///	@return true if line has no radius or no length							
		NOD() bool IsDegenerate(MemberType radius = std::numeric_limits<MemberType>::epsilon()) const noexcept {
			return pcNear(radius, MemberType(0)) || pcNear((mAB[0] - mAB[1]).Length(), MemberType(0));
		}

		/// Subdivide line																		
		///	@return the two new lines														
		NOD() std::array<ME, 2> Subdivide() const noexcept {
			const T midpoint = mAB[0] + (mAB[1] - mAB[0]) / MemberType(2);
			return { 
				ME(mAB[0], midpoint), 
				ME(midpoint, mAB[1])
			};
		}

		/// Calculate signed distance															
		///	@param point - the point from which distance is calculated			
		///	@return the distance																
		NOD() MemberType SD(const PointType& point) const {
			auto pa = point - mAB[0];
			auto ba = mAB[1] - mAB[0];
			auto h = pcClamp01(pa.Dot(ba) / ba.Dot(ba));
			return (pa - ba * h).Length();
		}

		/// Access points																			
		NOD() auto& operator [] (pcptr index) const noexcept {
			return mAB[index];
		}
		NOD() auto& operator [] (pcptr index) noexcept {
			return mAB[index];
		}

		/// Convert to other kinds of lines													
		template<class ALT>
		NOD() explicit operator TLine<ALT>() const noexcept {
			return { static_cast<ALT>(mAB[0]), static_cast<ALT>(mAB[1]) };
		}

	protected:
		PointType mAB[2];
	};
	#pragma pack(pop)


	///																								
	///	Templated line loop																	
	///																								
	template<class T>
	class TLineLoop : public TAny<T> {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TLineLoop) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "LineLoop";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a line loop of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ALineLoop));
			return reflection;
		}

		NOD() ME Clone() const {
			ME cloned;
			static_cast<TAny<T>&>(cloned) = TAny<T>::Clone();
			return cloned;
		}
	};


	///																								
	///	Templated line strip																	
	///																								
	template<class T>
	class TLineStrip : public TAny<T> {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TLineStrip) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "LineStrip";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a line strip of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ALineStrip));
			return reflection;
		}

		NOD() ME Clone() const {
			ME cloned;
			static_cast<TAny<T>&>(cloned) = TAny<T>::Clone();
			return cloned;
		}
	};

	PC_DEFINE_ABSTRACT_DATA(Line, "An abstract line primitive",
		Line3, REFLECT_BASE(ATopology));

	PC_DEFINE_ABSTRACT_DATA(LineLoop, "An abstract line loop primitive",
		LineLoop3, REFLECT_BASE(ALine));

	PC_DEFINE_ABSTRACT_DATA(LineStrip, "An abstract line strip (spline) primitive",
		LineStrip3, REFLECT_BASE(ALine));

} // namespace PCFW::Math

