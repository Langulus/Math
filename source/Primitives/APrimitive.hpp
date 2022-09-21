///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Vectors.hpp"
#include "../Ranges.hpp"
#include "../Matrices/TMatrix.hpp"

namespace Langulus::Math
{

	PC_DECLARE_AND_DEFINE_ABSTRACT_DATA(Primitive, "An abstract primitive", void);
	PC_DECLARE_AND_DEFINE_ABSTRACT_DATA(Topology, "An abstract topology", void, REFLECT_BASE(APrimitive));

} // namespace Langulus::Math