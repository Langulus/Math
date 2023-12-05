///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TPlane.hpp"
#include "../SignedDistance/TPlane.inl"

namespace Langulus::Math
{

   /// Construction from normal and offset                                    
   ///   @param normal - the plane normal                                     
   ///   @param offset - the plane distance from origin                       
   template<CT::Vector T>
   constexpr TPlane<T>::TPlane(const T& normal, TypeOf<T> offset) noexcept
      : mNormal {normal}
      , mOffset {offset} {
      Normalize();
   }

   /// Construction from a matrix column                                      
   ///   @param column - the column                                           
   template<CT::Vector T>
   constexpr TPlane<T>::TPlane(const TVector<TypeOf<T>, MemberCount + 1>& column) noexcept
      : mNormal {column}
      , mOffset {column[MemberCount]} {
      Normalize();
   }

   /// Construction from distance times direction                             
   ///   @param offset - the offset                                           
   template<CT::Vector T>
   constexpr TPlane<T>::TPlane(const T& offset) noexcept {
      const auto d = offset.Length();
      mNormal = offset / d;
      mOffset = d;
   }

   /// Flip the plane                                                         
   ///   @return a reference to this plane                                    
   template<CT::Vector T>
   TPlane<T>& TPlane<T>::Flip() noexcept {
      mNormal *= TypeOf<T> {-1};
      mOffset *= TypeOf<T> {-1};
      return *this;
   }

   /// Normalize the plane                                                    
   ///   @return a normalized plane                                           
   template<CT::Vector T>
   TPlane<T>& TPlane<T>::Normalize() noexcept {
      const auto length = mNormal.Length();
      if (0 != length) {
         mNormal /= length;
         mOffset /= length;
      }
      return *this;
   }

   /// Check if plane is degenerate                                           
   ///   @return true if at least one offset is zero                          
   template<CT::Vector T>
   constexpr bool TPlane<T>::IsDegenerate() const noexcept {
      return mNormal.Length() == TypeOf<T> {0};
   }

   /// Check if plane is hollow                                               
   ///   @return always false, because planes aren't volumes                  
   template<CT::Vector T>
   constexpr bool TPlane<T>::IsHollow() const noexcept {
      return false;
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   template<CT::Vector T>
   auto TPlane<T>::SignedDistance(const T& point) const {
      return Math::SignedDistance(point, *this);
   }

} // namespace Langulus::Math

