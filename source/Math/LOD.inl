///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Numbers/Level.hpp"

namespace Langulus::Math
{

   /// LOD state construction                                                 
   LANGULUS(INLINED)
   LOD::LOD(const Level& level, const Matrix4& view, const Matrix4& proj)
      : mLevel {level}
      , mView {view}
      , mViewInverted {view.Invert()}
      , mFrustum {mViewInverted * proj} {}

   /// Create an identity LOD state                                           
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
   void LOD::Transform(const Matrix4& model) {
      mModel = model;
      mModelView = mModel * mViewInverted;
      mOrigin = mModelView.GetPosition();
      mRadius = mModelView.GetScale().HMax() * Real {0.5};
      mDistanceToSurface = mOrigin.Length() - mRadius;
      mLODIndex = 0;
      if (mDistanceToSurface > 0 && mRadius > 0) {
         // View is outside the sphere                                  
         const Real near = ::std::log10(mRadius / mDistanceToSurface);
         const Real far = ::std::log10(mDistanceToSurface / mRadius);
         mLODIndex = Math::Clamp(near - far, Real {MinIndex}, Real {MaxIndex});
      }
      else if (mDistanceToSurface < 0) {
         // Being inside the sphere always gives the most detail        
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
   /// If index is below zero, then we're observing from afar                 
   /// If index is above zero, then we're observing too close                 
   /// At zero we're observing the default quality asset                      
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
