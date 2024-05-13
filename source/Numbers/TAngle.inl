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
#include "TNumber.inl"


namespace Langulus::Math
{

   ///                                                                        
   ///   Type used for representing angles in degrees                         
   ///                                                                        
   template<CT::Number T> template<CT::Number N> LANGULUS(INLINED)
   constexpr TDegrees<T>::TDegrees(const TDegrees<N>& r) noexcept
      : Base {r} {}

   template<CT::Number T> template<CT::Number N> LANGULUS(INLINED)
   constexpr TDegrees<T>::TDegrees(const TRadians<N>& r) noexcept
      : Base {r.GetDegrees()} {}

   /// Construct from any number-convertible thing                            
   ///   @param a - value to set                                              
   template<CT::Number T> LANGULUS(INLINED)
   constexpr TDegrees<T>::TDegrees(const CT::Number auto& a) noexcept
      : Base {a} {}

   template<CT::Number T> LANGULUS(INLINED)
   constexpr T TDegrees<T>::GetRadians() const noexcept {
      return DegToRad(mValue);
   }

   template<CT::Number T> LANGULUS(INLINED)
   constexpr T TDegrees<T>::GetDegrees() const noexcept {
      return mValue;
   }

   template<CT::Number T> LANGULUS(INLINED)
   Lossless<Real, T> TDegrees<T>::Cos() const noexcept {
      return Math::Cos(DegToRad(mValue));
   }

   template<CT::Number T> LANGULUS(INLINED)
   Lossless<Real, T> TDegrees<T>::Sin() const noexcept {
      return Math::Sin(DegToRad(mValue));
   }


   ///                                                                        
   ///   Type used for representing angles in radians                         
   ///                                                                        
   template<CT::Number T> template<CT::Number N> LANGULUS(INLINED)
   constexpr TRadians<T>::TRadians(const TRadians<N>& r) noexcept
      : Base {r} {}

   template<CT::Number T> template<CT::Number N> LANGULUS(INLINED)
   constexpr TRadians<T>::TRadians(const TDegrees<N>& r) noexcept
      : Base {r.GetRadians()} {}

   /// Construct from any number-convertible thing                            
   ///   @param a - value to set                                              
   template<CT::Number T> LANGULUS(INLINED)
   constexpr TRadians<T>::TRadians(const CT::Number auto& a) noexcept
      : Base {a} {}

   template<CT::Number T> LANGULUS(INLINED)
   constexpr T TRadians<T>::GetRadians() const noexcept {
      return mValue;
   }

   template<CT::Number T> LANGULUS(INLINED)
   constexpr T TRadians<T>::GetDegrees() const noexcept {
      return RadToDeg(mValue);
   }

   template<CT::Number T> LANGULUS(INLINED)
   Lossless<Real, T> TRadians<T>::Cos() const noexcept {
      return Math::Cos(mValue);
   }

   template<CT::Number T> LANGULUS(INLINED)
   Lossless<Real, T> TRadians<T>::Sin() const noexcept {
      return Math::Sin(mValue);
   }

   
   /// Construct from a descriptor                                            
   ///   @param describe - the descriptor to scan                             
   template<CT::Angle T, CT::Dimension D> LANGULUS(INLINED)
   TAngle<T, D>::TAngle(Describe&& describe) {
      LANGULUS_ASSUME(UserAssumes, *describe,
         "Empty descriptor for TAngle");

      // Attempt initializing without any conversion                    
      if (not describe->ExtractData(mValue)) {
         // Attempt converting anything to T                            
         if (not describe->ExtractDataAs(mValue)) {
            // Nothing was initialized. This is always an error in the  
            // context of the descriptor-constructor. If descriptor was 
            // empty, the default constructor would've been explicitly  
            // called, instead of this one. This way we can find out    
            // whether or not an angle instance was initialized or not. 
            LANGULUS_OOPS(Construct, "Bad TAngle descriptor",
               ", nothing was initialized: ", *describe);
         }
      }
   }

   /// Convert from any angle to text                                         
   template<CT::Angle T, CT::Dimension D> LANGULUS(INLINED)
   TAngle<T, D>::operator Anyness::Text() const {
      Anyness::Text result;
      result += NameOf<TAngle>();
      result += Flow::Code::Operator::OpenScope;
      result += Anyness::Text {mValue};
      result += Flow::Code::Operator::CloseScope;
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
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator += (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs + rhs;
      return lhs;
   }
      
   /// Destructively subtract two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator -= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs - rhs;
      return lhs;
   }
      
   /// Destructively multiply two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator *= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs * rhs;
      return lhs;
   }

   /// Destructively divide two similar angles                                
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator /= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) {
      lhs = lhs / rhs;
      return lhs;
   }

} // namespace Langulus::Math