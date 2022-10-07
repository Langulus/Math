///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Matrices/TMatrix.hpp"
#include "../Numbers/TAngle.hpp"

namespace Langulus::Math
{

	template<CT::DenseNumber>
	class TQuaternion;

	using Quaternionf = TQuaternion<RealSP>;
	using Quaterniond = TQuaternion<RealDP>;
	using Quaternion = TQuaternion<Real>;

	template<CT::Vector T>
	NOD() TMatrix<typename T::MemberType, T::MemberCount + 1> pcCompose(const TQuaternion<typename T::MemberType>&, const T & = 0, const T & = 1) noexcept;

	namespace A
	{

		/// Used as an imposed base for any type that can be interpretable as a	
		/// quaternion																				
		struct Quaternion {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::Quaternion;
		};

		/// Used as an imposed base for any type that can be interpretable as a	
		/// quaternion of the same type														
		template<CT::DenseNumber T>
		struct QuaternionOfType : public Quaternion {
			LANGULUS(CONCRETE) TQuaternion<T>;
			LANGULUS_BASES(Quaternion);
			using MemberType = T;
		};

	} // namespace Langulus::Math::A


	///																								
	///	Templated quaternion																	
	///																								
	template<CT::DenseNumber T>
	class TQuaternion {
	public:
		using MemberType = T;
		static constexpr Count MemberCount = 4;

		T mArray[4] {0, 0, 0, 1};

	public:
		constexpr TQuaternion() noexcept = default;

		/// Copy construction																	
		///	@param a - the quaternion to copy											
		constexpr TQuaternion(const TQuaternion& a) noexcept
			: mArray {a.mArray[0], a.mArray[1], a.mArray[2], a.mArray[3]} { }

		/// Manual construction																	
		///	@param a - x component															
		///	@param b - y component															
		///	@param c - c component															
		///	@param d - w component															
		constexpr TQuaternion(const T& a, const T& b, const T& c, const T& d) noexcept
			: mArray {a, b, c, d} { }

		/// Creation from dense memory														
		///	@param ar - beginning of array to copy										
		constexpr TQuaternion(const T* ar) noexcept
			: mArray {ar[0], ar[1], ar[2], ar[3]} { }

		/// Creation from sparse memory														
		///	@param ar - beginning of pointer array to copy							
		constexpr TQuaternion(const T** ar) noexcept
			: mArray {*ar[0], *ar[1], *ar[2], *ar[3]} { }

		/// Construct a roll (around Z) quaternion from 2x2 matrix					
		///	@param matrix - 2x2 matrix to convert to a roll quaternion			
		constexpr TQuaternion(const TMatrix<T, 2, 2>& matrix) noexcept {
			const auto trace = T(1) + matrix[0] + matrix[3];
			const auto S = pcSqrt(trace) * T(2);
			mArray[0] = mArray[1] = T(0);
			mArray[2] = (matrix[2] - matrix[1]) / S;
			mArray[3] = T(0.25) * S;
			return;
		}

		/// Constructor from 3x3 matrix														
		///	@param matrix - 3x3 matrix to convert to a quaternion					
		constexpr TQuaternion(const TMatrix<T, 3, 3>& mat) noexcept {
			const auto m11 = mat.Get(0, 0), m12 = mat.Get(0, 1), m13 = mat.Get(0, 2);
			const auto m21 = mat.Get(1, 0), m22 = mat.Get(1, 1), m23 = mat.Get(1, 2);
			const auto m31 = mat.Get(2, 0), m32 = mat.Get(2, 1), m33 = mat.Get(2, 2);
			const auto trace = m11 + m22 + m33;
			T s;
			if (trace > 0) {
				s = T(0.5) / pcSqrt(trace + T(1.0));
				mArray[3] = T(0.25) / s;
				mArray[0] = (m32 - m23) * s;
				mArray[1] = (m13 - m31) * s;
				mArray[2] = (m21 - m12) * s;
			}
			else if (m11 > m22 && m11 > m33) {
				s = T(2.0) * pcSqrt(T(1.0) + m11 - m22 - m33);
				mArray[3] = (m32 - m23) / s;
				mArray[0] = T(0.25) * s;
				mArray[1] = (m12 + m21) / s;
				mArray[2] = (m13 + m31) / s;
			}
			else if (m22 > m33) {
				s = T(2.0) * pcSqrt(T(1.0) + m22 - m11 - m33);
				mArray[3] = (m13 - m31) / s;
				mArray[0] = (m12 + m21) / s;
				mArray[1] = T(0.25) * s;
				mArray[2] = (m23 + m32) / s;
			}
			else {
				s = T(2.0) * pcSqrt(T(1.0) + m33 - m11 - m22);
				mArray[3] = (m21 - m12) / s;
				mArray[0] = (m13 + m31) / s;
				mArray[1] = (m23 + m32) / s;
				mArray[2] = T(0.25) * s;
			}
		}

		/// Constructor from 4x4 matrix (only the 3x3 part is relevant)			
		///	@param matrix - 4x4 matrix to convert to a quaternion					
		constexpr TQuaternion(const TMatrix<T, 4, 4>& matrix) noexcept
			: TQuaternion(static_cast<TMatrix<T, 3, 3>>(matrix)) {}

		/// Serialize quaternion to GASM														
		NOD() explicit operator Flow::Code() const {
			Flow::Code result;
			result += RTTI::MetaData::Of<ME>();
			result += Flow::Code::OpenScope;
			result += (*this)[0];
			result += ", ";
			result += (*this)[1];
			result += ", ";
			result += (*this)[2];
			result += ", ";
			result += (*this)[3];
			result += Flow::Code::CloseScope;
			return result;
		}

		NOD() constexpr auto& operator [] (const Offset a) noexcept {
			return mArray[a];
		}

		NOD() constexpr auto& operator [] (const Offset a) const noexcept {
			return mArray[a];
		}

		NOD() constexpr auto operator () () noexcept {
			return mArray;
		}

		NOD() constexpr auto operator () () const noexcept {
			return mArray;
		}

		/// Get the magnitude of the quaternion											
		///	@return the scalar magnitude													
		NOD() constexpr T Length() const noexcept {
			T accum = mArray[0] * mArray[0];
			for (int i = 1; i < MemberCount; ++i)
				accum += mArray[i] * mArray[i];
			return pcSqrt(accum);
		}

		/// Quaterion-quaternion product														
		///	@param lhs - the left operand													
		///	@param rhs - the right operand												
		///	@return the product of the two provided quaternions					
		NOD() friend ME operator * (const ME& lhs, const ME& rhs) noexcept {
			return {
				lhs.mArray[0] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[0] + lhs.mArray[1] * rhs.mArray[2] - lhs.mArray[2] * rhs.mArray[1],
				lhs.mArray[1] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[1] + lhs.mArray[2] * rhs.mArray[0] - lhs.mArray[0] * rhs.mArray[2],
				lhs.mArray[2] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[2] + lhs.mArray[0] * rhs.mArray[1] - lhs.mArray[1] * rhs.mArray[0],
				lhs.mArray[3] * rhs.mArray[3] - lhs.mArray[0] * rhs.mArray[0] - lhs.mArray[1] * rhs.mArray[1] - lhs.mArray[2] * rhs.mArray[2]
			};
		}

		/// Quaterion * Vector																	
		template<class K, pcptr C>
		NOD() friend TVector<K, C> operator * (const ME& me, const TVector<K, C>& point) noexcept requires(C >= 2) {
			ME vecQuat;
			if constexpr (C == 2)
				vecQuat = {static_cast<T>(point[0]), static_cast<T>(point[1]), T(0), T(0)};
			else
				vecQuat = {static_cast<T>(point[0]), static_cast<T>(point[1]), static_cast<T>(point[2]), T(0)};

			const ME resQuat = (me.Conjugate() * vecQuat) * me;
			return {resQuat.mArray};
		}

		/// Vector * Quaterion																	
		template<class K, pcptr C>
		NOD() friend TVector<K, C> operator * (const TVector<K, C>& point, const ME& me) noexcept requires(C >= 2) {
			ME vecQuat;
			if constexpr (C == 2)
				vecQuat = {static_cast<T>(point[0]), static_cast<T>(point[1]), T(0), T(0)};
			else
				vecQuat = {static_cast<T>(point[0]), static_cast<T>(point[1]), static_cast<T>(point[2]), T(0)};

			const ME resQuat = (me * vecQuat) * me.Conjugate();
			return {resQuat.mArray};
		}

		/// Quaterion *= Quaternion															
		friend void operator *= (ME& me, const ME& other) noexcept {
			me = me * other;
		}

		/// Quaternion + Scalar																	
		template<Number K>
		NOD() friend ME operator + (const ME& me, const K& other) noexcept {
			return SIMD::AddWrap<ME>(me.mArray, other);
		}

		/// Scalar + Quaternion																	
		template<Number K>
		NOD() friend ME operator + (const K& other, const ME& me) noexcept {
			return me * other;
		}

		/// Quaternion - Scalar																	
		template<Number K>
		NOD() friend ME operator - (const ME& me, const K& other) noexcept {
			return SIMD::SubtractWrap<ME>(me.mArray, other);
		}

		/// Scalar - Quaternion 																
		template<Number K>
		NOD() friend ME operator - (const K& other, const ME& me) noexcept {
			return SIMD::SubtractWrap<ME>(other, me.mArray);
		}

		/// Quaternion * Scalar																	
		template<Number K>
		NOD() friend ME operator * (const ME& me, const K& other) noexcept {
			return SIMD::MultiplyWrap<ME>(me.mArray, other);
		}

		/// Scalar * Quaternion 																
		template<Number K>
		NOD() friend ME operator * (const K& other, const ME& me) noexcept {
			return me * other;
		}

		/// Quaternion / Scalar																	
		template<Number K>
		NOD() friend ME operator / (const ME& me, const K& other) noexcept {
			return SIMD::DivideWrap<ME>(me.mArray, other);
		}

		/// Scalar / Quaternion 																
		template<Number K>
		NOD() friend ME operator / (const K& other, const ME& me) noexcept {
			return SIMD::DivideWrap<ME>(other, me.mArray);
		}

		/// Create a quaternion from euler angles	in radians							
		/*
		inline static constexpr ME FromEuler(const T& yaw, const T& pitch, const T& roll) noexcept {
			const auto qy = FromAxisAngle(Up<T>, yaw);
			const auto qx = FromAxisAngle(Right<T>, pitch);
			const auto qz = FromAxisAngle(Forward<T>, roll);
			return (qx * qy) * qz;
		}*/

		/// Create a quaternion from axis and angle in radians						
		NOD() static constexpr ME FromAxisAngle(const TVector<T, 3>& axis, const T angle) noexcept {
			const auto hangle = angle * T(0.5);
			const auto sin_a = pcSin(hangle);
			return ME(sin_a * axis[0], sin_a * axis[1], sin_a * axis[2], pcCos(hangle));
		}

		/// Create a quaternion from an angle												
		template<Dimension AXIS, bool RAD>
		NOD() static constexpr ME FromAngle(const TAngle<T, AXIS, RAD>& angle) noexcept {
			if constexpr (AXIS == Dimension::X)
				return FromAxisAngle(Vectors::Right<T>, angle.GetRadians());
			else if constexpr (AXIS == Dimension::Y)
				return FromAxisAngle(Vectors::Up<T>, angle.GetRadians());
			else if constexpr (AXIS == Dimension::Z)
				return FromAxisAngle(Vectors::Forward<T>, angle.GetRadians());
			else LANGULUS_ASSERT("Unsupported axis");
		}

		/// Constructor from axii and angles												
		/*inline static constexpr ME FromAxiiAndAngles(
			const TVec<T, 4>& right_pitch,
			const TVec<T, 4>& up_yaw,
			const TVec<T, 4>& look_roll) noexcept {
			const auto qyaw = FromAxisAngle(up_yaw, up_yaw[3]);
			const auto qtilt = FromAxisAngle(right_pitch, right_pitch[3]);
			const auto qroll = FromAxisAngle(look_roll, look_roll[3]);
			return qyaw * qtilt * qroll;
		}*/

		/// Quaternion from two normals														
		/*inline static constexpr ME FromNormals(const TVec<T, 3>& from, const TVec<T, 3>& to) noexcept {
			auto H = from + to;
			H.Normalize();
			return {
				from[1] * H[2] - from[2] * H[1],
				from[2] * H[0] - from[0] * H[2],
				from[0] * H[1] - from[1] * H[0],
				from.Dot(H)
			};
		}*/

		/// Quaternion look at																	
		constexpr ME& LookAt(const TVector<T, 3>& dir) noexcept {
			auto look = (*this) * Vectors::Forward<T>;
			auto axis = dir % look;
			auto angle = T(1) / dir.Dot(look);
			return FromAxisAngle(axis, angle);
		}

		/// Get rotated axii (doesn't normalize the quaternion)						
		NOD() constexpr auto GetForward() const noexcept {
			return *this * Vectors::Forward<T>;
		}

		NOD() constexpr auto GetBackward() const noexcept {
			return *this * Vectors::Backward<T>;
		}

		NOD() constexpr auto GetRight() const noexcept {
			return *this * Vectors::Right<T>;
		}

		NOD() constexpr auto GetLeft() const noexcept {
			return *this * Vectors::Left<T>;
		}

		NOD() constexpr auto GetUp() const noexcept {
			return *this * Vectors::Up<T>;
		}

		NOD() constexpr auto GetDown() const noexcept {
			return *this * Vectors::Down<T>;
		}

		/// Get conjugated quaternion															
		NOD() constexpr ME Conjugate() const noexcept {
			auto result = *this * T(-1);
			result[3] *= T(-1);
			return result;
		}

		/// Get normalized quaternion															
		NOD() constexpr ME Normalize() const {
			const auto l = Length();
			if (l == T(0))
				throw Except::Arithmetic("Degenerate quaternion");

			const auto t = T(1) / l;
			return *this * t;
		}

		/// Conjugate operator																	
		NOD() constexpr ME operator - () const noexcept {
			return Conjugate();
		}

		/// Convert to a 4x4 matrix															
		template<RealNumber K = T>
		NOD() explicit constexpr operator TMat<K, 4, 4>() const noexcept {
			using VectorType = TVec<K, 3>;
			return pcCompose<VectorType>(*this);
		}

		/// Convert to a 3x3 matrix															
		template<RealNumber K = T>
		NOD() explicit constexpr operator TMat<K, 3, 3>() const noexcept {
			using VectorType = TVec<K, 3>;
			return pcCompose<VectorType>(*this);
		}

		///																							
		///	Compare																				
		///																							
		NOD() friend constexpr bool operator == (const ME& lhs, const ME& rhs) noexcept {
			return pcNear(lhs[0], rhs[0])
				&& pcNear(lhs[1], rhs[1])
				&& pcNear(lhs[2], rhs[2])
				&& pcNear(lhs[3], rhs[3]);
		}
	};


	/// Compose a transformation matrix by combining position, orientation		
	/// and scale																					
	///	@param q - the orientation															
	///	@param p - the position																
	///	@param s - the scale																	
	///	@return the composed matrix														
	template<CT::Vector T>
	NOD() TMatrix<typename T::MemberType, T::MemberCount + 1>
		pcCompose(const TQuaternion<typename T::MemberType>& q, const T& p, const T& s) noexcept {
		using K = typename T::MemberType;
		TMatrix<K, T::MemberCount + 1> result;
		auto& x = q[0];
		auto& y = q[1];
		auto& z = q[2];
		auto& w = q[3];

		auto x2 = x + x, y2 = y + y, z2 = z + z;
		auto xx = x * x2, xy = x * y2, xz = x * z2;
		auto yy = y * y2, yz = y * z2, zz = z * z2;
		auto wx = w * x2, wy = w * y2, wz = w * z2;
		auto& sx = s[0];
		auto& sy = s[1];
		auto& sz = s[2];

		result.Get(0, 0) = (K(1) - (yy + zz)) * sx;
		result.Get(1, 0) = (xy + wz) * sx;
		result.Get(2, 0) = (xz - wy) * sx;

		result.Get(0, 1) = (xy - wz) * sy;
		result.Get(1, 1) = (K(1) - (xx + zz)) * sy;
		result.Get(2, 1) = (yz + wx) * sy;

		result.Get(0, 2) = (xz + wy) * sz;
		result.Get(1, 2) = (yz - wx) * sz;
		result.Get(2, 2) = (K(1) - (xx + yy)) * sz;

		result.SetPosition(p);
		return result;
	}

} // namespace Langulus::Math
