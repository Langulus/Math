///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Matrices/TMatrix.hpp"


namespace Langulus::Math
{

   template<CT::ScalarBased>
   struct TQuaternion;

   template<CT::ScalarBased T>
   using TQuat = TQuaternion<T>;

   using Quaternionf = TQuaternion<Float>;
   using Quaterniond = TQuaternion<Double>;
   using Quaternion  = TQuaternion<Real>;

   using Quatf = Quaternionf;
   using Quatd = Quaterniond;
   using Quat  = Quaternion;

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
   template<CT::ScalarBased T>
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
   template<CT::ScalarBased T>
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
         constexpr auto defaultClassName = RTTI::LastCppNameOf<TQuaternion>();
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
      LANGULUS(NAME) GenerateToken();
      LANGULUS(NULLIFIABLE) false;
      LANGULUS_BASES(Base, A::QuaternionOfType<T>);

      // Make TQuaternion match the CT::QuaternionBased concept         
      static constexpr bool CTTI_QuaternionTrait = true;
      // Override the inherited trait                                   
      static constexpr bool CTTI_VectorTrait = false;

      using Base::Base;
      constexpr TQuaternion() noexcept;
      constexpr TQuaternion(const Base&) noexcept;
      constexpr TQuaternion(const TMatrix<T, 2>&) noexcept;
      template<Count COLUMNS, Count ROWS>
      constexpr TQuaternion(const TMatrix<T, COLUMNS, ROWS>&)
         noexcept requires (COLUMNS >= 3 and ROWS >= 3);

      NOD() explicit operator Anyness::Text() const;
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

      template<CT::ScalarBased K = T, Count COLUMNS, Count ROWS>
      NOD() explicit constexpr operator TMatrix<K, COLUMNS, ROWS>() const noexcept
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
   NOD() constexpr auto operator * (const CT::QuaternionBased auto&, const CT::QuaternionBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::QuaternionBased auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::VectorBased auto&, const CT::QuaternionBased auto&) noexcept;

   constexpr void operator *= (CT::QuaternionBased auto&, const CT::QuaternionBased auto&) noexcept;

   NOD() constexpr auto operator + (const CT::QuaternionBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::ScalarBased auto&, const CT::QuaternionBased auto&) noexcept;

   NOD() constexpr auto operator - (const CT::QuaternionBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::ScalarBased auto&, const CT::QuaternionBased auto&) noexcept;

   NOD() constexpr auto operator * (const CT::QuaternionBased auto&, const CT::ScalarBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::ScalarBased auto&, const CT::QuaternionBased auto&) noexcept;

   NOD() constexpr auto operator / (const CT::QuaternionBased auto&, const CT::ScalarBased auto&);
   NOD() constexpr auto operator / (const CT::ScalarBased auto&, const CT::QuaternionBased auto&);

} // namespace Langulus::Math