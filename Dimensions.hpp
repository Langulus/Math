#pragma once
#include "IncludeMemory.hpp"

namespace PCFW::Math
{

	/// Unique dimension identifiers															
	enum class Dimension {
		X, Y, Z, W, Time
	};


	///																								
	///	Templated dimensional																
	///																								
	/// Used as a common base for any type that can be interpretable as a		
	/// vector of the same size and dimensions											
	///																								
	template<pcptr RANK>
	struct TRank {
		static constexpr pcptr Rank = RANK;

		REFLECT_MANUALLY(TRank) {
			static const Text name = Text("Rank") + Rank;
			auto reflection = RTTI::ReflectData::From<ME>(name, "A rank pattern");
			reflection.MakeAbstract();
			return reflection;
		}
	};

} // namespace PCFW::Math