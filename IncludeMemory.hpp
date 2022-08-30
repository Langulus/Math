#pragma once
#include <PCFW.Memory.hpp>
#include <PCFW.Flow.hpp>

#if defined(PC_EXPORT_MATH)
	#define PC_API_MATH LANGULUS_EXPORT()
#else
	#define PC_API_MATH LANGULUS_IMPORT()
#endif

namespace PCFW::Math
{

	using namespace ::PCFW::Memory;

	/// Complex number concept																	
	template<class T>
	concept ComplexNumber = requires (T a) {
		Number<typename T::MemberType>;
		pcptr(T::MemberCount);
		a.mArray;
	};

	/// When given two arithmetic types, choose the one that is most lossless	
	/// after an arithmetic operation of any kind is performed between both		
	template<Number T1, Number T2>
	using TLossless = Conditional<
				(RealNumber<Decay<T1>> && IntegerNumber<Decay<T2>>)
			|| (SignedNumber<Decay<T1>> && UnsignedNumber<Decay<T2>>)
			|| (sizeof(Decay<T1>) > sizeof(Decay<T2>)), Decay<T1>, Decay<T2>
	>;

} // namespace PCFW::Math
