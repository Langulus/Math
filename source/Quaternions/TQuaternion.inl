///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TQuaternion.hpp"
#include "../Vectors/TVector.inl"
#include "../Matrices/TMatrix.inl"

#define TEMPLATE()   template<CT::ScalarBased T>
#define QUAT()       TQuaternion<T>


namespace Langulus::Math
{

   /// Default quaternion construction to identity                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr QUAT()::TQuaternion() noexcept
      : Base {0, 0, 0, 1} {
      static_assert(CT::Vector<QUAT()>,
         "Quaternions should match CT::Vector");
      static_assert(CT::QuaternionBased<QUAT()>,
         "Quaternions shouldn't match CT::VectorBased");
      static_assert(not CT::VectorBased<QUAT()>,
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
      x = y = T {0};
      z = (matrix[2] - matrix[1]) / S;
      w = T {.25} *S;
   }

   /// Constructor from 3x3 matrix                                            
   ///   @param matrix - 3x3 matrix to convert to a quaternion                
   TEMPLATE() template<Count COLUMNS, Count ROWS>
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
      all[biggestIndex] = biggestVal;

      const T mult = T {0.25} / biggestVal;
      switch (biggestIndex) {
      case 0:
         w = (m[1][2] - m[2][1]) * mult;
         y = (m[0][1] + m[1][0]) * mult;
         z = (m[2][0] + m[0][2]) * mult;
         break;
      case 1:
         w = (m[2][0] - m[0][2]) * mult;
         x = (m[0][1] + m[1][0]) * mult;
         z = (m[1][2] + m[2][1]) * mult;
         break;
      case 2:
         w = (m[0][1] - m[1][0]) * mult;
         x = (m[2][0] + m[0][2]) * mult;
         y = (m[1][2] + m[2][1]) * mult;
         break;
      case 3:
         z = (m[1][2] - m[2][1]) * mult;
         y = (m[2][0] - m[0][2]) * mult;
         x = (m[0][1] - m[1][0]) * mult;
         break;
      default:
         // Never really happens, just silence warnings                 
         break;
      }
   }

   /// Serialize quaternion to text                                           
   TEMPLATE() LANGULUS(INLINED)
   QUAT()::operator Anyness::Text() const {
      return Base::template Serialize<Anyness::Text, TQuaternion>();
   }

   /// Serialize quaternion to code                                           
   TEMPLATE() LANGULUS(INLINED)
   QUAT()::operator Flow::Code() const {
      return Base::template Serialize<Flow::Code, TQuaternion>();
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
   TEMPLATE() template<CT::Angle A, CT::Dimension D> LANGULUS(INLINED)
   constexpr QUAT() QUAT()::FromAngle(const TAngle<A, D>& angle) noexcept {
      if constexpr (CT::Same<D, Traits::X>)
         return FromAxis(TVector<T, 4>{1, 0, 0, 0}, angle); //TODO weird MSVC bugs, can't use Axes::X for some reason
      else if constexpr (CT::Same<D, Traits::Y>)
         return FromAxis(TVector<T, 4>{0, 1, 0, 0}, angle);
      else if constexpr (CT::Same<D, Traits::Z>)
         return FromAxis(TVector<T, 4>{0, 0, 1, 0}, angle);
      else
         static_assert(false, "Unsupported dimension");
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
   TEMPLATE() template<CT::ScalarBased K, Count COLUMNS, Count ROWS>
   constexpr QUAT()::operator TMatrix<K, COLUMNS, ROWS>()
   const noexcept requires (COLUMNS >= 3 and ROWS >= 3) {
      const K qxx = x * x;
      const K qyy = y * y;
      const K qzz = z * z;
      const K qxz = x * z;
      const K qxy = x * y;
      const K qyz = y * z;
      const K qwx = w * x;
      const K qwy = w * y;
      const K qwz = w * z;

      constexpr K one {1};
      constexpr K two {2};
      TMatrix<K, COLUMNS, ROWS> result;
      result[0].x = one - two * (qyy + qzz);
      result[0].y =       two * (qxy + qwz);
      result[0].z =       two * (qxz - qwy);

      result[1].x =       two * (qxy - qwz);
      result[1].y = one - two * (qxx + qzz);
      result[1].z =       two * (qyz + qwx);

      result[2].x =       two * (qxz + qwy);
      result[2].y =       two * (qyz - qwx);
      result[2].z = one - two * (qxx + qyy);
      return result;
   }


   ///                                                                        
   ///   Operators that involve quaternions                                   
   ///                                                                        

   /// Quaterion-quaternion product                                           
   ///   @param lhs - the left operand                                        
   ///   @param rhs - the right operand                                       
   ///   @return the product of the two provided quaternions                  
   constexpr auto operator * (
      const CT::QuaternionBased auto& lhs,
      const CT::QuaternionBased auto& rhs
   ) noexcept {
      return LosslessQuaternion<decltype(lhs), decltype(rhs)> {
         lhs.x * rhs.w + lhs.w * rhs.x
       + lhs.y * rhs.z - lhs.z * rhs.y,
         lhs.y * rhs.w + lhs.w * rhs.y
       + lhs.z * rhs.x - lhs.x * rhs.z,
         lhs.z * rhs.w + lhs.w * rhs.z
       + lhs.x * rhs.y - lhs.y * rhs.x,
         lhs.w * rhs.w - lhs.x * rhs.x
       - lhs.y * rhs.y - lhs.z * rhs.z
      };
   }

   /// Quaterion * Vector                                                     
   ///   @param lhs - left hand side quaternion                               
   ///   @param rhs - right hand side vector of at least 2 components         
   ///   @return a lossless product of the two                                
   LANGULUS(INLINED)
   constexpr auto operator * (
      const CT::QuaternionBased auto& lhs,
      const CT::VectorBased     auto& rhs
   ) noexcept {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      const Q vecQuat {typename Q::Base3 {rhs}, 0};
      return typename Q::Base3 {(lhs.Conjugate() * vecQuat) * lhs};
   }

   /// Vector * Quaterion                                                     
   ///   @param lhs - left hand side vector of at least 2 components          
   ///   @param rhs - right hand side quaternion                              
   ///   @return a lossless product of the two                                
   LANGULUS(INLINED)
   constexpr auto operator * (
      const CT::VectorBased     auto& lhs,
      const CT::QuaternionBased auto& rhs
   ) noexcept {
      return rhs.Conjugate() * lhs;
   }

   /// Quaterion *= Quaternion                                                
   LANGULUS(INLINED)
   constexpr void operator *= (
            CT::QuaternionBased auto& lhs,
      const CT::QuaternionBased auto& rhs
   ) noexcept {
      lhs = lhs * rhs;
   }

   /// Quaternion + Scalar                                                    
   LANGULUS(INLINED)
   constexpr auto operator + (
      const CT::QuaternionBased auto& lhs,
      const CT::ScalarBased     auto& rhs
   ) noexcept {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Add(lhs, rhs)};
   }

   /// Scalar + Quaternion                                                    
   LANGULUS(INLINED)
   constexpr auto operator + (
      const CT::ScalarBased     auto& lhs,
      const CT::QuaternionBased auto& rhs
   ) noexcept {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Add(lhs, rhs)};
   }

   /// Quaternion - Scalar                                                    
   LANGULUS(INLINED)
   constexpr auto operator - (
      const CT::QuaternionBased auto& lhs,
      const CT::ScalarBased     auto& rhs
   ) noexcept {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Subtract(lhs, rhs)};
   }

   /// Scalar - Quaternion                                                    
   LANGULUS(INLINED)
   constexpr auto operator - (
      const CT::ScalarBased     auto& lhs,
      const CT::QuaternionBased auto& rhs
   ) noexcept {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Subtract(lhs, rhs)};
   }

   /// Quaternion * Scalar                                                    
   LANGULUS(INLINED)
   constexpr auto operator * (
      const CT::QuaternionBased auto& lhs,
      const CT::ScalarBased     auto& rhs
   ) noexcept {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Multiply(lhs, rhs)};
   }

   /// Scalar * Quaternion                                                    
   LANGULUS(INLINED)
   constexpr auto operator * (
      const CT::ScalarBased     auto& lhs,
      const CT::QuaternionBased auto& rhs
   ) noexcept {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Multiply(lhs, rhs)};
   }

   /// Quaternion / Scalar                                                    
   LANGULUS(INLINED)
   constexpr auto operator / (
      const CT::QuaternionBased auto& lhs,
      const CT::ScalarBased     auto& rhs
   ) {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Divide(lhs, rhs)};
   }

   /// Scalar / Quaternion                                                    
   LANGULUS(INLINED)
   constexpr auto operator / (
      const CT::ScalarBased     auto& lhs,
      const CT::QuaternionBased auto& rhs
   ) {
      using Q = LosslessQuaternion<decltype(lhs), decltype(rhs)>;
      return Q {SIMD::Divide(lhs, rhs)};
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
   template<CT::VectorBased T>
   NOD() constexpr Math::TMatrix<TypeOf<T>, T::MemberCount + 1>
   Matrix::From(const Math::TQuaternion<TypeOf<T>>& q, const T& p, const T& s) noexcept {
      using K = TypeOf<T>;
      Math::TMatrix<K, T::MemberCount + 1> result;
      auto x2 = q.x + q.x;
      auto y2 = q.y + q.y;
      auto z2 = q.z + q.z;
      auto xx = q.x * x2;
      auto xy = q.x * y2;
      auto xz = q.x * z2;
      auto yy = q.y * y2;
      auto yz = q.y * z2;
      auto zz = q.z * z2;
      auto wx = q.w * x2;
      auto wy = q.w * y2;
      auto wz = q.w * z2;

      constexpr K one {1};
      result[0].x = (one - (yy + zz)) * s.x;
      result[1].x =        (xy + wz)  * s.x;
      result[2].x =        (xz - wy)  * s.x;
                                         
      result[0].y =        (xy - wz)  * s.y;
      result[1].y = (one - (xx + zz)) * s.y;
      result[2].y =        (yz + wx)  * s.y;
                                         
      result[0].z =        (xz + wy)  * s.z;
      result[1].z =        (yz - wx)  * s.z;
      result[2].z = (one - (xx + yy)) * s.z;

      result.SetPosition(p);
      return result;
   }

} // namespace Langulus::A

#undef TEMPLATE
#undef QUAT
