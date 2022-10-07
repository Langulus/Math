///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Vectors/TVector.hpp"
#include "Vectors/TNormal.hpp"
#include "Vectors/TSampler.hpp"
#include "Vectors/TForce.hpp"
#include "Vectors/TSizer.hpp"

namespace Langulus::Math
{

	using Grad2v1 = TGrad2<vec1>;
	using Grad2v1f = TGrad2<vec1f>;
	using Grad2v1d = TGrad2<vec1d>;
	using Grad2v1i = TGrad2<vec1i>;
	using Grad2v1u = TGrad2<vec1u>;

	using Grad2v2 = TGrad2<vec2>;
	using Grad2v2f = TGrad2<vec2f>;
	using Grad2v2d = TGrad2<vec2d>;
	using Grad2v2i = TGrad2<vec2i>;
	using Grad2v2u = TGrad2<vec2u>;

	using Grad2v3 = TGrad2<vec3>;
	using Grad2v3f = TGrad2<vec3f>;
	using Grad2v3d = TGrad2<vec3d>;
	using Grad2v3i = TGrad2<vec3i>;
	using Grad2v3u = TGrad2<vec3u>;

	using Grad2v4 = TGrad2<vec4>;
	using Grad2v4f = TGrad2<vec4f>;
	using Grad2v4d = TGrad2<vec4d>;
	using Grad2v4i = TGrad2<vec4i>;
	using Grad2v4u = TGrad2<vec4u>;

	/// Canonical vectors																		
	namespace Vectors
	{

		template<CT::DenseNumber T>
		constexpr TVector<T, 4> Origin {0, 0, 0, 0};

		template<CT::DenseNumber T>
		constexpr TVector<T, 4> Forward {0, 0, 1, 0};

		template<CT::DenseNumber T>
		constexpr TVector<T, 4> Backward {0, 0, -1, 0};

		template<CT::DenseNumber T>
		constexpr TVector<T, 4> Up {0, 1, 0, 0};

		template<CT::DenseNumber T>
		constexpr TVector<T, 4> Down {0, -1, 0, 0};

		template<CT::DenseNumber T>
		constexpr TVector<T, 4> Right {1, 0, 0, 0};

		template<CT::DenseNumber T>
		constexpr TVector<T, 4> Left {-1, 0, 0, 0};

	} // Langulus::Math::Vectors
} // namespace Langulus::Math