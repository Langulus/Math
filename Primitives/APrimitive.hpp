#pragma once
#include "../Vectors.hpp"
#include "../Ranges.hpp"
#include "../Matrices/TMatrix.hpp"

namespace PCFW::Math
{

	PC_DECLARE_AND_DEFINE_ABSTRACT_DATA(Primitive, "An abstract primitive", void);
	PC_DECLARE_AND_DEFINE_ABSTRACT_DATA(Topology, "An abstract topology", void, REFLECT_BASE(APrimitive));

} // namespace PCFW::Math