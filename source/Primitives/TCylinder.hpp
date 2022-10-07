///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Primitive.hpp"

namespace Langulus::Math
{

	///																								
	/// Infinite 3D cylinder with varying radius, centered at origin				
	/// D determines the direction of the cylinder's height							
	///																								
	///																								
	///		^		^ +D	^		^																
	///		|		|		|		|																
	///		| _ _ | _ _	|		|																
	///		|/		|	  \|		|																
	///		|		+		|		|																
	///		|\_________/|		| infinite height											
	///		|				|		|																
	///		|				|		v																
	///		|		+		|	----																
	///		|	origin	|																		
	///		| _ _ _ _ _	|																		
	///		|/			  \|																		
	///		|		+		|																		
	///		|\____|____/|																		
	///		|		|		|																		
	///		V		|<--->V mRadius															
	///																								
	template<CT::Vector T, CT::Dimension D = Traits::Y>
	struct TCylinder {
		LANGULUS(POD) true;
		LANGULUS_BASES(A::Primitive);

		using PointType = T;
		using typename T::MemberType;
		using Dimension = D;
		using T::MemberCount;
		static_assert(MemberCount == 3, "Can't have a non-3D cylinder");
		static_assert(D::Index < 3, "Can't extend cylinder in that dimension");

		MemberType mRadius {.5};

	public:
		NOD() constexpr bool IsDegenerate() const noexcept;
		NOD() constexpr bool IsHollow() const noexcept;
		NOD() auto SignedDistance(const T&) const;
	};


	///																								
	/// Capped 3D cylinder with varying size, centered at origin					
	/// D determines the direction of the cylinder's height							
	///																								
	///				^ +D																			
	///				|																				
	///		  ____|____																			
	///		 /		|	  \																		
	///		|		+		|	----																
	///		|\_________/|		^ 																
	///		|				|		|	mHeight													
	///		|				|		v																
	///		|		+		|	----																
	///		|	origin	|																		
	///		| _ _ _ _ _	|																		
	///		|/			  \|																		
	///		|		+		|																		
	///		 \____|____/																		
	///				|		|																		
	///				|<--->| mRadius															
	///																								
	template<CT::Vector T, CT::Dimension D = Traits::Y>
	struct TCylinderCapped : public TCylinder<T, D> {
		using Base = TCylinder<T>;
		using typename Base::PointType;
		using typename Base::MemberType;
		using Base::MemberCount;
		using Base::mRadius;

		MemberType mHeight {.5};

	public:
		NOD() constexpr bool IsDegenerate() const noexcept;
		NOD() constexpr bool IsHollow() const noexcept;
		NOD() auto SignedDistance(const T&) const;
	};

} // namespace Langulus::Math

#include "TCylinder.inl"