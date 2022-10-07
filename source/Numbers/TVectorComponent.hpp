///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Dimensions.hpp"
#include "../Numbers/TNumber.hpp"

namespace Langulus::Math
{

	template<CT::DenseNumber, Count>
	class TVector;

	using vec1 = TVector<Real, 1>;
	using vec1f = TVector<RealSP, 1>;
	using vec1d = TVector<RealDP, 1>;
	using vec1i = TVector<signed, 1>;
	using vec1u = TVector<unsigned, 1>;
	using vec1i8 = TVector<::std::int8_t, 1>;
	using vec1u8 = TVector<uint8, 1>;
	using vec1i16 = TVector<::std::int16_t, 1>;
	using vec1u16 = TVector<::std::uint16_t, 1>;
	using vec1i32 = TVector<::std::int32_t, 1>;
	using vec1u32 = TVector<::std::uint32_t, 1>;
	using vec1i64 = TVector<::std::int64_t, 1>;
	using vec1u64 = TVector<::std::uint64_t, 1>;

	using vec2 = TVector<Real, 2>;
	using vec2f = TVector<RealSP, 2>;
	using vec2d = TVector<RealDP, 2>;
	using vec2i = TVector<signed, 2>;
	using vec2u = TVector<unsigned, 2>;
	using vec2i8 = TVector<::std::int8_t, 2>;
	using vec2u8 = TVector<uint8, 2>;
	using vec2i16 = TVector<::std::int16_t, 2>;
	using vec2u16 = TVector<::std::uint16_t, 2>;
	using vec2i32 = TVector<::std::int32_t, 2>;
	using vec2u32 = TVector<::std::uint32_t, 2>;
	using vec2i64 = TVector<::std::int64_t, 2>;
	using vec2u64 = TVector<::std::uint64_t, 2>;

	using vec3 = TVector<Real, 3>;
	using vec3f = TVector<RealSP, 3>;
	using vec3d = TVector<RealDP, 3>;
	using vec3i = TVector<signed, 3>;
	using vec3u = TVector<unsigned, 3>;
	using vec3i8 = TVector<::std::int8_t, 3>;
	using vec3u8 = TVector<uint8, 3>;
	using vec3i16 = TVector<::std::int16_t, 3>;
	using vec3u16 = TVector<::std::uint16_t, 3>;
	using vec3i32 = TVector<::std::int32_t, 3>;
	using vec3u32 = TVector<::std::uint32_t, 3>;
	using vec3i64 = TVector<::std::int64_t, 3>;
	using vec3u64 = TVector<::std::uint64_t, 3>;

	using vec4 = TVector<Real, 4>;
	using vec4f = TVector<RealSP, 4>;
	using vec4d = TVector<RealDP, 4>;
	using vec4i = TVector<signed, 4>;
	using vec4u = TVector<unsigned, 4>;
	using vec4i8 = TVector<::std::int8_t, 4>;
	using vec4u8 = TVector<uint8, 4>;
	using vec4i16 = TVector<::std::int16_t, 4>;
	using vec4u16 = TVector<::std::uint16_t, 4>;
	using vec4i32 = TVector<::std::int32_t, 4>;
	using vec4u32 = TVector<::std::uint32_t, 4>;
	using vec4i64 = TVector<::std::int64_t, 4>;
	using vec4u64 = TVector<::std::uint64_t, 4>;


	///																								
	///	Vector component																		
	///																								
	template<CT::DenseNumber T, CT::Dimension D>
	class TVectorComponent : public TNumber<T, TVectorComponent<T, D>> {
		using Base = TNumber<T, TVectorComponent<T, D>>;
	public:
		using Dimension = D;
		using MemberType = T;
		using Base::TNumber;
	};

} // namespace Langulus::Math