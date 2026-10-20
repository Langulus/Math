///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/Numbers/Level.hpp>
#include <Langulus/Matrices/TMatrix.hpp>
#include <Langulus/Primitives/TFrustum.hpp>


namespace Langulus::Math
{
   ///                                                                        
   ///   Level of detail state                                                
   ///                                                                        
   ///   A helper structure that is used to fetch the correct LOD index. LOD  
   /// index is a geometry/texture, that is designed to represent a zoomed-in 
   /// or a zoomed-out region of another geometry/texture. These regions can  
   /// be generated on the fly, or may reuse existing geometry/texture.       
   ///                                                                        
   ///   LOD is determined by the real distance between camera's near plane,  
   /// and the object's surface:                                              
   ///                                                                        
   ///       /          | LOD 0 is the point of view, where the object        
   ///      /           | perfectly fits the screen. usually resources are    
   ///     /            | designed for this distance.                         
   ///    / near plane  |           ___                        |              
   ///   /     v        v          /   \                       |              
   ///  O      | <------x-------> | x <--- object center       |  far plane   
   ///   \     distance            \___/                       |              
   ///    \                        ^                           |              
   ///     camera furstum          |                           |              
   ///                             |                                          
   /// <- LOD up to +6             |                                          
   ///    (camera is far away)     object surface LOD -6 (camera is up close) 
   ///    object reduced to dot    we zoom in on the surcace.                 
   ///                                                                        
   struct LOD {
      using LODIndex = int32_t;
      using AbsoluteLODIndex = uint32_t;

      Level mLevel;
      Mat4 mView;
      Mat4 mViewInverted;
      Mat4 mModel;
      TFrustum<Vec3> mFrustum;

      // Calculated after Transform()                                   
      Mat4 mModelView;
      Vec4 mOrigin;
      Real mRadius;
      Real mDistanceToSurface;
      Real mLODIndex;

      static constexpr LODIndex MinIndex = -6;
      static constexpr LODIndex MaxIndex = 6;
      static constexpr LODIndex IndexCount = MaxIndex - MinIndex + 1;

   public:
      LOD() = default;

      /// LOD state construction                                              
      ///   @param level - the level the camera is on                         
      ///   @param view - the camera view transformation                      
      ///   @param proj - the camera projection transformation                
      LOD(const Level& level, const Mat4& view, const Mat4& proj)
         : mLevel {level}
         , mView {view}
         , mViewInverted {view.Invert()}
         , mFrustum {mViewInverted * proj} {}


      /// Recalculate LOD state by specifying an identity model matrix        
      void Transform() {
         mModel = {};
         mModelView = mViewInverted;
         mOrigin = {};
         mRadius = {};
         mDistanceToSurface = {};
         mLODIndex = 0;
      }

      /// Recalculate LOD state by specifying the model matrix                
      ///   @attention assumes the view matrices have been set prior          
      ///   @param model the model transformation                             
      void Transform(const Mat4& model) {
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
      Real GetNormalizedDistance() const noexcept {
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
      Real GetIndex() const noexcept {
         return mLODIndex;
      }

      /// Get LOD index in the range [0;IndexCount)                           
      ///   @return the absolute index                                        
      auto GetAbsoluteIndex() const noexcept -> AbsoluteLODIndex {
         return static_cast<AbsoluteLODIndex>(
            static_cast<LODIndex>(mLODIndex) - MinIndex
         );
      }
   };
}