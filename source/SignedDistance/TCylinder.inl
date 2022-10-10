///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Primitives/TCylinder.hpp"

/// The following code follows specific guidelines, so it is used in C++, as	
/// well as used as a basis for generating GLSL/HLSL equivalent functions		
///TODO refer to guidelines
namespace Langulus::Math
{

	/// Signed distance function for a centered 3D cylinder							
	template<CT::DenseNumber T, CT::Dimension D>
	T SignedDistance(const TVector<T, 3>& point, const TCylinder<TVector<T, 3>, D>& cylinder) {
		if constexpr (CT::Same<D, Traits::X>)
			return Length(point.yz()) - cylinder.mRadius;
		else if constexpr (CT::Same<D, Traits::Y>)
			return Length(point.xz()) - cylinder.mRadius;
		else if constexpr (CT::Same<D, Traits::Z>)
			return Length(point.xy()) - cylinder.mRadius;
		else
			LANGULUS_ERROR("Unsupported dimension");
	};

} // namespace Langulus::Math
