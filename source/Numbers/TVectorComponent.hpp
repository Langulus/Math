///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Dimensions.hpp"

namespace Langulus::Math
{

	template<class, Count>
	class TVector;

	template<class T, Count S>
	using TVec = TVector<T, S>;

	using vec1 = TVec<Real, 1>;
	using vec1f = TVec<RealSP, 1>;
	using vec1d = TVec<RealDP, 1>;
	using vec1i = TVec<signed, 1>;
	using vec1u = TVec<unsigned, 1>;
	using vec1i8 = TVec<::std::int8_t, 1>;
	using vec1u8 = TVec<::std::uint8_t, 1>;
	using vec1i16 = TVec<::std::int16_t, 1>;
	using vec1u16 = TVec<::std::uint16_t, 1>;
	using vec1i32 = TVec<::std::int32_t, 1>;
	using vec1u32 = TVec<::std::uint32_t, 1>;
	using vec1i64 = TVec<::std::int64_t, 1>;
	using vec1u64 = TVec<::std::uint64_t, 1>;

	using vec2 = TVec<Real, 2>;
	using vec2f = TVec<RealSP, 2>;
	using vec2d = TVec<RealDP, 2>;
	using vec2i = TVec<signed, 2>;
	using vec2u = TVec<unsigned, 2>;
	using vec2i8 = TVec<::std::int8_t, 2>;
	using vec2u8 = TVec<::std::uint8_t, 2>;
	using vec2i16 = TVec<::std::int16_t, 2>;
	using vec2u16 = TVec<::std::uint16_t, 2>;
	using vec2i32 = TVec<::std::int32_t, 2>;
	using vec2u32 = TVec<::std::uint32_t, 2>;
	using vec2i64 = TVec<::std::int64_t, 2>;
	using vec2u64 = TVec<::std::uint64_t, 2>;

	using vec3 = TVec<Real, 3>;
	using vec3f = TVec<RealSP, 3>;
	using vec3d = TVec<RealDP, 3>;
	using vec3i = TVec<signed, 3>;
	using vec3u = TVec<unsigned, 3>;
	using vec3i8 = TVec<::std::int8_t, 3>;
	using vec3u8 = TVec<::std::uint8_t, 3>;
	using vec3i16 = TVec<::std::int16_t, 3>;
	using vec3u16 = TVec<::std::uint16_t, 3>;
	using vec3i32 = TVec<::std::int32_t, 3>;
	using vec3u32 = TVec<::std::uint32_t, 3>;
	using vec3i64 = TVec<::std::int64_t, 3>;
	using vec3u64 = TVec<::std::uint64_t, 3>;

	using vec4 = TVec<Real, 4>;
	using vec4f = TVec<RealSP, 4>;
	using vec4d = TVec<RealDP, 4>;
	using vec4i = TVec<signed, 4>;
	using vec4u = TVec<unsigned, 4>;
	using vec4i8 = TVec<::std::int8_t, 4>;
	using vec4u8 = TVec<::std::uint8_t, 4>;
	using vec4i16 = TVec<::std::int16_t, 4>;
	using vec4u16 = TVec<::std::uint16_t, 4>;
	using vec4i32 = TVec<::std::int32_t, 4>;
	using vec4u32 = TVec<::std::uint32_t, 4>;
	using vec4i64 = TVec<::std::int64_t, 4>;
	using vec4u64 = TVec<::std::uint64_t, 4>;


	///																								
	///	Vector component																		
	///																								
	template<CT::Dense T, class DIMENSION = void>
	struct TVectorComponent : public TNumber<T, TVectorComponent<T, INDEX>> {
	private:
		using NUMBER_BASE = TNumber<T, TVectorComponent<T, INDEX>>;

	public:
		static_assert(Dense<T>, "Can't have sparse vector component");
		static constexpr auto Index = INDEX;

		REFLECT_MANUALLY(TVectorComponent) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(pcIsNullifiable<ME>, "Must be NULLIFIABLE");
			static_assert(sizeof(T) == sizeof(ME), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				if constexpr (Index == Dimension::X) {
					name += "VecX";
					info += "x";
				}
				else if constexpr (Index == Dimension::Y) {
					name += "VecY";
					info += "y";
				}
				else if constexpr (Index == Dimension::Z) {
					name += "VecZ";
					info += "z";
				}
				else if constexpr (Index == Dimension::W) {
					name += "VecW";
					info += "w";
				}
				else LANGULUS_ASSERT("Unsupported vector component index");
				name.TypeSuffix<T>();
				name = name.StandardToken();
				info += " vector component of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(AVector),
				REFLECT_BASE(T));
			return reflection;
		}

	public:
		using NUMBER_BASE::TNumber;

		NOD() constexpr operator T& () noexcept {
			return NUMBER_BASE::mValue;
		}

		NOD() constexpr operator const T& () const noexcept {
			return NUMBER_BASE::mValue;
		}
	};

} // namespace Langulus::Math