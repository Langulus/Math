///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TVector.hpp"

LANGULUS_DECLARE_TRAIT(Sampler, "Sampler trait");

namespace Langulus::Math
{

	/// Commonly used samplers																	
	using Sampler1 = TSampler<vec1>;
	using Sampler2 = TSampler<vec2>;
	using Sampler3 = TSampler<vec3>;
	using Sampler4 = TSampler<vec4>;


	///																								
	///	An abstract sampler																	
	///																								
	PC_DECLARE_ABSTRACT_DATA(Sampler);


	///																								
	///	A templated sampler																	
	///	It's just a vector, specialized for accessing textures/volumes			
	///																								
	template<ComplexNumber T>
	struct TSampler : public T {
		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr pcptr MemberCount = T::MemberCount;

		REFLECT_MANUALLY(TSampler) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(pcIsNullifiable<ME>, "Must be NULLIFIABLE");
			static_assert(sizeof(T) == sizeof(ME), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Sampler";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a sampler of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ASampler),
				REFLECT_BASE(T));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			return reflection;
		}

	public:
		using T::T;

		constexpr TSampler(const T& other)
			: T{ other } {}

		/// Convert from any sampler to text												
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			T::WriteBody(result);
			return result;
		}
	};

	PC_DEFINE_ABSTRACT_DATA(Sampler, "An abstract sampler coordinate", Sampler3);

} // namespace Langulus::Math
