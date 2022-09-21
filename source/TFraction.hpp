///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "IncludeMemory.hpp"
#include "Functions.hpp"

namespace Langulus::Math
{

	/// Predeclarations																			
	template<RealNumber T>
	struct TFraction;

	using Fraction = TFraction<real>;


	///																								
	///	Templated fraction																	
	///																								
	/// It's a specialized number type, that acts only on the fractional part	
	/// of real numbers. Zeroes to the front of this number are acceptable		
	/// (034 -> 00034, etc. become accordingly 0.034 and 0.00034 when real)		
	///																								
	template<RealNumber T>
	struct TFraction : public TNumber<T, TFraction<T>> {
	private:
		using NUMBER_BASE = TNumber<T, TFraction<T>>;
	public:
		REFLECT_MANUALLY(TFraction) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(pcIsNullifiable<ME>, "Must be NULLIFIABLE");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Fraction";
				if constexpr (!Same<T, real>)
					name.TypeSuffix<T>();
				name = name.StandardToken();
				info += "a fraction of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ANumber));
			reflection.template SetAbilities<ME>(
				REFLECT_ABILITY(Create),
				REFLECT_CONVERSIONS(T, GASM));
			return reflection;
		}

		using NUMBER_BASE::TNumber;

		///																							
		PC_VERB(Create) {
			TODO();
		}

		/// Convert to text																		
		NOD() explicit operator GASM() const {
			GASM result;
			result += static_cast<T>(*this);
			return result;
		}
	};

	/// Quaternion typelists																	
	struct TFractionTypeGenerator {
		template<RealNumber... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TFraction<T>...>;
	};

	using TFractionTypes = TTYPELIST_FROM(TFractionTypeGenerator, RealTypes);

} // namespace Langulus::Math
