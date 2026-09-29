///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"
#include <Langulus/CT/Normalized.hpp>
#include <Langulus/CT/Range.hpp>

#define TEMPLATE()   template<CT::Dense T>
#define TME()        TRange<T>


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
}

namespace Langulus
{
   /// An abstract range that always concretizises into the most versatile    
   /// type depending on context. Range4 by default, as it's the most         
   /// versatile type.                                                        
   struct Range {
      using CTTI_Abstract = Yup;
      using CTTI_Concrete = Math::Range4;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range of the same size                                                 
   template<size_t S>
   struct RangeOfSize : Range {
      using CTTI_Concrete  = Math::TRange<Math::TVector<Langulus::Real, S>>;
      using CTTI_Bases     = Range;
      using CTTI_Array     = Yes<S>;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// range of the same type                                                 
   template<CT::Dense T>
   struct RangeOfType : Range {
      using CTTI_Concrete  = Math::TRange<Math::TVector<T, 4>>;
      using CTTI_Typed     = T;
      using CTTI_Bases     = Range;
   };
}

namespace Langulus::Math
{
   ///                                                                        
   ///   Templated range                                                      
   ///                                                                        
   #pragma pack(push, 1)
   TEMPLATE()
   struct TRange {
      static constexpr size_t ScalarCount = ExtentOf<T> * 2;
      static constexpr auto   Default     = T::Default;

      using PointType         = T;
      using ScalarType        = TypeOf<T>;
      using CoalescedType     = TVector<ScalarType, ScalarCount, static_cast<int>(Default)>;
      using PointTypeNotNormalized = TVector<ScalarType, ExtentOf<T>>;

      union {
         // Useful representation for directly feeding to SIMD          
         CoalescedType mMinMax {};

         struct {
            PointType mMin;
            PointType mMax;
         };
      };

   private:
      /// Custom name generator at compile-time for ranges                    
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TRange>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset = 0;

         constexpr auto S = ExtentOf<T>;
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
         for (auto i : SuffixOf<TypeOf<T>>())
            name[offset++] = i;

         return name;
      }

   public:
      using CTTI_Range        = Yup;
      using CTTI_Normalized   = Maybe<CT::Normalized<T>>;
      using CTTI_Typed        = ScalarType;
      using CTTI_Array        = Yes<ScalarCount>;
      using CTTI_Named        = Yes<GenerateToken()>;
      using CTTI_POD          = Maybe<CT::POD<T>>;
      using CTTI_Nullable     = Maybe<CT::Nullable<T>>;
      using CTTI_Members      = Members<&TRange::mMin, &TRange::mMax>;
      using CTTI_Bases        = Types<
         RangeOfSize<(ScalarCount > 1 ? ScalarCount / 2 : 1)>,
         RangeOfType<ScalarType>,
         ScalarType
      >;

   public:
      constexpr TRange() noexcept;
      constexpr TRange(const TRange&) noexcept;
      constexpr TRange(const CT::Vector auto&) noexcept;
      constexpr TRange(const CT::Vector auto&, const CT::Vector auto&) noexcept;
      constexpr TRange(const CT::Scalar auto&) noexcept;
      constexpr TRange(const CT::Scalar auto&, const CT::Scalar auto&) noexcept;
      constexpr TRange(const PointType&, const PointType&) noexcept;
      constexpr TRange(const ScalarType&, const ScalarType&) noexcept;

      TRange(const CT::SIMD auto&) noexcept;
      TRange(Describe&&);

      ///                                                                     
      ///   Assignment                                                        
      ///                                                                     
      constexpr auto operator = (const TRange&) noexcept -> TRange&;
      constexpr auto operator = (const CT::Range  auto&) noexcept -> TRange&;
      constexpr auto operator = (const CT::Vector auto&) noexcept -> TRange&;
      constexpr auto operator = (const CT::Scalar auto&) noexcept -> TRange&;

      template<class N, CT::Dimension D>
      constexpr auto& operator = (const TVectorComponent<N, D>&) noexcept;

      /*explicit operator Annies::Text() const;
      explicit operator Flow::Code() const;*/

      constexpr auto Embrace(const auto&...) noexcept -> TRange&;
      constexpr auto Intersect(const CT::Range auto&) const noexcept -> TRange;

      auto GetMin() const noexcept -> PointType const&;
      auto GetMax() const noexcept -> PointType const&;
      auto Length() const noexcept -> PointTypeNotNormalized;
      auto Center() const noexcept -> PointType;

      constexpr bool IsDegenerate() const noexcept;
      constexpr bool Contains(const PointType&) const noexcept;
      constexpr bool ContainsHalfClosed(const PointType&) const noexcept;
      constexpr auto ClampRev(const PointType&) const noexcept -> PointType;
      constexpr auto Clamp(const PointType&) const noexcept -> PointType;

      constexpr auto operator |  (const TRange&) const noexcept -> TRange;
      constexpr auto operator |= (const TRange&)       noexcept -> TRange&;

      constexpr auto operator [] (size_t)       noexcept -> ScalarType&;
      constexpr auto operator [] (size_t) const noexcept -> ScalarType const&;
   };
   #pragma pack(pop)


   namespace Inner
   {
      template<class LHS, class RHS>
      consteval auto LosslessRange() {
         using L = Decay<LHS>;
         using R = Decay<RHS>;
         if constexpr (CT::Range<L>) {
            if constexpr (CT::Range<R>)
               return (TRange<LosslessVector<typename L::PointType, typename R::PointType>>*) nullptr;
            else
               return (TRange<LosslessVector<typename L::PointType, R>>*) nullptr;
         }
         else {
            if constexpr (CT::Range<R>)
               return (TRange<LosslessVector<L, typename R::PointType>>*) nullptr;
            else
               return (TRange<LosslessVector<L, R>>*) nullptr;
         }
      }
   }

   /// Generate a lossless range type from provided LHS and RHS types         
   ///   @tparam LHS - left hand side, can be scalar/array/vector/range       
   ///   @tparam RHS - right hand side, can be scalar/array/vector/range      
   template<class LHS, class RHS>
   using LosslessRange = Deptr<decltype(Inner::LosslessRange<LHS, RHS>())>;
}

#undef TEMPLATE
#undef TME