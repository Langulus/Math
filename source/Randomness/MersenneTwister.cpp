///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "MersenneTwister.hpp"

namespace Langulus::Math
{

	/// Credit goes to http://www.bedaux.net/mtrand/									
	/// Mersenne Twister random number generator											
	/// Generate new state vector																
	void PCMRNG::GenState() noexcept {
		for (int i = 0; i < (mN - mM); ++i)
			mState[i] = mState[i + mM] ^ Twiddle(mState[i], mState[i + 1]);
		for (int i = mN - mM; i < (mN - 1); ++i)
			mState[i] = mState[i + mM - mN] ^ Twiddle(mState[i], mState[i + 1]);
		mState[mN - 1] = mState[mM - 1] ^ Twiddle(mState[mN - 1], mState[0]);
		mP = 0;
	}

	/// Init by 32 bit seed																		
	///	@param s - the seed																	
	void PCMRNG::SetSeed(Seed s) noexcept {
		mState[0] = s & 0xFFFFFFFFUL;
		for (int i = 1; i < mM; ++i) {
			mState[i] = 1812433253UL * (mState[i - 1] ^ (mState[i - 1] >> 30)) + i;
			mState[i] &= 0xFFFFFFFFUL;
		}
		mP = mN;
	}

	/// Init by an array of seeds																
	///	@param array - array of seeds														
	///	@param size - size of the array													
	void PCMRNG::SetSeed(const Seed* array, int size) noexcept {
		SetSeed(19650228UL);
		int i = 1, j = 0;
		for (int k = ((mN > size) ? mN : size); k; --k) {
			mState[i] = (mState[i] ^ ((mState[i - 1] ^ (mState[i - 1] >> 30)) * 1664525UL)) + array[j] + j;
			mState[i] &= 0xFFFFFFFFUL;
			++j; j %= size;
			if ((++i) == mN) {
				mState[0] = mState[mN - 1]; i = 1;
			}
		}
		for (int k = mN - 1; k; --k) {
			mState[i] = (mState[i] ^ ((mState[i - 1] ^ (mState[i - 1] >> 30)) * 1566083941UL)) - i;
			mState[i] &= 0xFFFFFFFFUL;
			if ((++i) == mN) {
				mState[0] = mState[mN - 1]; i = 1;
			}
		}
		mState[0] = 0x80000000UL;
		mP = mN;
	}

} // namespace Langulus::Math