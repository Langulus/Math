#pragma once
#include "../Functions.hpp"
#include "../Vectors/TVector.hpp"

/// Traits for accessing individual channels												
LANGULUS_DECLARE_TRAIT(R, "Red color channel");
LANGULUS_DECLARE_TRAIT(G, "Green color channel");
LANGULUS_DECLARE_TRAIT(B, "Blue color channel");
LANGULUS_DECLARE_TRAIT(A, "Alpha color channel");
LANGULUS_DECLARE_TRAIT(D, "Depth color channel");

namespace PCFW::Math
{

	/// Color channel enumeration																
	enum class ColorChannel {
		Red = 0, Green, Blue, Alpha, Depth
	};

	/// Predeclaration																			
	template<ComplexNumber T>
	struct TColor;

	/// Much shorter name																		
	template<ComplexNumber T>
	using TCol = TColor<T>;

	/// Commonly used colors																	
	using rgb24 = TCol<TVec<pcu8, 3>>;
	using rgba32 = TCol<TVec<pcu8, 4>>;
	using rgb96 = TCol<TVec<pcr32, 3>>;
	using rgba128 = TCol<TVec<pcr32, 4>>;

	using rgba = rgba32;
	using rgb = rgb24;

	template<Number T, ColorChannel INDEX>
	struct TColorChannel;

	/// Single value color representations													
	using red8 = TColorChannel<pcu8, ColorChannel::Red>;
	using red32 = TColorChannel<pcr32, ColorChannel::Red>;
	using green8 = TColorChannel<pcu8, ColorChannel::Green>;
	using green32 = TColorChannel<pcr32, ColorChannel::Green>;
	using blue8 = TColorChannel<pcu8, ColorChannel::Blue>;
	using blue32 = TColorChannel<pcr32, ColorChannel::Blue>;
	using alpha8 = TColorChannel<pcu8, ColorChannel::Alpha>;
	using alpha32 = TColorChannel<pcr32, ColorChannel::Alpha>;
	using depth16 = TColorChannel<pcu16, ColorChannel::Depth>;
	using depth32 = TColorChannel<pcr32, ColorChannel::Depth>;

	/// Commonly used colors																	
	using red = red8;
	using green = green8;
	using blue = blue8;
	using alpha = alpha8;
	using depth = depth32;


	///																								
	///	Abstract color																			
	///																								
	PC_DECLARE_ABSTRACT_DATA(Color);


	///																								
	///	Color channel																			
	///																								
	template<Number T, ColorChannel INDEX>
	struct TColorChannel : public TNumber<T, TColorChannel<T, INDEX>> {
	public:
		static constexpr auto Index = INDEX;

	private:
		static_assert(Dense<T>, "Can't have sparse color channel");
		using NUMBER_BASE = TNumber<T, TColorChannel<T, INDEX>>;

		REFLECT_MANUALLY(TColorChannel) {
			static_assert(sizeof(ME) == sizeof(T), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				if constexpr (Index == ColorChannel::Red) {
					name += "Red";
					info += "red";
				}
				else if constexpr (Index == ColorChannel::Green) {
					name += "Green";
					info += "green";
				}
				else if constexpr (Index == ColorChannel::Blue) {
					name += "Blue";
					info += "blue";
				}
				else if constexpr (Index == ColorChannel::Alpha) {
					name += "Alpha";
					info += "alpha";
				}
				else if constexpr (Index == ColorChannel::Depth) {
					name += "Depth";
					info += "depth";
				}
				else LANGULUS_ASSERT("Color channel not implemented");

				name.TypeSuffix<T>();
				name = name.StandardToken();
				info += " color channel of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(AColor),
				REFLECT_BASE(T));

			if constexpr (Index == ColorChannel::Red) {
				reflection.template SetMembers<ME>(
					REFLECT_MEMBER_TRAIT(mValue, R));
			}
			else if constexpr (Index == ColorChannel::Green) {
				reflection.template SetMembers<ME>(
					REFLECT_MEMBER_TRAIT(mValue, G));
			}
			else if constexpr (Index == ColorChannel::Blue) {
				reflection.template SetMembers<ME>(
					REFLECT_MEMBER_TRAIT(mValue, B));
			}
			else if constexpr (Index == ColorChannel::Alpha) {
				reflection.template SetMembers<ME>(
					REFLECT_MEMBER_TRAIT(mValue, A));
			}
			else if constexpr (Index == ColorChannel::Depth) {
				reflection.template SetMembers<ME>(
					REFLECT_MEMBER_TRAIT(mValue, D));
			}
			else LANGULUS_ASSERT("Color channel not implemented");

			return reflection;
		}

	public:
		using NUMBER_BASE::TNumber;

		NOD() constexpr operator T& () noexcept {
			return NUMBER_BASE::operator T&();
		}

		NOD() constexpr operator const T& () const noexcept {
			return NUMBER_BASE::operator const T&();
		}
	};

} // namespace PCFW::Math
