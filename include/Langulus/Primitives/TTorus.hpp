///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Primitive.hpp"


namespace Langulus::Math
{
   ///                                                                        
   /// 3D torus                                                               
   ///                                                                        
   template<CT::CustomVector T, CT::Dimension D = Tags::Y>
   struct TTorus {
      using CTTI_POD    = Maybe<CT::POD<T>>;
      using CTTI_Typed  = TypeOf<T>;
      using CTTI_Bases  = Math::Primitive;

      using PointType  = T;
      using ScalarType = TypeOf<T>;
      using T::MemberCount;
      static_assert(MemberCount == 3, "Can't have a non-three-dimensional torus");
      static_assert(D::Index < 3, "Can't extend torus in that dimension");

      ScalarType mOuterRadius {.5};
      ScalarType mInnerRadius {.5};

   public:
      /// Check if torus is degenerate                                        
      ///   @return true if at least one radius is zero                       
      constexpr bool IsDegenerate() const noexcept {
         return mInnerRadius == 0 || mOuterRadius == 0;
      }

      /// Check if torus is hollow                                            
      ///   @return true if at least one of the radii is negative             
      constexpr bool IsHollow() const noexcept {
         return mInnerRadius * mOuterRadius < 0;
      }
   };
}

