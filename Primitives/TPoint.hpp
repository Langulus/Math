#pragma once
#include "APrimitive.hpp"

namespace PCFW::Math
{

	template<class T> class TPoint;

	using Point1 = TPoint<vec1>;
	using Point2 = TPoint<vec2>;
	using Point3 = TPoint<vec3>;

	using Point = Point3;


	///																								
	///	An abstract point																		
	///																								
	PC_DECLARE_ABSTRACT_DATA(Point);


	///																								
	///	A concrete point																		
	///																								
	#pragma pack(push, 1)
	template<class T>
	class EMPTY_BASE() TPoint : public T {
	public:
		static_assert(pcHasBase<T, AVector>, "TPoint base must inherit a vector");

		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr pcptr MemberCount = T::MemberCount;

		REFLECT_MANUALLY(TPoint) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(pcIsNullifiable<ME>, "Must be NULLIFIABLE");
			static_assert(pcIsPOD<T>, "Must be POD");
			static_assert(pcIsNullifiable<T>, "Must be NULLIFIABLE");
			static_assert(sizeof(ME) == sizeof(T), "Size mismatch");
			static_assert(sizeof(MemberType) * MemberCount == sizeof(ME), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Point";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a point of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(APoint),
				REFLECT_BASE(T));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			return reflection;
		}

	public:
		using T::T;

		constexpr TPoint(const T& other)
			: T{ other } {}

		/// Convert from any normal to text													
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			T::WriteBody(result);
			return result;
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() MemberType SD(const T& point) const {
			return (point - *this).Length();
		}
	};
	#pragma pack(pop)

	PC_DEFINE_ABSTRACT_DATA(Point, "An abstract point primitive",
		Point3, REFLECT_BASE(ATopology));

} // namespace PCFW::Math
