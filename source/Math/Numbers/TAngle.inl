///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TAngle.hpp"


namespace Langulus::Math
{

   ///                                                                        
   ///   Type used for representing angles in degrees                         
   ///                                                                        
   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   constexpr T TDegrees<T>::GetRadians() const noexcept {
      return DegToRad(mValue);
   }

   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   constexpr T TDegrees<T>::GetDegrees() const noexcept {
      return mValue;
   }

   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   Lossless<Real, T> TDegrees<T>::Cos() const noexcept {
      return Math::Cos(DegToRad(mValue));
   }

   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   Lossless<Real, T> TDegrees<T>::Sin() const noexcept {
      return Math::Sin(DegToRad(mValue));
   }


   ///                                                                        
   ///   Type used for representing angles in radians                         
   ///                                                                        
   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   constexpr T TRadians<T>::GetRadians() const noexcept {
      return mValue;
   }

   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   constexpr T TRadians<T>::GetDegrees() const noexcept {
      return RadToDeg(mValue);
   }

   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   Lossless<Real, T> TRadians<T>::Cos() const noexcept {
      return Math::Cos(mValue);
   }

   template<CT::DenseNumber T>
   LANGULUS(INLINED)
   Lossless<Real, T> TRadians<T>::Sin() const noexcept {
      return Math::Sin(mValue);
   }

   /// Convert from any angle to text                                         
   template<CT::Angle T, CT::Dimension D>
   LANGULUS(INLINED)
   TAngle<T, D>::operator Flow::Code() const {
      Flow::Code result;
      result += NameOf<TAngle>();
      result += Flow::Code::OpenScope;
      result += Text {mValue};
      result += Flow::Code::CloseScope;
      return result;
   }

   /// Add two similar angles                                                 
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator + (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue + rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue + DegToRad(rhs.mValue);
      else 
         return lhs.mValue + RadToDeg(rhs.mValue);
   }

   /// Subtract two similar angles                                            
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator - (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue - rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue - DegToRad(rhs.mValue);
      else
         return lhs.mValue - RadToDeg(rhs.mValue);
   }

   /// Multiply two similar angles                                            
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator * (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue * rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue * DegToRad(rhs.mValue);
      else
         return lhs.mValue * RadToDeg(rhs.mValue);
   }
      
   /// Divide two similar angles                                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   NOD() LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator / (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) {
      if constexpr (CT::Same<LHST, RHST>)
         return lhs.mValue / rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue / DegToRad(rhs.mValue);
      else
         return lhs.mValue / RadToDeg(rhs.mValue);
   }

   /// Destructively add two similar angles                                   
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator += (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs + rhs;
      return lhs;
   }
      
   /// Destructively subtract two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator -= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs - rhs;
      return lhs;
   }
      
   /// Destructively multiply two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator *= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs * rhs;
      return lhs;
   }

   /// Destructively divide two similar angles                                
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator /= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) {
      lhs = lhs / rhs;
      return lhs;
   }

} // namespace Langulus::Math