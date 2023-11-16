///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TRange.hpp"

#define TEMPLATE() template<CT::Dense T>
#define TME() TRange<T>


namespace Langulus::Math
{

   /// Copy constructor                                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const TRange& a) noexcept
      : mBounds {a.mMin, a.mMax} {}

   /// Scalar construction (min == max)                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType& minmax) noexcept
      : mBounds {minmax, minmax} {}

   /// Manual construction from min & max                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType& min, const PointType& max) noexcept
      : mBounds {min, max} {}

   /// From dense data                                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType* a) noexcept
      : TRange {a[0], a[1]} {}

   /// From sparse data                                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType* const* a) noexcept
      : TRange {*a[0], *a[1]} {}

   /// Convert any range to text                                              
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      Flow::Code result;
      result += NameOf<TRange>();
      result += Flow::Code::OpenScope;
         result += mBounds.mMin.operator Flow::Code();
         result += ", ";
         result += mBounds.mMax.operator Flow::Code();
      result += Flow::Code::CloseScope;
      return result;
   }

   TEMPLATE()
   template<class N>
   LANGULUS(INLINED)
   constexpr TME()& TME()::Embrace(const N& other) noexcept {
      mBounds.mMin = Min(mBounds.mMin, other);
      mBounds.mMax = Max(mBounds.mMax, other);
      return *this;
   }

   TEMPLATE()
   template<class N>
   LANGULUS(INLINED)
   constexpr TME()& TME()::ConstrainBy(const N& limits) noexcept {
      mBounds.mMin = Clamp(mBounds.mMin, limits.mBounds.mMin, limits.mBounds.mMax);
      mBounds.mMax = Clamp(mBounds.mMax, limits.mBounds.mMin, limits.mBounds.mMax);
      return *this;
   }

   TEMPLATE() LANGULUS(INLINED)
   typename TME()::PointType TME()::Length() const noexcept {
      return mBounds.mMax - mBounds.mMin;
   }

   TEMPLATE() LANGULUS(INLINED)
   typename TME()::PointType TME()::Center() const noexcept {
      return mBounds.mMin + Length() * 0.5f;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsDegenerate() const noexcept {
      return mBounds.mMin == mBounds.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::Inside(const PointType& a) const noexcept {
      return a >= mBounds.mMin and a <= mBounds.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsInsideHalfClosed(const PointType& x) const noexcept {
      return x >= mBounds.mMin and x < mBounds.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::PointType TME()::ClampRev(const PointType& pos) const noexcept {
      return pos.ClampRev(mBounds.mMin, mBounds.mMax);
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::PointType TME()::Clamp(const PointType& pos) const noexcept {
      return pos.Clamp(mBounds.mMin, mBounds.mMax);
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::operator | (const TME()& a) const noexcept {
      return {
         mBounds.mMin.Clamp(a.mBounds.mMin, a.mBounds.mMax),
         mBounds.mMax.Clamp(a.mBounds.mMin, a.mBounds.mMax)
      };
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator |= (const TME()& a) noexcept {
      *this = *this | a;
   }


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        

   /// Returns an inverted range                                              
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::RangeBased auto& rhs) noexcept {
      return rhs * Decay<TypeOf<decltype(rhs)>> {-1};
   }
   
   /// Returns the sum of any two ranges                                      
   /// Only the intersecting elements are added and returned                  
   ///   min[4] + min[2] = min[2]                                             
   ///   max[4] + max[2] = max[2]                                             
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::RangeBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Vector + Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::RangeBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Scalar + Vector                                                        
   constexpr auto operator + (const CT::DenseScalar auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }


   /// Returns the sum of two ranges                                          
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto operator + (const TRange<T1>& me, const TRange<T2>& other) noexcept {
      return TRange<decltype(Fake<T1>() + Fake<T2>())> {
         me.mMin + other.mMin,
         me.mMax + other.mMax
      };
   }

   /// Returns the difference of two ranges                                   
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto operator - (const TRange<T1>& me, const TRange<T2>& other) noexcept {
      return TRange<decltype(Fake<T1>() - Fake<T2>())> {
         me.mMin - other.mMin,
         me.mMax - other.mMax
      };
   }

   /// Returns the product of two ranges                                      
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto operator * (const TRange<T1>& me, const TRange<T2>& other) noexcept {
      return TRange<decltype(Fake<T1>() * Fake<T2>())> {
         me.mMin * other.mMin,
         me.mMax * other.mMax
      };
   }

   /// Returns the division of two ranges                                     
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto operator / (const TRange<T1>& me, const TRange<T2>& other) {
      return TRange<decltype(Fake<T1>() / Fake<T2>())> {
         me.mMin / other.mMin,
         me.mMax / other.mMax
      };
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        

   /// Add                                                                    
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto& operator += (TRange<T1>& me, const TRange<T2>& other) noexcept {
      me.mMin += other.mMin;
      me.mMax += other.mMax;
      return me;
   }

   /// Subtract                                                               
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto& operator -= (TRange<T1>& me, const TRange<T2>& other) noexcept {
      me.mMin -= other.mMin;
      me.mMax -= other.mMax;
      return me;
   }

   /// Multiply                                                               
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto& operator *= (TRange<T1>& me, const TRange<T2>& other) noexcept {
      me.mMin *= other.mMin;
      me.mMax *= other.mMax;
      return me;
   }

   /// Divide                                                                 
   template<class T1, class T2>
   LANGULUS(INLINED)
   auto& operator /= (TRange<T1>& me, const TRange<T2>& other) {
      me.mMin /= other.mMin;
      me.mMax /= other.mMax;
      return me;
   }

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME