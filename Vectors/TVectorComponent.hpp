#pragma once
#include "../Functions.hpp"
#include "../Dimensions.hpp"

LANGULUS_DECLARE_TRAIT(X, "X vector component");
LANGULUS_DECLARE_TRAIT(Y, "Y vector component");
LANGULUS_DECLARE_TRAIT(Z, "Z vector component");
LANGULUS_DECLARE_TRAIT(W, "W vector component");

namespace PCFW::Math
{

	PC_DECLARE_ABSTRACT_DATA(Vector);

	template<Number T, pcptr S>
	class TVector;

	/// Much shorter name																		
	template<Number T, pcptr S>
	using TVec = TVector<T, S>;

	/// Often used instantiations																
	using vec1 = TVec<real, 1>;
	using vec1f = TVec<pcr32, 1>;
	using vec1d = TVec<pcr64, 1>;
	using vec1i = TVec<pcptrSigned, 1>;
	using vec1u = TVec<pcptr, 1>;
	using vec1i8 = TVec<pci8, 1>;
	using vec1u8 = TVec<pcu8, 1>;
	using vec1i16 = TVec<pci16, 1>;
	using vec1u16 = TVec<pcu16, 1>;
	using vec1i32 = TVec<pci32, 1>;
	using vec1u32 = TVec<pcu32, 1>;
	using vec1i64 = TVec<pci64, 1>;
	using vec1u64 = TVec<pcu64, 1>;

	using vec2 = TVec<real, 2>;
	using vec2f = TVec<pcr32, 2>;
	using vec2d = TVec<pcr64, 2>;
	using vec2i = TVec<pcptrSigned, 2>;
	using vec2u = TVec<pcptr, 2>;
	using vec2i8 = TVec<pci8, 2>;
	using vec2u8 = TVec<pcu8, 2>;
	using vec2i16 = TVec<pci16, 2>;
	using vec2u16 = TVec<pcu16, 2>;
	using vec2i32 = TVec<pci32, 2>;
	using vec2u32 = TVec<pcu32, 2>;
	using vec2i64 = TVec<pci64, 2>;
	using vec2u64 = TVec<pcu64, 2>;

	using vec3 = TVec<real, 3>;
	using vec3f = TVec<pcr32, 3>;
	using vec3d = TVec<pcr64, 3>;
	using vec3i = TVec<pcptrSigned, 3>;
	using vec3u = TVec<pcptr, 3>;
	using vec3i8 = TVec<pci8, 3>;
	using vec3u8 = TVec<pcu8, 3>;
	using vec3i16 = TVec<pci16, 3>;
	using vec3u16 = TVec<pcu16, 3>;
	using vec3i32 = TVec<pci32, 3>;
	using vec3u32 = TVec<pcu32, 3>;
	using vec3i64 = TVec<pci64, 3>;
	using vec3u64 = TVec<pcu64, 3>;

	using vec4 = TVec<real, 4>;
	using vec4f = TVec<pcr32, 4>;
	using vec4d = TVec<pcr64, 4>;
	using vec4i = TVec<pcptrSigned, 4>;
	using vec4u = TVec<pcptr, 4>;
	using vec4i8 = TVec<pci8, 4>;
	using vec4u8 = TVec<pcu8, 4>;
	using vec4i16 = TVec<pci16, 4>;
	using vec4u16 = TVec<pcu16, 4>;
	using vec4i32 = TVec<pci32, 4>;
	using vec4u32 = TVec<pcu32, 4>;
	using vec4i64 = TVec<pci64, 4>;
	using vec4u64 = TVec<pcu64, 4>;

	///																								
	///	Vector component																		
	///																								
	template<Number T, Dimension INDEX>
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

} // namespace PCFW::Math