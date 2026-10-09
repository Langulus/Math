///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Primitive.hpp"
#include "../Numbers/TAngle.hpp"


namespace Langulus::Math
{
   ///                                                                        
   /// 3D cone with varying dimensions, centered around origin                
   /// D determines the direction of the cone's pointy side                   
   ///                                                                        
   template<CT::CustomVector T, CT::Dimension D = Tags::Y>
   struct TCone {
      using CTTI_POD    = Yup;
      using CTTI_Typed  = TypeOf<T>;
      using CTTI_Bases  = Primitive;

      using PointType = T;
      using Dimension = D;
      static_assert(ExtentOf<T> == 3, "Can't have a non-3D cone");
      static_assert(D::Index < 3, "Can't extend cone in that dimension");

      // Size of the cone                                               
      TypeOf<T> mHeight {.5};

      // Angle of the cone's slope                                      
      TRadians<TypeOf<T>> mAngle {HALFPI<TypeOf<T>>};

   public:
      /// Check if cone is degenerate                                         
      ///   @return true if at least one offset is zero                       
      constexpr bool IsDegenerate() const noexcept {
         return mHeight == 0 || mAngle == 0;
      }

      /// Check if cone is hollow                                             
      ///   @return true if at least one of the offsets is negative           
      constexpr bool IsHollow() const noexcept {
         return mHeight < 0;
      }
   };
}