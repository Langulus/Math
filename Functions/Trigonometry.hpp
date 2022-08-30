#pragma once
#include "../IncludeMemory.hpp"
#include "Arithmetics.hpp"

namespace PCFW::Math
{

	///																								
	/// Constants																					
	///																								
	template<RealNumber T = real>
	constexpr T PI = T(3.1415926535897932385L);

	template<RealNumber T = real>
	constexpr T TAU = PI<T> * T(2);

	template<RealNumber T = real>
	constexpr T HALFPI = PI<T> * T(0.5);

	template<RealNumber T = real>
	constexpr T PIi = T(1) / PI<T>;

	template<RealNumber T = real>
	constexpr T TAUi = T(1) / TAU<T>;

	template<RealNumber T = real>
	constexpr T HALFPIi = T(1) / HALFPI<T>;

	template<RealNumber T = real>
	constexpr T LOGHALF = T(-0.30102999566L);

	template<RealNumber T = real>
	constexpr T LOGHALFi = T(1) / LOGHALF<T>;

	template<RealNumber T = real>
	constexpr T I180 = T(1) / T(180);

	template<RealNumber T = real>
	constexpr T PIxI180 = PI<T> * I180<T>;

	template<RealNumber T = real>
	constexpr T PIix180 = PIi<T> * T(180);

	template<RealNumber T = real>
	constexpr T GOLDEN_ANGLE = (T(3) - pcSqrt<T>(5)) * PI<T>;


	/// Calculate cosine																			
	///	@param a - angle in radians														
	template<class T>
	inline auto pcCos(const T& a) noexcept {
		if constexpr (requires(T a) { a.Cos(); })
			return a.Cos();
		else if constexpr (RealNumber<T>)
			return std::cos(a);
		else LANGULUS_ASSERT("T must either have Cos() method, or be a real number");
	}

	/// Calculate cosine in degrees															
	///	@param a - angle in degrees														
	template<class T>
	inline auto pcCosDeg(const T& a) noexcept {
		if constexpr (requires(T a) { a.Cos(); })
			return (a * PIxI180<T>).Cos();
		else if constexpr (RealNumber<T>)
			return std::cos(a * PIxI180<T>);
		else LANGULUS_ASSERT("T must either have Cos() method, or be a real number");
	}

	/// Calculate sine																			
	///	@param a - angle in radians														
	template<class T>
	inline auto pcSin(const T& a) noexcept {
		if constexpr (requires(T a) { a.Sin(); })
			return a.Sin();
		else if constexpr (RealNumber<T>)
			return std::sin(a);
		else LANGULUS_ASSERT("T must either have Sin() method, or be a real number");
	}

	/// Calculate sine in degrees																
	///	@param a - angle in radians														
	template<class T>
	inline auto pcSinDeg(const T& a) noexcept {
		if constexpr (requires(T a) { a.Sin(); })
			return (a * PIxI180<T>).Sin();
		else if constexpr (RealNumber<T>)
			return std::sin(a * PIxI180<T>);
		else LANGULUS_ASSERT("T must either have Sin() method, or be a real number");
	}

	/// Returns the arc tangent of x, expressed in radians							
	///	@param a - angle in radians														
	template<class T>
	inline auto pcAtan(const T& a) noexcept {
		if constexpr (requires(T a) { a.Atan(); })
			return a.Atan();
		else if constexpr (RealNumber<T>)
			return std::atan(a);
		else LANGULUS_ASSERT("T must either have Atan() method, or be a real number");
	}

	/// Returns the arc tangent of y/x, expressed in radians							
	///	@param a - angle in radians														
	template<class T>
	inline auto pcAtan2(const T& a, const T& b) noexcept {
		if constexpr (requires(T a, T b) { a.Atan2(b); })
			return a.Atan2(b);
		else if constexpr (RealNumber<T>)
			return std::atan2(b, a);
		else LANGULUS_ASSERT("T must either have Atan2() method, or be a real number");
	}
	
	/// Degree to radian conversion															
	///	@param degrees - degrees to convert to radians								
	template<class T>
	constexpr auto pcD2R(const T& degrees) noexcept {
		return degrees * PIxI180<T>;
	}

	/// Radians to degrees conversion														
	///	@param radians - radians to convert to degrees								
	template<class T>
	constexpr auto pcR2D(const T& radians) noexcept {
		return radians * PIix180<T>;
	}

} // namespace PCFW::Math
