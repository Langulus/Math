///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Numbers/Level.hpp"
#include "Matrices/TMatrix.hpp"
#include "Primitives/TFrustum.hpp"


namespace Langulus::Math
{

   using LODIndex = int32_t;
   using AbsoluteLODIndex = uint32_t;

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
   ///                  | LOD 0 is the point of view, where the object        
   ///                  | perfectly fits the screen                           
   ///                  |                                                     
   ///     near plane   |           ___                        |              
   ///         v        v          /   \                       |              
   ///      O> | <------x------->  | x <--- object center      |  far camera  
   ///    camera     distance      \___/                       |  plane       
   ///                             ^                           |              
   /// <- LOD up to +6             |                                          
   ///    (furthest)             object surface LOD-6 (closest)               
   ///    object appears         object goes outside the screen               
   ///    as a dot                                                            
   struct LOD {
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
      LOD(const Level&, const Mat4& view, const Mat4& proj);

      void Transform();
      void Transform(const Mat4&);
      NOD() Real GetNormalizedDistance() const noexcept;
      NOD() Real GetIndex() const noexcept;
      NOD() AbsoluteLODIndex GetAbsoluteIndex() const noexcept;
   };

} // namespace Langulus::Math