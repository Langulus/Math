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
	struct TQuaternion : public TVector<T, 4> {
		using Base = TVector<T, 4>;
		using Base::Base;
		using Base::mArray;

		/// Default quaternion construction to identity									
		constexpr TQuaternion() noexcept
			: Base {0, 0, 0, 1} {}

		/// Construct a roll (around Z) quaternion from 2x2 matrix					
		///	@param matrix - 2x2 matrix to convert to a roll quaternion			
		constexpr TQuaternion(const TMatrix<T, 2, 2>& matrix) noexcept {
			const auto trace = T {1} + matrix[0] + matrix[3];
			const auto S = Sqrt(trace) * T {2};
			mArray[0] = mArray[1] = T {0};
			mArray[2] = (matrix[2] - matrix[1]) / S;
			mArray[3] = T {.25} *S;
		}

		/// Constructor from 3x3 matrix														
		///	@param matrix - 3x3 matrix to convert to a quaternion					
		constexpr TQuaternion(const TMatrix<T, 3, 3>& mat) noexcept {
			const auto m11 = mat.Get(0, 0), m12 = mat.Get(0, 1), m13 = mat.Get(0, 2);
			const auto m21 = mat.Get(1, 0), m22 = mat.Get(1, 1), m23 = mat.Get(1, 2);
			const auto m31 = mat.Get(2, 0), m32 = mat.Get(2, 1), m33 = mat.Get(2, 2);
			const auto trace = m11 + m22 + m33;
			constexpr T one {1};
			constexpr T quarter {.25};
			constexpr T two {2};
			constexpr T half {.5};

			T s;
			if (trace > 0) {
				s = half / Sqrt(trace + one);
				mArray[3] = quarter / s;
				mArray[0] = (m32 - m23) * s;
				mArray[1] = (m13 - m31) * s;
				mArray[2] = (m21 - m12) * s;
			}
			else if (m11 > m22 && m11 > m33) {
				s = two * Sqrt(one + m11 - m22 - m33);
				mArray[3] = (m32 - m23) / s;
				mArray[0] = quarter * s;
				mArray[1] = (m12 + m21) / s;
				mArray[2] = (m13 + m31) / s;
			}
			else if (m22 > m33) {
				s = two * Sqrt(one + m22 - m11 - m33);
				mArray[3] = (m13 - m31) / s;
				mArray[0] = (m12 + m21) / s;
				mArray[1] = quarter * s;
				mArray[2] = (m23 + m32) / s;
			}
			else {
				s = two * Sqrt(one + m33 - m11 - m22);
				mArray[3] = (m21 - m12) / s;
				mArray[0] = (m13 + m31) / s;
				mArray[1] = (m23 + m32) / s;
				mArray[2] = quarter * s;
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

		/// Quaterion-quaternion product														
		///	@param lhs - the left operand													
		///	@param rhs - the right operand												
		///	@return the product of the two provided quaternions					
		NOD() friend TQuaternion operator * (const TQuaternion& lhs, const TQuaternion& rhs) noexcept {
			return {
				lhs.mArray[0] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[0] + lhs.mArray[1] * rhs.mArray[2] - lhs.mArray[2] * rhs.mArray[1],
				lhs.mArray[1] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[1] + lhs.mArray[2] * rhs.mArray[0] - lhs.mArray[0] * rhs.mArray[2],
				lhs.mArray[2] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[2] + lhs.mArray[0] * rhs.mArray[1] - lhs.mArray[1] * rhs.mArray[0],
				lhs.mArray[3] * rhs.mArray[3] - lhs.mArray[0] * rhs.mArray[0] - lhs.mArray[1] * rhs.mArray[1] - lhs.mArray[2] * rhs.mArray[2]
			};
		}

		/// Create a quaternion from euler angles	in radians							
		/*
		inline static constexpr ME FromEuler(const T& yaw, const T& pitch, const T& roll) noexcept {
			const auto qy = FromAxisAngle(Up<T>, yaw);
			const auto qx = FromAxisAngle(Right<T>, pitch);
			const auto qz = FromAxisAngle(Forward<T>, roll);
			return (qx * qy) * qz;
		}*/

		/// Create a quaternion from axis and angle										
		template<CT::Angle A>
		NOD() static constexpr TQuaternion FromAxisAngle(const TVector<T, 3>& axis, const A& angle) noexcept {
			const auto halfangle = angle * T {0.5};
			return {axis * Sin(halfangle), Cos(halfangle)};
		}

		/// Create a quaternion from an oriented angle									
		template<CT::Angle A, CT::Dimension D>
		NOD() static constexpr TQuaternion FromAngle(const TAngle<A, D>& angle) noexcept {
			if constexpr (CT::Same<D, Traits::X>)
				return FromAxisAngle(Vectors::Right<T>, angle);
			else if constexpr (CT::Same<D, Traits::Y>)
				return FromAxisAngle(Vectors::Up<T>, angle);
			else if constexpr (CT::Same<D, Traits::Z>)
				return FromAxisAngle(Vectors::Forward<T>, angle);
			else
				LANGULUS_ERROR("Unsupported dimension");
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
		constexpr TQuaternion& LookAt(const TVector<T, 3>& dir) noexcept {
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
		NOD() constexpr TQuaternion Conjugate() const noexcept {
			auto result = *this * T(-1);
			result[3] *= T(-1);
			return result;
		}

		/// Get normalized quaternion															
		NOD() constexpr TQuaternion Normalize() const {
			return Base::Normalize();
		}

		/// Conjugate operator																	
		NOD() constexpr TQuaternion operator - () const noexcept {
			return Conjugate();
		}

		/// Convert to a 4x4 matrix															
		template<CT::DenseNumber K = T>
		NOD() explicit constexpr operator TMatrix<K, 4, 4>() const noexcept {
			return pcCompose<TVector<K, 3>>(*this);
		}

		/// Convert to a 3x3 matrix															
		template<CT::DenseNumber K = T>
		NOD() explicit constexpr operator TMatrix<K, 3, 3>() const noexcept {
			return pcCompose<TVector<K, 3>>(*this);
		}

		///																							
		///	Compare																				
		///																							
		using Base::operator ==;
	};


	/// Quaterion * Vector																		
	///	@param lhs - left hand side quaternion											
	///	@param rhs - right hand side vector of at least 2 components			
	///	@return a lossless product of the two											
	template<CT::DenseNumber T1, CT::DenseNumber T2, Count C>
	NOD() auto operator * (const TQuaternion<T1>& lhs, const TVector<T2, C>& rhs) noexcept requires(C >= 2) {
		using LT = Lossless<T1, T2>;
		const TQuaternion<LT> vecQuat {TVector<T2, 3>(rhs), 0};
		return TVector<LT, C> {(lhs.Conjugate() * vecQuat) * lhs};
	}

	/// Vector * Quaterion																		
	///	@param lhs - left hand side vector of at least 2 components				
	///	@param rhs - right hand side quaternion										
	///	@return a lossless product of the two											
	template<CT::DenseNumber T1, CT::DenseNumber T2, Count C>
	NOD() auto operator * (const TVector<T1, C>& lhs, const TQuaternion<T2>& rhs) noexcept requires(C >= 2) {
		using LT = Lossless<T1, T2>;
		const TQuaternion<LT> vecQuat {TVector<T2, 3>(lhs), 0};
		return TVector<LT, C> {(lhs * vecQuat) * rhs.Conjugate()};
	}

	/// Quaterion *= Quaternion																
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	void operator *= (TQuaternion<T1>& lhs, const TQuaternion<T2>& rhs) noexcept {
		lhs = lhs * rhs;
	}

	/// Quaternion + Scalar																		
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator + (const TQuaternion<T1>& lhs, const T2& rhs) noexcept {
		using LT = Lossless<T1, T2>;
		return SIMD::AddWrap<TQuaternion<LT>>(lhs.mArray, rhs);
	}

	/// Scalar + Quaternion																		
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator + (const T1& lhs, const TQuaternion<T2>& rhs) noexcept {
		using LT = Lossless<T1, T2>;
		return SIMD::AddWrap<TQuaternion<LT>>(lhs, rhs.mArray);
	}

	/// Quaternion - Scalar																		
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator - (const TQuaternion<T1>& lhs, const T2& rhs) noexcept {
		using LT = Lossless<T1, T2>;
		return SIMD::SubtractWrap<TQuaternion<LT>>(lhs.mArray, rhs);
	}

	/// Scalar - Quaternion 																	
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator - (const T1& lhs, const TQuaternion<T2>& rhs) noexcept {
		using LT = Lossless<T1, T2>;
		return SIMD::SubtractWrap<TQuaternion<LT>>(lhs, rhs.mArray);
	}

	/// Quaternion * Scalar																		
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator * (const TQuaternion<T1>& lhs, const T2& rhs) noexcept {
		using LT = Lossless<T1, T2>;
		return SIMD::MultiplyWrap<TQuaternion<LT>>(lhs.mArray, rhs);
	}

	/// Scalar * Quaternion 																	
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator * (const T1& lhs, const TQuaternion<T2>& rhs) noexcept {
		using LT = Lossless<T1, T2>;
		return SIMD::MultiplyWrap<TQuaternion<LT>>(lhs, rhs.mArray);
	}

	/// Quaternion / Scalar																		
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator / (const TQuaternion<T1>& lhs, const T2& rhs) {
		using LT = Lossless<T1, T2>;
		return SIMD::DivideWrap<TQuaternion<LT>>(lhs.mArray, rhs);
	}

	/// Scalar / Quaternion 																	
	template<CT::DenseNumber T1, CT::DenseNumber T2>
	NOD() auto operator / (const T1& lhs, const TQuaternion<T2>& rhs) {
		using LT = Lossless<T1, T2>;
		return SIMD::DivideWrap<TQuaternion<LT>>(lhs, rhs.mArray);
	}


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

		constexpr K one {1};
		result.Get(0, 0) = (one - (yy + zz)) * sx;
		result.Get(1, 0) = (xy + wz) * sx;
		result.Get(2, 0) = (xz - wy) * sx;

		result.Get(0, 1) = (xy - wz) * sy;
		result.Get(1, 1) = (one - (xx + zz)) * sy;
		result.Get(2, 1) = (yz + wx) * sy;

		result.Get(0, 2) = (xz + wy) * sz;
		result.Get(1, 2) = (yz - wx) * sz;
		result.Get(2, 2) = (one - (xx + yy)) * sz;

		result.SetPosition(p);
		return result;
	}

} // namespace Langulus::Math
