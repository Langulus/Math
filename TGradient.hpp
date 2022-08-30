#pragma once
#include "IncludeMemory.hpp"

namespace PCFW::Math
{

	template<class T, pcptr S>
	class TGradient;

	template<class T, pcptr S>
	using TGrad = TGradient<T, S>;

	template<class T>
	using TGrad2 = TGradient<T, 2>;


	///																								
	///	An abstract gradient																	
	///																								
	PC_DECLARE_ABSTRACT_DATA(Gradient);


	///																								
	///	GRADIENT																					
	///																								
	/// Useful for capsulating continuous properties, getting their				
	/// derivatives, and so on. Can capsulate anything, as long as it				
	/// has arithmetic operators.																
	///																								
	template<class T, pcptr S>
	class TGradient : POD {
	public:
		using PointType = T;
		static constexpr pcptr StateCount = S;

		REFLECT_MANUALLY(TGradient) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(StateCount > 1, "Can't have a gradient with less than two states");
			auto subtype = DataID::Reflect<PointType>();
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Grad";
				name += StateCount;
				name += subtype->GetToken();
				name = name.StandardToken();
				info += "a gradient with ";
				info += StateCount;
				info += " states of type ";
				info += subtype->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mNullifiable = pcIsNullifiable<T>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(AGradient));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER(mBuffer));
			reflection.template SetAbilities<ME>(
				REFLECT_ABILITY(Integrate),
				REFLECT_CONVERSIONS(GASM));
			return reflection;
		}

	public:
		/// Default construction																
		TGradient() = default;

		/// Manual construction																	
		///	@param initial - the initial value											
		TGradient(const PointType& initial) {
			for (auto& i : mBuffer)
				i = initial;
		}

		/// Manual construction via a variadic head-tail								
		template <typename... Args>
		constexpr TGradient(VARIADIC_HEADTAIL(Args, StateCount, PointType)) noexcept
			: mBuffer { head, PointType(tail)... } { }

		/// Access values in order of relevance (current value is at 0)			
		///	@param index - the index														
		///	@return a constant reference to the value									
		NOD() auto& operator [](const pcptr& index) const {
			if (mIndex - index < StateCount)
				return mBuffer[mIndex - index];
			return mBuffer[StateCount - index];
		}

		/// Access values in order of relevance (current value is at 0)			
		///	@param index - the index														
		///	@return a reference to the value												
		NOD() auto& operator [](const pcptr& index) {
			if (mIndex - index < StateCount)
				return mBuffer[mIndex - index];
			return mBuffer[StateCount - index];
		}

		/// Compare two gradients																
		///	@param other - the gradient to compare against							
		///	@return true if both gradients are the same								
		NOD() bool operator == (const ME& other) const {
			for (pcptr i = 0; i < StateCount; ++i) {
				if (mBuffer[i] != other.mBuffer[i])
					return false;
			}
			return true;
		}

		/// Compare two gradients																
		///	@param other - the gradient to compare against							
		///	@return true if both gradients are the same								
		NOD() bool operator != (const ME& other) const {
			for (pcptr i = 0; i < StateCount; ++i) {
				if (mBuffer[i] == other.mBuffer[i])
					return false;
			}
			return true;
		}

		/// Convert to text																		
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			result += GASM::OpenScope;
				for (pcptr i = 0; i < StateCount; ++i) {
					result += (*this)[i];
					if (i < StateCount - 1)
						result += GASM::AndSeparator;
				}
			result += GASM::CloseScope;
			return result;
		}

		/// Revert. If size is too short you'll lose state								
		T& Revert() noexcept {
			--mIndex;
			if (mIndex >= StateCount)
				mIndex = StateCount - 1;

			Current() = Previous();
			return Current();
		}

		/// Progression																			
		T& Update() noexcept {
			// Move marker																	
			++mIndex;
			if (mIndex >= StateCount)
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
			return mIndex >= 1 ? mBuffer[mIndex - 1] : mBuffer[StateCount - 1];
		}
		NOD() T& Previous() noexcept {
			return mIndex >= 1 ? mBuffer[mIndex - 1] : mBuffer[StateCount - 1];
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
		PC_VERB(Integrate) {
			if (verb.GetMass() > 0)
				verb << Sum();
			else if (verb.GetMass() < 0)
				verb << Delta();
		}

	public:
		T mBuffer[StateCount] = {};
		pcptr mIndex = 0;
	};

	PC_DEFINE_ABSTRACT_DATA(Gradient, "An abstract gradient", void);

} // namespace PCFW::Math
