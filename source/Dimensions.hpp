///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "IncludeMemory.hpp"

namespace Langulus::Math
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

} // namespace Langulus::Math