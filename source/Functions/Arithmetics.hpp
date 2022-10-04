///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Common.hpp"

LANGULUS_EXCEPTION(Arithmetic);

namespace Langulus::CT
{

	///																								
	/// All Langulus::Math arithmetic types have these properties					
	///																								

	/// Checks for an Abs() method															
	template<class T>
	concept HasAbs = requires (const Decay<T> c) {
		{c.Abs()} -> CT::Same<T>;
	};

	/// Checks for a Round() method															
	template<class T>
	concept HasRound = requires (const Decay<T> c) {
		{c.Round()} -> CT::Same<T>;
	};

	/// Checks for a Floor() method															
	template<class T>
	concept HasFloor = requires (const Decay<T> c) {
		{c.Floor()} -> CT::Same<T>;
	};

	/// Checks for a Ceil() method															
	template<class T>
	concept HasCeil = requires (const Decay<T> c) {
		{c.Ceil()} -> CT::Same<T>;
	};

	/// Checks for a Sign() method															
	template<class T>
	concept HasSign = requires (const Decay<T> c) {
		{c.Sign()} -> CT::Same<T>;
	};

	/// Checks for a Sqrt() method															
	template<class T>
	concept HasSqrt = requires (const Decay<T> c) {
		{c.Sqrt()} -> CT::Same<T>;
	};

	/// Checks for a Frac() method															
	template<class T>
	concept HasFrac = requires (const Decay<T> c) {
		{c.Frac()} -> CT::Same<T>;
	};

	/// Checks for a Pow(exponent) method													
	template<class B, class E>
	concept HasPow = requires (const Decay<B> b, const Decay<E> e) {
		{b.Pow(e)} -> CT::Same<B>;
	};

	/// Checks for a Min(x) method															
	template<class T1, class T2>
	concept HasMin = requires (const Decay<T1> a, const Decay<T2> b) {
		{a.Min(b)} -> CT::Same<T1>;
	};

	/// Checks for a Max(x) method															
	template<class T1, class T2>
	concept HasMax = requires (const Decay<T1> a, const Decay<T2> b) {
		{a.Max(b)} -> CT::Same<T1>;
	};

	/// Checks for a Mod(x) method															
	template<class T1, class T2>
	concept HasMod = requires (const Decay<T1> a, const Decay<T2> b) {
		{a.Mod(b)} -> CT::Same<T1>;
	};

	/// Checks for a Dot(x) method															
	template<class T1, class T2>
	concept HasDot = requires (const Decay<T1> a, const Decay<T2> b) {
		{a.Dot(b)} -> CT::Number;
	};
	
	/// Checks for a Length() method															
	template<class T>
	concept HasLength = requires (const Decay<T> a) {
		{a.Length()} -> CT::Number;
	};
	
	/// Checks for a Sum() method																
	template<class T>
	concept HasSum = requires (const Decay<T> a) {
		{a.Sum()} -> CT::Number;
	};

	/// Checks for a Cross(x) method															
	template<class T1, class T2>
	concept HasCross = requires (const Decay<T1> a, const Decay<T2> b) {
		{a.Cross(b)} -> CT::Same<T1>;
	};
	
	/// Checks for a Step(edge) method														
	template<class T, class EDGE>
	concept HasStep = requires (const Decay<T> a, const Decay<EDGE> b) {
		{a.Step(b)} -> CT::Same<T>;
	};
	
	/// Checks for a Normalize() method														
	template<class T>
	concept HasNormalize = requires (const Decay<T> a) {
		{a.Normalize()} -> CT::Same<T>;
	};
	
	/// Checks for an Exp() method															
	template<class T>
	concept HasExp = requires (const Decay<T> a) {
		{a.Exp()} -> CT::Same<T>;
	};

	/// Checks for a Clamp(min,max) method													
	template<class T, class MIN, class MAX>
	concept HasClamp = requires (const Decay<T> v, const Decay<MIN> min, const Decay<MAX> max) {
		{v.Clamp(min, max)} -> CT::Same<T>;
	};

	/// Checks for a ClampRev(min,max) method												
	template<class T, class MIN, class MAX>
	concept HasClampRev = requires (const Decay<T> v, const Decay<MIN> min, const Decay<MAX> max) {
		{v.ClampRev(min, max)} -> CT::Same<T>;
	};

	/// Check if two types are multipliable												
	template<class LHS, class RHS>
	concept Multipliable = requires (const Decay<LHS> a, const Decay<RHS> b) {
		{a * b} -> CT::Same<LHS>;
	};

} // namespace Langulus::CT


namespace Langulus::Math
{
	
	/// Get absolute value																		
	///	@param a - the number/class to absolute										
	///	@return either T or whatever Abs() returns for class						
	template<CT::Dense T>
	NOD() constexpr auto Abs(const T& a) noexcept {
		if constexpr (CT::HasAbs<T>)
			return a.Abs();
		else if constexpr (CT::Unsigned<T>)
			return a;
		else if constexpr (CT::Signed<T>)
			return a < T {0} ? -a : a;
		else
			LANGULUS_ERROR("T must either have Abs() method, or be a number");
	}

	/// Signed unit																				
	///	@param a - the number/class to get sign of									
	///	@return either T(-1) or T(1), or whatever Sign() returns for class	
	template<CT::Dense T>
	NOD() constexpr auto Sign(const T& a) noexcept {
		if constexpr (CT::HasSign<T>)
			return a.Sign();
		else if constexpr (CT::Unsigned<T>) {
			(a);
			return T {1};
		}
		else if constexpr (CT::Signed<T>)
			return a < T {0} ? T {-1} : T {1};
		else
			LANGULUS_ERROR("T must either have Sign() method, or be a number");
	}

	/// Calculate base to the power of the exponent										
	///	@param base - value to exponentiate												
	///	@param exponent - the power to raise to										
	///	@return the exponentiated number, or whatever Pow() returns in class	
	template<CT::Dense B, CT::Dense E>
	NOD() constexpr auto Pow(B base, E exponent) noexcept {
		if constexpr (CT::HasPow<B, E>)
			return base.Pow(exponent);
		else if constexpr (CT::Integer<B, E>) {
			// Credit goes to: http://stackoverflow.com/questions/101439	
			B result {1};
			while (exponent) {
				if constexpr (CT::Unsigned<B>) {
					if (exponent & E {1})
						result *= base;
					exponent >>= E {1};
					base *= base;
				}
				else {
					result *= base;
					--exponent;
				}
			}
			return result;
		}
		else if constexpr (CT::Real<B>)
			return ::std::pow(base, exponent);
		else
			LANGULUS_ERROR("T must either have Pow(exponent) method, or be a number");
	}

	/// Get the smallest of the provided													
	template<CT::Dense T1, CT::Dense T2, CT::Dense... TAIL>
	NOD() constexpr auto Min(T1&& t1, T2&& t2, TAIL&&... tail) {
		if constexpr (sizeof...(TAIL) == 0) {
			if constexpr (CT::HasMin<T1, T2>)
				return t1.Min(t2);
			else if constexpr (CT::Sortable<T1, T2>)
				return t1 < t2 ? t1 : t2;
			else
				LANGULUS_ERROR("T must either have Min(t2) method, or be sortable");
		}
		else return Min(Min(t1, t2), tail...);
	}

	/// Get the biggest of the provided														
	template<CT::Dense T1, CT::Dense T2, CT::Dense... TAIL>
	NOD() constexpr auto Max(T1&& t1, T2&& t2, TAIL&&... tail) {
		if constexpr (sizeof...(TAIL) == 0) {
			if constexpr (CT::HasMax<T1, T2>)
				return t1.Max(t2);
			else if constexpr (CT::Sortable<T1, T2>)
				return t1 > t2 ? t1 : t2;
			else
				LANGULUS_ERROR("T must either have Max(t2) method, or be sortable");
		}
		else return Max(Max(t1, t2), tail...);
	}

	/// Round 																						
	template<CT::Dense T>
	NOD() constexpr auto Round(const T& a) noexcept {
		if constexpr (CT::HasRound<T>)
			return a.Round();
		else if constexpr (CT::Integer<T>)
			return a;
		else if constexpr (CT::Real<T>)
			return ::std::round(a);
		else
			LANGULUS_ERROR("T must either have Round() method, or be a number");
	}

	/// Round and return an integer															
	template<CT::Dense T>
	NOD() constexpr auto Roundi(const T& a) noexcept {
		if constexpr (CT::HasRound<T>)
			return static_cast<int>(a.Round());
		else if constexpr (CT::Integer<T>)
			return a;
		else if constexpr (CT::RealDP<T>) {
			const auto aa = a + T {6755399441055744.0};
			return reinterpret_cast<const int&>(aa);
		}
		else if constexpr (CT::RealSP<T>) {
			const auto aa = static_cast<double>(a) + double {6755399441055744.0};
			return reinterpret_cast<const int&>(aa);
		}
		else
			LANGULUS_ERROR("T must either have Round() method, or be a number");
	}

	/// Floor																						
	template<CT::Dense T>
	NOD() constexpr auto Floor(const T& a) noexcept {
		if constexpr (CT::HasFloor<T>)
			return a.Floor();
		else if constexpr (CT::Integer<T>)
			return a;
		else if constexpr (CT::Real<T>) {
			const auto round_a = Round<T>(a);
			return round_a <= a ? round_a : round_a - T {1};
		}
		else
			LANGULUS_ERROR("T must either have Floor() method, or be a number");
	}

	/// Floor and return an integer															
	template<CT::Dense T>
	NOD() constexpr auto Floori(const T& a) noexcept {
		return static_cast<int>(Floor<T>(a));
	}

	/// Ceil																							
	template<CT::Dense T>
	NOD() constexpr auto Ceil(const T& a) noexcept {
		if constexpr (CT::HasCeil<T>)
			return a.Ceil();
		else if constexpr (CT::Integer<T>)
			return a;
		else if constexpr (CT::Real<T>) {
			const auto round_a = Round<T>(a);
			return round_a >= a ? round_a : round_a + T(1);
		}
		else
			LANGULUS_ERROR("T must either have Ceil() method, or be a number");
	}

	/// Ceil and return an integer															
	template<CT::Dense T>
	NOD() constexpr auto Ceili(const T& a) noexcept {
		return static_cast<int>(Ceil<T>(a));
	}

	/// Get square of anything with multiplication operator							
	template<CT::Dense T>
	NOD() constexpr auto Sq(const T& n) noexcept {
		if constexpr (CT::Multipliable<T>)
			return n * n;
		else
			LANGULUS_ERROR("T must be CT::Multipliable");
	}

	namespace Detail
	{

		/// Compile time square root using binary search								
		template<CT::Unsigned T>
		NOD() constexpr T SqrtHelper(const T& x, const T& lo, const T& hi) noexcept requires CT::Dense<T> {
			return lo == hi
				? lo
				: ((x / ((lo + hi + T {1}) / T {2}) < ((lo + hi + T {1}) / T {2}))
					? SqrtHelper<T>(x, lo, ((lo + hi + T {1}) / T {2}) - T {1})
					: SqrtHelper<T>(x, ((lo + hi + T {1}) / T {2}), hi));
		}

	} // namespace Detail

	/// Square root																				
	///	@attention assumes x is not a negative number								
	template<CT::Dense T>
	NOD() constexpr auto Sqrt(const T& x) {
		if constexpr (CT::HasSqrt<T>)
			return x.Sqrt();
		else if constexpr (CT::Unsigned<T>)
			return Detail::SqrtHelper<T>(x, 0, x / 2 + 1);
		else if constexpr (CT::Integer<T>) {
			LANGULUS_ASSUME(UserAssumes, x >= 0,
				"Square root of negative signed integer");
			return T {Sqrt(::std::make_unsigned_t<T> {x})};
		}
		else if constexpr (CT::Real<T>) {
			LANGULUS_ASSUME(UserAssumes, x >= 0,
				"Square root of negative real");

			T p {1};
			while (p <= x / p)
				p = T {2} *p;

			T r {p};
			do {
				p = r;
				r = (r + x / r) * T {0.5f};
			} while (r < p);
			return p;
		}
		else LANGULUS_ERROR("T must either have Sqrt() method, or be a number");
	}
	
	/// Get a fractional part																	
	template<CT::Dense T>
	NOD() constexpr auto Frac(const T& f) noexcept {
		if constexpr (CT::HasFrac<T>)
			return f.Frac();
		else if constexpr (CT::Real<T>)
			return f - Floor(f);
		else if constexpr (CT::Integer<T>)
			return T {0};
		else
			LANGULUS_ERROR("T must either have Frac() method, or be a number");
	}

	/// Modulate																					
	template<CT::Dense T1, CT::Dense T2>
	NOD() constexpr auto Mod(const T1& x, const T2& y) noexcept {
		if constexpr (CT::HasMod<T1, T2>)
			return x.Mod(y);
		else if constexpr (CT::Integer<T1>)
			return x - y * T1 {Floor(RealDP{x} / RealDP{y})};
		else if constexpr (CT::Real<T1>)
			return x - y * Floor(x / y);
		else
			LANGULUS_ERROR("T must either have Mod(y) method, or be a number");
	}

	/// Remaps a [0; 1] range to a [-1; 1] range											
	template<CT::Dense T>
	NOD() constexpr auto Center(const T& a) noexcept {
		return a * T {2} - T {1};
	}

	/// Clamp a value inside the interval [min;max]										
	template<CT::Dense T, CT::Dense MIN, CT::Dense MAX>
	NOD() constexpr auto Clamp(const T& v, const MIN& min, const MAX& max) noexcept {
		if constexpr (CT::HasClamp<T, MIN, MAX>)
			return v.Clamp(min, max);
		else if constexpr (CT::Number<T, MIN, MAX>)
			return v < min ? min : (v > max ? max : v);
		else
			LANGULUS_ERROR("T must either have Clamp(min, max) method, or be a number");
	}

	/// Clamp a value inside the interval [0:1]											
	template<CT::Dense T>
	NOD() constexpr auto Clamp01(const T& v) noexcept {
		return Clamp(v, T {0}, T {1});
	}

	/// Clamp a value outside the interval (min:max)									
	/// If the value is near min, min is returned, otherwise max is returned	
	template<CT::Dense T, CT::Dense MIN, CT::Dense MAX>
	NOD() constexpr auto ClampRev(const T& v, const MIN& min, const MAX& max) noexcept {
		if constexpr (CT::HasClampRev<T, MIN, MAX>)
			return v.ClampRev(min, max);
		else if constexpr (CT::Number<T, MIN, MAX>) {
			const auto halfd = T {max - min} / T {2};
			if (v > min && v < max)
				return v - min > halfd ? max : min;
			return v;
		}
		else LANGULUS_ERROR("T must either have ClampRev(min, max) method, or be a number");
	}

	/// Dot product																				
	template<CT::Dense T1, CT::Dense T2>
	NOD() constexpr auto Dot(const T1& a, const T2& b) noexcept {
		if constexpr (CT::HasDot<T1, T2>)
			return a.Dot(b);
		else LANGULUS_ERROR("T must have Dot(b) method");
	}

	/// Self dot product																			
	template<CT::Dense T>
	NOD() constexpr auto Dot2(const T& a) noexcept {
		return Dot(a, a);
	}

	/// Cross product																				
	template<CT::Dense T1, CT::Dense T2>
	NOD() constexpr auto Cross(const T1& a, const T2& b) noexcept {
		if constexpr (CT::HasCross<T1, T2>)
			return a.Cross(b);
		else LANGULUS_ERROR("T must have Cross(b) method");
	}

	/// Get length (as in magnitude)															
	template<CT::Dense T>
	NOD() constexpr auto Length(const T& v) noexcept {
		if constexpr (CT::HasLength<T>)
			return v.Length();
		else if constexpr (CT::Number<T>)
			return Abs(v);
		else
			LANGULUS_ERROR("T must either have Length() method, or be a number");
	}

	/// Distance																					
	template<CT::Dense T1, CT::Dense T2>
	NOD() constexpr auto Distance(const T1& p0, const T2& p1) noexcept {
		return Length(p0 - p1);
	}

	/// Normalize																					
	template<CT::Dense T>
	NOD() constexpr auto Normalize(const T& v) noexcept {
		if constexpr (CT::HasNormalize<T>)
			return v.Normalize();
		else
			LANGULUS_ERROR("T must have Normalize() method");
	}

	/// Step function																				
	template<CT::Dense T, CT::Dense EDGE>
	NOD() constexpr auto Step(const EDGE& edge, const T& x) noexcept {
		if constexpr (CT::HasStep<T, EDGE>)
			return x.Step(edge);
		else if constexpr (CT::Number<T, EDGE>)
			return x < edge ? T {0} : T {1};
		else
			LANGULUS_ERROR("T must either have Step(edge) method, or be a number");
	}

	/// Smooth step (Hermite) interpolation, analogous to the GLSL function		
	template<CT::Dense T, CT::Dense MIN, CT::Dense MAX>
	NOD() constexpr auto SmoothStep(const MIN& min, const MAX& max, const T& x) noexcept {
		const T t = Clamp01((x - T {min}) / T {max - min});
		return t * t * (-t * T {2} + T {3});
	}

	/// Returns the base-e exponential function of x, which is e raised to x	
	///	@param exponent - the power to raise to										
	///	@return e^x																				
	template<CT::Dense T>
	NOD() constexpr auto Exp(const T& x) noexcept {
		if constexpr (CT::HasExp<T>)
			return x.Exp();
		else if constexpr (CT::Number<T>)
			return ::std::exp(x);
		else
			LANGULUS_ERROR("T must either have Exp() method, or be a number");
	}

	/// Solve 2^x																					
	template<CT::Dense T>
	NOD() constexpr auto Exp2(const T& x) noexcept {
		return Pow(T {2}, x);
	}

	/// Sum of positive numbers [0;n], or elements of vector						
	template<CT::Dense T>
	NOD() constexpr T Sum(const T& n) noexcept {
		if constexpr (CT::HasSum<T>)
			return n.Sum();
		else if constexpr (CT::Number<T>) {
			LANGULUS_ASSUME(UserAssumes, n >= 0, "Can't get sum of non-positive integers");
			return (n * (n + T {1})) / T {2};
		}
		else LANGULUS_ERROR("T must either have Sum() method, or be a number");
	}

	/// A Kahan summation used to minimize floating-point math error				
	///	@param cookie - provide zero on first iteration								
	///	@param input - the number to add, repeat for more numbers				
	///	@param output - the sum, gets overwritten every time						
	template<CT::Dense T>
	void KahanSum(T& cookie, const T& input, T& output) noexcept {
		T y = input - cookie;
		// So far, so good: cookie be zero on first iteration					
		T t = output + y;
		// Output is big, y small - low-order y is lost							
		cookie = (t - output) - y;
		// (t - sum) recovers high-order y											
		output = t;
		// Next time around, the lost low part will be fixed					
	}

	/// Linear interpolation																	
	///	@param n0 - first point																
	///	@param n1 - second point															
	///	@param a - rate																		
	///	@return the linearly interpolated value										
	template<CT::Dense T1, CT::Dense T2, CT::Dense R>
	NOD() constexpr auto Lerp(const T1& n0, const T2& n1, const R& a) noexcept {
		return n0 + a * (n1 - n0);
	}

	/// Cubic interpolation (Hermit interpolation, using tangents)					
	///	@param n0 - first point																
	///	@param m0 - tangent to first point												
	///	@param n1 - second point															
	///	@param m1 - tangent to second point												
	///	@param a - rate																		
	///	@return the cubically interpolated value										
	template<CT::Dense T1, CT::Dense T2, CT::Dense T3, CT::Dense T4, CT::Dense T5>
	NOD() constexpr auto CerpTan(const T1& n0, const T2& m0, const T3& n1, const T4& m1, const T5& a) noexcept {
		const auto t2 = a * a;
		const auto t3 = t2 * a;
		return
			  T1 {T1 {2} * t3 - T1 {3} * t2 + T1 {1}} * n0
			+ T1 {t3 - T1 {2} * t2 + T1 {a}} * T1 {m0}
			+ T3 {T3 {-2} * t3 + T3 {3} * t2} * n1
			+ T3 {t3 - t2} * T3 {m1};
	}

	/// Cubic interpolation																		
	///	@param n0 - the point before the first point									
	///	@param n1 - first point																
	///	@param n2 - second point															
	///	@param n3 - the point after the second point									
	///	@param a - the rate																	
	///	@return the cubically interpolated value										
	template<CT::Dense T1, CT::Dense T2, CT::Dense T3, CT::Dense T4, CT::Dense T5>
	NOD() constexpr auto Cerp(const T1& n0, const T2& n1, const T3& n2, const T4& n3, const T5& a) noexcept {
		const auto t2 = a * a;
		const auto t3 = t2 * a;
		const auto p = (n3 - n2) - (n0 - n1);
		return p * t3 + ((n0 - n1) - p) * t2 + (n2 - n0) * a + n1;
	}

} // namespace Langulus::Math