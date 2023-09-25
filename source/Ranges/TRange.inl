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

#define TEMPLATE() template<class T>
#define TME() TRange<T>


namespace Langulus::Math
{

   /// Copy constructor                                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const TRange& a) noexcept
      : mMin {a.mMin}
      , mMax {a.mMax} {}

   /// Scalar construction (min == max)                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType& minmax) noexcept
      : mMin {minmax}
      , mMax {minmax} {}

   /// Manual construction from min & max                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType& min, const PointType& max) noexcept
      : mMin {min}
      , mMax {max} {}

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
         result += mMin.operator Flow::Code();
         result += ", ";
         result += mMax.operator Flow::Code();
      result += Flow::Code::CloseScope;
      return result;
   }

   TEMPLATE()
   template<class N>
   LANGULUS(INLINED)
   constexpr TME()& TME()::Embrace(const N& other) noexcept {
      mMin = Min(mMin, other);
      mMax = Max(mMax, other);
      return *this;
   }

   TEMPLATE()
   template<class N>
   LANGULUS(INLINED)
   constexpr TME()& TME()::ConstrainBy(const N& limits) noexcept {
      mMin = Clamp(mMin, limits.mMin, limits.mMax);
      mMax = Clamp(mMax, limits.mMin, limits.mMax);
      return *this;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::operator == (const TME()& a) const noexcept {
      return mMin == a.mMin and mMax == a.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::operator >= (const TME()& a) const noexcept {
      return mMin >= a.mMin or mMax >= a.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::operator <= (const TME()& a) const noexcept {
      return mMin <= a.mMin or mMax <= a.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::operator <  (const TME()& a) const noexcept {
      return mMin < a.mMin or mMax < a.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::operator >  (const TME()& a) const noexcept {
      return mMin > a.mMin or mMax > a.mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   typename TME()::PointType TME()::Length() const noexcept {
      return mMax - mMin;
   }

   TEMPLATE() LANGULUS(INLINED)
   typename TME()::PointType TME()::Center() const noexcept {
      return mMin + Length() * 0.5f;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsDegenerate() const noexcept {
      return mMin == mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::Inside(const PointType& a) const noexcept {
      return a >= mMin and a <= mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsInsideHalfClosed(const PointType& x) const noexcept {
      return x >= mMin and x < mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::PointType TME()::ClampRev(const PointType& pos) const noexcept {
      return pos.ClampRev(mMin, mMax);
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::PointType TME()::Clamp(const PointType& pos) const noexcept {
      return pos.Clamp(mMin, mMax);
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::operator | (const TME()& a) const noexcept {
      return {
         mMin.Clamp(a.mMin, a.mMax),
         mMax.Clamp(a.mMin, a.mMax)
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
   template<class T>
   LANGULUS(INLINED)
   constexpr TRange<T> operator - (const TRange<T>& me) noexcept {
      return {-me.mMin, -me.mMax};
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