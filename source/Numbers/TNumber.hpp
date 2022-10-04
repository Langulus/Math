///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Common.hpp"

namespace Langulus::Math
{

	///																								
	///	Templated number																		
	///																								
	/// Serves various kinds of purposes:													
	///	1. Provides a safety layer, that asserts underflows/overflows/etc.	
	///		when building in safe-mode														
	///	2. Provides consistent handling of infinities across all arithmetic	
	///		types																					
	///	3. Allows for types, such as std::int8_t and std::uint8_t to be		
	///		considered CT::Number, without suffering the usual implicit			
	///		conversion-to-text-hell															
	///	4. Gives a layer for integration with langulus flows and verbs			
	///																								
	template<class T, class WRAPPER>
	class TNumber {
	public:
		LANGULUS(NUMBER) T;

		T mValue;
	};

} // namespace Langulus::Math