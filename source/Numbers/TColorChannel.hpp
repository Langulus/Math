///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TVectorComponent.hpp"

namespace Langulus::Math
{

	template<CT::Vector>
	struct TColor;

	template<CT::Vector T>
	using TCol = TColor<T>;

	using rgb24 = TCol<vec3u8>;
	using rgba32 = TCol<vec4u8>;
	using rgb96 = TCol<vec3f>;
	using rgba128 = TCol<vec4f>;

	using rgba = rgba32;
	using rgb = rgb24;

	template<CT::DenseNumber, CT::Dimension>
	struct TColorChannel;

	using red8 = TColorChannel<uint8, Traits::R>;
	using green8 = TColorChannel<uint8, Traits::G>;
	using blue8 = TColorChannel<uint8, Traits::B>;
	using alpha8 = TColorChannel<uint8, Traits::A>;
	using red32 = TColorChannel<RealSP, Traits::R>;
	using green32 = TColorChannel<RealSP, Traits::G>;
	using blue32 = TColorChannel<RealSP, Traits::B>;
	using alpha32 = TColorChannel<RealSP, Traits::A>;
	using depth16 = TColorChannel<::std::uint16_t, Traits::D>;
	using depth32 = TColorChannel<RealSP, Traits::D>;

	using red = red8;
	using green = green8;
	using blue = blue8;
	using alpha = alpha8;
	using depth = depth32;


	///																								
	///	Color channel																			
	///																								
	template<CT::DenseNumber T, CT::Dimension D>
	struct TColorChannel : public TNumber<T, TColorChannel<T, D>> {
		using Base = TNumber<T, TColorChannel<T, D>>;
	public:
		using Dimension = D;
		using MemberType = T;
		using Base::TNumber;
	};

} // namespace Langulus::Math
