///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TPlane.hpp"
#include "../Ranges/TRange.hpp"
#include "../Matrices/TMatrix.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::Vector T>
      struct TFrustum;

      using Frustum2 = TFrustum<Vec2>;
      using Frustum3 = TFrustum<Vec3>;

      using Frustum = Frustum3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract frustum                                                 
      struct Frustum : Primitive {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Frustum;
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing frustum primitives                       
      template<class...T>
      concept Frustum = (DerivedFrom<T, A::Frustum> and ...);

   } // namespace Langulus::CT

} // namespace Langulus

namespace Langulus::Math
{

   ///                                                                        
   ///   2D/3D frustum, centered around origin                                
   ///                                                                        
   template<CT::Vector T>
   struct TFrustum : A::Frustum {
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Frustum);

      static constexpr Count MemberCount = T::MemberCount;
      using PointType  = T;
      using ScalarType = TypeOf<PointType>;
      using MatrixType = TMatrix<ScalarType, MemberCount + 1>;
      static_assert(MemberCount > 1, "Can't have one-dimensional frustum");

      ::std::array<TPlane<T>, MemberCount * 2> mPlanes;

      enum {Left = 0, Right, Top, Bottom, Near, Far};

   public:
      constexpr TFrustum() noexcept;
      template<template<class> class S>
      constexpr TFrustum(S<TFrustum>&&) noexcept requires CT::Semantic<S<TFrustum>>;
      constexpr TFrustum(const MatrixType&) noexcept;

      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
      NOD() bool Intersects(const TRange<T>&) const noexcept;
   };

} // namespace Langulus::Math