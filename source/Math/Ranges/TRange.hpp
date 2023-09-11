///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
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

   using Range1f = TRange<Vec1f>;
   using Range1d = TRange<Vec1d>;

   using Range2f = TRange<Vec2f>;
   using Range2d = TRange<Vec2d>;
   using Range3f = TRange<Vec3f>;
   using Range3d = TRange<Vec3d>;
   using Range4f = TRange<Vec4f>;
   using Range4d = TRange<Vec4d>;

   using Range1 = TRange<Vec1>;
   using Range2 = TRange<Vec2>;
   using Range3 = TRange<Vec3>;
   using Range4 = TRange<Vec4>;

   using Range1u8 = TRange<Vec1u8>;
   using Range1u16 = TRange<Vec1u16>;
   using Range1u32 = TRange<Vec1u32>;
   using Range1u64 = TRange<Vec1u64>;
   using Range1i8 = TRange<Vec1i8>;
   using Range1i16 = TRange<Vec1i16>;
   using Range1i32 = TRange<Vec1i32>;
   using Range1i64 = TRange<Vec1i64>;

   using Range2u8 = TRange<Vec2u8>;
   using Range2u16 = TRange<Vec2u16>;
   using Range2u32 = TRange<Vec2u32>;
   using Range2u64 = TRange<Vec2u64>;
   using Range2i8 = TRange<Vec2i8>;
   using Range2i16 = TRange<Vec2i16>;
   using Range2i32 = TRange<Vec2i32>;
   using Range2i64 = TRange<Vec2i64>;

   using Range3u8 = TRange<Vec3u8>;
   using Range3u16 = TRange<Vec3u16>;
   using Range3u32 = TRange<Vec3u32>;
   using Range3u64 = TRange<Vec3u64>;
   using Range3i8 = TRange<Vec3i8>;
   using Range3i16 = TRange<Vec3i16>;
   using Range3i32 = TRange<Vec3i32>;
   using Range3i64 = TRange<Vec3i64>;

   using Range4u8 = TRange<Vec4u8>;
   using Range4u16 = TRange<Vec4u16>;
   using Range4u32 = TRange<Vec4u32>;
   using Range4u64 = TRange<Vec4u64>;
   using Range4i8 = TRange<Vec4i8>;
   using Range4i16 = TRange<Vec4i16>;
   using Range4i32 = TRange<Vec4i32>;
   using Range4i64 = TRange<Vec4i64>;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range                                                                  
   struct Range {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::TRange<Math::Vec4>;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range of the same size                                                 
   template<Count S>
   struct RangeOfSize : Range {
      LANGULUS(CONCRETE) Math::TRange<Math::TVector<Real, S>>;
      LANGULUS_BASES(Range);
      static constexpr Count MemberCount {S};
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range of the same type                                                 
   template<CT::DenseNumber T>
   struct RangeOfType : Range {
      LANGULUS(CONCRETE) Math::TRange<Math::TVector<T, 4>>;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(Range);
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
      static constexpr Count MemberCount = T::MemberCount;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(
         A::RangeOfSize<MemberCount>, 
         A::RangeOfType<TypeOf<T>>
      );

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
         result += NameOf<TRange>();
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
