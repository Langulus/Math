///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "LOD.hpp"
#include "Matrices/TMatrix.inl"
#include "Numbers/Level.inl"
#include "Primitives/TFrustum.inl"


namespace Langulus::Math
{

   /// LOD state construction                                                 
   ///   @param level - the level the camera is on                            
   ///   @param view - the camera view transformation                         
   ///   @param proj - the camera projection transformation                   
   LANGULUS(INLINED)
   LOD::LOD(const Level& level, const Mat4& view, const Mat4& proj)
      : mLevel {level}
      , mView {view}
      , mViewInverted {view.Invert()}
      , mFrustum {mViewInverted * proj} {}

   /// Recalculate LOD state by specifying an identity model matrix           
   LANGULUS(INLINED)
   void LOD::Transform() {
      mModel = {};
      mModelView = mViewInverted;
      mOrigin = {};
      mRadius = {};
      mDistanceToSurface = {};
      mLODIndex = 0;
   }

   /// Recalculate LOD state by specifying the model matrix                   
   ///   @attention assumes the view matrices have been set prior             
   ///   @param model - the model transformation                              
   LANGULUS(INLINED)
   void LOD::Transform(const Mat4& model) {
      mModel = model;
      mModelView = mModel * mViewInverted;
      mOrigin = mModelView.GetPosition();
      mRadius = mModelView.GetScale().HMax() * Real {0.5};
      mDistanceToSurface = mOrigin.Length() - mRadius;
      mLODIndex = 0;

      if (mDistanceToSurface > 0 and mRadius > 0) {
         // View is outside the sphere of influence (SOI)               
         const Real near = ::std::log10(mRadius / mDistanceToSurface);
         const Real far = ::std::log10(mDistanceToSurface / mRadius);
         mLODIndex = Math::Clamp(near - far, Real {MinIndex}, Real {MaxIndex});
      }
      else if (mDistanceToSurface < 0) {
         // Being inside the SOI always gives the most detail           
         mLODIndex = Real {MaxIndex};
      }
   }

   /// Get the distance from the camera to the model's bounding sphere        
   /// surface, divided by the bounding sphere size                           
   ///   @return the distance                                                 
   LANGULUS(INLINED)
   Real LOD::GetNormalizedDistance() const noexcept {
      return mDistanceToSurface / mRadius;
   }

   /// Return the LOD index, which is a real number in the range              
   /// [MinIndex;MaxIndex]                                                    
   /// Calculate the LOD index via log10 distance from a sphere to            
   /// the camera view. You can imagine it as the number of zeroes behind     
   /// or in front of the distance                                            
   ///   If index is below zero, then we're observing from afar               
   ///   If index is above zero, then we're observing too close               
   ///   At zero we're observing the default quality asset                    
   ///   @return the LOD index                                                
   LANGULUS(INLINED)
   Real LOD::GetIndex() const noexcept {
      return mLODIndex;
   }

   /// Get LOD index in the range [0;IndexCount)                              
   ///   @return the absolute index                                           
   LANGULUS(INLINED)
   AbsoluteLODIndex LOD::GetAbsoluteIndex() const noexcept {
      return static_cast<AbsoluteLODIndex>(
         static_cast<LODIndex>(mLODIndex) - MinIndex
      );
   }

} // namespace Langulus::Math
