#pragma once
#include "TVector.hpp"

LANGULUS_DECLARE_TRAIT(Scale, "Scale/size trait");

namespace PCFW::Math
{

	/// Commonly used sizers																	
	using Sizer3 = TSizer<vec3>;
	using Sizer2 = TSizer<vec2>;
	using Sizer  = Sizer3;


	///																								
	///	Abstract sizer																			
	///																								
	PC_DECLARE_ABSTRACT_DATA(Sizer);


	///																								
	///	Templated sizer																		
	///	Vector specialization that defaults to 1 and is used for scaling		
	///																								
	template<ComplexNumber T>
	struct TSizer : public T, NOT_NULLIFIABLE {
		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr pcptr MemberCount = T::MemberCount;

		REFLECT_MANUALLY(TSizer) {
			// Sizer defaults to 1, so not nullifiable!							
			static_assert(!pcIsNullifiable<ME>, "Must NOT be NULLIFIABLE");
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(sizeof(T) == sizeof(ME), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Sizer";
				if constexpr (MemberCount != 3)
					name += MemberCount;
				if constexpr (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a scale vector of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(ASizer),
				REFLECT_BASE(T));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			return reflection;
		}

	public:
		using T::T;

		/// Default sizer construction														
		constexpr TSizer() noexcept
			: T {1} {}
			
		/// Copy (and convert) from same/bigger vectors of same/different types	
		/// Same as T constructor, but initializes to 1 by default					
		///	@param a - vector to copy														
		template<Number ALTT, pcptr ALTS>
		constexpr TSizer(const TVector<ALTT, ALTS>& a) noexcept {
			T::template Initialize<ALTT, ALTS, 1>(a);
		}

		/// Construct from component, if its index is smaller than SIZE			
		/// Same as T constructor, but initializes to 1 by default					
		///	@param a - component to set													
		template<Number N, Dimension I>
		constexpr TSizer(const TVectorComponent<N, I>& a) noexcept requires (pcptr(I) < MemberCount)
			: TSizer {} {
			if constexpr (T::DenseVector)
				T::mArray[I] = T::Adapt(a.mValue);
			else
				T::mArray[I] = const_cast<T*>(pcPtr(a.mValue));
		}

		/// Convert from any sizer to text													
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			T::WriteBody(result);
			return result;
		}
	};

	PC_DEFINE_ABSTRACT_DATA(Sizer, "An abstract sizer", Sizer);

} // namespace PCFW::Math