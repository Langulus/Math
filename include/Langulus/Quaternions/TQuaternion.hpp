///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Matrices/TMatrix.hpp"
#include <Langulus/CT/Quaternion.hpp>


namespace Langulus::Math
{
   template<CT::Number>
   struct TQuaternion;

   template<CT::Number T>
   using TQuat = TQuaternion<T>;

   using Quaternionf = TQuaternion<float>;
   using Quaterniond = TQuaternion<double>;
   using Quaternionr = TQuaternion<Real>;

   using Quatf = Quaternionf;
   using Quatd = Quaterniond;
   using Quat  = Quaternionr;


   /// Used as an imposed base for any type that can be interpretable as a    
   /// quaternion                                                             
   struct Quaternion {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Quat;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// quaternion of the same type                                            
   template<CT::Number T>
   struct QuaternionOfType : Quaternion {
      using CTTI_Concrete  = Math::TQuaternion<T>;
      using CTTI_Typed     = T;
      using CTTI_Bases     = Quaternion;
   };


   ///                                                                        
   ///   Templated quaternion                                                 
   ///                                                                        
   template<CT::Number T>
   struct TQuaternion : TVector<T, 4> {
      using Base  = TVector<T, 4>;
      using Base3 = TVector<T, 3>;

      using Base::x;
      using Base::first;
      using Base::y;
      using Base::second;
      using Base::z;
      using Base::third;
      using Base::w;
      using Base::fourth;

      using Base::all;

   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TQuaternion>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         // Write prefix                                                
         for (auto i : "Quat")
            name[offset++] = i;

         // Write suffix                                                
         --offset;
         for (auto i : SuffixOf<T>())
            name[offset++] = i;

         return name;
      }

   public:
      using CTTI_Named        = Yes<GenerateToken()>;;
      using CTTI_Nullable     = No;
      using CTTI_Bases        = Types<Base, QuaternionOfType<T>>;
      using CTTI_Quaternion   = Yup;
      using CTTI_Vector       = No;
      using CTTI_CustomVector = No;

      using Base::Base;
      constexpr TQuaternion() noexcept;
      constexpr TQuaternion(const Base&) noexcept;
      constexpr TQuaternion(const TMatrix<T, 2>&) noexcept;
      template<size_t COLUMNS, size_t ROWS>
      constexpr TQuaternion(const TMatrix<T, COLUMNS, ROWS>&)
         noexcept requires (COLUMNS >= 3 and ROWS >= 3);

      explicit operator Annies::Text() const;
      explicit operator Flow::Code() const;

      static constexpr TQuaternion FromAxis(const Base3&, CT::Angle auto const&) noexcept;

      template<CT::Angle A, CT::Dimension D>
      static constexpr TQuaternion FromAngle(const TAngle<A, D>&) noexcept;

      constexpr TQuaternion& LookAt(const Base3&) noexcept;

      constexpr auto GetForward() const noexcept;
      constexpr auto GetBackward() const noexcept;
      constexpr auto GetRight() const noexcept;
      constexpr auto GetLeft() const noexcept;
      constexpr auto GetUp() const noexcept;
      constexpr auto GetDown() const noexcept;

      constexpr TQuaternion Conjugate() const noexcept;
      constexpr TQuaternion Normalize() const;

      constexpr TQuaternion operator - () const noexcept;

      template<CT::Scalar K = T, size_t COLUMNS, size_t ROWS>
      explicit constexpr operator TMatrix<K, COLUMNS, ROWS>() const noexcept
      requires (COLUMNS >= 3 and ROWS >= 3);
   };


   /// Generate a lossless quaternion type from provided LHS and RHS types    
   ///   @tparam LHS - left hand side, can be scalar/array/vector             
   ///   @tparam RHS - right hand side, can be scalar/array/vector            
   template<class LHS, class RHS>
   using LosslessQuaternion = TQuaternion<Lossless<TypeOf<LHS>, TypeOf<RHS>>>;

   ///                                                                        
   ///   Operators that involve quaternions                                   
   ///                                                                        
   constexpr auto operator * (CT::Quaternion auto const&, CT::Quaternion auto const&) noexcept;
   constexpr auto operator * (CT::Quaternion auto const&, CT::CustomVector auto const&) noexcept;
   constexpr auto operator * (CT::CustomVector auto const&, CT::Quaternion auto const&) noexcept;

   constexpr void operator *= (CT::Quaternion auto&, CT::Quaternion auto const&) noexcept;

   constexpr auto operator + (CT::Quaternion auto const&, CT::Scalar auto const&) noexcept;
   constexpr auto operator + (CT::Scalar auto const&, CT::Quaternion auto const&) noexcept;

   constexpr auto operator - (CT::Quaternion auto const&, CT::Scalar auto const&) noexcept;
   constexpr auto operator - (CT::Scalar auto const&, CT::Quaternion auto const&) noexcept;

   constexpr auto operator * (CT::Quaternion auto const&, CT::Scalar auto const&) noexcept;
   constexpr auto operator * (CT::Scalar auto const&, CT::Quaternion auto const&) noexcept;

   constexpr auto operator / (CT::Quaternion auto const&, CT::Scalar auto const&);
   constexpr auto operator / (CT::Scalar auto const&, CT::Quaternion auto const&);
}