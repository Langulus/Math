///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Vectors.hpp"

namespace Langulus::Math
{

   template<CT::ScalarOrVector>
   struct TRange;

   using Range1f = TRange<vec1f>;
   using Range1d = TRange<vec1d>;

   using Range2f = TRange<vec2f>;
   using Range2d = TRange<vec2d>;
   using Range3f = TRange<vec3f>;
   using Range3d = TRange<vec3d>;
   using Range4f = TRange<vec4f>;
   using Range4d = TRange<vec4d>;

   using Range1 = TRange<vec1>;
   using Range2 = TRange<vec2>;
   using Range3 = TRange<vec3>;
   using Range4 = TRange<vec4>;

   using Range1u8 = TRange<vec1u8>;
   using Range1u16 = TRange<vec1u16>;
   using Range1u32 = TRange<vec1u32>;
   using Range1u64 = TRange<vec1u64>;
   using Range1i8 = TRange<vec1i8>;
   using Range1i16 = TRange<vec1i16>;
   using Range1i32 = TRange<vec1i32>;
   using Range1i64 = TRange<vec1i64>;

   using Range2u8 = TRange<vec2u8>;
   using Range2u16 = TRange<vec2u16>;
   using Range2u32 = TRange<vec2u32>;
   using Range2u64 = TRange<vec2u64>;
   using Range2i8 = TRange<vec2i8>;
   using Range2i16 = TRange<vec2i16>;
   using Range2i32 = TRange<vec2i32>;
   using Range2i64 = TRange<vec2i64>;

   using Range3u8 = TRange<vec3u8>;
   using Range3u16 = TRange<vec3u16>;
   using Range3u32 = TRange<vec3u32>;
   using Range3u64 = TRange<vec3u64>;
   using Range3i8 = TRange<vec3i8>;
   using Range3i16 = TRange<vec3i16>;
   using Range3i32 = TRange<vec3i32>;
   using Range3i64 = TRange<vec3i64>;

   using Range4u8 = TRange<vec4u8>;
   using Range4u16 = TRange<vec4u16>;
   using Range4u32 = TRange<vec4u32>;
   using Range4u64 = TRange<vec4u64>;
   using Range4i8 = TRange<vec4i8>;
   using Range4i16 = TRange<vec4i16>;
   using Range4i32 = TRange<vec4i32>;
   using Range4i64 = TRange<vec4i64>;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range                                                                  
   struct Range {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::TRange<Math::vec4>;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range of the same size                                                 
   template<Count S>
   struct RangeOfSize : public Range {
      LANGULUS(CONCRETE) Math::TRange<Math::TVector<Real, S>>;
      LANGULUS_BASES(Range);
      static constexpr Count MemberCount {S};
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range of the same type                                                 
   template<CT::DenseNumber T>
   struct RangeOfType : public Range {
      LANGULUS(CONCRETE) Math::TRange<Math::TVector<T, 4>>;
      LANGULUS_BASES(Range);
      using MemberType = T;
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated range                                                      
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::ScalarOrVector T>
   struct TRange {
      using PointType = T;
      using MemberType = typename T::MemberType;
      static constexpr Count MemberCount = T::MemberCount;
      LANGULUS_BASES(A::RangeOfSize<MemberCount>, A::RangeOfType<MemberType>);

      PointType mMin;
      PointType mMax;

   public:
      constexpr TRange() noexcept = default;

      /// Copy constructor                                                    
      constexpr TRange(const TRange& a) noexcept
         : mMin {a.mMin}
         , mMax {a.mMax} {}

      /// Scalar construction (min == max)                                    
      constexpr TRange(const PointType& minmax) noexcept
         : mMin {minmax}
         , mMax {minmax} {}

      /// Manual construction from min & max                                  
      constexpr TRange(const PointType& min, const PointType& max) noexcept
         : mMin {min}
         , mMax {max} {}

      /// From dense data                                                     
      constexpr TRange(const PointType* a) noexcept
         : TRange {a[0], a[1]} {}

      /// From sparse data                                                    
      constexpr TRange(const PointType* const* a) noexcept
         : TRange {*a[0], *a[1]} {}

      ~TRange() noexcept = default;

      /// Copy operator                                                       
      constexpr TRange& operator = (const TRange&) noexcept = default;

      /// Convert any range to text                                           
      NOD() explicit operator Flow::Code() const {
         Flow::Code result;
         result += MetaOf<TRange>();
         result += Flow::Code::OpenScope;
            result += mMin.operator Flow::Code();
            result += ", ";
            result += mMax.operator Flow::Code();
         result += Flow::Code::CloseScope;
         return result;
      }
      
      /// Arithmetics                                                         
      NOD() friend constexpr TRange operator - (const TRange& me) noexcept {
         return {-me.mMin, -me.mMax};
      }

      NOD() friend constexpr TRange operator + (const TRange& me, const TRange& other) noexcept {
         return {me.mMin + other.mMin, me.mMax + other.mMax};
      }

      NOD() friend constexpr TRange operator - (const TRange& me, const TRange& other) noexcept {
         return {me.mMin - other.mMin, me.mMax - other.mMax};
      }

      NOD() friend constexpr TRange operator * (const TRange& me, const TRange& other) noexcept {
         return {me.mMin * other.mMin, me.mMax * other.mMax};
      }

      NOD() friend constexpr TRange operator / (const TRange& me, const TRange& other) noexcept {
         return {me.mMin / other.mMin, me.mMax / other.mMax};
      }

      friend constexpr void operator += (TRange& me, const TRange& other) noexcept {
         me.mMin += other.mMin;
         me.mMax += other.mMax;
      }

      friend constexpr void operator -= (TRange& me, const TRange& other) noexcept {
         me.mMin -= other.mMin;
         me.mMax -= other.mMax;
      }

      friend constexpr void operator *= (TRange& me, const TRange& other) noexcept {
         me.mMin *= other.mMin;
         me.mMax *= other.mMax;
      }

      friend constexpr void operator /= (TRange& me, const TRange& other) noexcept {
         me.mMin /= other.mMin;
         me.mMax /= other.mMax;
      }

      template<class N>
      constexpr TRange& Embrace(const N& other) noexcept {
         mMin = Min(mMin, other);
         mMax = Max(mMax, other);
         return *this;
      }

      template<class N>
      constexpr TRange& ConstrainBy(const N& limits) noexcept {
         mMin = Clamp(mMin, limits.mMin, limits.mMax);
         mMax = Clamp(mMax, limits.mMin, limits.mMax);
         return *this;
      }

      NOD() constexpr bool operator == (const TRange& a) const noexcept {
         return mMin == a.mMin && mMax == a.mMax;
      }

      NOD() constexpr bool operator != (const TRange& a) const noexcept {
         return !(*this == a);
      }

      NOD() constexpr bool operator >= (const TRange& a) const noexcept {
         return mMin >= a.mMin || mMax >= a.mMax;
      }

      NOD() constexpr bool operator <= (const TRange& a) const noexcept {
         return mMin <= a.mMin || mMax <= a.mMax;
      }

      NOD() constexpr bool operator <  (const TRange& a) const noexcept {
         return mMin < a.mMin || mMax < a.mMax;
      }

      NOD() constexpr bool operator >  (const TRange& a) const noexcept {
         return mMin > a.mMin || mMax > a.mMax;
      }

      NOD() PointType Length() const noexcept {
         return mMax - mMin;
      }

      NOD() PointType Center() const noexcept {
         return mMin + Length() * 0.5f;
      }

      NOD() constexpr bool IsDegenerate() const noexcept {
         return mMin == mMax;
      }

      NOD() constexpr bool Inside(const PointType& a) const noexcept {
         return a >= mMin && a <= mMax;
      }

      NOD() constexpr bool IsInsideHalfClosed(const PointType& x) const noexcept {
         return x >= mMin && x < mMax;
      }

      NOD() constexpr PointType ClampRev(const PointType& pos) const noexcept {
         return pos.ClampRev(mMin, mMax);
      }

      NOD() constexpr PointType Clamp(const PointType& pos) const noexcept {
         return pos.Clamp(mMin, mMax);
      }

      NOD() constexpr TRange operator | (const TRange& a) const noexcept {
         return {
            mMin.Clamp(a.mMin, a.mMax),
            mMax.Clamp(a.mMin, a.mMax)
         };
      }

      constexpr void operator |= (const TRange& a) noexcept {
         *this = *this | a;
      }
   };
   #pragma pack(pop)

} // namespace Langulus::Math
