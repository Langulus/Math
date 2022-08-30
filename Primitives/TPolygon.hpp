#pragma once
#include "APrimitive.hpp"

namespace PCFW::Math
{

	template<class T> class TPolygon;

	using Polygon2 = TPolygon<Point2>;
	using Polygon3 = TPolygon<Point3>;


	///																								
	///	Abstract polygon																		
	///																								
	PC_DECLARE_ABSTRACT_DATA(Polygon);


	///																								
	///	A templated polygon																	
	///																								
	template<class T>
	class TPolygon : public TAny<T> {
	public:
		static_assert(pcHasBase<T, AVector>, "TPolygon base must inherit a vector");

		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TPolygon) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Poly";
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
				REFLECT_BASE(APolygon));
			return reflection;
		}

	public:
		/// Calculate signed distance															
		NOD() MemberType SD(const PointType& p) const {
			TODO();
		}

		NOD() ME Clone() const {
			ME cloned;
			static_cast<TAny<T>&>(cloned) = TAny<T>::Clone();
			return cloned;
		}
	};

	PC_DEFINE_ABSTRACT_DATA(Polygon, "An abstract polygon primitive",
		Polygon3, REFLECT_BASE(ATopology));

} // namespace PCFW::Math

