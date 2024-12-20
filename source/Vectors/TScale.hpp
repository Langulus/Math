///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TVector.hpp"


namespace Langulus
{
   namespace Math
   {
      template<CT::VectorBased>
      struct TScale;

      using Scale1      = TScale<TVector<Real, 1, 1>>;
      using Scale1f     = TScale<TVector<Float, 1, 1>>;
      using Scale1d     = TScale<TVector<Double, 1, 1>>;
      using Scale1i     = TScale<TVector<signed, 1, 1>>;
      using Scale1u     = TScale<TVector<unsigned, 1, 1>>;
      using Scale1i8    = TScale<TVector<::std::int8_t, 1, 1>>;
      using Scale1u8    = TScale<TVector<::std::uint8_t, 1, 1>>;
      using Scale1i16   = TScale<TVector<::std::int16_t, 1, 1>>;
      using Scale1u16   = TScale<TVector<::std::uint16_t, 1, 1>>;
      using Scale1i32   = TScale<TVector<::std::int32_t, 1, 1>>;
      using Scale1u32   = TScale<TVector<::std::uint32_t, 1, 1>>;
      using Scale1i64   = TScale<TVector<::std::int64_t, 1, 1>>;
      using Scale1u64   = TScale<TVector<::std::uint64_t, 1, 1>>;

      using Scale2      = TScale<TVector<Real, 2, 1>>;
      using Scale2f     = TScale<TVector<Float, 2, 1>>;
      using Scale2d     = TScale<TVector<Double, 2, 1>>;
      using Scale2i     = TScale<TVector<signed, 2, 1>>;
      using Scale2u     = TScale<TVector<unsigned, 2, 1>>;
      using Scale2i8    = TScale<TVector<::std::int8_t, 2, 1>>;
      using Scale2u8    = TScale<TVector<::std::uint8_t, 2, 1>>;
      using Scale2i16   = TScale<TVector<::std::int16_t, 2, 1>>;
      using Scale2u16   = TScale<TVector<::std::uint16_t, 2, 1>>;
      using Scale2i32   = TScale<TVector<::std::int32_t, 2, 1>>;
      using Scale2u32   = TScale<TVector<::std::uint32_t, 2, 1>>;
      using Scale2i64   = TScale<TVector<::std::int64_t, 2, 1>>;
      using Scale2u64   = TScale<TVector<::std::uint64_t, 2, 1>>;

      using Scale3      = TScale<TVector<Real, 3, 1>>;
      using Scale3f     = TScale<TVector<Float, 3, 1>>;
      using Scale3d     = TScale<TVector<Double, 3, 1>>;
      using Scale3i     = TScale<TVector<signed, 3, 1>>;
      using Scale3u     = TScale<TVector<unsigned, 3, 1>>;
      using Scale3i8    = TScale<TVector<::std::int8_t, 3, 1>>;
      using Scale3u8    = TScale<TVector<::std::uint8_t, 3, 1>>;
      using Scale3i16   = TScale<TVector<::std::int16_t, 3, 1>>;
      using Scale3u16   = TScale<TVector<::std::uint16_t, 3, 1>>;
      using Scale3i32   = TScale<TVector<::std::int32_t, 3, 1>>;
      using Scale3u32   = TScale<TVector<::std::uint32_t, 3, 1>>;
      using Scale3i64   = TScale<TVector<::std::int64_t, 3, 1>>;
      using Scale3u64   = TScale<TVector<::std::uint64_t, 3, 1>>;

      using Scale4      = TScale<TVector<Real, 4, 1>>;
      using Scale4f     = TScale<TVector<Float, 4, 1>>;
      using Scale4d     = TScale<TVector<Double, 4, 1>>;
      using Scale4i     = TScale<TVector<signed, 4, 1>>;
      using Scale4u     = TScale<TVector<unsigned, 4, 1>>;
      using Scale4i8    = TScale<TVector<::std::int8_t, 4, 1>>;
      using Scale4u8    = TScale<TVector<::std::uint8_t, 4, 1>>;
      using Scale4i16   = TScale<TVector<::std::int16_t, 4, 1>>;
      using Scale4u16   = TScale<TVector<::std::uint16_t, 4, 1>>;
      using Scale4i32   = TScale<TVector<::std::int32_t, 4, 1>>;
      using Scale4u32   = TScale<TVector<::std::uint32_t, 4, 1>>;
      using Scale4i64   = TScale<TVector<::std::int64_t, 4, 1>>;
      using Scale4u64   = TScale<TVector<::std::uint64_t, 4, 1>>;

      using Scale       = Scale3;
      using Scalef      = Scale3f;
      using Scaled      = Scale3d;
      using Scalei      = Scale3i;
      using Scaleu      = Scale3u;
      using Scalei8     = Scale3i8;
      using Scaleu8     = Scale3u8;
      using Scalei16    = Scale3i16;
      using Scaleu16    = Scale3u16;
      using Scalei32    = Scale3i32;
      using Scaleu32    = Scale3u32;
      using Scalei64    = Scale3i64;
      using Scaleu64    = Scale3u64;

   } // namespace Langulus::Math

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// size                                                                
      struct Scale {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Scale;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// size of the same size                                               
      template<Count S>
      struct ScaleOfSize : Scale {
         LANGULUS(CONCRETE) Math::TScale<Math::TVector<::Langulus::Real, S, 1>>;
         LANGULUS_BASES(Scale);
         static constexpr Count MemberCount {S};
         static_assert(S > 0, "Scale must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// size of the same type                                               
      template<CT::Number T>
      struct ScaleOfType : Scale {
         LANGULUS(CONCRETE) Math::TScale<Math::TVector<T, 3, 1>>;
         LANGULUS_BASES(Scale);
         LANGULUS(TYPED) T;
      };

   } // namespace Langulus::A

   namespace Math
   {

      ///                                                                     
      ///   Templated size                                                    
      /// Vector specialization that defaults to 1 and is used for scaling    
      ///                                                                     
      template<CT::VectorBased T>
      struct TScale : T {
         using T::MemberCount;
         using T::T;

      private:
         static consteval auto GenerateToken() {
            constexpr auto defaultClassName = RTTI::LastCppNameOf<TScale>();
            ::std::array<char, defaultClassName.size() + 1> name {};
            ::std::size_t offset {};

            if constexpr (MemberCount > 4) {
               for (auto i : defaultClassName)
                  name[offset++] = i;
               return name;
            }

            // Write prefix                                             
            for (auto i : "Scale")
               name[offset++] = i;

            // Write size                                               
            --offset;
            name[offset++] = '0' + MemberCount;

            // Write suffix                                             
            for (auto i : SuffixOf<TypeOf<T>>())
               name[offset++] = i;
            return name;
         }

      public:
         LANGULUS(NAME)  GenerateToken();
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(
            A::ScaleOfSize<MemberCount>,
            A::ScaleOfType<TypeOf<T>>,
            T
         );

         static_assert(T::Default == TypeOf<T> {1},
            "Scaling type does not default to 1");

         /// Convert from any size to code                                    
         NOD() explicit operator Flow::Code() const {
            return T::template Serialize<Flow::Code, TScale>();
         }

         /// Convert from any size to text                                    
         NOD() explicit operator Anyness::Text() const {
            return T::template Serialize<Anyness::Text, TScale>();
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus
