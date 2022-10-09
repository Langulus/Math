///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Vectors/TVector.hpp"

namespace Langulus::Math
{

	template<CT::Vector>
	struct TColor;

	using rgb24 = TColor<vec3u8>;
	using rgba32 = TColor<vec4u8>;
	using rgb96 = TColor<vec3f>;
	using rgba128 = TColor<vec4f>;

	using rgba = rgba32;
	using rgb = rgb24;

	template<CT::DenseNumber, CT::Dimension>
	struct TColorComponent;

	using red8 = TColorComponent<uint8, Traits::R>;
	using green8 = TColorComponent<uint8, Traits::G>;
	using blue8 = TColorComponent<uint8, Traits::B>;
	using alpha8 = TColorComponent<uint8, Traits::A>;
	using red32 = TColorComponent<RealSP, Traits::R>;
	using green32 = TColorComponent<RealSP, Traits::G>;
	using blue32 = TColorComponent<RealSP, Traits::B>;
	using alpha32 = TColorComponent<RealSP, Traits::A>;
	using depth16 = TColorComponent<::std::uint16_t, Traits::D>;
	using depth32 = TColorComponent<RealSP, Traits::D>;

	using red = red8;
	using green = green8;
	using blue = blue8;
	using alpha = alpha8;
	using depth = depth32;


	///																								
	///	Color channel																			
	///																								
	template<CT::DenseNumber T, CT::Dimension D>
	struct TColorComponent : public TNumber<T, TColorComponent<T, D>> {
		using Base = TNumber<T, TColorComponent<T, D>>;
	public:
		using Dimension = D;
		using MemberType = T;
		using Base::Base;
	};

} // namespace Langulus::Math
