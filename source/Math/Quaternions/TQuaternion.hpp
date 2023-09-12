///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
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
   struct TQuaternion;

   template<CT::DenseNumber T>
   using TQuat = TQuaternion<T>;

   using Quaternionf = TQuaternion<Float>;
   using Quaterniond = TQuaternion<Double>;
   using Quaternion = TQuaternion<Real>;

   using Quatf = Quaternionf;
   using Quatd = Quaterniond;
   using Quat = Quaternion;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as a    
   /// quaternion                                                             
   struct Quaternion {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::Quaternion;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// quaternion of the same type                                            
   template<CT::DenseNumber T>
   struct QuaternionOfType : Quaternion {
      LANGULUS(CONCRETE) Math::TQuaternion<T>;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(Quaternion);
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated quaternion                                                 
   ///                                                                        
   template<CT::DenseNumber T>
   struct TQuaternion : TVector<T, 4> {
      using Base = TVector<T, 4>;
      using Base3 = TVector<T, 3>;

      LANGULUS_BASES(Base, A::QuaternionOfType<T>);

      using Base::Base;
      using Base::mArray;

      constexpr TQuaternion() noexcept;
      constexpr TQuaternion(const Base&) noexcept;
      constexpr TQuaternion(const TMatrix<T, 2>&) noexcept;

      template<Count COLUMNS, Count ROWS>
      constexpr TQuaternion(const TMatrix<T, COLUMNS, ROWS>&)
         noexcept requires (COLUMNS >= 3 and ROWS >= 3);

      NOD() explicit operator Flow::Code() const;

      NOD() static constexpr TQuaternion FromAxis(const Base3&, const CT::Angle auto&) noexcept;

      template<CT::Angle A, CT::Dimension D>
      NOD() static constexpr TQuaternion FromAngle(const TAngle<A, D>&) noexcept;

      constexpr TQuaternion& LookAt(const Base3&) noexcept;

      NOD() constexpr auto GetForward() const noexcept;
      NOD() constexpr auto GetBackward() const noexcept;
      NOD() constexpr auto GetRight() const noexcept;
      NOD() constexpr auto GetLeft() const noexcept;
      NOD() constexpr auto GetUp() const noexcept;
      NOD() constexpr auto GetDown() const noexcept;

      NOD() constexpr TQuaternion Conjugate() const noexcept;
      NOD() constexpr TQuaternion Normalize() const;

      NOD() constexpr TQuaternion operator - () const noexcept;

      template<CT::DenseNumber K = T, Count COLUMNS, Count ROWS>
      NOD() explicit constexpr operator TMatrix<K, COLUMNS, ROWS>()
         const noexcept requires (COLUMNS >= 3 and ROWS >= 3);
   };


   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() TQuat<Lossless<T1, T2>> operator * (const TQuat<T1>&, const TQuat<T2>&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2, Count C>
   NOD() TVec<Lossless<T1, T2>, C> operator * (const TQuat<T1>&, const TVec<T2, C>&) noexcept requires(C >= 2);

   template<CT::DenseNumber T1, CT::DenseNumber T2, Count C>
   NOD() TVec<Lossless<T1, T2>, C> operator * (const TVec<T1, C>&, const TQuat<T2>&) noexcept requires(C >= 2);

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   void operator *= (TQuat<T1>&, const TQuat<T2>&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator + (const TQuat<T1>&, const T2&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator + (const T1&, const TQuat<T2>&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator - (const TQuat<T1>&, const T2&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator - (const T1&, const TQuat<T2>&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator * (const TQuat<T1>&, const T2&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator * (const T1&, const TQuat<T2>&) noexcept;

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator / (const TQuat<T1>&, const T2&);

   template<CT::DenseNumber T1, CT::DenseNumber T2>
   NOD() auto operator / (const T1&, const TQuat<T2>&);

} // namespace Langulus::Math

#include "TQuaternion.inl"