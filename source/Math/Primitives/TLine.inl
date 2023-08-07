///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TLine.hpp"

#define TEMPLATE() template<CT::Vector T>

namespace Langulus::Math
{

   /// Default construction (along x)                                      
   TEMPLATE() LANGULUS(INLINED)
   constexpr TLine<T>::TLine() noexcept {
      mAB[1][0] = TypeOf<T> {0};
   }

   /// Manual construction from two points of any type                     
   ///   @param p1 - first point                                           
   ///   @param p2 - second point                                          
   TEMPLATE()
   template<CT::Vector ALT_T>
   LANGULUS(INLINED)
   constexpr TLine<T>::TLine(const ALT_T& p1, const ALT_T& p2) noexcept
      : mAB {T{p1}, T{p2}} {}

   /// Manual construction from two points of any type (unsafe)            
   ///   @param points - pointer to the two points                         
   TEMPLATE()
   template<CT::Vector ALT_T>
   LANGULUS(INLINED)
   constexpr TLine<T>::TLine(const ALT_T* points) noexcept
      : mAB {points[0], points[1]} {}

   /// Manual construction from two points of any type, indexed            
   ///   @param points - pointer to the two points                         
   ///   @param indices - indices for the points array                     
   TEMPLATE()
   template<CT::Vector ALT_T, CT::Integer IDX>
   LANGULUS(INLINED)
   constexpr TLine<T>::TLine(const ALT_T* points, const IDX(&indices)[2]) noexcept
      : mAB {points[indices[0]], points[indices[1]]} {}

   /// Check if line is degenerate                                         
   ///   @param radius - the line radius used for tolerance                
   ///   @return true if line has no radius or no length                   
   TEMPLATE() LANGULUS(INLINED)
   bool TLine<T>::IsDegenerate() const noexcept {
      return (mAB[0] - mAB[1]).Length() == TypeOf<T> {0};
   }

   /// Subdivide line                                                      
   ///   @return the two new lines                                         
   TEMPLATE() LANGULUS(INLINED)
   ::std::array<TLine<T>, 2> TLine<T>::Subdivide() const noexcept {
      const T midpoint = mAB[0] + (mAB[1] - mAB[0]) / TypeOf<T> {2};
      return {{mAB[0], midpoint}, {midpoint, mAB[1]}};
   }

   /// Calculate signed distance                                           
   ///   @param point - the point from which distance is calculated        
   ///   @return the distance                                              
   TEMPLATE() LANGULUS(INLINED)
   auto TLine<T>::SignedDistance(const PointType& point) const {
      const auto pa = point - mAB[0];
      const auto ba = mAB[1] - mAB[0];
      const auto h = Saturate(Dot(pa, ba) / Dot2(ba));
      return Math::Length(pa - ba * h);
   }

   /// Access points (const)                                               
   ///   @param index - index of the point                                 
   ///   @return a reference to the point                                  
   TEMPLATE() LANGULUS(INLINED)
   auto& TLine<T>::operator [] (Offset index) const noexcept {
      return mAB[index];
   }

   /// Access points                                                       
   ///   @param index - index of the point                                 
   ///   @return a reference to the point                                  
   TEMPLATE() LANGULUS(INLINED)
   auto& TLine<T>::operator [] (Offset index) noexcept {
      return mAB[index];
   }

   /// Convert to other kinds of lines                                     
   ///   @tparam ALT - alternative point type (deducible)                  
   TEMPLATE()
   template<CT::Vector ALT>
   LANGULUS(INLINED)
   TLine<T>::operator TLine<ALT>() const noexcept {
      return {static_cast<ALT>(mAB[0]), static_cast<ALT>(mAB[1])};
   }

} // namespace Langulus::Math

#undef TEMPLATE