#pragma once
#include "TVector.hpp"

LANGULUS_DECLARE_TRAIT(Aim, "Rotation trait; used for normals/tangents/bitangents");

namespace PCFW::Math
{

	/// Commonly used 3D normal																
	using Normal = TNormal<vec3>;


	///																								
	///	Abstract normal																		
	///																								
	PC_DECLARE_ABSTRACT_DATA(Normal);


	///																								
	///	Templated normal																		
	///	It is essentially a vector that gets normalized after any change		
	///																								
	template<ComplexNumber T>
	struct TNormal : public T, NOT_NULLIFIABLE {
		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr pcptr MemberCount = T::MemberCount;
		static_assert(MemberCount > 1, "Can't have TNormal that is smaller than 2D");

		REFLECT_MANUALLY(TNormal) {
			// Zero normal is considered degenerate								
			static_assert(!pcIsNullifiable<ME>, "Must NOT be NULLIFIABLE");
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(sizeof(T) == sizeof(ME), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Normal";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a normalized vector of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ANormal),
				REFLECT_BASE(T));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			return reflection;
		}

	public:
		using T::T;

		/// Construct a normal from a vector												
		///	@param other - the vector to normalize										
		constexpr TNormal(const T& other)
			: T {other.Normalize()} {}

		/// Convert from any normal to text													
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			T::WriteBody(result);
			return result;
		}
	};

	PC_DEFINE_ABSTRACT_DATA(Normal, "An abstract normalized value", Normal);

} // namespace PCFW::Math