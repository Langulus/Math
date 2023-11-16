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

#define TEMPLATE() template<CT::Dense T>
#define TME() TRange<T>


namespace Langulus::Math
{

   TEMPLATE() struct TRange;

   using Range1f   = TRange<Vec1f>;
   using Range1d   = TRange<Vec1d>;
                   
   using Range2f   = TRange<Vec2f>;
   using Range2d   = TRange<Vec2d>;
   using Range3f   = TRange<Vec3f>;
   using Range3d   = TRange<Vec3d>;
   using Range4f   = TRange<Vec4f>;
   using Range4d   = TRange<Vec4d>;
                   
   using Range1    = TRange<Vec1>;
   using Range2    = TRange<Vec2>;
   using Range3    = TRange<Vec3>;
   using Range4    = TRange<Vec4>;

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
   template<CT::Dense T>
   struct RangeOfType : Range {
      LANGULUS(CONCRETE) Math::TRange<Math::TVector<T, 4>>;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(Range);
   };

} // namespace Langulus::A

namespace Langulus
{
   namespace CT
   {
      /// Anything that has the range trait                                   
      template<class... T>
      concept RangeBased = ((Decay<T>::CTTI_RangeTrait) and ...);
   }

   /// Custom name generator at compile-time for ranges                       
   TEMPLATE()
   constexpr auto CustomName(Of<Math::TME()>&&) noexcept {
      constexpr auto defaultClassName = RTTI::LastCppNameOf<Math::TME()>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      constexpr auto S = Math::TME()::MemberCount;
      if constexpr (S > 4) {
         for (auto i : defaultClassName)
            name[offset++] = i;
         return name;
      }

      // Write prefix                                                   
      for (auto i : "Range")
         name[offset++] = i;

      // Write size                                                     
      --offset;
      name[offset++] = '0' + S;

      // Write suffix                                                   
      for (auto i : SuffixOf<TypeOf<Math::TME()>>())
         name[offset++] = i;

      return name;
   }
}

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated range                                                      
   ///                                                                        
   #pragma pack(push, 1)
   TEMPLATE()
   struct TRange {
      using PointType = T;
      using MemberType = TypeOf<T>;
      static constexpr Count MemberCount = CountOf<T>;

      union {
         struct {
            PointType mMin;
            PointType mMax;
         } mBounds {};

         // Useful representation for directly feeding to SIMD          
         MemberType mArray[MemberCount * 2];
      };

   public:
      LANGULUS(NAME)  CustomNameOf<TRange>::Generate();
      LANGULUS(TYPED) MemberType;
      LANGULUS_BASES(
         A::RangeOfSize<MemberCount>,
         A::RangeOfType<MemberType>
      );

      // Make TRange match the CT::RangeBased concept                   
      static constexpr bool CTTI_RangeTrait = true;

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


   /// Generate a lossless range type from provided LHS and RHS types         
   ///   @tparam LHS - left hand side, can be scalar/array/vector/range       
   ///   @tparam RHS - right hand side, can be scalar/array/vector/range      
   template<class LHS, class RHS>
   using LosslessRange = TRange<LosslessVector<
      typename LHS::PointType, typename RHS::PointType>>;


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   /// Returns an inverted range                                              
   NOD() constexpr auto operator - (const CT::RangeBased auto&) noexcept;

   /// Returns the sum of two ranges                                          
   NOD() constexpr auto operator + (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator + (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator + (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator + (const CT::RangeBased  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator + (const CT::VectorBased auto&, const CT::RangeBased  auto&) noexcept;

   /// Returns the difference of two ranges                                   
   NOD() constexpr auto operator - (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator - (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator - (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator - (const CT::RangeBased  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator - (const CT::VectorBased auto&, const CT::RangeBased  auto&) noexcept;

   /// Returns the product of two ranges                                      
   NOD() constexpr auto operator * (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator * (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator * (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator * (const CT::RangeBased  auto&, const CT::VectorBased auto&) noexcept;
   NOD() constexpr auto operator * (const CT::VectorBased auto&, const CT::RangeBased  auto&) noexcept;

   /// Returns the division of two ranges                                     
   NOD() constexpr auto operator / (const CT::RangeBased  auto&, const CT::RangeBased  auto&);
   NOD() constexpr auto operator / (const CT::RangeBased  auto&, const CT::DenseScalar auto&);
   NOD() constexpr auto operator / (const CT::DenseScalar auto&, const CT::RangeBased  auto&);
   NOD() constexpr auto operator / (const CT::RangeBased  auto&, const CT::VectorBased auto&);
   NOD() constexpr auto operator / (const CT::VectorBased auto&, const CT::RangeBased  auto&);


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   constexpr auto& operator += (CT::RangeBased auto&, const CT::RangeBased  auto&) noexcept;
   constexpr auto& operator += (CT::RangeBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator += (CT::RangeBased auto&, const CT::DenseScalar auto&) noexcept;

   /// Subtract                                                               
   constexpr auto& operator -= (CT::RangeBased auto&, const CT::RangeBased  auto&) noexcept;
   constexpr auto& operator -= (CT::RangeBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator -= (CT::RangeBased auto&, const CT::DenseScalar auto&) noexcept;

   /// Multiply                                                               
   constexpr auto& operator *= (CT::RangeBased auto&, const CT::RangeBased  auto&) noexcept;
   constexpr auto& operator *= (CT::RangeBased auto&, const CT::VectorBased auto&) noexcept;
   constexpr auto& operator *= (CT::RangeBased auto&, const CT::DenseScalar auto&) noexcept;

   /// Divide                                                                 
   constexpr auto& operator /= (CT::RangeBased auto&, const CT::RangeBased  auto&);
   constexpr auto& operator /= (CT::RangeBased auto&, const CT::VectorBased auto&);
   constexpr auto& operator /= (CT::RangeBased auto&, const CT::DenseScalar auto&);


   ///                                                                        
   ///   Comparing                                                            
   ///                                                                        
   /// Smaller                                                                
   NOD() constexpr auto operator <  (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;

   /// Bigger                                                                 
   NOD() constexpr auto operator >  (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator >  (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;

   /// Bigger or equal                                                        
   NOD() constexpr auto operator >= (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator >= (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;

   /// Smaller or equal                                                       
   NOD() constexpr auto operator <  (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator <  (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;

   /// Equal                                                                  
   NOD() constexpr auto operator == (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator == (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator == (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;

   NOD() constexpr auto operator != (const CT::RangeBased  auto&, const CT::RangeBased  auto&) noexcept;
   NOD() constexpr auto operator != (const CT::RangeBased  auto&, const CT::DenseScalar auto&) noexcept;
   NOD() constexpr auto operator != (const CT::DenseScalar auto&, const CT::RangeBased  auto&) noexcept;

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME