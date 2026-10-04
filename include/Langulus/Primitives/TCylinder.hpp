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
   template<CT::CustomVector, CT::Dimension = Tags::Y>
   struct TCylinder;

   template<CT::CustomVector, CT::Dimension = Tags::Y>
   struct TCylinderCapped;

   using Cylinder3       = TCylinder<Vec3>;
   using CylinderCapped3 = TCylinderCapped<Vec3>;

   /// An abstract cylinder                                                   
   struct Cylinder : Primitive {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Cylinder3;
      using CTTI_Bases     = Primitive;
   };
}

namespace Langulus::CT
{
   /// Concept for distinguishing cylinder primitives                         
   template<class...T>
   concept Cylinder = (DerivedFrom<T, Math::Cylinder> and ...);
}

namespace Langulus::Math
{
   ///                                                                        
   /// Infinite 3D cylinder with varying radius, centered at origin.          
   /// D determines the direction of the cylinder's height.                   
   ///                                                                        
   ///                                                                        
   ///      ^     ^ +D  ^      ^                                              
   ///      '     |     '      |                                              
   ///      ' _ _ | _ _ '      |                                              
   ///      '/    |    \'      |                                              
   ///      |     +     |      |                                              
   ///      |\_________/|      | infinite height                              
   ///      |           |      |                                              
   ///      |           |      v                                              
   ///      |     +     |   ----                                              
   ///      |   origin  |                                                     
   ///      | _ _ _ _ _ |                                                     
   ///      |/         \|                                                     
   ///      |     +     |                                                     
   ///      '\____|____/'                                                     
   ///      '     |     '                                                     
   ///      V     |<--->V mRadius                                             
   ///                                                                        
   template<CT::CustomVector T, CT::Dimension D>
   struct TCylinder : Cylinder {
      using CTTI_Abstract  = No;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Cylinder;

      using PointType = T;
      using Dimension = D;
      
      static_assert(ExtentOf<T> >= 3, 
         "Can't have a cylinder with lower than 3 dimensions");
      static_assert(D::Index < 3, 
         "Can't extend cylinder in that dimension");

      TypeOf<T> mRadius {.5};

   public:
      constexpr bool IsDegenerate() const noexcept {
         return mRadius == 0;
      }

      constexpr bool IsHollow() const noexcept {
         return mRadius < 0;
      }

      auto SignedDistance(T const& point) const {
         return Math::SignedDistance(point, *this);
      }
   };


   ///                                                                        
   /// Capped 3D cylinder with varying size, centered at origin.              
   /// D determines the direction of the cylinder's height.                   
   ///                                                                        
   ///            ^ +D                                                        
   ///            |                                                           
   ///        ____|____                                                       
   ///      ./    |    \.                                                     
   ///      |     +     |   ----                                              
   ///      |\_________/|      ^                                              
   ///      |           |      |   mHeight                                    
   ///      |           |      v                                              
   ///      |     +     |   ----                                              
   ///      |   origin  |                                                     
   ///      | _ _ _ _ _ |                                                     
   ///      |/         \|                                                     
   ///      |     +     |                                                     
   ///       \____|____/                                                      
   ///            |     |                                                     
   ///            |<--->| mRadius                                             
   ///                                                                        
   template<CT::CustomVector T, CT::Dimension D>
   struct TCylinderCapped : TCylinder<T, D> {
      using Base = TCylinder<T, D>;
      using Base::mRadius;

      TypeOf<T> mHeight {.5};

   public:
      constexpr bool IsDegenerate() const noexcept {
         return mRadius == 0 or mHeight == 0;
      }

      constexpr bool IsHollow() const noexcept {
         return mRadius < 0 or mHeight < 0;
      }

      auto SignedDistance(T const& point) const {
         return Math::SignedDistance(point, *this);
      }
   };
}