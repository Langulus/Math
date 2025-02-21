///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TRange.hpp"
#include "../Vectors/TVector.inl"
#include <Langulus/Anyness/Construct.hpp>

#define TEMPLATE()   template<CT::Dense T>
#define TME()        TRange<T>


namespace Langulus::Math
{

   /// Copy constructor                                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const TRange& a) noexcept {
      SIMD::Convert<0>(a.mMinMax, mMinMax);
   }

   /// Construct the range sequentially, like so:                             
   /// minX, minY, minZ..., maxX, maxY, maxZ...                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const CT::Vector auto& other) noexcept {
      SIMD::Convert<0>(DeintCast(other), mMinMax);

      if constexpr (CT::Normalized<T>) {
         mMin = mMin.Normalize();
         mMax = mMax.Normalize();
      }
   }

   /// Construct the range from scalar                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const CT::Scalar auto& other) noexcept {
      SIMD::Convert<0>(DeintCast(other), mMinMax);

      if constexpr (CT::Normalized<T>) {
         mMin = mMin.Normalize();
         mMax = mMax.Normalize();
      }
   }

   /// Create range from a min and a max vectors                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType& min, const PointType& max) noexcept {
      for (Count i = 0; i < CountOf<T>; ++i) {
         mMinMax[i] = min.all[i];
         mMinMax[i + CountOf<T>] = max.all[i];
      }
   }

   /// Create range from a min and a max scalars                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const MemberType& min, const MemberType& max) noexcept {
      for (Count i = 0; i < CountOf<T>; ++i) {
         mMinMax[i] = min;
         mMinMax[i + CountOf<T>] = max;
      }

      if constexpr (CT::Normalized<T>) {
         mMin = mMin.Normalize();
         mMax = mMax.Normalize();
      }
   }
   
   /// Create from registers                                                  
   TEMPLATE() LANGULUS(INLINED)
   TME()::TRange(const CT::SIMD auto& source) noexcept {
      SIMD::Store(source, mMinMax);

      if constexpr (CT::Normalized<T>) {
         mMin = mMin.Normalize();
         mMax = mMax.Normalize();
      }
   }
   
   /// Construct from a descriptor                                            
   ///   @param describe - the descriptor to scan                             
   TEMPLATE()
   TME()::TRange(Describe&& describe) {
      LANGULUS_ASSUME(UserAssumes, *describe,
         "Empty descriptor for TRange");

      if (describe->CastsTo<A::Range>()) {
         mMin = Describe {describe->GetMember(*describe->GetType()->GetMember({}, {}, 0), 0)};
         mMax = Describe {describe->GetMember(*describe->GetType()->GetMember({}, {}, 1), 0)};
         return;
      }
      else if (describe->CastsTo<A::Vector>() and describe->GetCount() == 2) {
         mMin = Describe {describe->GetElement(0)};
         mMax = Describe {describe->GetElement(1)};
         return;
      }
      else if (describe->CastsTo<A::Number>()) {
         mMinMax = {describe.Forward()};

         if constexpr (CT::Normalized<T>) {
            mMin = mMin.Normalize();
            mMax = mMax.Normalize();
         }
         return;
      }

      // Nothing was initialized. This is always an error in the        
      // context of the descriptor-constructor. If descriptor was       
      // empty, the default constructor would've been explicitly        
      // called, instead of this one. This way we can differentiate     
      // whether or not a vector object was successfully initialized.   
      LANGULUS_OOPS(Construct, "Bad TRange descriptor", 
         ", nothing was initialized: ", *describe);
   }

   /// Copy range                                                             
   ///   @param r - the range to copy                                         
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator = (const TRange& r) noexcept -> TRange& {
      return *new (this) TRange {r};
   }

   /// Copy range                                                             
   ///   @param r - the range to copy                                         
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator = (const CT::RangeBased auto& r) noexcept -> TRange& {
      return *new (this) TRange {DeintCast(r)};
   }

   /// Copy vector                                                            
   ///   @param v - the vector to copy                                        
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator = (const CT::VectorBased auto& v) noexcept -> TRange& {
      return *new (this) TRange {DeintCast(v)};
   }
  
   /// Copy scalar                                                            
   ///   @param s - the scalar value                                          
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator = (const CT::ScalarBased auto& s) noexcept -> TRange& {
      return *new (this) TRange {DeintCast(s)};
   }

   /// Set only a specific component                                          
   ///   @param c - the component to overwrite                                
   ///   @return a reference to this vector                                   
   TEMPLATE() template<CT::ScalarBased N, CT::Dimension D> LANGULUS(INLINED)
   constexpr auto& TME()::operator = (const TVectorComponent<N, D>& c) noexcept {
      return *new (this) TRange {PointType {c}};
   }

   /// Serialize to code                                                      
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

   /// Serialize to text                                                      
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Anyness::Text() const {
      using Anyness::Text;
      Text result;
      result += NameOf<TRange>();
      result += "(";
      if constexpr (MemberCount == 2) {
         Anyness::MakeBlock(mMin.all).Serialize(result);
         result += "; ";
         Anyness::MakeBlock(mMax.all).Serialize(result);
      }
      else {
         result += "(";
            Anyness::MakeBlock(mMin.all).Serialize(result);
         result += "); (";
            Anyness::MakeBlock(mMax.all).Serialize(result);
         result += ")";
      }
      result += ")";
      return result;
   }

   /// Incorporate a point into the range                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Embrace(const auto&...other) noexcept -> TRange& {
      ((mMin = Math::Min(mMin, other)),...);
      ((mMax = Math::Max(mMax, other)),...);
      return *this;
   }

   /// Get the intersection with another range                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Intersect(const CT::RangeBased auto& limits) const noexcept -> TRange {
      return {
         Math::Clamp(mMin, limits.mMin, limits.mMax),
         Math::Clamp(mMax, limits.mMin, limits.mMax)
      };
   }

   /// Get the minimum value                                                  
   TEMPLATE() LANGULUS(INLINED)
   auto TME()::GetMin() const noexcept -> const PointType& {
      return mMin;
   }

   /// Get the maximum value                                                  
   TEMPLATE() LANGULUS(INLINED)
   auto TME()::GetMax() const noexcept -> const PointType& {
      return mMax;
   }

   /// Get the difference between the maximum and the minimum                 
   TEMPLATE() LANGULUS(INLINED)
   auto TME()::Length() const noexcept -> PointTypeNotNormalized {
      if constexpr (CT::Normalized<T>)
         return PointTypeNotNormalized {mMax} - PointTypeNotNormalized {mMin};
      else
         return mMax - mMin;
   }

   /// Get the range's center                                                 
   TEMPLATE() LANGULUS(INLINED)
   auto TME()::Center() const noexcept -> PointType {
      return mMin + Length() * 0.5f;
   }

   /// Check if the range is degenerate (has zero length)                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsDegenerate() const noexcept {
      return mMin == mMax;
   }

   /// Check if a point resides inside the closed interval                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::Contains(const PointType& a) const noexcept {
      return a >= mMin and a <= mMax;
   }

   /// Check if a point resides inside the half-closed interval               
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::ContainsHalfClosed(const PointType& x) const noexcept {
      return x >= mMin and x < mMax;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::ClampRev(const PointType& pos) const noexcept -> PointType {
      return pos.ClampRev(mMin, mMax);
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Clamp(const PointType& pos) const noexcept -> PointType {
      return pos.Clamp(mMin, mMax);
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator | (const TME()& a) const noexcept -> TRange {
      return {
         mMin.Clamp(a.mMin, a.mMax),
         mMax.Clamp(a.mMin, a.mMax)
      };
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator |= (const TME()& a) noexcept -> TRange& {
      *this = *this | a;
   }
   
   /// Get Nth range element                                                  
   ///   @attention assumes index is in range's MemberCount limits            
   ///   @param a - index of the element                                      
   ///      0,   1,   2,   ... CountOf<T> + 0, CountOf<T> + 1, CountOf<T> + 2 
   ///      minX minY minZ ... maxX            maxY            maxZ ...       
   ///   @returns a reference to the component                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator [] (const Offset a) noexcept -> MemberType& {
      return mMinMax[a];
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator [] (const Offset a) const noexcept -> const MemberType& {
      return mMinMax[a];
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
      return Ret {SIMD::Add(lhs.mMinMax, rhs.mMinMax)};
   }

   /// Range + Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs.mMinMax, rhs)};
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
      return Ret {SIMD::Add(lhs, rhs.mMinMax)};
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
      return Ret {SIMD::Subtract(lhs.mMinMax, rhs.mMinMax)};
   }

   /// Range + Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs.mMinMax, rhs)};
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
      return Ret {SIMD::Subtract(lhs, rhs.mMinMax)};
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
      return Ret {SIMD::Multiply(lhs.mMinMax, rhs.mMinMax)};
   }

   /// Range * Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs.mMinMax, rhs)};
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
      return Ret {SIMD::Multiply(lhs, rhs.mMinMax)};
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
      return Ret {SIMD::Divide(lhs.mMinMax, rhs.mMinMax)};
   }

   /// Range / Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) {
      using Ret = LosslessRange<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs.mMinMax, rhs)};
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
      return Ret {SIMD::Divide(lhs, rhs.mMinMax)};
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
   constexpr auto& operator += (CT::RangeBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      lhs.mMinMax += rhs.mMinMax;
      return lhs;
   }

   constexpr auto& operator += (CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using R = Deref<decltype(lhs)>;
      lhs.mMinMax += R {rhs, rhs};
      return lhs;
   }

   constexpr auto& operator += (CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      lhs.mMinMax += rhs;
      return lhs;
   }

   /// Subtract                                                               
   constexpr auto& operator -= (CT::RangeBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      lhs.mMinMax -= rhs.mMinMax;
      return lhs;
   }

   constexpr auto& operator -= (CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using R = Deref<decltype(lhs)>;
      lhs.mMinMax -= R {rhs, rhs};
      return lhs;
   }

   constexpr auto& operator -= (CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      lhs.mMinMax -= rhs;
      return lhs;
   }

   /// Multiply                                                               
   constexpr auto& operator *= (CT::RangeBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      lhs.mMinMax *= rhs.mMinMax;
      return lhs;
   }

   constexpr auto& operator *= (CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using R = Deref<decltype(lhs)>;
      lhs.mMinMax *= R {rhs, rhs};
      return lhs;
   }

   constexpr auto& operator *= (CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      lhs.mMinMax *= rhs;
      return lhs;
   }

   /// Divide                                                                 
   constexpr auto& operator /= (CT::RangeBased auto& lhs, const CT::RangeBased  auto& rhs) {
      lhs.mMinMax /= rhs.mMinMax;
      return lhs;
   }

   constexpr auto& operator /= (CT::RangeBased auto& lhs, const CT::VectorBased auto& rhs) {
      using R = Deref<decltype(lhs)>;
      lhs.mMinMax /= R {rhs, rhs};
      return lhs;
   }

   constexpr auto& operator /= (CT::RangeBased auto& lhs, const CT::ScalarBased auto& rhs) {
      lhs.mMinMax /= rhs;
      return lhs;
   }


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   constexpr auto operator <  (const CT::RangeBased  auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs.Length() < rhs.Length();
   }

   constexpr auto operator <  (const CT::RangeBased  auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return lhs.mMax < rhs;
   }

   constexpr auto operator <  (const CT::ScalarBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs < rhs.mMin;
   }

   /// Bigger                                                                 
   constexpr auto operator >  (const CT::RangeBased  auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs.Length() > rhs.Length();
   }

   constexpr auto operator >  (const CT::RangeBased  auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return lhs.mMin > rhs;
   }

   constexpr auto operator >  (const CT::ScalarBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs > rhs.mMax;
   }

   /// Bigger or equal                                                        
   constexpr auto operator >= (const CT::RangeBased  auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs.Length() >= rhs.Length();
   }

   constexpr auto operator >= (const CT::RangeBased  auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return lhs.mMin >= rhs;
   }

   constexpr auto operator >= (const CT::ScalarBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs >= rhs.mMax;
   }

   /// Smaller or equal                                                       
   constexpr auto operator <= (const CT::RangeBased  auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs.Length() <= rhs.Length();
   }

   constexpr auto operator <= (const CT::RangeBased  auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return lhs.mMax <= rhs;
   }

   constexpr auto operator <= (const CT::ScalarBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return lhs <= rhs.mMin;
   }


   ///                                                                        
   /// Equal                                                                  
   ///                                                                        
   /// Range == Range                                                         
   constexpr auto operator == (const CT::RangeBased  auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return SIMD::Equals(lhs.mMinMax, rhs.mMinMax);
   }

   /// Range == Scalar                                                        
   constexpr auto operator == (const CT::RangeBased  auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::Equals(lhs.mMinMax, rhs);
   }

   /// Scalar == Range                                                        
   constexpr auto operator == (const CT::ScalarBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return SIMD::Equals(rhs.mMinMax, lhs);
   }

   /// Range == Vector                                                        
   constexpr auto operator == (const CT::RangeBased  auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using R = Deref<decltype(lhs)>;
      return SIMD::Equals(lhs.mMinMax, typename R::CoalescedType {rhs});
   }

   /// Vector == Range                                                        
   constexpr auto operator == (const CT::VectorBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return rhs == lhs;
   }

   constexpr auto operator != (const CT::RangeBased  auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return not (lhs == rhs);
   }

   constexpr auto operator != (const CT::RangeBased  auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return not (lhs == rhs);
   }

   constexpr auto operator != (const CT::ScalarBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return not (rhs == lhs);
   }

   constexpr auto operator != (const CT::RangeBased  auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return not (lhs == rhs);
   }

   constexpr auto operator != (const CT::VectorBased auto& lhs, const CT::RangeBased  auto& rhs) noexcept {
      return not (rhs == lhs);
   }

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME


namespace Langulus::Ranges
{

   using Math::Range3;
   using Math::Vec3;

   //TODO use infinities instead of big numbers
   constexpr Range3 In      { -1, +1 };
   constexpr Range3 On      { +1, +1 };
   constexpr Range3 Under   { {-1, -1, -1},    {+1, -1, +1} };
   constexpr Range3 Above   { {-1, +1, -1},    {+1, +1000, +1} };
   constexpr Range3 Below   { {-1, -1000, -1}, {+1, -1, +1} };
   constexpr Range3 Center  { 0, 0 };
   constexpr Range3 Middle  { -0.5, +0.5 };
   constexpr Range3 Rear    { {-1, -1, -1},    {+1, +1, -1} };
   constexpr Range3 Behind  { {-1, -1, -1000}, {+1, +1, -1} };
   constexpr Range3 Front   { {-1, -1, 1},     {+1, +1, 1} };
   constexpr Range3 Ahead   { {-1, -1, 1},     {+1, +1, 1000} };
   constexpr Range3 Left    { {-1000, -1, -1}, {-1, +1, +1} };
   constexpr Range3 Right   { {1, -1, -1},     {1000, +1, +1} };

} // namespace Langulus::Ranges

LANGULUS_DEFINE_CONSTANT(RangeIn, ::Langulus::Ranges::In,
   "Ranges::In", "A canonical 'in' range")
LANGULUS_DEFINE_CONSTANT(RangeOn, ::Langulus::Ranges::On,
   "Ranges::On", "A canonical 'on the surface' range")
LANGULUS_DEFINE_CONSTANT(RangeUnder, ::Langulus::Ranges::Under,
   "Ranges::Under", "A canonical 'on the underside' range")
LANGULUS_DEFINE_CONSTANT(RangeAbove, ::Langulus::Ranges::Above,
   "Ranges::Above", "A canonical 'above and beyond' range")
LANGULUS_DEFINE_CONSTANT(RangeBelow, ::Langulus::Ranges::Below,
   "Ranges::Below", "A canonical 'below and beyond' range")
LANGULUS_DEFINE_CONSTANT(RangeCenter, ::Langulus::Ranges::Center,
   "Ranges::Center", "A canonical center range (not really a range)")
LANGULUS_DEFINE_CONSTANT(RangeMiddle, ::Langulus::Ranges::Middle,
   "Ranges::Middle", "A canonical 'middle' range")
LANGULUS_DEFINE_CONSTANT(RangeRear, ::Langulus::Ranges::Rear,
   "Ranges::Rear", "A canonical 'on the rear surface' range")
LANGULUS_DEFINE_CONSTANT(RangeBehind, ::Langulus::Ranges::Behind,
   "Ranges::Behind", "A canonical 'behind and beyond' range")
LANGULUS_DEFINE_CONSTANT(RangeFront, ::Langulus::Ranges::Front,
   "Ranges::Front", "A canonical 'on the front surface' range")
LANGULUS_DEFINE_CONSTANT(RangeAhead, ::Langulus::Ranges::Ahead,
   "Ranges::Ahead", "A canonical 'ahead and beyond' range")
LANGULUS_DEFINE_CONSTANT(RangeLeft, ::Langulus::Ranges::Left,
   "Ranges::Left", "A canonical 'on the left and beyond' range")
LANGULUS_DEFINE_CONSTANT(RangeRight, ::Langulus::Ranges::Right,
   "Ranges::Right", "A canonical 'on the right and beyond' range")
