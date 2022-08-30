#pragma once
#include "Colors/TColor.hpp"
#include "Vectors.hpp"

namespace PCFW::Math
{

	namespace Colors
	{
		constexpr rgba White { 255, 255, 255, 255 };
		constexpr rgba Black { 0, 0, 0, 255 };
		constexpr rgba Grey { 127, 127, 127, 255 };
		constexpr rgba Red { 255, 0, 0, 255 };
		constexpr rgba Green { 0, 255, 0, 255 };
		constexpr rgba DarkGreen { 0, 128, 0, 255 };
		constexpr rgba Blue { 0, 0, 255, 255 };
		constexpr rgba DarkBlue { 0, 0, 128, 255 };
		constexpr rgba Cyan { 128, 128, 255, 255 };
		constexpr rgba DarkCyan { 80, 80, 128, 255 };
		constexpr rgba Orange { 128, 128, 0, 255 };
		constexpr rgba Yellow { 255, 255, 0, 255 };
		constexpr rgba Purple { 255, 0, 255, 255 };
		constexpr rgba DarkPurple { 128, 0, 128, 255 };
	}

	/// Luma weights for BT.601 standard, used for convertion to grayscale		
	constexpr vec3 pcLumaBT601 { real(0.299), real(0.587), real(0.114) };

	/// Luma weights for BT.709 standard, used for convertion to grayscale		
	constexpr vec3 pcLumaBT709 { real(0.2126), real(0.7152), real(0.0722) };

	/// Luma weights for BT.2100 standard, used for convertion to grayscale		
	constexpr vec3 pcLumaBT2100 { real(0.2627), real(0.6780), real(0.0593) };

	/// Color typelists																			
	struct TColorTypeGenerator {
		template<ComplexNumber... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TColor<T>...>;
	};

	using TColor1Types = decltype(TColorTypeGenerator::ForEach(std::declval<TVec1Types>()));
	using TColor2Types = decltype(TColorTypeGenerator::ForEach(std::declval<TVec2Types>()));
	using TColor3Types = decltype(TColorTypeGenerator::ForEach(std::declval<TVec3Types>()));
	using TColor4Types = decltype(TColorTypeGenerator::ForEach(std::declval<TVec4Types>()));
	using TColorTypes = TTYPELIST_CAT4(TColor1Types, TColor2Types ,TColor3Types ,TColor4Types);

} // namespace PCFW::Math

namespace PCFW::Constants
{
	namespace Colors = Math::Colors;
}

LANGULUS_DECLARE_CONSTANT(White, Colors::White, "White color");
LANGULUS_DECLARE_CONSTANT(Black, Colors::Black, "Black color");
LANGULUS_DECLARE_CONSTANT(Grey, Colors::Grey, "Grey color");
LANGULUS_DECLARE_CONSTANT(Red, Colors::Red, "Red color");
LANGULUS_DECLARE_CONSTANT(Green, Colors::Green, "Green color");
LANGULUS_DECLARE_CONSTANT(DarkGreen, Colors::DarkGreen, "Dark green color");
LANGULUS_DECLARE_CONSTANT(Blue, Colors::Blue, "Blue color");
LANGULUS_DECLARE_CONSTANT(DarkBlue, Colors::DarkBlue, "Dark blue color");
LANGULUS_DECLARE_CONSTANT(Cyan, Colors::Cyan, "Cyan color");
LANGULUS_DECLARE_CONSTANT(DarkCyan, Colors::DarkCyan, "Dark cyan color");
LANGULUS_DECLARE_CONSTANT(Orange, Colors::Orange, "Orange color");
LANGULUS_DECLARE_CONSTANT(Yellow, Colors::Yellow, "Yellow color");
LANGULUS_DECLARE_CONSTANT(Purple, Colors::Purple, "Purple color");
LANGULUS_DECLARE_CONSTANT(DarkPurple, Colors::DarkPurple, "Dark purple color");