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
   ///   Templated 2D/3D plane                                                
   ///                                                                        
   template<CT::CustomVector T>
   struct TPlane {
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Nullable  = Maybe<CT::Nullable<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::Primitive;

      using PointType  = T;
      using ScalarType = TypeOf<T>;
      static_assert(ExtentOf<T> > 1, "Can't have one-dimensional plane");

      // Default orientation is always towards user                     
      T mNormal = Axes::Backward<ScalarType>;

      // The offset of the plane, along the normal                      
      ScalarType mOffset = 0;

   public:
      constexpr TPlane() noexcept = default;

      /// Construction from normal and offset                                 
      constexpr TPlane(const T& normal, ScalarType offset) noexcept 
         : mNormal {normal}
         , mOffset {offset} {
         Normalize();
      }

      /// Construction from a matrix column                                   
      constexpr TPlane(const TVector<ScalarType, ExtentOf<T> + 1>& column) noexcept 
         : mNormal {column}
         , mOffset {column[ExtentOf<T>]} {
         Normalize();
      }

      /// Construction from distance * direction                              
      constexpr TPlane(const T& offset) noexcept {
         const auto d = offset.Length();
         mNormal = offset / d;
         mOffset = d;
      }

      /// Flip the plane                                                      
      auto Flip() noexcept -> TPlane& {
         mNormal *= ScalarType {-1};
         mOffset *= ScalarType {-1};
         return *this;
      }

      /// Normalize the plane                                                 
      auto Normalize() noexcept -> TPlane& {
         const auto length = mNormal.Length();
         if (0 != length) {
            mNormal /= length;
            mOffset /= length;
         }
         return *this;
      }

      /// Check if plane is degenerate                                        
      ///   @return true if at least one offset is zero                       
      constexpr bool IsDegenerate() const noexcept {
         return mNormal.Length() == ScalarType {0};
      }

      /// Calculate signed distance                                           
      ///   @param point point to check distance from                         
      ///   @return the distance to the plane                                 
      auto SignedDistance(const T& point) const {
         return Math::SignedDistance(point, *this);
      }
   };
}