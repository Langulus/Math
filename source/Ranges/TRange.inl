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

#define TEMPLATE()   template<CT::Dense T>
#define TME()        TRange<T>


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

   /// Construct the range sequentially, like so:                             
   /// minX, minY, minZ..., maxX, maxY, maxZ...                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const CT::Vector auto& other) noexcept {
      SIMD::Convert<0>(DesemCast(other), mArray);
   }

   /// Construct the range from scalar                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const CT::Scalar auto& other) noexcept {
      SIMD::Convert<0>(DesemCast(other), mArray);
   }

   /// Create range from a min and a max vectors                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const PointType& min, const PointType& max) noexcept
      : mMin {min}
      , mMax {max} {}

   /// Create range from a min and a max scalars                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TRange(const MemberType& min, const MemberType& max) noexcept
      : mMin {min}
      , mMax {max} {}
   
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
   
   /// Construct from a descriptor                                            
   ///   @param describe - the descriptor to scan                             
   TEMPLATE()
   TME()::TRange(Describe&& describe) {
      LANGULUS_ASSUME(UserAssumes, *describe,
         "Empty descriptor for TRange");

      // Attempt initializing without any conversion                    
      auto initialized = describe->ExtractData(mArray);
      if (not initialized) {
         // Attempt converting anything to T                            
         initialized = describe->ExtractDataAs(mArray);
      }

      switch (initialized) {
      case 0:
         // Nothing was initialized. This is always an error in the     
         // context of the descriptor-constructor. If descriptor was    
         // empty, the default constructor would've been explicitly     
         // called, instead of this one. This way we can differentiate  
         // whether or not a vector object was successfully initialized.
         LANGULUS_OOPS(Construct, "Bad TRange descriptor", 
            ", nothing was initialized: ", *describe);
      case 1:
         // Only one provided element is handled as scalar constructor  
         // Copy first element in array to the rest                     
         for (; initialized < MemberCount; ++initialized)
            mArray[initialized] = mArray[0];
         break;
      default:
         // Initialize unavailable elements to the vector's default     
         for (; initialized < MemberCount; ++initialized)
            mArray[initialized] = T::Default;
         break;
      }
   }

   /// Copy range                                                             
   ///   @param r - the range to copy                                         
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::RangeBased auto& r) noexcept {
      return *new (this) TRange {DesemCast(r)};
   }

   /// Copy vector                                                            
   ///   @param v - the vector to copy                                        
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::VectorBased auto& v) noexcept {
      return *new (this) TRange {DesemCast(v)};
   }
  
   /// Copy scalar                                                            
   ///   @param s - the scalar value                                          
   ///   @return a reference to this range                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::ScalarBased auto& s) noexcept {
      return *new (this) TRange {DesemCast(s)};
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
   
   /// Get Nth range element                                                  
   ///   @attention assumes index is in range's MemberCount limits            
   ///   @param a - index of the element                                      
   ///      0,   1,   2,   ... CountOf<T> + 0, CountOf<T> + 1, CountOf<T> + 2 
   ///      minX minY minZ ... maxX            maxY            maxZ ...       
   ///   @returns a reference to the component                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr TypeOf<T>& TME()::operator [] (const Offset a) noexcept {
      return mArray[a];
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr const TypeOf<T>& TME()::operator [] (const Offset a) const noexcept {
      return mArray[a];
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