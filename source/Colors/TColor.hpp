///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TColorChannel.hpp"

namespace Langulus::Math
{

	using ConsoleColor = Logger::ConsoleColor;

	///																								
	///	Abstract color of specific size													
	///																								
	template<pcptr SIZE>
	struct EMPTY_BASE() TSizedColor : POD, NULLIFIABLE {
		static_assert(SIZE > 0, "Color size must be greater than zero");
		static constexpr pcptr MemberCount = SIZE;
		REFLECT_MANUALLY(TSizedColor);
	};

	///																								
	///	Templated color																		
	///																								
	#pragma pack(push, 1)
	template<ComplexNumber T>
	struct EMPTY_BASE() TColor : public T {
	public:
		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr pcptr MemberCount = T::MemberCount;
		REFLECT_MANUALLY(TColor);

	public:
		using T::T;

		constexpr TColor(const T&);

		template<pcptr SIZE = T::MemberCount>
		TColor(ConsoleColor) requires (SIZE >= 3);

		template<ColorChannel INDEX, class K = typename T::MemberType, pcptr SIZE = T::MemberCount>
		constexpr TColor<T>& operator = (const TColorChannel<K, INDEX>&) noexcept requires (pcptr(INDEX) < SIZE);

		NOD() explicit operator GASM() const;
		NOD() explicit operator ConsoleColor() const;
	};
	#pragma pack(pop)

	PC_DEFINE_ABSTRACT_DATA(Color, "An abstract color", rgba);

} // namespace Langulus::Math

#include "TColor.inl"