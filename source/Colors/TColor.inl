///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TColor.hpp"
#define TEMPLATE() template<CT::Vector T>

namespace Langulus::Math
{

	/// Covert a console color to a 3-component color									
	///	@param from - the console color to create from								
	TEMPLATE()
	constexpr TColor<T>::TColor(Logger::Color from)
		: T {} {
		if constexpr (MemberCount == 4) {
			if constexpr (CT::Real<MemberType>)
				mArray[3] = 1;
			else
				mArray[3] = 255;
		}

		switch (from) {
		case Logger::DarkBlue:
		case Logger::DarkBlueBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[2] = 0.5;
			else
				mArray[2] = 128;
			break;
		case Logger::Blue:
		case Logger::BlueBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[2] = 1.0;
			else
				mArray[2] = 255;
			break;
		case Logger::DarkGreen:
		case Logger::DarkGreenBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[1] = 0.5;
			else
				mArray[1] = 128;
			break;
		case Logger::DarkCyan:
		case Logger::DarkCyanBgr:
			if constexpr (CT::Real<MemberType>) {
				mArray[0] = mArray[1] = 0.33333;
				mArray[2] = 0.5;
			}
			else {
				mArray[0] = mArray[1] = 85;
				mArray[2] = 128;
			}
			break;
		case Logger::Cyan:
		case Logger::CyanBgr:
			if constexpr (CT::Real<MemberType>) {
				mArray[0] = mArray[1] = 0.5;
				mArray[2] = 1.0;
			}
			else {
				mArray[0] = mArray[1] = 128;
				mArray[2] = 255;
			}
			break;
		case Logger::Green:
		case Logger::GreenBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[1] = 1.0;
			else
				mArray[1] = 255;
			break;
		case Logger::DarkRed:
		case Logger::DarkRedBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = 0.5;
			else
				mArray[0] = 128;
			break;
		case Logger::DarkPurple:
		case Logger::DarkPurpleBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = mArray[2] = 0.5;
			else
				mArray[0] = mArray[2] = 128;
			break;
		case Logger::Purple:
		case Logger::PurpleBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = mArray[2] = 1.0;
			else
				mArray[0] = mArray[2] = 255;
			break;
		case Logger::DarkYellow:
		case Logger::DarkYellowBgr:
			if constexpr (CT::Real<MemberType>) {
				mArray[0] = 0.5;
				mArray[1] = 0.333333;
			}
			else {
				mArray[0] = 128;
				mArray[1] = 85;
			}
			break;
		case Logger::DarkGray:
		case Logger::DarkGrayBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = mArray[1] = mArray[2] = 0.33333;
			else
				mArray[0] = mArray[1] = mArray[2] = 85;
			break;
		case Logger::Yellow:
		case Logger::YellowBgr:
			if constexpr (CT::Real<MemberType>) {
				mArray[0] = 1.0;
				mArray[1] = 0.5;
			}
			else {
				mArray[0] = 255;
				mArray[1] = 128;
			}
			break;
		case Logger::Red:
		case Logger::RedBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = 1.0;
			else
				mArray[0] = 255;
			break;
		case Logger::White:
		case Logger::WhiteBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = mArray[1] = mArray[2] = 1.0;
			else
				mArray[0] = mArray[1] = mArray[2] = 255;
			break;
		case Logger::Gray:
		case Logger::GrayBgr:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = mArray[1] = mArray[2] = 0.5;
			else
				mArray[0] = mArray[1] = mArray[2] = 128;
			break;
		case Logger::Black:
		case Logger::BlackBgr:
		case Logger::NoForeground:
		case Logger::NoBackground:
			if constexpr (CT::Real<MemberType>)
				mArray[0] = mArray[1] = mArray[2] = 0.0;
			else
				mArray[0] = mArray[1] = mArray[2] = 0;
			break;
		}
	}

	/// Copy a channel																			
	TEMPLATE()
	template<CT::DenseNumber ALTT, CT::Dimension D>
	constexpr TColor<T>& TColor<T>::operator = (const TColorComponent<ALTT, D>& com) noexcept {
		static_assert(D::Index < MemberCount, "Index out of bounds");
		mArray[D::Index] = Adapt(com.mValue);
		return *this;
	}

	/// Serialize the color to flow code													
	TEMPLATE()
	TColor<T>::operator Flow::Code() const {
		return Serialize<TColor>();
	}

	/// Covert to a console color																
	TEMPLATE()
	TColor<T>::operator Logger::Color() const {
		constexpr Logger::Color ColorMap[3][3][3] = {
			{
				// 0 Red																		
				{ Logger::Black,		Logger::DarkBlue,		Logger::Blue	},	// 0 Green	
				{ Logger::DarkGreen,	Logger::DarkCyan,		Logger::Cyan	},	// 1 Green	
				{ Logger::Green,		Logger::Cyan,			Logger::Cyan	},	// 2 Green	
				// ^ 0 blue				|   ^ 1 blue			|   ^ 2 blue		
			},
			{
				// 1 Red																		
				{ Logger::DarkRed,	Logger::DarkPurple,	Logger::Purple },	// 0 Green	
				{ Logger::DarkYellow,Logger::Gray,			Logger::Cyan	},	// 1 Green	
				{ Logger::Yellow,		Logger::Green,			Logger::Cyan	},	// 2 Green	
				// ^ 0 blue				|   ^ 1 blue			|   ^ 2 blue		
			},
			{
				// 2 Red																		
				{ Logger::Red,			Logger::Red,			Logger::Purple },	// 0 Green	
				{ Logger::Yellow,		Logger::Red,			Logger::Purple },	// 1 Green	
				{ Logger::Yellow,		Logger::Yellow,		Logger::White	},	// 2 Green	
				// ^ 0 blue				|   ^ 1 blue			|   ^ 2 blue		
			}
		};

		constexpr MemberType d3 {3};
		if constexpr (CT::Real<MemberType>) {
			const auto red = static_cast<::std::uint8_t>(
				Clamp01(mArray[0]) * d3);
			const auto green = static_cast<::std::uint8_t>(
				Clamp01(mArray[1]) * d3);
			const auto blue = static_cast<::std::uint8_t>(
				Clamp01(mArray[2]) * d3);
			return ColorMap[red][green][blue];
		}
		else {
			constexpr auto third = ::std::numeric_limits<MemberType>::max() / d3;
			return ColorMap
				[mArray[0] / third]
				[mArray[1] / third]
				[mArray[2] / third];
		}
	}

} // namespace Langulus::Math

#undef TEMPLATE
