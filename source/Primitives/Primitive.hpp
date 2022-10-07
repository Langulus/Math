///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Matrices/TMatrix.hpp"
#include "../Functions/Trigonometry.hpp"

namespace Langulus::Math::A
{

	struct Primitive {
		LANGULUS(INFO) "An abstract primitive";
		LANGULUS(ABSTRACT) true;
	};

	struct Topology : public Primitive {
		LANGULUS(INFO) "An abstract topology";
		LANGULUS_BASES(Primitive);
	};

} // namespace Langulus::Math::A