#include "Times.hpp"
#include <PCFW.OS.hpp>
#if LANGULUS_OS_IS(LINUX)
	#include <unistd.h>
#endif

namespace PCFW::Math
{

	/// Platform dependent sleep function													
	void pcSleep(PCTime usec) {
		#if LANGULUS_OS_IS(WINDOWS)
			Sleep(static_cast<DWORD>(pcu64(usec) / pcu64(1000)));
		#else
			usleep(static_cast<useconds_t>(usec.Microseconds()));
		#endif
	}

	/// Constructor																				
	PCTimer::PCTimer() {
		#if LANGULUS_OS_IS(WINDOWS)
			LARGE_INTEGER mWinFrequency;
			QueryPerformanceFrequency(&mWinFrequency);
			mFrequency = pcu64(mWinFrequency.QuadPart);
		#elif LANGULUS_OS_IS(LINUX)
			timespec mUnixFrequency;
			clock_getres(CLOCK_MONOTONIC, &mUnixFrequency);
			mFrequency = pcu64(mUnixFrequency.tv_nsec);
		#endif

		mStart = GetRawTime();
		mEnd = mStart;
	}

	/// Use OS to extract time																	
	pcu64 PCTimer::GetRawTime() const {
		#if LANGULUS_OS_IS(WINDOWS)		
			LARGE_INTEGER mWinEnd;
			QueryPerformanceCounter(&mWinEnd);
			return pcu64(mWinEnd.QuadPart);
		#elif LANGULUS_OS_IS(LINUX)
			timespec mUnixEnd;
			clock_gettime(CLOCK_MONOTONIC, &mUnixEnd);
			return (mUnixEnd.tv_sec * 1000000000 + mUnixEnd.tv_nsec * mFrequency);
		#endif
	}

} // namespace PCFW::Math