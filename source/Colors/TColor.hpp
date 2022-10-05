///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Numbers/TColorChannel.hpp"

namespace Langulus::Math
{
	namespace A
	{

		///																							
		/// An abstract color																	
		/// Used as an imposed base for any type that can be interpretable as a	
		/// color																					
		///																							
		struct Color {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) rgba;
		};

		///																							
		/// An abstract color of specific size												
		/// Used as an imposed base for any type that can be interpretable as a	
		/// color of the same size																
		///																							
		template<Count S>
		struct ColorOfSize : public Color {
			LANGULUS(CONCRETE) TColor<TVector<::std::uint8_t, S>>;
			LANGULUS_BASES(Color);
			static constexpr Count MemberCount {S};
			static_assert(S > 0, "Color size must be greater than zero");
		};

		///																							
		/// An abstract color of specific type												
		/// Used as an imposed base for any type that can be interpretable as a	
		/// color of the same type																
		///																							
		template<CT::DenseNumber T>
		struct ColorOfType : public Color {
			LANGULUS(CONCRETE) TColor<TVector<T, 4>>;
			LANGULUS_BASES(Color);
			using MemberType = T;
		};

	} // namespace Langulus::Math::A


	///																								
	///	Templated color																		
	///																								
	#pragma pack(push, 1)
	template<CT::Vector T>
	struct TColor : public T {
		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr Count MemberCount = T::MemberCount;
		LANGULUS_BASES(A::ColorOfSize<MemberCount>, A::ColorOfType<MemberType>);

	public:
		using T::T;
		using T::mArray;

		constexpr TColor(const T&);
		constexpr TColor(Logger::Color);

		template<CT::DenseNumber ALTT, CT::Dimension D>
		constexpr TColor<T>& operator = (const TColorChannel<ALTT, D>&) noexcept;

		NOD() explicit operator Flow::Code() const;
		NOD() explicit operator Logger::Color() const;
	};
	#pragma pack(pop)

} // namespace Langulus::Math

#include "TColor.inl"