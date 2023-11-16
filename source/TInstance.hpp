///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Numbers/Level.hpp"
#include "Numbers/TAngle.hpp"
#include "Ranges/TRange.hpp"
#include "Vectors/TVector.hpp"
#include "Vectors/TNormal.hpp"
#include "Vectors/TForce.hpp"
#include "Quaternions/TQuaternion.hpp"
#include "Randomness/MersenneTwister.hpp"

#define VERBOSE_TINSTANCE(a) // Logger::Verbose() << a


namespace Langulus::Math
{

   ///                                                                        
   ///   Instance                                                             
   ///                                                                        
   /// Provides higher level functionality for rotation, translation,         
   /// scaling, and primitive collisions. Can be 2D or 3D, depending on T     
   ///                                                                        
   template<CT::Vector T>
   class TInstance {
   public:
      using ScalarType = TypeOf<T>;
      using PointType = T;
      using MatrixType = TMatrix<ScalarType, T::MemberCount + 1, T::MemberCount + 1>;
      using RangeType = TRange<T>;
      using QuatType = TQuaternion<ScalarType>;
      using SizeType = TScale<T>;

   public:
      TInstance() noexcept = default;

      NOD() RangeType GetRange(Level) const;
      NOD() RangeType GetRangeRotated(Level) const;

      NOD() PointType GetPositionNext(const ScalarType&) const noexcept;
      NOD() PointType GetPositionPrev(const ScalarType&) const noexcept;
      NOD() PointType GetVelocityNext(const ScalarType&) const noexcept;
      NOD() PointType GetVelocityPrev(const ScalarType&) const noexcept;

      NOD() PointType GetRight() const noexcept;
      NOD() PointType GetUp() const noexcept;
      NOD() PointType GetForward() const noexcept;
      NOD() SizeType GetScale(Level) const;
      NOD() SizeType GetScale() const noexcept;
      NOD() QuatType GetAim() const noexcept;
      NOD() PointType GetPosition(Level) const;
      NOD() PointType GetPosition() const noexcept;
      NOD() Level GetLevel() const noexcept;

      NOD() MatrixType GetModelTransform(Level) const;
      NOD() MatrixType GetModelTransform() const;

      NOD() MatrixType GetViewTransform(Level) const;
      NOD() MatrixType GetViewTransform() const;

      void ConstrainPosition(const TInstance<T>&, const RangeType&);

      template<bool RELATIVE = false>
      void SetScale(const SizeType&);
      template<bool RELATIVE = false>
      void SetPosition(const PointType&);

      NOD() PointType RandomPosition(RNG&, const RangeType&) const;

      void Move(Verb&);

      template<CT::Angle A, CT::Dimension D>
      void Rotate(ScalarType, const TAngle<A, D>&, bool relative = false);

      template<class K>
      void Move(ScalarType, const TNormal<K>&, bool relative = false);

      template<class K>
      void Move(ScalarType, const TScale<K>&, bool relative = false);

      template<class K>
      void Move(ScalarType, const TPoint<K>&, bool relative = false);

      template<class K>
      void Move(ScalarType, const TForce<K>&, bool relative = false);

      void ChangeLevel(ScalarType, const Level&, bool relative = false);

      bool operator == (const TInstance&) const noexcept;

   public:
      // Optional parent for inheriting transformations                 
      Ptr<TInstance<T>> mParent;

      // Position in space                                              
      PointType mPosition;

      // Velocity incurred by simulation                                
      PointType mSimVelocity;
      // Velocity incurred by user interaction                          
      PointType mUseVelocity;
      // Total velocity                                                 
      PointType mVelocity;

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
   };

} // namespace Langulus::Math