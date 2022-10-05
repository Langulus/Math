///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TVector.hpp"

namespace Langulus::Math
{

	/// Commonly used normal																	
	using Normal = TNormal<vec3>;

	namespace A
	{

		///																							
		/// An abstract normal																	
		/// Used as an imposed base for any type that can be interpretable as a	
		/// normal																					
		///																							
		struct Normal {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) Normal;
		};

		///																							
		/// An abstract normal of specific size											
		/// Used as an imposed base for any type that can be interpretable as a	
		/// normal of the same size															
		///																							
		template<Count S>
		struct NormalOfSize : public Normal {
			LANGULUS(CONCRETE) TNormal<TVector<Real, S>>;
			LANGULUS_BASES(Normal);
			static constexpr Count MemberCount {S};
			static_assert(S > 1, "Normal size must be greater than one");
		};

		///																							
		/// An abstract normal of specific type											
		/// Used as an imposed base for any type that can be interpretable as a	
		/// normal of the same type															
		///																							
		template<CT::DenseNumber T>
		struct NormalOfType : public Normal {
			LANGULUS(CONCRETE) TNormal<TVector<T, 4>>;
			LANGULUS_BASES(Normal);
			using MemberType = T;
		};

	} // namespace Langulus::Math::A


	///																								
	///	Templated normal																		
	///																								
	/// It is essentially a vector that gets normalized after any change			
	///																								
	template<CT::Vector T>
	struct TNormal : public T {
		using PointType = T;
		using MemberType = typename T::MemberType;
		static constexpr Count MemberCount = T::MemberCount;
		static_assert(S > 1, "Normal size must be greater than one");
		LANGULUS_BASES(A::NormalOfSize<MemberCount>, A::NormalOfType<MemberType>);

	public:
		using T::T;
		using T::mArray;

		/// Construct a normal from a vector												
		///	@param other - the vector to normalize										
		constexpr TNormal(const T& other)
			: T {other.Normalize()} {}

		/// Convert from any normal to text													
		NOD() explicit operator Flow::Code() const {
			Flow::Code result;
			result += RTTI::MetaData::Of<TNormal>();
			T::WriteBody(result);
			return result;
		}
	};

} // namespace Langulus::Math