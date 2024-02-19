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
#include "../Vectors/TVector.inl"

#define TEMPLATE() template<CT::Dense T>
#define TME() TRange<T>


namespace Langulus::Math
{

   /// Default constructor                                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange() noexcept
      : mMin {}
      , mMax {} {}

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
   
#if LANGULUS_SIMD(128BIT)
   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m128& source) noexcept {
      SIMD::Store(source, mArray);
   }

   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m128d& source) noexcept {
      SIMD::Store(source, mArray);
   }

   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m128i& source) noexcept {
      SIMD::Store(source, mArray);
   }
#endif

#if LANGULUS_SIMD(256BIT)
   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m256& source) noexcept {
      SIMD::Store(source, mArray);
   }

   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m256d& source) noexcept {
      SIMD::Store(source, mArray);
   }

   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m256i& source) noexcept {
      SIMD::Store(source, mArray);
   }
#endif

#if LANGULUS_SIMD(512BIT)
   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m512& source) noexcept {
      SIMD::Store(source, mArray);
   }

   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m512d& source) noexcept {
      SIMD::Store(source, mArray);
   }

   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const simde__m512i& source) noexcept {
      SIMD::Store(source, mArray);
   }
#endif

   /// Copy range                                                             
   ///   @param r - the range to copy                                         
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::RangeBased auto& r) noexcept {
      return *new (this) TRange {r};
   }

   /// Copy vector                                                            
   ///   @param v - the vector to copy                                        
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::VectorBased auto& v) noexcept {
      return *new (this) TRange {v};
   }
  
   /// Copy scalar                                                            
   ///   @param s - the scalar value                                          
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::ScalarBased auto& s) noexcept {
      return *new (this) TRange {s};
   }

   /// Set only a specific component                                          
   ///   @param c - the component to overwrite                                
   ///   @return a reference to this vector                                   
   TEMPLATE()
   template<CT::ScalarBased N, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr auto& TME()::operator = (const TVectorComponent<N, D>& c) noexcept {
      return *new (this) TRange {PointType {c}};
   }

   /// Convert any range to text                                              
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      using Flow::Code;
      Code result;
      result += NameOf<TRange>();
      result += Code::Operator::OpenScope;
         result += mMin.operator Code();
         result += ", ";
         result += mMax.operator Code();
      result += Code::Operator::CloseScope;
      return result;
   }

   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Anyness::Text() const {
      return operator Flow::Code();
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::Embrace(const auto& other) noexcept {
      mMin = Min(mMin, other);
      mMax = Max(mMax, other);
      return *this;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::ConstrainBy(const auto& limits) noexcept {
      mMin = Clamp(mMin, limits.mMin, limits.mMax);
      mMax = Clamp(mMax, limits.mMin, limits.mMax);
      return *this;
   }

   TEMPLATE() LANGULUS(INLINED)
   const typename TME()::PointType& TME()::GetMin() const noexcept {
      return mMin;
   }

   TEMPLATE() LANGULUS(INLINED)
   const typename TME()::PointType& TME()::GetMax() const noexcept {
      return mMax;
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
      return Ret {SIMD::Add(lhs.mArray, rhs.mArray)};
   }

   /// Range + Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs.mArray, rhs)};
   }

   /// Range + Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs.mMin + rhs, lhs.mMax + rhs}; //TODO can be optimized further by caching rhs in a register
   }

   /// Scalar + Range                                                         
   constexpr auto operator + (const CT::ScalarBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs.mArray)};
   }

   /// Vector + Range                                                         
   constexpr auto operator + (const CT::VectorBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs + rhs.mMin, lhs + rhs.mMax}; //TODO can be optimized further by caching lhs in a register
   }

   /// Returns the difference of any two ranges                               
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::RangeBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs.mArray, rhs.mArray)};
   }

   /// Range + Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs.mArray, rhs)};
   }

   /// Range + Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs.mMin - rhs, lhs.mMax - rhs}; //TODO can be optimized further by caching rhs in a register
   }

   /// Scalar + Range                                                         
   constexpr auto operator - (const CT::ScalarBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs, rhs.mArray)};
   }

   /// Vector + Range                                                         
   constexpr auto operator - (const CT::VectorBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs - rhs.mMin, lhs - rhs.mMax}; //TODO can be optimized further by caching lhs in a register
   }

   /// Returns the Hadamard product of any two ranges                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::RangeBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs.mArray, rhs.mArray)};
   }

   /// Range * Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs.mArray, rhs)};
   }

   /// Range * Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs.mMin * rhs, lhs.mMax * rhs}; //TODO can be optimized further by caching rhs in a register
   }

   /// Scalar * Range                                                         
   constexpr auto operator * (const CT::ScalarBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs, rhs.mArray)};
   }

   /// Vector * Range                                                         
   constexpr auto operator * (const CT::VectorBased auto& lhs, const CT::RangeBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs * rhs.mMin, lhs * rhs.mMax}; //TODO can be optimized further by caching lhs in a register
   }

   /// Returns the Hadamard division of any two ranges                        
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::RangeBased auto& lhs, const CT::RangeBased auto& rhs) {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs.mArray, rhs.mArray)};
   }

   /// Range / Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs.mArray, rhs)};
   }

   /// Range / Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs.mMin / rhs, lhs.mMax / rhs}; //TODO can be optimized further by caching rhs in a register
   }

   /// Scalar / Range                                                         
   constexpr auto operator / (const CT::ScalarBased auto& lhs, const CT::RangeBased auto& rhs) {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs, rhs.mArray)};
   }

   /// Vector / Range                                                         
   constexpr auto operator / (const CT::VectorBased auto& lhs, const CT::RangeBased auto& rhs) {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {lhs / rhs.mMin, lhs / rhs.mMax}; //TODO can be optimized further by caching lhs in a register
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