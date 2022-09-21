///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
namespace Langulus::Math
{

	template<pcptr SIZE>
	REFLECT_MANUALLY_IMPL(TSizedColor<SIZE>) {
		static_assert(pcIsPOD<ME>, "Type must be POD");
		static_assert(pcIsNullifiable<ME>, "Type must be NULLIFIABLE");
		static GASM name, info;
		if (name.IsEmpty()) {
			name += "Color";
			name += MemberCount;
			name = name.StandardToken();
			info += "an abstract color of a size ";
			info += MemberCount;
		}

		auto reflection = RTTI::ReflectData::From<ME>(name, info);
		reflection.mConcrete = DataID::Of<rgba>;
		reflection.template SetBases<ME>(
			REFLECT_BASE(AColor));
		reflection.MakeAbstract();
		return reflection;
	}

	#define TEMPLATE() template<ComplexNumber T>

	TEMPLATE()
	REFLECT_MANUALLY_IMPL(TColor<T>) {
		static_assert(sizeof(ME) == sizeof(T), "Size mismatch");
		static_assert(pcIsPOD<ME>, "Type must be POD");
		static_assert(pcIsNullifiable<ME>, "Type must be NULLIFIABLE");
		static GASM name, info;
		if (name.IsEmpty()) {
			if constexpr (MemberCount == 3 && Same<MemberType, pcu8>)
				name = "rgb";
			else if constexpr (MemberCount == 4 && Same<MemberType, pcu8>)
				name = "rgba";
			else {
				name += "Color";
				name += MemberCount;
				name.TypeSuffix<MemberType>();
			}
			name = name.StandardToken();
			info += "a color with ";
			info += MemberCount;
			info += " channels of type ";
			info += DataID::Reflect<MemberType>()->GetToken();
		}

		auto reflection = RTTI::ReflectData::From<ME>(name, info);
		reflection.template SetBases<ME>(
			REFLECT_BASE(TSizedColor<MemberCount>),
			REFLECT_BASE(T));
		reflection.template SetAbilities<ME>(
			REFLECT_CONVERSIONS(GASM));

		if constexpr (MemberCount == 1) {
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], R));
		}
		else if constexpr (MemberCount == 2) {
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], R),
				REFLECT_MEMBER_TRAIT(mArray[1], G)
			);
		}
		else if constexpr (MemberCount == 3) {
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], R),
				REFLECT_MEMBER_TRAIT(mArray[1], G),
				REFLECT_MEMBER_TRAIT(mArray[2], B)
			);
		}
		else if constexpr (MemberCount == 4) {
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], R),
				REFLECT_MEMBER_TRAIT(mArray[1], G),
				REFLECT_MEMBER_TRAIT(mArray[2], B),
				REFLECT_MEMBER_TRAIT(mArray[3], A)
			);
		}
		else reflection.template SetMembers<ME>(
			REFLECT_MEMBER(mArray));
		return reflection;
	}

	/// Construct color from vector															
	/// @param other - the vector to copy													
	TEMPLATE()
	constexpr TColor<T>::TColor(const T& other)
		: T {other} {}

	/// Covert a console color to a 3-component color									
	///	@param from - the console color to create from								
	TEMPLATE()
	template<pcptr SIZE>
	TColor<T>::TColor(ConsoleColor from) requires (SIZE >= 3)
		: T {} {
		if constexpr (MemberCount == 4) {
			if constexpr (RealNumber<MemberType>)	T::mArray[3] = 1;
			else											T::mArray[3] = 255;
		}

		switch (from) {
		case ccDarkBlue:
			if constexpr (RealNumber<MemberType>)	T::mArray[2] = 0.5;
			else											T::mArray[2] = 128;
			break;
		case ccBlue:
			if constexpr (RealNumber<MemberType>)	T::mArray[2] = 1.0;
			else											T::mArray[2] = 255;
			break;
		case ccDarkGreen:
			if constexpr (RealNumber<MemberType>)	T::mArray[1] = 0.5;
			else											T::mArray[1] = 128;
			break;
		case ccDarkCyan:
			if constexpr (RealNumber<MemberType>) {
				T::mArray[0] = T::mArray[1] = 0.33333;
				T::mArray[2] = 0.5;
			}
			else {
				T::mArray[0] = T::mArray[1] = 85;
				T::mArray[2] = 128;
			}
			break;
		case ccCyan:
			if constexpr (RealNumber<MemberType>) {
				T::mArray[0] = T::mArray[1] = 0.5;
				T::mArray[2] = 1.0;
			}
			else {
				T::mArray[0] = T::mArray[1] = 128;
				T::mArray[2] = 255;
			}
			break;
		case ccGreen:
			if constexpr (RealNumber<MemberType>)	T::mArray[1] = 1.0;
			else											T::mArray[1] = 255;
			break;
		case ccDarkRed:
			if constexpr (RealNumber<MemberType>)	T::mArray[0] = 0.5;
			else											T::mArray[0] = 128;
			break;
		case ccDarkPurple:
			if constexpr (RealNumber<MemberType>)
				T::mArray[0] = T::mArray[2] = 0.5;
			else
				T::mArray[0] = T::mArray[2] = 128;
			break;
		case ccPurple:
			if constexpr (RealNumber<MemberType>)
				T::mArray[0] = T::mArray[2] = 1.0;
			else
				T::mArray[0] = T::mArray[2] = 255;
			break;
		case ccDarkYellow:
			if constexpr (RealNumber<MemberType>) {
				T::mArray[0] = 0.5;
				T::mArray[1] = 0.333333;
			}
			else {
				T::mArray[0] = 128;
				T::mArray[1] = 85;
			}
			break;
		case ccGray:
			if constexpr (RealNumber<MemberType>)
				T::mArray[0] = T::mArray[1] = T::mArray[2] = 0.33333;
			else
				T::mArray[0] = T::mArray[1] = T::mArray[2] = 85;
			break;
		case ccYellow:
			if constexpr (RealNumber<MemberType>) {
				T::mArray[0] = 1.0;
				T::mArray[1] = 0.5;
			}
			else {
				T::mArray[0] = 255;
				T::mArray[1] = 128;
			}
			break;
		case ccRed:
			if constexpr (RealNumber<MemberType>)	T::mArray[0] = 1.0;
			else											T::mArray[0] = 255;
			break;
		case ccWhite:
			if constexpr (RealNumber<MemberType>)
				T::mArray[0] = T::mArray[1] = T::mArray[2] = 1.0;
			else
				T::mArray[0] = T::mArray[1] = T::mArray[2] = 255;
			break;
		case ccDarkWhite:
			if constexpr (RealNumber<MemberType>)
				T::mArray[0] = T::mArray[1] = T::mArray[2] = 0.5;
			else
				T::mArray[0] = T::mArray[1] = T::mArray[2] = 128;
			break;
		}
	}

	/// Copy a channel																			
	TEMPLATE()
	template<ColorChannel INDEX, class K, pcptr SIZE>
	constexpr TColor<T>& TColor<T>::operator = (const TColorChannel<K, INDEX>& com) noexcept requires (pcptr(INDEX) < SIZE) {
		constexpr auto idx = pcptr(INDEX);
		static_assert(idx < MemberCount, "Index out of bounds");
		if constexpr (Same<K, MemberType>)
			(*this)[idx] = com.mValue;
		else
			(*this)[idx] = static_cast<typename T::DenseT>(com.mValue);
		return *this;
	}

	/// Serialize the color to GASM															
	TEMPLATE()
	TColor<T>::operator GASM() const {
		GASM result;
		result += DataID::Of<ME>;
		T::WriteBody(result);
		return result;
	}

	/// Covert to a console color																
	TEMPLATE()
	TColor<T>::operator ConsoleColor() const {
		constexpr ConsoleColor ColorMap[3][3][3] = {
			{
				// 0 Red																		
				{ ccBlack,			ccDarkBlue,			ccBlue	},// 0 Green	
				{ ccDarkGreen,		ccDarkCyan,			ccCyan	},// 1 Green	
				{ ccGreen,			ccCyan,				ccCyan	},// 2 Green	
				// ^ 0 blue    |   ^ 1 blue      |   ^ 2 blue					
			},
			{
				// 1 Red																		
				{ ccDarkRed,		ccDarkPurple,		ccPurple },// 0 Green	
				{ ccDarkYellow,	ccGray,				ccCyan	},// 1 Green	
				{ ccYellow,			ccGreen,				ccCyan	},// 2 Green	
				// ^ 0 blue    |   ^ 1 blue      |   ^ 2 blue					
			},
			{
				// 2 Red																		
				{ ccRed,				ccRed,				ccPurple },// 0 Green	
				{ ccYellow,			ccRed,				ccPurple },// 1 Green	
				{ ccYellow,			ccYellow,			ccWhite	},// 2 Green	
				// ^ 0 blue    |   ^ 1 blue      |   ^ 2 blue					
			}
		};

		if constexpr (RealNumber<MemberType>) {
			const pcu8 red = static_cast<pcu8>(pcClamp01(T::mArray[0]) * MemberType(3));
			const pcu8 green = static_cast<pcu8>(pcClamp01(T::mArray[1]) * MemberType(3));
			const pcu8 blue = static_cast<pcu8>(pcClamp01(T::mArray[2]) * MemberType(3));
			return ColorMap[red][green][blue];
		}
		else {
			constexpr auto third = ::std::numeric_limits<MemberType>::max() / MemberType(3);
			return ColorMap[T::mArray[0] / third][T::mArray[1] / third][T::mArray[2] / third];
		}
	}

	#undef TEMPLATE

} // namespace Langulus::Math
