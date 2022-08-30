#pragma once
#include "../IncludeMemory.hpp"

namespace PCFW::Math
{

	/// A seed																						
	struct Seed : public TNumber<pcu32, Seed> {
		using TNumber::TNumber;
	};


	/// Mersenne Twister random number generator											
	/// Credit goes to http://www.bedaux.net/mtrand/									
	class PCMRNG {
	public:
		/// Constructor with 32 bit int as seed											
		PCMRNG(Seed s) noexcept {
			mState[mN] = { 0x0UL };
			mP = 0;
			SetSeed(s);
		}

		/// Constructor with array of size 32 bit ints as seed						
		PCMRNG(const Seed* aarray, int size) noexcept {
			mState[mN] = { 0x0UL };
			mP = 0;
			SetSeed(aarray, size);
		}

		/// Copy RNG state operator															
		PCMRNG& operator = (const PCMRNG&) noexcept = default;

		/// Overload operator() to make this a generator (functor)					
		///	@return the newly generated number											
		pcu32 operator() () noexcept {
			return RandI32();
		}

		/// Provide random numbers for different integer types						
		///	@return the newly generated number											
		template<class T> 
		T GenerateInt() noexcept {
			return T(RandI32() % (pcu32(std::numeric_limits<T>::max()) + pcu32(-pci64(std::numeric_limits<T>::min())) + 1)) + std::numeric_limits<T>::min();
		}

		/// Generates real numbers in the half-open interval [0, 1)					
		///	@return the newly generated number											
		template<class T> 
		T GenerateRealHalfOpen() noexcept {
			return static_cast<T>(RandI32()) * (1. / 4294967296.);
		}

		/// Generates real numbers in the closed interval [0, 1]						
		///	@return the newly generated number											
		template<class T> 
		T GenerateRealClosed() noexcept {
			return static_cast<T>(RandI32()) * static_cast<T>(1. / 4294967295.);
		}

		/// Generates real numbers in the open interval (0, 1)						
		///	@return the newly generated number											
		template<class T> 
		T GenerateRealOpen() noexcept {
			return (static_cast<T>(RandI32()) + .5) * (1. / 4294967296.);
		}

		/// The two seed functions																
		PC_API_MATH void SetSeed(Seed) noexcept;
		PC_API_MATH void SetSeed(const Seed*, int size) noexcept;

	private:
		// Compile time constants:														
		static constexpr int mN = 624, mM = 397;

		// Static variables:																
		Seed	mState[mN + 1];	// State vector array							
		int	mP;					// Position in state array						

		// Private functions used to generate the random numbers				
		inline Seed Twiddle(Seed u, Seed v) noexcept {
			return (((u & 0x80000000U) | (v & 0x7FFFFFFFU)) >> Seed(1)) ^ ((v & 1U) != Seed(0) ? 0x9908B0DFU : 0x0U);
		}

		PC_API_MATH void GenState() noexcept;

	protected:
		inline pcu32 RandI32() noexcept {
			if (mP == mN) 
				GenState();
				
			// new state vector needed													
			// gen_state() is split off to be non-inline, because 			
			// it is only called	once in every 624 calls and					
			// otherwise irand() would become too big	to get					
			// inlined																		
			Seed x = mState[mP++];
			x ^= (x >> Seed(11));
			x ^= (x << Seed(7)) & 0x9D2C5680U;
			x ^= (x << Seed(15)) & 0xEFC60000U;
			return static_cast<pcu32>(x ^ (x >> Seed(18)));
		}
	};

} // namespace PCFW::Math
