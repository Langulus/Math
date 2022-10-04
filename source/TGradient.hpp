///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Common.hpp"

namespace Langulus::Math
{

	template<class T, Count S>
	class TGradient;

	template<class T, Count S>
	using TGrad = TGradient<T, S>;

	template<class T>
	using TGrad2 = TGradient<T, 2>;

	namespace A
	{

		///																							
		///	An abstract gradient																
		///																							
		///	Used as an imposed base for any type that can be interpretable as	
		/// a gradient																				
		///																							
		struct Gradient {
			LANGULUS(ABSTRACT) true;
		};

	} // namespace Langulus::Math::A


	///																								
	///	Templated gradient																	
	///																								
	///	Useful for capsulating continuous properties and getting their			
	/// derivatives. Can capsulate anything, as long as it is arithmetic.		
	///																								
	template<class T, Count S>
	class TGradient {
	public:
		LANGULUS(POD) CT::POD<T>;
		LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
		LANGULUS_BASES(A::Gradient);

		using PointType = T;
		static constexpr Count StateCount = S;
		static_assert(S > 1, "Can't have a gradient with less than two states");

	protected:
		T mBuffer[S] {};
		Offset mIndex {};

	public:
		TGradient() = default;

		/// Manual construction																	
		///	@param initial - the initial value											
		TGradient(const T& initial) {
			for (auto& i : mBuffer)
				i = initial;
		}

		/// Manual construction via a variadic head-tail								
		///	@param arguments... - list of states										
		template<class... A>
		constexpr TGradient(A&&... arguments) noexcept
			: mBuffer {Forward<A>(arguments)...} { }

		/// Access values in order of relevance (current value is at 0)			
		///	@param index - the index														
		///	@return a constant reference to the value									
		NOD() auto& operator [](const Offset& index) const {
			if (mIndex - index < S)
				return mBuffer[mIndex - index];
			return mBuffer[S - index];
		}

		/// Access values in order of relevance (current value is at 0)			
		///	@param index - the index														
		///	@return a reference to the value												
		NOD() auto& operator [](const Offset& index) {
			if (mIndex - index < S)
				return mBuffer[mIndex - index];
			return mBuffer[S - index];
		}

		/// Compare two gradients																
		///	@param other - the gradient to compare against							
		///	@return true if both gradients are the same								
		NOD() bool operator == (const TGradient& other) const {
			for (Offset i = 0; i < S; ++i) {
				if (mBuffer[i] != other.mBuffer[i])
					return false;
			}

			return true;
		}

		/// Revert																					
		///	@attention if size is too short you'll lose state						
		T& Revert() noexcept {
			--mIndex;
			if (mIndex >= S)
				mIndex = S - 1;

			Current() = Previous();
			return Current();
		}

		/// Progression																			
		T& Update() noexcept {
			// Move marker																	
			++mIndex;
			if (mIndex >= S)
				mIndex = 0;

			// Initially, current value always equals previous					
			// You can modify it as many times you want before calling		
			// update again.																
			Current() = Previous();
			return Current();
		}

		/// Get the current value																
		NOD() const T& Current() const noexcept {
			return mBuffer[mIndex];
		}

		NOD() T& Current() noexcept {
			return mBuffer[mIndex];
		}

		/// Get the previous value																
		NOD() const T& Previous() const noexcept {
			return mIndex >= 1 ? mBuffer[mIndex - 1] : mBuffer[S - 1];
		}

		NOD() T& Previous() noexcept {
			return mIndex >= 1 ? mBuffer[mIndex - 1] : mBuffer[S - 1];
		}

		/// Get the last difference															
		///	@return the difference between the last two states						
		NOD() T Delta() const {
			return Current() - Previous();
		}

		/// Get a projection in the future													
		NOD() T Project(const T& steps) const {
			return Current() + Delta() * steps;
		}

		/// Reset																					
		void Reset(const T& value) noexcept {
			for (auto& i : mBuffer)
				i = value;
			mIndex = 0;
		}

		/// Sum																						
		NOD() T Sum() const noexcept {
			T sum = {};
			for (auto& i : mBuffer)
				sum += i;
			return sum;
		}

		/// Integrate/differentiate															
		void Integrate(Flow::Verb& verb) {
			if (verb.GetMass() > 0)
				verb << Sum();
			else if (verb.GetMass() < 0)
				verb << Delta();
		}

		/// Convert to text																		
		NOD() explicit operator Flow::Code() const {
			Flow::Code result;
			result += MetaData::Of<TGradient>();
			result += Flow::Code::OpenScope;
			for (Offset i = 0; i < S; ++i) {
				result += Text {(*this)[i]};
				if (i < S - 1)
					result += ", ";
			}
			result += Flow::Code::CloseScope;
			return result;
		}
	};

} // namespace Langulus::Math
