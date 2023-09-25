///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TQuaternion.hpp"
#include "../Vectors/TVector.inl"
#include "../Matrices/TMatrix.inl"

#define TEMPLATE() template<CT::DenseNumber T>
#define QUAT() TQuaternion<T>


namespace Langulus::Math
{

   /// Default quaternion construction to identity                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT()::TQuaternion() noexcept
      : Base {0, 0, 0, 1} {
      static_assert(CT::Vector<QUAT()>,
         "Quaternions should match CT::Vector");
      static_assert(CT::VectorBased<QUAT()>,
         "Quaternions should match CT::VectorBased");
      static_assert(sizeof(QUAT()) == sizeof(Base),
         "Quaternions should match Base size");
      static_assert(sizeof(QUAT()) == sizeof(T) * 4,
         "Quaternions should match T*4 size");
      static_assert(CountOf<QUAT()> == 4,
         "Quaternions should have four elements");
      static_assert(CT::Exact<TypeOf<QUAT()>, T>,
         "Quaternions should have type");
   }

   /// Quaternion construction from 4-component vector                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT()::TQuaternion(const Base& v) noexcept
      : Base {v} {}

   /// Construct a roll (around Z) quaternion from 2x2 matrix                 
   ///   @param matrix - 2x2 matrix to convert to a roll quaternion           
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT()::TQuaternion(const TMatrix<T, 2, 2>& matrix) noexcept {   
      const auto trace = T {1} + matrix[0] + matrix[3];
      const auto S = Math::Sqrt(trace) * T {2};
      mArray[0] = mArray[1] = T {0};
      mArray[2] = (matrix[2] - matrix[1]) / S;
      mArray[3] = T {.25} *S;
   }

   /// Constructor from 3x3 matrix                                            
   ///   @param matrix - 3x3 matrix to convert to a quaternion                
   TEMPLATE()
   template<Count COLUMNS, Count ROWS>
   constexpr QUAT()::TQuaternion(
      const TMatrix<T, COLUMNS, ROWS>& m
   ) noexcept requires (COLUMNS >= 3 and ROWS >= 3) {
      const T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
      const T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
      const T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
      const T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

      Offset biggestIndex = 3;
      T fourBiggestSquaredMinus1 = fourWSquaredMinus1;

      if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
         fourBiggestSquaredMinus1 = fourXSquaredMinus1;
         biggestIndex = 0;
      }

      if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
         fourBiggestSquaredMinus1 = fourYSquaredMinus1;
         biggestIndex = 1;
      }

      if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
         fourBiggestSquaredMinus1 = fourZSquaredMinus1;
         biggestIndex = 2;
      }

      const T biggestVal = Math::Sqrt(fourBiggestSquaredMinus1 + T {1}) * T {0.5};
      mArray[biggestIndex] = biggestVal;

      const T mult = T {0.25} / biggestVal;
      switch (biggestIndex) {
      case 0:
         mArray[3] = (m[1][2] - m[2][1]) * mult;
         mArray[1] = (m[0][1] + m[1][0]) * mult;
         mArray[2] = (m[2][0] + m[0][2]) * mult;
         break;
      case 1:
         mArray[3] = (m[2][0] - m[0][2]) * mult;
         mArray[0] = (m[0][1] + m[1][0]) * mult;
         mArray[2] = (m[1][2] + m[2][1]) * mult;
         break;
      case 2:
         mArray[3] = (m[0][1] - m[1][0]) * mult;
         mArray[0] = (m[2][0] + m[0][2]) * mult;
         mArray[1] = (m[1][2] + m[2][1]) * mult;
         break;
      case 3:
         mArray[2] = (m[1][2] - m[2][1]) * mult;
         mArray[1] = (m[2][0] - m[0][2]) * mult;
         mArray[0] = (m[0][1] - m[1][0]) * mult;
         break;
      default:
         // Never really happens, just silence warnings                 
         break;
      }
   }

   /// Serialize quaternion to code                                           
   TEMPLATE() LANGULUS(INLINED)
   QUAT()::operator Flow::Code() const {
      return Base::template Serialize<TQuaternion>();
   }

   /// Create a quaternion from euler angles   in radians                     
   /*
   inline static constexpr ME FromEuler(const T& yaw, const T& pitch, const T& roll) noexcept {
      const auto qy = FromAxisAngle(Up<T>, yaw);
      const auto qx = FromAxisAngle(Right<T>, pitch);
      const auto qz = FromAxisAngle(Forward<T>, roll);
      return (qx * qy) * qz;
   }*/

   /// Create a quaternion from axis and angle                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT() QUAT()::FromAxis(const Base3& axis, const CT::Angle auto& angle) noexcept {
      using A = Deref<decltype(angle)>;
      const auto halfangle = angle * A {.5};
      return {
         axis * Math::Sin(halfangle), 
         Math::Cos(halfangle)
      };
   }

   /// Create a quaternion from an oriented angle                             
   TEMPLATE()
   template<CT::Angle A, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr QUAT() QUAT()::FromAngle(const TAngle<A, D>& angle) noexcept {
      if constexpr (CT::Same<D, Traits::X>)
         return FromAxisAngle(Axes::X<T>, angle);
      else if constexpr (CT::Same<D, Traits::Y>)
         return FromAxisAngle(Axes::Y<T>, angle);
      else if constexpr (CT::Same<D, Traits::Z>)
         return FromAxisAngle(Axes::Z<T>, angle);
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
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT()& QUAT()::LookAt(const Base3& dir) noexcept {
      auto look = (*this) * Axes::Forward<T>;
      auto axis = dir % look;
      auto angle = T {1} / dir.Dot(look);
      return FromAxisAngle(axis, angle);
   }

   /// Get rotated axii (doesn't normalize the quaternion)                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto QUAT()::GetForward() const noexcept {
      return *this * Axes::Forward<T>;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto QUAT()::GetBackward() const noexcept {
      return *this * Axes::Backward<T>;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto QUAT()::GetRight() const noexcept {
      return *this * Axes::Right<T>;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto QUAT()::GetLeft() const noexcept {
      return *this * Axes::Left<T>;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto QUAT()::GetUp() const noexcept {
      return *this * Axes::Up<T>;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto QUAT()::GetDown() const noexcept {
      return *this * Axes::Down<T>;
   }

   /// Get conjugated quaternion                                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT() QUAT()::Conjugate() const noexcept {
      auto result = *this * T {-1};
      result[3] *= T {-1};
      return result;
   }

   /// Get normalized quaternion                                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT() QUAT()::Normalize() const {
      return Base::Normalize();
   }

   /// Conjugate operator                                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT() QUAT()::operator - () const noexcept {
      return Conjugate();
   }

   /// Convert to a matrix                                                    
   TEMPLATE()
   template<CT::DenseNumber K, Count COLUMNS, Count ROWS>
   constexpr QUAT()::operator TMatrix<K, COLUMNS, ROWS>()
   const noexcept requires (COLUMNS >= 3 and ROWS >= 3) {
      const K qxx = mArray[0] * mArray[0];
      const K qyy = mArray[1] * mArray[1];
      const K qzz = mArray[2] * mArray[2];
      const K qxz = mArray[0] * mArray[2];
      const K qxy = mArray[0] * mArray[1];
      const K qyz = mArray[1] * mArray[2];
      const K qwx = mArray[3] * mArray[0];
      const K qwy = mArray[3] * mArray[1];
      const K qwz = mArray[3] * mArray[2];

      constexpr K one {1};
      constexpr K two {2};
      TMatrix<K, COLUMNS, ROWS> r;
      r[0][0] = one - two * (qyy + qzz);
      r[0][1] =       two * (qxy + qwz);
      r[0][2] =       two * (qxz - qwy);

      r[1][0] =       two * (qxy - qwz);
      r[1][1] = one - two * (qxx + qzz);
      r[1][2] =       two * (qyz + qwx);

      r[2][0] =       two * (qxz + qwy);
      r[2][1] =       two * (qyz - qwx);
      r[2][2] = one - two * (qxx + qyy);
      return r;
   }

   /// Quaterion-quaternion product                                           
   ///   @param lhs - the left operand                                        
   ///   @param rhs - the right operand                                       
   ///   @return the product of the two provided quaternions                  
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   constexpr TQuat<Lossless<T1, T2>> operator * (const TQuat<T1>& lhs, const TQuat<T2>& rhs) noexcept {
      return {
         lhs.mArray[0] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[0] + lhs.mArray[1] * rhs.mArray[2] - lhs.mArray[2] * rhs.mArray[1],
         lhs.mArray[1] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[1] + lhs.mArray[2] * rhs.mArray[0] - lhs.mArray[0] * rhs.mArray[2],
         lhs.mArray[2] * rhs.mArray[3] + lhs.mArray[3] * rhs.mArray[2] + lhs.mArray[0] * rhs.mArray[1] - lhs.mArray[1] * rhs.mArray[0],
         lhs.mArray[3] * rhs.mArray[3] - lhs.mArray[0] * rhs.mArray[0] - lhs.mArray[1] * rhs.mArray[1] - lhs.mArray[2] * rhs.mArray[2]
      };
   }

   /// Quaterion * Vector                                                     
   ///   @param lhs - left hand side quaternion                               
   ///   @param rhs - right hand side vector of at least 2 components         
   ///   @return a lossless product of the two                                
   template<CT::DenseNumber T1, CT::DenseNumber T2, Count C>
   LANGULUS(INLINED)
   constexpr TVec<Lossless<T1, T2>, C> operator * (
      const TQuat<T1>& lhs,
      const TVec<T2, C>& rhs
   ) noexcept requires(C >= 2) {
      using LT = Lossless<T1, T2>;
      const TQuaternion<LT> vecQuat {TVector<T2, 3>(rhs), 0};
      return (lhs.Conjugate() * vecQuat) * lhs;
   }

   /// Vector * Quaterion                                                     
   ///   @param lhs - left hand side vector of at least 2 components          
   ///   @param rhs - right hand side quaternion                              
   ///   @return a lossless product of the two                                
   template<CT::DenseNumber T1, CT::DenseNumber T2, Count C>
   LANGULUS(INLINED)
   constexpr TVec<Lossless<T1, T2>, C> operator * (
      const TVec<T1, C>& lhs,
      const TQuat<T2>& rhs
   ) noexcept requires(C >= 2) {
      return rhs.Conjugate() * lhs;
   }

   /// Quaterion *= Quaternion                                                
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr void operator *= (TQuat<T1>& lhs, const TQuat<T2>& rhs) noexcept {
      lhs = lhs * rhs;
   }

   /// Quaternion + Scalar                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator + (const TQuat<T1>& lhs, const T2& rhs) noexcept {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Add(lhs, rhs, a);
      return Ret {a};
   }

   /// Scalar + Quaternion                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator + (const T1& lhs, const TQuat<T2>& rhs) noexcept {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Add(lhs, rhs, a);
      return Ret {a};
   }

   /// Quaternion - Scalar                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator - (const TQuat<T1>& lhs, const T2& rhs) noexcept {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Subtract(lhs, rhs, a);
      return Ret {a};
   }

   /// Scalar - Quaternion                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator - (const T1& lhs, const TQuat<T2>& rhs) noexcept {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Subtract(lhs, rhs, a);
      return Ret {a};
   }

   /// Quaternion * Scalar                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator * (const TQuat<T1>& lhs, const T2& rhs) noexcept {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Multiply(lhs, rhs, a);
      return Ret {a};
   }

   /// Scalar * Quaternion                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator * (const T1& lhs, const TQuat<T2>& rhs) noexcept {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Multiply(lhs, rhs, a);
      return Ret {a};
   }

   /// Quaternion / Scalar                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator / (const TQuat<T1>& lhs, const T2& rhs) {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Divide(lhs, rhs, a);
      return Ret {a};
   }

   /// Scalar / Quaternion                                                    
   template<CT::DenseNumber T1, CT::DenseNumber T2>
   LANGULUS(INLINED)
   constexpr auto operator / (const T1& lhs, const TQuat<T2>& rhs) {
      using Ret = TQuat<Lossless<T1, T2>>;
      typename Ret::ArrayType a;
      SIMD::Divide(lhs, rhs, a);
      return Ret {a};
   }

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Compose a transformation matrix by combining position, orientation     
   /// and scale                                                              
   ///   @param q - the orientation quaternion                                
   ///   @param p - the position vector                                       
   ///   @param s - the scale vector                                          
   ///   @return the composed matrix                                          
   template<CT::Vector T>
   NOD() constexpr Math::TMatrix<TypeOf<T>, T::MemberCount + 1>
   Matrix::From(const Math::TQuaternion<TypeOf<T>>& q, const T& p, const T& s) noexcept {
      using K = TypeOf<T>;
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
      result.mColumns[0][0] = (one - (yy + zz)) * sx;
      result.mColumns[1][0] = (xy + wz) * sx;
      result.mColumns[2][0] = (xz - wy) * sx;

      result.mColumns[0][1] = (xy - wz) * sy;
      result.mColumns[1][1] = (one - (xx + zz)) * sy;
      result.mColumns[2][1] = (yz + wx) * sy;

      result.mColumns[0][2] = (xz + wy) * sz;
      result.mColumns[1][2] = (yz - wx) * sz;
      result.mColumns[2][2] = (one - (xx + yy)) * sz;

      result.SetPosition(p);
      return result;
   }

} // namespace Langulus::A

#undef TEMPLATE
#undef QUAT
