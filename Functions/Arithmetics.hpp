#pragma once
#include "../IncludeMemory.hpp"

LANGULUS_DECLARE_EXCEPTION(Arithmetic);

namespace PCFW::Math
{
	
	/// Absolute values of any signed number, or any with Abs() member			
	///	@param a - the number/class to absolute										
	///	@return either T or whatever Abs() returns for class						
	template<class T>
	NOD() constexpr auto pcAbs(const T& a) noexcept {
		if constexpr (UnsignedNumber<T>)
			return a;
		else if constexpr (SignedNumber<T>)
			return a < T(0) ? -a : a;
		else if constexpr (requires (T c) { c.Abs(); })
			return a.Abs();
		else LANGULUS_ASSERT("T must either have Abs() method, or be a number");
	}

	/// Signed unit																				
	///	@param a - the number/class to get sign of									
	///	@return either T(-1) or T(1), or whatever Sign() returns for class	
	template<class T>
	NOD() constexpr auto pcSign(const T& a) noexcept {
		if constexpr (UnsignedNumber<T>) {
			(a);
			return T(1);
		}
		else if constexpr (SignedNumber<T>)
			return a < T(0) ? T(-1) : T(1);
		else if constexpr (requires (T c) { c.Sign(); })
			return a.Sign();
		else LANGULUS_ASSERT("T must either have Sign() method, or be a number");
	}

	/// Calculate base to the power of the exponent										
	///	@param base - value to exponentiate												
	///	@param exponent - the power to raise to										
	///	@return the exponentiated number, or whatever Pow() returns in class	
	template<class T1, class T2>
	NOD() constexpr auto pcPow(T1 base, T2 exponent) noexcept {
		if constexpr (IntegerNumber<T1, T2>) {
			/// Credit goes to: http://stackoverflow.com/questions/101439			
			T1 result = T1(1);
			while (exponent) {
				if constexpr (UnsignedInteger<T1>) {
					if (exponent & 1)
						result *= base;
					exponent >>= 1;
					base *= base;
				}
				else {
					result *= base;
					--exponent;
				}
			}
			return result;
		}
		else if constexpr (RealNumber<T1>)
			return std::pow(base, exponent);
		else if constexpr (requires (T1 b, T2 e) { b.Pow(e); })
			return base.Pow(exponent);
		else LANGULUS_ASSERT("T must either have base.Pow(exponent) method, or be a number");
	}

	/// Get the smaller value of the provided												
	template <class T1, class T2, class... TAIL>
	NOD() constexpr auto pcMin(T1&& t1, T2&& t2, TAIL&&... tail) {
		if constexpr (sizeof...(TAIL) == 0) {
			if constexpr (requires (T1 a, T2 b) { a.Min(b); })
				return t1.Min(t2);
			else if constexpr (Sortable<T1, T2>)
				return t1 < t2 ? t1 : t2;
			else LANGULUS_ASSERT("T must either have t1.Min(t2) method, or be sortable");
		}
		else return pcMin(pcMin(t1, t2), tail...);
	}

	/// Get the biggest value of the provided												
	template <class T1, class T2, class... TAIL>
	NOD() constexpr auto pcMax(T1&& t1, T2&& t2, TAIL&&... tail) {
		if constexpr (sizeof...(TAIL) == 0) {
			if constexpr (requires (T1 a, T2 b) { a.Max(b); })
				return t1.Max(t2);
			else if constexpr (Sortable<T1, T2>)
				return t1 > t2 ? t1 : t2;
			else LANGULUS_ASSERT("T must either have t1.Max(t2) method, or be sortable");
		}
		else return pcMax(pcMax(t1, t2), tail...);
	}

	/// Round 																						
	template<class T>
	NOD() constexpr auto pcRound(const T& a) noexcept {
		if constexpr (IntegerNumber<T>)
			return a;
		else if constexpr (RealNumber<T>)
			return std::round(a);
		else if constexpr (requires (T x) { x.Round(); })
			return a.Round();
		else LANGULUS_ASSERT("T must either have Round() method, or be a number");
	}

	/// Round and return an integer															
	template<class T>
	NOD() constexpr auto pcRoundi(const T& a) noexcept {
		if constexpr (IntegerNumber<T>)
			return a;
		else if constexpr (Same<T, pcr64>) {
			const auto aa = a + 6755399441055744.0;
			return reinterpret_cast<const int&>(aa);
		}
		else if constexpr (Same<T, pcr32>) {
			const auto aa = static_cast<pcr64>(a) + 6755399441055744.0;
			return reinterpret_cast<const int&>(aa);
		}
		else if constexpr (requires (T x) { x.Round(); })
			return static_cast<int>(a.Round());
		else LANGULUS_ASSERT("T must either have Round() method, or be a number");
	}

	/// Floor																						
	template<class T>
	NOD() constexpr auto pcFloor(const T& a) noexcept {
		if constexpr (IntegerNumber<T>)
			return a;
		else if constexpr (RealNumber<T>) {
			const auto round_a = pcRound<T>(a);
			return round_a <= a ? round_a : round_a - T(1);
		}
		else if constexpr (requires (T x) { x.Floor(); })
			return a.Floor();
		else LANGULUS_ASSERT("T must either have Floor() method, or be a number");
	}

	/// Floor and return integer																
	template<class T>
	NOD() constexpr auto pcFloori(const T& a) noexcept {
		return static_cast<int>(pcFloor<T>(a));
	}

	/// Ceil																							
	template<class T>
	NOD() constexpr auto pcCeil(const T& a) noexcept {
		if constexpr (IntegerNumber<T>)
			return a;
		else if constexpr (RealNumber<T>) {
			const auto round_a = pcRound<T>(a);
			return round_a >= a ? round_a : round_a + T(1);
		}
		else if constexpr (requires (T x) { x.Ceil(); })
			return a.Ceil();
		else LANGULUS_ASSERT("T must either have Ceil() method, or be a number");
	}

	/// Ceil a real, return integer															
	template<class T>
	NOD() constexpr auto pcCeili(const T& a) noexcept {
		return static_cast<int>(pcCeil<T>(a));
	}

	/// Check if an unsigned integer is square											
	template<UnsignedNumber T>
	NOD() constexpr bool pcIsPowerOfTwo(const T& n) noexcept {
		return (n != 0) && ((n & (n - 1)) == 0);
	}

	/// Get square of anything with multiplication operator							
	template<class T>
	NOD() constexpr auto pcSq(const T& n) noexcept {
		if constexpr (requires (T x) { x * x; })
			return n * n;
		else LANGULUS_ASSERT("T must have * operator");
	}

	namespace DetailSqrt
	{
		/// Compile time square root using binary search								
		template<UnsignedNumber T>
		NOD() constexpr T SqrtHelper(const T& x, const T& lo, const T& hi) noexcept {
			return
				lo == hi
				? lo
				: ((x / ((lo + hi + 1) / 2) < ((lo + hi + 1) / 2))
					? SqrtHelper<T>(x, lo, ((lo + hi + 1) / 2) - 1)
					: SqrtHelper<T>(x, ((lo + hi + 1) / 2), hi));
		}
	} // namespace DetailpcSqrt

	/// Square root																				
	template<class T>
	NOD() constexpr auto pcSqrt(const T& x) {
		if constexpr (UnsignedNumber<T>)
			return DetailSqrt::SqrtHelper<T>(x, 0, x / 2 + 1);
		else if constexpr (IntegerNumber<T>) {
			SAFETY(if (x < 0)
				throw Except::Arithmetic("Square root of negative signed integer"));
			return T(pcSqrt(typename std::make_unsigned<T>::type(x)));
		}
		else if constexpr (RealNumber<T>) {
			SAFETY(if (x < 0)
				throw Except::Arithmetic("Square root of negative real"));

			T p = 1;
			while (p <= x / p)
				p = 2 * p;

			T r = p;
			do {
				p = r;
				r = (r + x / r) * 0.5f;
			} while (r < p);
			return p;
		}
		else if constexpr (requires (T a) { a.Sqrt(); })
			return x.Sqrt();
		else LANGULUS_ASSERT("T must either have Sqrt() method, or be a number");
	}


	///																								
	///	INTERPOLATION																			
	///																								

	/// 1D Linear interpolation																
	///	@param n0 - first point																
	///	@param n1 - second point															
	///	@param a - rate																		
	///	@return the linearly interpolated value										
	template<class T1, class T2, class T3>
	NOD() constexpr auto pcLerp(const T1& n0, const T2& n1, const T3& a) noexcept {
		return n0 + a * (n1 - n0);
	}

	/// 1D Cubic interpolation (Hermit interpolation, using tangents)				
	///	@param n0 - first point																
	///	@param m0 - tangent to first point												
	///	@param n1 - second point															
	///	@param m1 - tangent to second point												
	///	@param a - rate																		
	///	@return the cubically interpolated value										
	template<class T1, class T2, class T3, class T4, class T5>
	NOD() constexpr auto pcCerpTan(const T1& n0, const T2& m0, const T3& n1, const T4& m1, const T5& a) noexcept {
		const auto t2 = a * a;
		const auto t3 = t2 * a;
		return (2 * t3 - 3 * t2 + 1) * n0 + (t3 - 2 * t2 + a) * m0 + ((-2) * t3 + 3 * t2) * n1 + (t3 - t2) * m1;
	}

	/// 1D Cubic interpolation																	
	///	@param n0 - the point before the first point									
	///	@param n1 - first point																
	///	@param n2 - second point															
	///	@param n3 - the point after the second point									
	///	@param a - the rate																	
	///	@return the cubically interpolated value										
	template<class T1, class T2, class T3, class T4, class T5>
	NOD() constexpr auto pcCerp(const T1& n0, const T2& n1, const T3& n2, const T4& n3, const T5& a) noexcept {
		const auto t2 = a * a;
		const auto t3 = t2 * a;
		const auto p = (n3 - n2) - (n0 - n1);
		return p * t3 + ((n0 - n1) - p) * t2 + (n2 - n0) * a + n1;
	}

	/// Get fractional part of a real number												
	template<class T>
	NOD() constexpr auto pcFrac(const T& f) noexcept {
		if constexpr (requires (T a) { a.Frac(); })
			return f.Frac();
		else if constexpr (RealNumber<T>)
			return f - pcFloor(f);
		else if constexpr (IntegerNumber<T>)
			return T(0);
		else LANGULUS_ASSERT("T must either have Frac() method, or be a number");
	}

	/// Modulation of real numbers															
	template<class T1, class T2>
	NOD() constexpr auto pcMod(const T1& x, const T2& y) noexcept {
		if constexpr (requires (T1 a, T2 b) { a.Mod(b); })
			return x.Mod(y);
		else if constexpr (IntegerNumber<T1>)
			return x - y * T1(pcFloor(pcr64(x) / pcr64(y)));
		else if constexpr (RealNumber<T1>)
			return x - y * pcFloor(x / y);
		else LANGULUS_ASSERT("T must either have x.Mod(y) method, or be a number");
	}

	/// Remaps a [0; 1] range to a [-1; 1] range											
	template<class T>
	NOD() constexpr auto pcCenter(const T& a) noexcept {
		return a * 2 - 1;
	}

	/// Clamp a value in the interval [min;max]											
	template<class T1, class T2, class T3>
	NOD() constexpr auto pcClamp(const T1& value, const T2& min, const T3& max) noexcept {
		if constexpr (requires (T1 a, T1 b, T1 c) { a.Clamp(b, c); })
			return value.Clamp(T1(min), T1(max));
		else if constexpr (Number<T1> && Number<T2> && Number<T3>)
			return value < min ? min : (value > max ? max : value);
		else LANGULUS_ASSERT("T must either have value.Clamp(min, max) method, or be a number");
	}

	/// Clamp a value in the interval [0:1]												
	template<class T>
	NOD() constexpr auto pcClamp01(const T& value) noexcept {
		return pcClamp(value, T(0), T(1));
	}

	/// Clamp a value outside the interval (min:max)									
	/// If the value is near min, min is returned, otherwise max is returned	
	template<class T1, class T2, class T3>
	NOD() constexpr auto pcClampRev(const T1& value, const T2& min, const T3& max) noexcept {
		if constexpr (requires (T1 a, T1 b, T1 c) { a.ClampRev(b, c); })
			return value.ClampRev(T1(min), T1(max));
		else if constexpr (Number<T1> && Number<T2> && Number<T3>) {
			const auto halfd = (max - min) / 2;
			if (value > min && value < max)
				return value - min > halfd ? max : min;
			return value;
		}
		else LANGULUS_ASSERT("T must either have value.ClampRev(min, max) method, or be a number");
	}

	/// Dot two types that have a Dot method												
	template<class T1, class T2>
	NOD() constexpr auto pcDot(const T1& v1, const T2& v2) noexcept {
		if constexpr (requires (T1 a, T2 b) { a.Dot(b); })
			return v1.Dot(v2);
		else LANGULUS_ASSERT("T must have v1.Dot(v2) method");
	}

	/// Self-dot product																			
	template<class T>
	NOD() constexpr auto pcDot2(const T& v1) noexcept {
		return pcDot(v1, v1);
	}

	/// Cross two types that have a Cross method											
	template<class T1, class T2>
	NOD() constexpr auto pcCross(const T1& v1, const T2& v2) noexcept {
		if constexpr (requires (T1 a, T2 b) { a.Cross(b); })
			return v1.Cross(v2);
		else LANGULUS_ASSERT("T must have v1.Cross(v2) method");
	}

	/// Get the length of numbers and complex numbers									
	template<class T>
	NOD() constexpr auto pcLength(const T& v1) noexcept {
		if constexpr (requires (T a) { a.Length(); })
			return v1.Length();
		else if constexpr (Number<T>)
			return pcAbs(v1);
		else LANGULUS_ASSERT("T must either have v1.Length() method, or be a number");
	}

	/// Get the distance between two values												
	template<class T1, class T2>
	NOD() constexpr auto pcDistance(const T1& p0, const T2& p1) noexcept {
		return pcLength(p0 - p1);
	}

	/// Normalize anything that has a Normalize method									
	template<class T>
	NOD() constexpr auto pcNormalize(const T& v) noexcept {
		if constexpr (requires (T a) { a.Normalize(); })
			return v.Normalize();
		else LANGULUS_ASSERT("T must have v.Normalize() method");
	}

	/// Step function																				
	template<class T1, class T2>
	NOD() constexpr auto pcStep(const T1& edge, const T2& x) noexcept {
		if constexpr (requires (T1 a, T2 b) { b.Step(a); })
			return x.Step(edge);
		else if constexpr (Number<T1> && Number<T2>)
			return x < edge ? T2(0) : T2(1);
		else LANGULUS_ASSERT("T must either have x.Step(edge) method, or be a number");
	}

	/// Smooth step (Hermite) interpolation, analogous to the GLSL function		
	template<class T1, class T2, class T3>
	NOD() constexpr auto pcSmoothStep(const T1& min, const T2& max, const T3& x) noexcept {
		const auto t = pcClamp((x - min) / (max - min), 0, 1);
		return t * t * (-t * 2 + 3);
	}

	/// Returns the base-e exponential function of x, which is e raised to x	
	///	@param exponent - the power to raise to										
	///	@return e^x																				
	template<class T>
	NOD() constexpr auto pcExp(const T& x) noexcept {
		if constexpr (requires (T a) { a.Exp(); })
			return x.Exp();
		else if constexpr (Number<T>)
			return std::exp(x);
		else LANGULUS_ASSERT("T must either have Exp() method, or be a number");
	}

	/// Solve 2^x																					
	template<class T>
	NOD() constexpr auto pcExp2(const T& x) noexcept {
		return pcPow(T(2), x);
	}

	/// Sum of positive integers [0;n]														
	template<class T>
	NOD() constexpr T pcSum(const T& n) noexcept {
		if constexpr (requires (T a) { a.Sum(); })
			return n.Sum();
		else if constexpr (Number<T>)
			return (n * (n + T(1))) / T(2);
		else LANGULUS_ASSERT("T must either have Sum() method, or be a number");
	}

	/// A Kahan summation used to minimize floating-point math error				
	///	@param cookie - provide zero on first iteration								
	///	@param input - the number to add, repeat for more numbers				
	///	@param output - the sum, gets overwritten every time						
	template<Number T>
	void pcKSum(T& cookie, const T& input, T& output) noexcept {
		T y = input - cookie;
		// So far, so good: cookie be zero on first iteration					
		T t = output + y;
		// Output is big, y small - low-order y is lost							
		cookie = (t - output) - y;
		// (t - sum) recovers high-order y											
		output = t;
		// Next time around, the lost low part will be fixed					
	}

} // namespace PCFW::Math