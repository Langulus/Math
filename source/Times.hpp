///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Functions/Arithmetics.hpp"
#include "TGradient.hpp"
#include <ctime>

namespace Langulus::Math
{

	/// Abstract time																				
	PC_DECLARE_AND_DEFINE_ABSTRACT_DATA(Time, "Abstract time", void);


	/// Seconds after Big Bang	Period														
	///																								
	/// In this table each row is defined in seconds after the Big Bang,			
	/// with earliest at the top of the chart. (see Cosmological decade)			
	///																								
	/// 10^-45 to 10^-40			Planck Epoch												
	/// 10^-40 to 10^-35																			
	/// 10^-35 to 10^-30			Epoch of Grand Unification								
	/// 10^-30 to 10^-25																			
	/// 10^-25 to 10^-20																			
	/// 10^-20 to 10^-15																			
	/// 10^-15 to 10^-10			Electroweak Epoch											
	/// 10^-10 to 10^-5																			
	/// 10^-5 to 10^0				Hadron Epoch												
	/// 10^0 to 10^5				Lepton Epoch												
	/// 10^5 to 10^10				Epoch of Nucleosynthesis								
	/// 10^10 to 10^15			Epoch of Galaxies											
	/// 10^15 to 10^20																			
	///																								
	/// The present time is approximately 4.3*10^17 seconds after the Big Bang	
	/// the Sun and Earth formed about 2*10^17 seconds after the Big Bang.		
	/// 10^20 seconds is 3 trillion years (3*10^12 years) in the future.			
	///																								

	///																								
	///	TIME																						
	///																								
	/// The Universal Time used by Piception. 64-bit counter on small scale		
	/// (max is ~599.73 years). Useful for short scale measurements, like		
	/// between frames.																			
	/// It doesn't accurately convert time from day upwards.							
	/// Resolution depends on hardware. 													
	///																								
	class PC_API_MATH PCTime : public TNumber<pcu64, PCTime> {
		REFLECT(PCTime);
	public:
		using TNumber<pcu64, PCTime>::TNumber;

		static constexpr pcu64 Infinity = std::numeric_limits<pcu64>::max();
		static constexpr pcu64 Microsecond = 1;
		static constexpr pcu64 Millisecond = Microsecond * 1000;
		static constexpr pcu64 Second = Millisecond * 1000;
		static constexpr real InverseSecond = real(1) / real(Second);
		static constexpr pcu64 Minute = Second * 60;
		static constexpr pcu64 Hour = Minute * 60;
		static constexpr pcu64 Day = Hour * 24;

		/// Create time from real seconds (like from verb time)						
		NOD() static inline PCTime FromSeconds(const real& secondsReal) noexcept {
			return Second * static_cast<pcu64>(pcFloori(secondsReal))
				+ static_cast<pcu64>(static_cast<real>(Second) * pcFrac(secondsReal));
		}

		/// Convert to debug text																
		NOD() explicit inline operator Debug() const {
			Text result;
			result += Microseconds();
			result += "us";
			return result;
		}

		/// Convert to GASM																		
		NOD() explicit inline operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			result += GASM::OpenScope;
			result += Microseconds();
			result += GASM::CloseScope;
			return result;
		}

		/// Get the passed days (this is an approximation)								
		NOD() constexpr pcu64 Days() const noexcept {
			return mValue / Day;
		}

		/// Get the passed hours																
		NOD() constexpr pcu64 Hours() const noexcept {
			return mValue / Hour;
		}

		/// Get the passed minutes																
		NOD() constexpr pcu64 Minutes() const noexcept {
			return mValue / Minute;
		}

		/// Get the passed seconds																
		NOD() constexpr pcu64 Seconds() const noexcept {
			return mValue / Second;
		}

		/// Get the passed milliseconds														
		NOD() constexpr pcu64 Milliseconds() const noexcept {
			return mValue / Millisecond;
		}

		/// Get the passed microseconds														
		NOD() constexpr pcu64 Microseconds() const noexcept {
			return mValue / Microsecond;
		}

		/// Get the passed seconds as real fractions										
		NOD() constexpr real SecondsReal() const noexcept {
			return static_cast<real>(mValue) * InverseSecond;
		}
	};

	using TimeGradient = TGrad2<PCTime>;
	

	///																								
	///	UNIVERSAL TIME STAMP																	
	///																								
	///	The Universal Time Stamp Used by Piception.									
	/// 64-bit counter on universal scale.													
	/// Useful for universal scale time computation.									
	///																								
	///	This timestamp union can hold from -536870911*10^255						
	/// to +536870911*10^255 years.															
	/// Warning: if max mYears is reached, then the timer switches to				
	/// low-resolution year counting. This means, that if mYears reaches			
	/// 536870911*2, and when High Res part makes a full cycle,						
	/// 10^mYearsExponent years will pass on each Low-Res cycle.					
	/// This mechanic allows for approximate simulation of a whole year, even	
	/// out of the scope of the observable universe. I needed that. ;)			
	///																								
	class PC_API_MATH PCTimeStamp {
		REFLECT(PCTimeStamp);
	public:
		constexpr PCTimeStamp() noexcept {}
		constexpr PCTimeStamp(const ME& other) noexcept
			: mData(other.mData) { }

		/// Manual construction																	
		///	@param year - the year (from -536870911 to +536870911)				
		///	@param hour - the hour (from 0 to 23)										
		///	@param minute - the minute (from 0 to 59)									
		///	@param second - the second (from 0 to 59)									
		///	@param exponent - the year exponent (from 0 to 255)					
		constexpr PCTimeStamp(
			const pci64 year, 
			const pcu32 day = 0, 
			const pcu32 hour = 0, 
			const pcu32 minute = 0, 
			const pcu32 second = 0, 
			const pcu8 exponent = 0) noexcept {
			mData.mParts.mYears = pcu32(year + ZERO_YEARS);
			mData.mParts.mDays = pcu16(day);
			mData.mParts.mHours = pcu8(hour);
			mData.mParts.mMinutes = pcu8(minute);
			mData.mParts.mSeconds = pcu8(second);
			mData.mParts.mYearsExp = exponent;
		}

		static constexpr pci32 ZERO_YEARS = 536870911u;

		/// Encapsulation																			
		constexpr pcu32 Seconds() const noexcept {
			return mData.mParts.mSeconds;
		}
		constexpr pcu32 Minutes() const noexcept {
			return mData.mParts.mMinutes;
		}
		constexpr pcu32 Hours() const noexcept {
			return mData.mParts.mHours;
		}
		constexpr pcu32 Days() const noexcept {
			return mData.mParts.mDays;
		}
		constexpr pcu32 Years() const noexcept {
			return mData.mParts.mYears;
		}
		constexpr pcu32 Exponent() const noexcept {
			return mData.mParts.mYearsExp;
		}
		constexpr pcu64 Raw() const noexcept {
			return mData.mRaw;
		}

		/// Set the timestamp to current time												
		inline void Now() {
			time_t rawtime;
			const tm* ptm;
			time(&rawtime);
			ptm = pcGMTime(rawtime);
			mData.mParts.mSeconds = pcu8(ptm->tm_sec);
			mData.mParts.mMinutes = pcu8(ptm->tm_min);
			mData.mParts.mHours = pcu8(ptm->tm_hour);
			mData.mParts.mDays = pcu16(ptm->tm_yday);
			mData.mParts.mYears = pcu32(ptm->tm_year) + 1900 + ZERO_YEARS;
		}

		/// Copying																					
		constexpr ME& operator = (const ME& other) noexcept {
			mData.mRaw = other.mData.mRaw;
			return *this;
		}

		/// Time arithmetic																		
		constexpr ME operator - (const ME& other) const noexcept {
			const auto seconds = pci8(mData.mParts.mSeconds) - pci8(other.mData.mParts.mSeconds);
			const auto minutes = pci8(mData.mParts.mMinutes) - pci8(other.mData.mParts.mMinutes) + (seconds / 60);
			const auto hours = pci8(mData.mParts.mHours) - pci8(other.mData.mParts.mHours) + (minutes / 60);
			const auto days = pci16(mData.mParts.mDays) - pci16(other.mData.mParts.mDays) + (hours / 24);
			const auto years = pci64(mData.mParts.mYears) - pci64(other.mData.mParts.mYears) + (days / 365);
			const auto exp = pci16(mData.mParts.mYearsExp) - pci16(other.mData.mParts.mYearsExp);
			return ME(pcu32(years), pcu32(days % 365), pcu32(hours % 24), pcu32(minutes % 60), pcu32(seconds % 60), pcu8(exp));
		}

		constexpr ME operator + (const ME& other) const noexcept {
			const pcu8 seconds = mData.mParts.mSeconds + other.mData.mParts.mSeconds;
			const pcu8 minutes = mData.mParts.mMinutes + other.mData.mParts.mMinutes + (seconds / 60);
			const pcu8 hours = mData.mParts.mHours + other.mData.mParts.mHours + (minutes / 60);
			const pcu16 days = mData.mParts.mDays + other.mData.mParts.mDays + (hours / 24);
			pci64 years = pci64(mData.mParts.mYears) + pci64(other.mData.mParts.mYears) + pci64(days / 365);
			pcu16 exp = mData.mParts.mYearsExp + other.mData.mParts.mYearsExp;
			while (years > ZERO_YEARS * 2) {
				++exp;
				years -= ZERO_YEARS * 2;
			}
			return ME(years - ZERO_YEARS, days % 365, hours % 24, minutes % 60, (seconds % 60), exp % 256);
		}

		constexpr ME operator * (const ME& other) const noexcept {
			const auto seconds = pci8(mData.mParts.mSeconds) * pci8(other.mData.mParts.mSeconds);
			const auto minutes = pci8(mData.mParts.mMinutes) * pci8(other.mData.mParts.mMinutes) + (seconds / 60);
			const auto hours = pci8(mData.mParts.mHours) * pci8(other.mData.mParts.mHours) + (minutes / 60);
			const auto days = pci16(mData.mParts.mDays) * pci16(other.mData.mParts.mDays) + (hours / 24);
			const auto years = pci64(mData.mParts.mYears) * pci64(other.mData.mParts.mYears) + (days / 365);
			const auto exp = pci16(mData.mParts.mYearsExp) * pci16(other.mData.mParts.mYearsExp);
			return ME(pcu32(years), pcu32(days % 365), pcu32(hours % 24), pcu32(minutes % 60), pcu32(seconds % 60), pcu8(exp));
		}

		constexpr ME operator / (const ME& other) const noexcept {
			const pcu8 seconds = mData.mParts.mSeconds / other.mData.mParts.mSeconds;
			const pcu8 minutes = mData.mParts.mMinutes / other.mData.mParts.mMinutes + (seconds / 60);
			const pcu8 hours = mData.mParts.mHours / other.mData.mParts.mHours + (minutes / 60);
			const pcu16 days = mData.mParts.mDays / other.mData.mParts.mDays + (hours / 24);
			pci64 years = pci64(mData.mParts.mYears / other.mData.mParts.mYears) + pci64(days / 365);
			pcu16 exp = mData.mParts.mYearsExp / other.mData.mParts.mYearsExp;
			while (years > ZERO_YEARS * 2) {
				++exp;
				years -= ZERO_YEARS * 2;
			}
			return ME(years - ZERO_YEARS, days % 365, hours % 24, minutes % 60, (seconds % 60), exp % 256);
		}

		constexpr ME& operator -= (const ME& other) noexcept {
			return *this = *this - other; 
		}
		constexpr ME& operator += (const ME& other) noexcept {
			return *this = *this + other; 
		}
		constexpr ME& operator *= (const ME& other) noexcept {
			return *this = *this * other; 
		}
		constexpr ME& operator /= (const ME& other) noexcept {
			return *this = *this / other; 
		}

		/// Sorting																					
		constexpr bool operator <  (const ME& other) const noexcept {
			return mData.mRaw < other.mData.mRaw;
		}
		constexpr bool operator >  (const ME& other) const noexcept {
			return mData.mRaw > other.mData.mRaw;
		}
		constexpr bool operator == (const ME& other) const noexcept {
			return mData.mRaw == other.mData.mRaw;
		}
		constexpr bool operator != (const ME& other) const noexcept {
			return mData.mRaw != other.mData.mRaw;
		}
		constexpr bool operator <= (const ME& other) const noexcept {
			return mData.mRaw <= other.mData.mRaw;
		}
		constexpr bool operator >= (const ME& other) const noexcept {
			return mData.mRaw >= other.mData.mRaw;
		}

	private:
		union TimeStampUnion {
			struct TimeStampParts {
				// High resolution part:												
				pcu8 mSeconds : 6;
				pcu8 mMinutes : 6;
				pcu8 mHours : 5;
				pcu16 mDays : 9;

				// Low resolution part:													
				pcu32 mYears : 30;
				pcu8 mYearsExp : 8;
			} mParts;

			pcu64 mRaw = 0;

			constexpr TimeStampUnion() noexcept : mRaw(0) {}
			constexpr TimeStampUnion(const pcu64& a) noexcept : mRaw(a) {}
		} mData;
	};

	using PCTimeStampGrad = TGrad2<PCTimeStamp>;


	///																								
	///	TIMER																						
	///																								
	/// Measures time in microseconds (1 / 1,000,000th sec)							
	/// Not suitable for large measurements.												
	///																								
	class PC_API_MATH PCTimer {
	public:
		PCTimer();
		~PCTimer() = default;

		/// Check if timer is running right now											
		inline bool IsActive() const noexcept {
			return mActive;
		}

		/// Start the timer																		
		inline void Start() {
			if (mActive)
				return;

			mActive = true;
			mStart = GetRawTime();
			mEnd = mStart;
		}

		/// Stop the timer																		
		inline PCTime Stop() {
			if (!mActive)
				return mEnd;

			mEnd = GetRawTime();
			mActive = false;
			return PCTime(Microseconds());
		}

		/// Get the amount of milliseconds that elapsed since							
		/// the timer started																	
		inline pcu64 Milliseconds() {
			if (mFrequency >= 1000000000u)
				// Nanosecond resolution												
				return (mEnd - mStart) / (mFrequency / 1000000000000u);
			else if (mFrequency >= 1000000u)
				// Microsecond resolution												
				return (mEnd - mStart) / (mFrequency / 1000000000u);
			else
				// Millisecond resolution												
				return (mEnd - mStart) / (mFrequency / 1000000u);
		}

		/// Get the amount of microseconds that elapsed since							
		/// the timer started																	
		inline pcu64 Microseconds() {
			if (mFrequency >= 1000000000u)
				// Nanosecond resolution												
				return (mEnd - mStart) / (mFrequency / 1000000000u);
			else if (mFrequency >= 1000000u)
				// Microsecond resolution												
				return (mEnd - mStart) / (mFrequency / 1000000u);
			else
				// Millisecond resolution												
				return (mEnd - mStart) / (mFrequency / 1000u);
		}

		pcu64 GetRawTime() const;
			
	private:
		bool mActive = false;
		pcu64 mFrequency = 0;
		pcu64 mStart = 0;
		pcu64 mEnd = 0;
	};

	PC_API_MATH void pcSleep(PCTime usec);

} // namespace Langulus::Math
