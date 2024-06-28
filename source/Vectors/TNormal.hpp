///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TVector.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::Vector T>
      struct TNormal;

      using Normal2      = TNormal<TVector<Real, 2>>;
      using Normal2f     = TNormal<TVector<Float, 2>>;
      using Normal2d     = TNormal<TVector<Double, 2>>;
      using Normal2i     = TNormal<TVector<signed, 2>>;
      using Normal2u     = TNormal<TVector<unsigned, 2>>;
      using Normal2i8    = TNormal<TVector<::std::int8_t, 2>>;
      using Normal2u8    = TNormal<TVector<::std::uint8_t, 2>>;
      using Normal2i16   = TNormal<TVector<::std::int16_t, 2>>;
      using Normal2u16   = TNormal<TVector<::std::uint16_t, 2>>;
      using Normal2i32   = TNormal<TVector<::std::int32_t, 2>>;
      using Normal2u32   = TNormal<TVector<::std::uint32_t, 2>>;
      using Normal2i64   = TNormal<TVector<::std::int64_t, 2>>;
      using Normal2u64   = TNormal<TVector<::std::uint64_t, 2>>;

      using Normal3      = TNormal<TVector<Real, 3>>;
      using Normal3f     = TNormal<TVector<Float, 3>>;
      using Normal3d     = TNormal<TVector<Double, 3>>;
      using Normal3i     = TNormal<TVector<signed, 3>>;
      using Normal3u     = TNormal<TVector<unsigned, 3>>;
      using Normal3i8    = TNormal<TVector<::std::int8_t, 3>>;
      using Normal3u8    = TNormal<TVector<::std::uint8_t, 3>>;
      using Normal3i16   = TNormal<TVector<::std::int16_t, 3>>;
      using Normal3u16   = TNormal<TVector<::std::uint16_t, 3>>;
      using Normal3i32   = TNormal<TVector<::std::int32_t, 3>>;
      using Normal3u32   = TNormal<TVector<::std::uint32_t, 3>>;
      using Normal3i64   = TNormal<TVector<::std::int64_t, 3>>;
      using Normal3u64   = TNormal<TVector<::std::uint64_t, 3>>;

      using Normal4      = TNormal<TVector<Real, 4>>;
      using Normal4f     = TNormal<TVector<Float, 4>>;
      using Normal4d     = TNormal<TVector<Double, 4>>;
      using Normal4i     = TNormal<TVector<signed, 4>>;
      using Normal4u     = TNormal<TVector<unsigned, 4>>;
      using Normal4i8    = TNormal<TVector<::std::int8_t, 4>>;
      using Normal4u8    = TNormal<TVector<::std::uint8_t, 4>>;
      using Normal4i16   = TNormal<TVector<::std::int16_t, 4>>;
      using Normal4u16   = TNormal<TVector<::std::uint16_t, 4>>;
      using Normal4i32   = TNormal<TVector<::std::int32_t, 4>>;
      using Normal4u32   = TNormal<TVector<::std::uint32_t, 4>>;
      using Normal4i64   = TNormal<TVector<::std::int64_t, 4>>;
      using Normal4u64   = TNormal<TVector<::std::uint64_t, 4>>;

      using Normal       = Normal3;
      using Normalf      = Normal3f;
      using Normald      = Normal3d;
      using Normali      = Normal3i;
      using Normalu      = Normal3u;
      using Normali8     = Normal3i8;
      using Normalu8     = Normal3u8;
      using Normali16    = Normal3i16;
      using Normalu16    = Normal3u16;
      using Normali32    = Normal3i32;
      using Normalu32    = Normal3u32;
      using Normali64    = Normal3i64;
      using Normalu64    = Normal3u64;

   } // namespace Langulus::Math

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// normal                                                              
      struct Normal {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Normal;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// normal of the same size                                             
      template<Count S>
      struct NormalOfSize : Normal {
         LANGULUS(CONCRETE) Math::TNormal<Math::TVector<Langulus::Real, S>>;
         LANGULUS_BASES(Normal);

         static constexpr Count MemberCount {S};
         static_assert(MemberCount > 1,
            "Normal size must be greater than one");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// normal of the same type                                             
      template<CT::Number T>
      struct NormalOfType : Normal {
         LANGULUS(CONCRETE) Math::TNormal<Math::TVector<T, 4>>;
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(Normal);

         static_assert(CT::Real<T>,
            "Normal can be only made of real numbers");
      };

   } // namespace Langulus::A
   
   /// Custom name generator at compile-time for normals                      
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TNormal<T>>&&) noexcept {
      using CLASS = Math::TNormal<T>;
      constexpr auto MemberCount = CLASS::MemberCount;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      if constexpr (MemberCount > 4) {
         for (auto i : defaultClassName)
            name[offset++] = i;
         return name;
      }

      // Write prefix                                                   
      for (auto i : "Normal")
         name[offset++] = i;

      // Write size                                                     
      --offset;
      name[offset++] = '0' + MemberCount;

      // Write suffix                                                   
      for (auto i : SuffixOf<TypeOf<T>>())
         name[offset++] = i;
      return name;
   }

   namespace Math
   {

      ///                                                                     
      ///   Templated normal                                                  
      ///                                                                     
      /// It is essentially a vector that gets normalized after any change    
      ///                                                                     
      template<CT::Vector T>
      struct TNormal : T {
         using PointType = T;
         using T::MemberCount;
         using T::T;

         static_assert(MemberCount > 1,
            "Normal size must be greater than one");
         static_assert(CT::Real<TypeOf<T>>,
            "Normal can be only made of real numbers");

         LANGULUS(NAME)  CustomNameOf<TNormal>::Generate();
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(
            A::NormalOfSize<MemberCount>,
            A::NormalOfType<TypeOf<T>>,
            T
         );

         /// Construct a normal from a vector                                 
         ///   @param other - the vector to normalize                         
         LANGULUS(INLINED)
         constexpr TNormal(const T& other)
            : T {other.Normalize()} {}

         /// Manual construction via a variadic head-tail                     
         /// Excessive elements are ignored, missing elements are defaulted   
         template<class T1, class T2, class...TN> LANGULUS(INLINED)
         constexpr TNormal(const T1& t1, const T2& t2, const TN&...tn)
            : T {T {t1, t2, tn...}.Normalize()} {}

         /// Descriptor constructor                                           
         ///   @param describe - the descriptor                               
         TNormal(Describe&& describe)
            : T {::std::forward<Describe>(describe)} {
            const auto l = T::Length();
            if (l == TypeOf<T> {0})
               LANGULUS_THROW(Arithmetic, "Degenerate normal");
            *this *= TypeOf<T> {1} / l;
         }

         /// Convert from any normal to code                                  
         LANGULUS(INLINED)
         explicit operator Flow::Code() const {
            return T::template Serialize<Flow::Code, TNormal>();
         }

         /// Convert from any normal to text                                  
         LANGULUS(INLINED)
         explicit operator Anyness::Text() const {
            return T::template Serialize<Anyness::Text, TNormal>();
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus
