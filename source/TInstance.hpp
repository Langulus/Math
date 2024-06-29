///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Numbers/Level.inl"
#include "Numbers/TAngle.hpp"
#include "Ranges/TRange.hpp"
#include "Vectors/TVector.hpp"
#include "Vectors/TNormal.hpp"
#include "Vectors/TForce.hpp"
#include "Vectors/TScale.hpp"
#include "Quaternions/TQuaternion.hpp"
#include "Randomness/MersenneTwister.hpp"
#include "Verbs/Move.hpp"

#if 0
   #define VERBOSE_TINSTANCE(a) Logger::Verbose() << a
#else
   #define VERBOSE_TINSTANCE(a) LANGULUS(NOOP)
#endif


namespace Langulus::Math
{

   ///                                                                        
   ///   Instance                                                             
   ///                                                                        
   /// Provides higher order functionality for rotation, translation,         
   /// scaling, and primitive collisions. Can be 2D or 3D, depending on T     
   ///                                                                        
   template<CT::VectorBased T>
   struct TInstance {
      using ScalarType = TypeOf<T>;
      using PointType  = T;
      using MatrixType = TMatrix<ScalarType, T::MemberCount + 1, T::MemberCount + 1>;
      using RangeType  = TRange<T>;
      using QuatType   = TQuaternion<ScalarType>;
      using SizeType   = TScale<TVector<ScalarType, T::MemberCount, 1>>;
      
      // Optional parent for inheriting transformations                 
      Anyness::Ref<TInstance<T>> mParent;

      // Position in space                                              
      PointType mPosition;

      // Velocity incurred by simulation                                
      Adaptive<PointType> mSimVelocity;
      // Velocity incurred by user interaction                          
      Adaptive<PointType> mUseVelocity;
      // Total velocity                                                 
      Adaptive<PointType> mVelocity;

      // Acceleration                                                   
      PointType mAcceleration;
      // The current orientation                                        
      QuatType mAim;
      // The current scale                                              
      SizeType mScale;

      // User-boundness of the instance                                 
      // Instances with zero sim-boundness, but high use-boundness are  
      // only explicitly moved and manipulated.                         
      // They are not slaves of the simulation and                      
      // will not move without user input - useful for explicit control 
      // on characters and so on. This might cause really unexpected    
      // results in worlds that are the size of an universe.            
      // Instances with sim-boundness of one are dependent on           
      // the simulation. You can use any ratio in order to blend        
      // between user and sim input, but only simulation-boundness is   
      // capped. Use-boundness might exceed 1, and even be reversed.    
      // Excessive use-boundness essentially directs energy to the      
      // physical system, so care must be taken to balance it out       
      // against the rest of energy applied from simulation. It's best  
      // to design a controller that relies on 1 SB, and 0 UB, so that  
      // physical movement is completely dependent on the simulation    
      // energy transfer. However, sometimes that is not an option, and 
      // involves quite elaborate tweeking and testing to behave well.  
      ScalarType mSimBoundness = 1;
      ScalarType mUseBoundness = 1;

      // Instance solidity. Solid instances are colliders.              
      // Nonsolid instances are never tested for collision.             
      // Volumes of water/air can have partial solidity, causing drag   
      // 1 is perfect solidity, while 0 is perfect permittance          
      ScalarType mSolid = 0;

      // Pickable instances are selectable by mouse ray                 
      bool mPickable = true;

      // Instance hollowness. Hollow instances are inverted. (ie rooms) 
      // This helps reuse geometry like cube, to make an empty box      
      // It also changes the face winding if not doublesided            
      bool mSigned = false;

      // Doublesidedness for degenerative shapes                        
      bool mBilateral = false;

      // Static instances are never updated (optimization only)         
      bool mStatic = false;

      // Octave change incurred by simulation                           
      Level mSimLevelChange = 0;
      // Octave change incurred by user interaction                     
      Level mUseLevelChange = 0;
      // Octave for scaling, position, acceleration and velocity        
      Level mLevel = 0;

   public:
      LANGULUS_VERBS(Verbs::Move);

      TInstance() noexcept = default;

      NOD() auto GetRange(Level) const -> RangeType;
      NOD() auto GetRangeRotated(Level) const -> RangeType;

      NOD() auto GetPositionNext(const ScalarType&) const noexcept -> PointType;
      NOD() auto GetPositionPrev(const ScalarType&) const noexcept -> PointType;
      NOD() auto GetVelocityNext(const ScalarType&) const noexcept -> PointType;
      NOD() auto GetVelocityPrev(const ScalarType&) const noexcept -> PointType;

      NOD() auto GetRight() const noexcept -> PointType;
      NOD() auto GetUp() const noexcept -> PointType;
      NOD() auto GetForward() const noexcept -> PointType;
      NOD() auto GetScale(Level) const -> SizeType;
      NOD() auto GetScale() const noexcept -> SizeType;
      NOD() auto GetAim() const noexcept -> QuatType;
      NOD() auto GetPosition(Level) const -> PointType;
      NOD() auto GetPosition() const noexcept -> PointType;
      NOD() auto GetLevel() const noexcept -> Level;

      NOD() auto GetModelTransform(Level) const -> MatrixType;
      NOD() auto GetModelTransform() const -> MatrixType;

      NOD() auto GetViewTransform(Level) const -> MatrixType;
      NOD() auto GetViewTransform() const -> MatrixType;

      void ConstrainPosition(const TInstance<T>&, const RangeType&);

      template<bool RELATIVE = false>
      void SetScale(const SizeType&);
      template<bool RELATIVE = false>
      void SetPosition(const PointType&);

      NOD() auto RandomPosition(RNG&, const RangeType&) const -> PointType;

      void Move(Flow::Verb&);

      template<CT::Angle A, CT::Dimension D>
      void Rotate(ScalarType, const TAngle<A, D>&, bool relative = false);

      template<class K>
      void Move(ScalarType, const TNormal<K>&, bool relative = false);

      template<class K>
      void Move(ScalarType, const TScale<K>&, bool relative = false);

      void Move(ScalarType, const CT::VectorBased auto&, bool relative = false);

      template<class K>
      void Move(ScalarType, const TForce<K>&, bool relative = false);

      void ChangeLevel(ScalarType, const Level&, bool relative = false);

      bool operator == (const TInstance&) const noexcept = default;
   };

} // namespace Langulus::Math