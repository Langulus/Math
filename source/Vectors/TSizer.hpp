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

	using Size3 = TSize<vec3>;
	using Size2 = TSize<vec2>;
	using Size = Size3;


	namespace A
	{

		/// Used as an imposed base for any type that can be interpretable as a	
		/// size																						
		struct Size {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::Size;
		};

		/// Used as an imposed base for any type that can be interpretable as a	
		/// size of the same size																
		template<Count S>
		struct SizeOfSize : public Size {
			LANGULUS(CONCRETE) TSize<TVector<Real, S>>;
			LANGULUS_BASES(Size);
			static constexpr Count MemberCount {S};
			static_assert(S > 0, "Size size must be greater than zero");
		};

		/// Used as an imposed base for any type that can be interpretable as a	
		/// size of the same type																
		template<CT::DenseNumber T>
		struct SizeOfType : public Size {
			LANGULUS(CONCRETE) TSize<TVector<T, 3>>;
			LANGULUS_BASES(Size);
			using MemberType = T;
		};

	} // namespace Langulus::Math::A


	///																								
	///	Templated size																			
	/// Vector specialization that defaults to 1 and is used for scaling			
	///																								
	template<CT::Vector T>
	struct TSize : public T {
		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount > 0, "Force size must be greater than zero");
		LANGULUS_BASES(A::SizeOfSize<MemberCount>, A::SizeOfType<MemberType>);
		LANGULUS(NULLIFIABLE) false;

	public:
		using T::mArray;

		/// Default size construction															
		constexpr TSize() noexcept
			: T {1} {}
			
		/// Copy (and convert) from same/bigger vectors of same/different types	
		/// Same as T constructor, but initializes to 1 by default					
		///	@param a - vector to copy														
		template<CT::DenseNumber ALTT, Count ALTS>
		constexpr TSize(const TVector<ALTT, ALTS>& a) noexcept {
			T::template Initialize<ALTT, ALTS, 1>(a);
		}

		/// Construct from component, if its index is smaller than SIZE			
		/// Same as T constructor, but initializes to 1 by default					
		///	@param a - component to set													
		template<CT::DenseNumber N, CT::Dimension D>
		constexpr TSize(const TVectorComponent<N, D>& a) noexcept
			: TSize {} {
			mArray[D::Index] = Adapt(a.mValue);
		}

		/// Convert from any size to text													
		NOD() explicit operator Flow::Code() const {
			return Serialize<TSize>();
		}
	};

} // namespace Langulus::Math