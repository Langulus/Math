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


namespace Langulus::Math
{
   template<CT::CustomVector T>
   struct TFrustum;

   using Frustum2 = TFrustum<Vec2>;
   using Frustum3 = TFrustum<Vec3>;

   /// An abstract frustum                                                    
   struct Frustum : Primitive {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Frustum3;
      using CTTI_Bases     = Primitive;
   };
}

namespace Langulus::CT
{
   /// Concept for distinguishing frustum primitives                          
   template<class...T>
   concept Frustum = (DerivedFrom<T, Math::Frustum> and ...);
}

namespace Langulus::Math
{
   ///                                                                        
   ///   2D/3D frustum, centered around origin                                
   ///                                                                        
   template<CT::CustomVector T>
   struct TFrustum : Frustum {
      using CTTI_Abstract  = No;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::Frustum;

      static constexpr size_t MemberCount = T::MemberCount;
      using PointType  = T;
      using ScalarType = TypeOf<PointType>;
      using MatrixType = TMatrix<ScalarType, MemberCount + 1>;
      static_assert(MemberCount > 1, "Can't have one-dimensional frustum");

      ::std::array<TPlane<T>, MemberCount * 2> mPlanes;

      enum {Left = 0, Right, Top, Bottom, Near, Far};

   public:
      constexpr TFrustum() noexcept;
      template<template<class> class S> requires CT::Intent<S<TFrustum<T>>>
      constexpr TFrustum(S<TFrustum>&&) noexcept;
      constexpr TFrustum(MatrixType const&) noexcept;

      constexpr bool IsDegenerate() const noexcept;
      constexpr bool IsHollow() const noexcept;
      bool Intersects(const TRange<T>&) const noexcept;
   };
}

#include "TFrustum.inl"