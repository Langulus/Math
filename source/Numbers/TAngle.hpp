///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TNumber.hpp"
#include "../Vectors.hpp"
#include "../Dimensions.hpp"

namespace Langulus::CT
{

   template<class T>
   concept Angle = DenseNumber<T> && requires {
      {Decay<T>::Radians} -> Bool;
   };

} // namespace Langulus::CT

namespace Langulus::Math
{

   ///                                                                        
   ///   Type used for representing angles in degrees                         
   ///                                                                        
   template<CT::DenseNumber T>
   struct TDegrees : TNumber<T, TDegrees<T>> {
      using Base = TNumber<T, TDegrees<T>>;
      using Base::Base;
      using Base::mValue;
      static constexpr bool Radians = false;

      NOD() constexpr T GetRadians() const noexcept {
         return DegToRad(mValue);
      }

      NOD() constexpr T GetDegrees() const noexcept {
         return mValue;
      }

      NOD() Lossless<Real, T> Cos() const noexcept {
         return Math::Cos(DegToRad(mValue));
      }
      NOD() Lossless<Real, T> Sin() const noexcept {
         return Math::Sin(DegToRad(mValue));
      }
   };

   ///                                                                        
   ///   Type used for representing angles in radians                         
   ///                                                                        
   template<CT::DenseNumber T>
   struct TRadians : TNumber<T, TRadians<T>> {
      using Base = TNumber<T, TRadians<T>>;
      using Base::Base;
      using Base::mValue;
      static constexpr bool Radians = true;

      NOD() constexpr T GetRadians() const noexcept {
         return mValue;
      }

      NOD() constexpr T GetDegrees() const noexcept {
         return RadToDeg(mValue);
      }

      NOD() Lossless<Real, T> Cos() const noexcept {
         return Math::Cos(mValue);
      }
      NOD() Lossless<Real, T> Sin() const noexcept {
         return Math::Sin(mValue);
      }
   };

   using Degrees = TDegrees<Real>;
   using Radians = TRadians<Real>;

   template<CT::Angle T, CT::Dimension D>
   struct TAngle;

   template<CT::Angle T>
   using TYaw = TAngle<T, Traits::Y>;
   template<CT::Angle T>
   using TPitch = TAngle<T, Traits::X>;
   template<CT::Angle T>
   using TRoll = TAngle<T, Traits::Z>;

   using Yawdf = TYaw<TDegrees<Float>>;
   using Yawdd = TYaw<TDegrees<Double>>;
   using Yawrf = TYaw<TRadians<Float>>;
   using Yawrd = TYaw<TRadians<Double>>;

   using Pitchdf = TPitch<TDegrees<Float>>;
   using Pitchdd = TPitch<TDegrees<Double>>;
   using Pitchrf = TPitch<TRadians<Float>>;
   using Pitchrd = TPitch<TRadians<Double>>;

   using Rolldf = TRoll<TDegrees<Float>>;
   using Rolldd = TRoll<TDegrees<Double>>;
   using Rollrf = TRoll<TRadians<Float>>;
   using Rollrd = TRoll<TRadians<Double>>;

   using Yawd = TYaw<Degrees>;
   using Yawr = TYaw<Radians>;
   using Pitchd = TPitch<Degrees>;
   using Pitchr = TPitch<Radians>;
   using Rolld = TRoll<Degrees>;
   using Rollr = TRoll<Radians>;

   constexpr Degrees operator""_deg(long double n) noexcept { return n; }
   constexpr Degrees operator""_deg(unsigned long long n) noexcept { return n; }
   constexpr Radians operator""_rad(long double n) noexcept { return {n}; }
   constexpr Radians operator""_rad(unsigned long long n) noexcept { return {n}; }

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as      
   /// an angle                                                               
   struct Angle {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::Radians;
   };

   /// Used as an imposed base for any type that can be interpretable as      
   /// an angle of the same dimension                                         
   template<CT::Dimension D>
   struct AngleOfDimension : Angle {
      LANGULUS(CONCRETE) Math::TAngle<Math::Radians, D>;
      LANGULUS_BASES(Angle);
   };

   /// Used as an imposed base for any type that can be interpretable as      
   /// an angle of the same type                                              
   template<CT::Angle T>
   struct AngleOfType : Angle {
      LANGULUS(CONCRETE) T;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(Angle);
   };

} // namespace Langulus::A


namespace Langulus::Math
{

   ///                                                                        
   ///   Templated angle                                                      
   ///                                                                        
   template<CT::Angle T, CT::Dimension D>
   struct TAngle : T {
      LANGULUS_BASES(T, A::AngleOfDimension<D>, A::AngleOfType<T>);
      using Dimension = D;
      using T::T;
      using T::mValue;

      /// Convert from any angle to text                                      
      NOD() explicit operator Flow::Code() const {
         Flow::Code result;
         result += MetaOf<TAngle>();
         result += Flow::Code::OpenScope;
         result += Text {mValue};
         result += Flow::Code::CloseScope;
         return result;
      }
   };


   /// Add two similar angles                                                 
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() constexpr TAngle<LHST, D> operator + (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue + rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue + DegToRad(rhs.mValue);
      else 
         return lhs.mValue + RadToDeg(rhs.mValue);
   }

   /// Subtract two similar angles                                            
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() constexpr TAngle<LHST, D> operator - (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue - rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue - DegToRad(rhs.mValue);
      else
         return lhs.mValue - RadToDeg(rhs.mValue);
   }

   /// Multiply two similar angles                                            
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() constexpr TAngle<LHST, D> operator * (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue * rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue * DegToRad(rhs.mValue);
      else
         return lhs.mValue * RadToDeg(rhs.mValue);
   }
      
   /// Divide two similar angles                                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() constexpr TAngle<LHST, D> operator / (const TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue / rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue / DegToRad(rhs.mValue);
      else
         return lhs.mValue / RadToDeg(rhs.mValue);
   }

   /// Destructively add two similar angles                                   
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   constexpr TAngle<LHST, D>& operator += (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
      lhs = lhs + rhs;
      return lhs;
   }
      
   /// Destructively subtract two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   constexpr TAngle<LHST, D>& operator -= (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
      lhs = lhs - rhs;
      return lhs;
   }
      
   /// Destructively multiply two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   constexpr TAngle<LHST, D>& operator *= (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) noexcept {
      lhs = lhs * rhs;
      return lhs;
   }

   /// Destructively divide two similar angles                                
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   constexpr TAngle<LHST, D>& operator /= (TAngle<LHST, D>& lhs, const TAngle<RHST, D>& rhs) {
      lhs = lhs / rhs;
      return lhs;
   }

} // namespace Langulus::Math