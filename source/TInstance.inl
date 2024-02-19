///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once 
#include "TInstance.hpp"
#include "Ranges/TRange.inl"
#include "Quaternions/TQuaternion.inl"

#define TEMPLATE() template<CT::VectorBased T>
#define TME() TInstance<T>


namespace Langulus::Math
{

   /// Get the range of the instance (aka AABB) from a ref octave             
   /// This doesn't take rotation into account, only scaling                  
   ///   @param reference - the reference octave                              
   ///   @return the AABB range                                               
   TEMPLATE()
   typename TME()::RangeType TME()::GetRange(Level level) const {
      const auto halfSize = GetScale() * ScalarType {.5};
      const auto factor   = Pow(Level::Unit, mLevel - level);
      const auto position = GetPosition();
      return (RangeType {-halfSize, halfSize} + position) * factor;
   }

   /// Get the range of the instance (aka AABB) from a ref octave             
   /// This takes rotation and scale into account                             
   ///   @param reference - the reference octave                              
   ///   @return the AABB range                                               
   TEMPLATE()
   typename TME()::RangeType TME()::GetRangeRotated(Level reference) const {
      // AABB before rotation                                           
      const auto aabb = GetRange(reference);
      if (aabb.IsDegenerate())
         return {};

      const auto center = aabb.Center();

      // Rotate each point of the AABB                                  
      // We don't actually have to rotate all the points, because       
      // they're coplanar and can later be reconstructed.               
      // So we just rotate only one of the bases around the center.     
      const auto orientation_matrix = static_cast<MatrixType>(mAim);
      const PointType base[4] = {
         orientation_matrix * (aabb.mMax - center),
         orientation_matrix * (PointType(aabb.mMax.x, aabb.mMax.y, aabb.mMin.z) - center),
         orientation_matrix * (PointType(aabb.mMax.x, aabb.mMin.y, aabb.mMax.z) - center),
         orientation_matrix * (PointType(aabb.mMax.x, aabb.mMin.y, aabb.mMin.z) - center)
      };

      // Use the rotated base to reconstruct the rest of the points     
      // They're simply mirrored relative to the center                 
      const PointType points[8] = {
         base[0] + center,  base[1] + center,  base[2] + center,  base[3] + center,
        -base[0] + center, -base[1] + center, -base[2] + center, -base[3] + center
      };

      // Then recalculate min/max values of the new AABB                
      return {
         Min(points[0], points[1], points[2], points[3], 
             points[4], points[5], points[6], points[7]),
         Max(points[0], points[1], points[2], points[3], 
             points[4], points[5], points[6], points[7])
      };
   }

   /// Get the future-projected position                                      
   ///   @param dt - delta time between frames                                
   ///   @return the projected position, based on current velocity            
   TEMPLATE()
   typename TME()::PointType TME()::GetPositionNext(const ScalarType& dt) const noexcept {
      return mPosition + mVelocity * dt;
   }

   /// Get the past-projected position                                        
   ///   @param dt - delta time between frames                                
   ///   @return the projected position, based on current velocity            
   TEMPLATE()
   typename TME()::PointType TME()::GetPositionPrev(const ScalarType& dt) const noexcept {
      return mPosition - mVelocity * dt;
   }

   /// Get the future-projected velocity                                      
   ///   @param dt - delta time between frames                                
   ///   @return the projected velocity, based on current acceleration        
   TEMPLATE()
   typename TME()::PointType TME()::GetVelocityNext(const ScalarType& dt) const noexcept {
      return mVelocity + mAcceleration * dt;
   }

   /// Get the past-projected velocity                                        
   ///   @param dt - delta time between frames                                
   ///   @return the projected velocity, based on current acceleration        
   TEMPLATE()
   typename TME()::PointType TME()::GetVelocityPrev(const ScalarType& dt) const noexcept {
      return mVelocity - mAcceleration * dt;
   }

   /// Get the right normal of the instance                                   
   ///   @return the oriented right vector                                    
   TEMPLATE()
   typename TME()::PointType TME()::GetRight() const noexcept {
      return GetAim() * Axes::Right<ScalarType>;
   }

   /// Get the up normal of the instance                                      
   ///   @return the oriented up vector                                       
   TEMPLATE()
   typename TME()::PointType TME()::GetUp() const noexcept {
      return GetAim() * Axes::Up<ScalarType>;
   }

   /// Get the forward normal of the instance                                 
   ///   @return the oriented forward vector                                  
   TEMPLATE()
   typename TME()::PointType TME()::GetForward() const noexcept {
      return GetAim() * Axes::Forward<ScalarType>;
   }

   /// Get scale, relative to a given octave                                  
   ///   @param octave - the octave                                           
   ///   @return the scale                                                    
   TEMPLATE()
   typename TME()::SizeType TME()::GetScale(Level level) const {
      const auto factor = Math::Pow(Level::Unit, mLevel - level);
      return GetScale() * factor;
   }

   /// Get scale                                                              
   ///   @return the scale                                                    
   TEMPLATE()
   typename TME()::SizeType TME()::GetScale() const noexcept {
      return mParent ? SizeType {mParent->GetScale() * mScale} : mScale;
   }

   /// Get orientation                                                        
   ///   @return the orientation quaternion                                   
   TEMPLATE()
   typename TME()::QuatType TME()::GetAim() const noexcept {
      return mParent ? (mParent->GetAim() * mAim).Normalize() : mAim;
   }

   /// Get position, relative to a given level                                
   ///   @param level - the level                                             
   ///   @return the position                                                 
   TEMPLATE()
   typename TME()::PointType TME()::GetPosition(Level level) const {
      const auto factor = Math::Pow(Level::Unit, mLevel - level);
      return GetPosition() * factor;
   }

   /// Get position                                                           
   ///   @return the position                                                 
   TEMPLATE()
   typename TME()::PointType TME()::GetPosition() const noexcept {
      return mParent ? mParent->GetPosition() + mPosition : mPosition;
   }

   /// Get octave                                                             
   ///   @return the octave                                                   
   TEMPLATE()
   Level TME()::GetLevel() const noexcept {
      return mLevel;
   }

   /// Get model transformation, relative to a given level                    
   ///   @param level - the level                                             
   ///   @return the model matrix                                             
   TEMPLATE()
   typename TME()::MatrixType TME()::GetModelTransform(Level level) const {
      const auto factor = Math::Pow(Level::Unit, mLevel - level);
      const auto translate = GetPosition() * factor;
      auto scale = GetScale() * factor;
      if (scale.IsDegenerate())
         scale = 1;
      return A::Matrix::From<PointType>(GetAim(), translate, scale);
   }

   /// Get model transformation                                               
   ///   @return the model matrix                                             
   TEMPLATE()
   typename TME()::MatrixType TME()::GetModelTransform() const {
      auto scale = GetScale();
      if (scale.IsDegenerate())
         scale = 1;
      return A::Matrix::From<PointType>(GetAim(), GetPosition(), scale);
   }

   /// Get view transformation, relative to a given level                     
   ///   @param level - the level                                             
   ///   @return the view matrix                                              
   TEMPLATE()
   typename TME()::MatrixType TME()::GetViewTransform(Level level) const {
      return A::Matrix::From<PointType>(GetAim(), GetPosition(level));
   }

   /// Get view transformation                                                
   ///   @return the view matrix                                              
   TEMPLATE()
   typename TME()::MatrixType TME()::GetViewTransform() const {
      return A::Matrix::From<PointType>(GetAim(), GetPosition());
   }

   /// Constrain to another instance                                          
   ///   @param limits - instance representing the possible volume            
   ///   @param range - symoblic range that transforms the limits             
   TEMPLATE()
   void TME()::ConstrainPosition(const TME()& limits, const RangeType& range) {
      // Clamp inside object                                            
      constexpr ScalarType half {.5};
      const auto thisscale = GetScale() * half;
      const auto otherscale = limits.GetScale() * half;
      const auto innerscale = (otherscale + thisscale) * range.mMin;
      const auto outerscale = (otherscale - thisscale) * range.mMax;
      const auto otherpos = limits.GetPosition();
      const RangeType inner {otherpos - innerscale, otherpos + innerscale};
      const RangeType outer {otherpos - outerscale, otherpos + outerscale};

      // Push outside inner limit                                       
      mPosition = inner.ClampRev(mPosition);

      // Push inside outer limit                                        
      mPosition = outer.Clamp(mPosition);
   }

   /// Set relative or absolute scale                                         
   ///   @tparam RELATIVE - if true, then ignores mParent chain               
   ///   @param scale - the new scale                                         
   TEMPLATE() template<bool RELATIVE>
   void TME()::SetScale(const SizeType& scale) {
      if constexpr (RELATIVE)
         mScale = scale;
      else {
         if (mParent)
            mScale = scale / mParent->GetScale();
         else
            mScale = scale;
      }
   }

   /// Set relative or absolute position                                      
   ///   @tparam RELATIVE - if true, then ignores mParent chain               
   ///   @param scale - the new scale                                         
   TEMPLATE() template<bool RELATIVE>
   void TME()::SetPosition(const PointType& position) {
      if constexpr (RELATIVE)
         mPosition = position;
      else {
         if (mParent)
            mPosition = position - mParent->GetPosition();
         else
            mPosition = position;
      }
   }

   /// Get a constrained random position that uses this instance volume       
   ///   @param rng - random number genrator to use                           
   ///   @param range - the symbolic range for modifying the volume           
   ///   @return the generated position                                       
   TEMPLATE()
   typename TME()::PointType TME()::RandomPosition(RNG& rng, const RangeType& range) const {
      // Clamp inside object                                            
      const auto thisscale = GetScale() * ScalarType {.5};
      const auto innerscale = thisscale * range.mMin;
      const auto outerscale = thisscale * range.mMax;

      // Get a random vector                                            
      const auto rnewpos = PointType {
         rng.Get<ScalarType>(),
         rng.Get<ScalarType>(),
         rng.Get<ScalarType>()
      } * ScalarType {2} - ScalarType {1};

      auto newpos = rnewpos * (outerscale - innerscale);
      newpos[0] += innerscale[0] * Math::Sign(newpos[0]);
      newpos[1] += innerscale[1] * Math::Sign(newpos[1]);
      newpos[2] += innerscale[2] * Math::Sign(newpos[2]);
      return newpos + GetPosition();
   }

   /// Rotate by euler angles                                                 
   ///   @param sign - the sign of the rotation                               
   ///   @param angle - the oriented angle                                    
   ///   @param relative - whether or not the angle is relative to current    
   TEMPLATE()
   template<CT::Angle A, CT::Dimension D>
   void TME()::Rotate(ScalarType sign, const TAngle<A, D>& angle, bool relative) {
      if (relative) {
         // The rotation axis is relative                               
         mAim *= QuatType::FromAngle(angle * sign);
      }
      else {
         // The rotation axis is absolute                               
         if constexpr (CT::Same<D, Traits::X>)
            mAim *= QuatType::FromAxisAngle(GetRight(), angle * sign);
         else if constexpr (CT::Same<D, Traits::Y>)
            mAim *= QuatType::FromAxisAngle(GetUp(), angle * sign);
         else if constexpr (CT::Same<D, Traits::Z>)
            mAim *= QuatType::FromAxisAngle(GetForward(), angle * sign);
         else
            LANGULUS_ERROR("Unsupported dimension");
      }
   }

   /// Move along a direction                                                 
   ///   @param sign - the sign of the movement                               
   ///   @param normal - the normalized direction                             
   ///   @param relative - whether or not normal is relative to current       
   TEMPLATE()
   template<class K>
   void TME()::Move(ScalarType sign, const TNormal<K>& normal, bool relative) {
      if (relative)
         mUseVelocity += -mAim * (normal * sign);
      else
         mUseVelocity += normal * sign;
   }

   /// Resize instance (movement inwards/outwards)                            
   ///   @param sign - the sign of the movement                               
   ///   @param sizer - the new size                                          
   ///   @param relative - whether or not size is relative to current         
   TEMPLATE()
   template<class K>
   void TME()::Move(ScalarType sign, const TScale<K>& sizer, bool relative) {
      if (relative)
         mScale += sizer * sign;
      else
         mScale = sizer * sign;
   }

   /// Sets a new position                                                    
   ///   @param sign - the sign of the movement                               
   ///   @param position - the new position                                   
   ///   @param relative - whether or not position is relative to current     
   TEMPLATE()
   template<class K>
   void TME()::Move(ScalarType sign, const TPoint<K>& position, bool relative) {
      if (relative)
         mPosition = -mAim * (sign * PointType {position});
      else
         mPosition = position;
   }

   /// Add a multioctave force                                                
   ///   @param sign - the sign of the movement                               
   ///   @param force - the force to apply                                    
   ///   @param relative - whether or not force is relative to current        
   TEMPLATE()
   template<class K>
   void TME()::Move(ScalarType sign, const TForce<K>& force, bool relative) {
      if (relative)
         mUseVelocity += -mAim * (force * sign);
      else
         mUseVelocity += force * sign;
   }

   /// Execute a move/rotate/scale verb                                       
   ///   @param verb - movement verb                                          
   TEMPLATE()
   void TME()::Move(Flow::Verb& verb) {
      const auto sign = Sign(verb.GetMass());
      bool relative = false;

      using Anyness::Block;
      using Anyness::Trait;

      verb.ForEachDeep([&](const Block& part) {
         // Read relativity first                                       
         part.ForEach([&relative](const Trait& trait) {
            if (trait.IsTrait<Traits::Relative>())
               relative = trait.AsCast<bool>();
         });

         Count done = part.ForEach(
            [&](const Normal& normal) {
               // Move towards normalized direction                     
               // All points move in the same direction                 
               VERBOSE_TINSTANCE("Moving along normal: " << normal 
                  << (relative ? " (relatively)" : ""));
               Move(sign, normal, relative);
               verb.Done();
            },
            [&](const Point2& point) {
               // Move towards a point in space                         
               // All points move in the same direction                 
               VERBOSE_TINSTANCE("Moving to a point2: " << point
                  << (relative ? " (relatively)" : ""));
               Move(sign, point, relative);
               verb.Done();
            },
            [&](const Point3& point) {
               // Move towards a point in space                         
               // All points move in the same direction                 
               VERBOSE_TINSTANCE("Moving to a point3: " << point
                  << (relative ? " (relatively)" : ""));
               Move(sign, point, relative);
               verb.Done();
            },
            [&](const Force2& force) {
               // Apply a force                                         
               // All points move in the same direction                 
               VERBOSE_TINSTANCE("Applying a force2: " << force
                  << (relative ? " (relatively)" : ""));
               Move(sign, force, relative);
               verb.Done();
            },
            [&](const Force3& force) {
               // Apply a force                                         
               // All points move in the same direction                 
               VERBOSE_TINSTANCE("Applying a force3: " << force
                  << (relative ? " (relatively)" : ""));
               Move(sign, force, relative);
               verb.Done();
            },
            [&](const Level& octave) {
               // Apply a change in octave                              
               // All points of a physical object move to/from center   
               VERBOSE_TINSTANCE("Applying an octave: " << octave
                  << (relative ? " (relatively)" : ""));
               ChangeLevel(sign, octave, relative);
               verb.Done();
            },
            [&](const Size& size) {
               // Apply a change in size                                
               // All points of a physical object move to/from center   
               VERBOSE_TINSTANCE("Applying a size: " << size
                  << (relative ? " (relatively)" : ""));
               Move(sign, size, relative);
               verb.Done();
            }
         );

         if (done > 0)
            return;

         if constexpr (T::MemberCount > 2) {
            // Yaw and pitch are allowed only above 2D                  
            done = part.ForEach(
               [&](const Yawd& angle) {
                  // Rotate via a yaw angle (turning around Y)          
                  // All points move around the center                  
                  VERBOSE_TINSTANCE("Yaw (degrees): " << angle 
                     << (relative ? " (relatively)" : ""));
                  Rotate(sign, angle, relative);
                  verb.Done();
               },
               [&](const Yawr& angle) {
                  // Rotate via a yaw angle (turning around Y)          
                  // All points move around the center                  
                  VERBOSE_TINSTANCE("Yaw (radians): " << angle
                     << (relative ? " (relatively)" : ""));
                  Rotate(sign, angle, relative);
                  verb.Done();
               },
               [&](const Pitchd& angle) {
                  // Rotate via a pitch angle (turning around X)        
                  // All points move around the center                  
                  VERBOSE_TINSTANCE("Pitch (degrees): " << angle 
                     << (relative ? " (relatively)" : ""));
                  Rotate(sign, angle, relative);
                  verb.Done();
               },
               [&](const Pitchr& angle) {
                  // Rotate via a pitch angle (turning around X)        
                  // All points move around the center                  
                  VERBOSE_TINSTANCE("Pitch (radians): " << angle
                     << (relative ? " (relatively)" : ""));
                  Rotate(sign, angle, relative);
                  verb.Done();
               }
            );

            if (done > 0)
               return;
         }

         done = part.ForEach(
            [&](const Rolld& angle) {
               // Rotate via a roll angle (turning around Z)            
               // All points of a physical object move around the center
               VERBOSE_TINSTANCE("Roll (degrees): " << angle 
                  << (relative ? " (relatively)" : ""));
               Rotate(sign, angle, relative);
               verb.Done();
            },
            [&](const Rollr& angle) {
               // Rotate via a roll angle (turning around Z)            
               // All points of a physical object move around the center
               VERBOSE_TINSTANCE("Roll (radians): " << angle
                  << (relative ? " (relatively)" : ""));
               Rotate(sign, angle, relative);
               verb.Done();
            }
         );
      });
   }

   /// Add/subtract an octave, essentially resizing the instance              
   ///   @param sign - the sign for the change                                
   ///   @param octave - the octave offset                                    
   TEMPLATE()
   void TME()::ChangeLevel(ScalarType sign, const Level& octave, bool relative) {
      if (relative)
         mUseLevelChange += octave * Level {sign};
      else
         mUseLevelChange = octave * Level {sign};
   }

} // namespace Langulus::Math

#undef TME
#undef TEMPLATE