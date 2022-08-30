#pragma once
#include "TVector.hpp"
#include "../Level.hpp"

namespace PCFW::Math
{

	/// Commonly used forces																	
	using Force2 = TForce<vec2>;
	using Force3 = TForce<vec3>;
	using Force = Force3;


	///																								
	///	Abstract force																			
	///																								
	PC_DECLARE_ABSTRACT_DATA(Force);


	///																								
	///	Templated force																		
	///																								
	template<ComplexNumber T>
	struct TForce : public T, private AForce {
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static constexpr pcptr MemberCount = PointType::MemberCount;

		REFLECT_MANUALLY(TForce) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(pcIsNullifiable<ME>, "Must be NULLIFIABLE");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Force";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr(!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a force of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(AForce),
				REFLECT_BASE(T));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mLevel, Level));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			return reflection;
		}

	public:
		/// Construct force from vector and level											
		///	@param force - the direction times magnitude of the force			
		///	@param level - the level in which the force acts						
		constexpr TForce(const T& force, Level level = {}) noexcept
			: T {force}
			, mLevel {level} {}

		/// Convert from any force to text													
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			result += GASM::OpenScope;
			auto& asVector = static_cast<const T&>(*this);
			for (auto& x : asVector) {
				result += x;
				result += GASM::AndSeparator;
			}
			result += mLevel;
			result += GASM::CloseScope;
			return result;
		}

		// The level in which the force operates									
		Level mLevel {};
	};


	PC_DEFINE_ABSTRACT_DATA(Force, "An abstract force", Force);

} // namespace PCFW::Math