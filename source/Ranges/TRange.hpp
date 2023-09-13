///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"


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

   using Range1  = TRange<Vec1>;
   using Range2  = TRange<Vec2>;
   using Range3  = TRange<Vec3>;
   using Range4  = TRange<Vec4>;

   using Range1u8  = TRange<Vec1u8>;
   using Range1u16 = TRange<Vec1u16>;
   using Range1u32 = TRange<Vec1u32>;
   using Range1u64 = TRange<Vec1u64>;
   using Range1i8  = TRange<Vec1i8>;
   using Range1i16 = TRange<Vec1i16>;
   using Range1i32 = TRange<Vec1i32>;
   using Range1i64 = TRange<Vec1i64>;

   using Range2u8  = TRange<Vec2u8>;
   using Range2u16 = TRange<Vec2u16>;
   using Range2u32 = TRange<Vec2u32>;
   using Range2u64 = TRange<Vec2u64>;
   using Range2i8  = TRange<Vec2i8>;
   using Range2i16 = TRange<Vec2i16>;
   using Range2i32 = TRange<Vec2i32>;
   using Range2i64 = TRange<Vec2i64>;

   using Range3u8  = TRange<Vec3u8>;
   using Range3u16 = TRange<Vec3u16>;
   using Range3u32 = TRange<Vec3u32>;
   using Range3u64 = TRange<Vec3u64>;
   using Range3i8  = TRange<Vec3i8>;
   using Range3i16 = TRange<Vec3i16>;
   using Range3i32 = TRange<Vec3i32>;
   using Range3i64 = TRange<Vec3i64>;

   using Range4u8  = TRange<Vec4u8>;
   using Range4u16 = TRange<Vec4u16>;
   using Range4u32 = TRange<Vec4u32>;
   using Range4u64 = TRange<Vec4u64>;
   using Range4i8  = TRange<Vec4i8>;
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
      constexpr TRange(const TRange&) noexcept;
      constexpr TRange(const PointType&) noexcept;
      constexpr TRange(const PointType&, const PointType&) noexcept;
      constexpr TRange(const PointType*) noexcept;
      constexpr TRange(const PointType* const*) noexcept;
      ~TRange() noexcept = default;

      constexpr TRange& operator = (const TRange&) noexcept = default;

      NOD() explicit operator Flow::Code() const;

      template<class N>
      constexpr TRange& Embrace(const N&) noexcept;

      template<class N>
      constexpr TRange& ConstrainBy(const N&) noexcept;

      NOD() constexpr bool operator == (const TRange&) const noexcept;
      NOD() constexpr bool operator >= (const TRange&) const noexcept;
      NOD() constexpr bool operator <= (const TRange&) const noexcept;
      NOD() constexpr bool operator <  (const TRange&) const noexcept;
      NOD() constexpr bool operator >  (const TRange&) const noexcept;

      NOD() PointType Length() const noexcept;
      NOD() PointType Center() const noexcept;
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool Inside(const PointType&) const noexcept;
      NOD() constexpr bool IsInsideHalfClosed(const PointType&) const noexcept;
      NOD() constexpr PointType ClampRev(const PointType&) const noexcept;
      NOD() constexpr PointType Clamp(const PointType&) const noexcept;

      NOD() constexpr TRange operator | (const TRange&) const noexcept;
      constexpr TRange& operator |= (const TRange&) noexcept;
   };
   #pragma pack(pop)


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   /// Returns an inverted range                                              
   template<CT::ScalarOrVector T>
   NOD() constexpr TRange<T> operator - (const TRange<T>&) noexcept;

   /// Returns the sum of two ranges                                          
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   NOD() auto operator + (const TRange<T1>&, const TRange<T2>&) noexcept;

   /// Returns the difference of two ranges                                   
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   NOD() auto operator - (const TRange<T1>&, const TRange<T2>&) noexcept;

   /// Returns the product of two ranges                                      
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   NOD() auto operator * (const TRange<T1>&, const TRange<T2>&) noexcept;

   /// Returns the division of two ranges                                     
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   NOD() auto operator / (const TRange<T1>&, const TRange<T2>&);


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   auto& operator += (TRange<T1>&, const TRange<T2>&) noexcept;

   /// Subtract                                                               
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   auto& operator -= (TRange<T1>&, const TRange<T2>&) noexcept;

   /// Multiply                                                               
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   auto& operator *= (TRange<T1>&, const TRange<T2>&) noexcept;

   /// Divide                                                                 
   template<CT::ScalarOrVector T1, CT::ScalarOrVector T2>
   auto& operator /= (TRange<T1>&, const TRange<T2>&);

} // namespace Langulus::Math
