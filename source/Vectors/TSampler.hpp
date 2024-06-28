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
   
      template<CT::VectorBased T>
      struct TSampler;

      using Sampler1    = TSampler<TVector<Real, 1>>;
      using Sampler1f   = TSampler<TVector<Float, 1>>;
      using Sampler1d   = TSampler<TVector<Double, 1>>;
      using Sampler1i   = TSampler<TVector<signed, 1>>;
      using Sampler1u   = TSampler<TVector<unsigned, 1>>;
      using Sampler1i8  = TSampler<TVector<::std::int8_t, 1>>;
      using Sampler1u8  = TSampler<TVector<::std::uint8_t, 1>>;
      using Sampler1i16 = TSampler<TVector<::std::int16_t, 1>>;
      using Sampler1u16 = TSampler<TVector<::std::uint16_t, 1>>;
      using Sampler1i32 = TSampler<TVector<::std::int32_t, 1>>;
      using Sampler1u32 = TSampler<TVector<::std::uint32_t, 1>>;
      using Sampler1i64 = TSampler<TVector<::std::int64_t, 1>>;
      using Sampler1u64 = TSampler<TVector<::std::uint64_t, 1>>;

      using Sampler2    = TSampler<TVector<Real, 2>>;
      using Sampler2f   = TSampler<TVector<Float, 2>>;
      using Sampler2d   = TSampler<TVector<Double, 2>>;
      using Sampler2i   = TSampler<TVector<signed, 2>>;
      using Sampler2u   = TSampler<TVector<unsigned, 2>>;
      using Sampler2i8  = TSampler<TVector<::std::int8_t, 2>>;
      using Sampler2u8  = TSampler<TVector<::std::uint8_t, 2>>;
      using Sampler2i16 = TSampler<TVector<::std::int16_t, 2>>;
      using Sampler2u16 = TSampler<TVector<::std::uint16_t, 2>>;
      using Sampler2i32 = TSampler<TVector<::std::int32_t, 2>>;
      using Sampler2u32 = TSampler<TVector<::std::uint32_t, 2>>;
      using Sampler2i64 = TSampler<TVector<::std::int64_t, 2>>;
      using Sampler2u64 = TSampler<TVector<::std::uint64_t, 2>>;

      using Sampler3    = TSampler<TVector<Real, 3>>;
      using Sampler3f   = TSampler<TVector<Float, 3>>;
      using Sampler3d   = TSampler<TVector<Double, 3>>;
      using Sampler3i   = TSampler<TVector<signed, 3>>;
      using Sampler3u   = TSampler<TVector<unsigned, 3>>;
      using Sampler3i8  = TSampler<TVector<::std::int8_t, 3>>;
      using Sampler3u8  = TSampler<TVector<::std::uint8_t, 3>>;
      using Sampler3i16 = TSampler<TVector<::std::int16_t, 3>>;
      using Sampler3u16 = TSampler<TVector<::std::uint16_t, 3>>;
      using Sampler3i32 = TSampler<TVector<::std::int32_t, 3>>;
      using Sampler3u32 = TSampler<TVector<::std::uint32_t, 3>>;
      using Sampler3i64 = TSampler<TVector<::std::int64_t, 3>>;
      using Sampler3u64 = TSampler<TVector<::std::uint64_t, 3>>;

      using Sampler4    = TSampler<TVector<Real, 4>>;
      using Sampler4f   = TSampler<TVector<Float, 4>>;
      using Sampler4d   = TSampler<TVector<Double, 4>>;
      using Sampler4i   = TSampler<TVector<signed, 4>>;
      using Sampler4u   = TSampler<TVector<unsigned, 4>>;
      using Sampler4i8  = TSampler<TVector<::std::int8_t, 4>>;
      using Sampler4u8  = TSampler<TVector<::std::uint8_t, 4>>;
      using Sampler4i16 = TSampler<TVector<::std::int16_t, 4>>;
      using Sampler4u16 = TSampler<TVector<::std::uint16_t, 4>>;
      using Sampler4i32 = TSampler<TVector<::std::int32_t, 4>>;
      using Sampler4u32 = TSampler<TVector<::std::uint32_t, 4>>;
      using Sampler4i64 = TSampler<TVector<::std::int64_t, 4>>;
      using Sampler4u64 = TSampler<TVector<::std::uint64_t, 4>>;

      using Sampler     = Sampler2;
      using Samplerf    = Sampler2f;
      using Samplerd    = Sampler2d;
      using Sampleri    = Sampler2i;
      using Sampleru    = Sampler2u;
      using Sampleri8   = Sampler2i8;
      using Sampleru8   = Sampler2u8;
      using Sampleri16  = Sampler2i16;
      using Sampleru16  = Sampler2u16;
      using Sampleri32  = Sampler2i32;
      using Sampleru32  = Sampler2u32;
      using Sampleri64  = Sampler2i64;
      using Sampleru64  = Sampler2u64;

   } // namespace Langulus::Math

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// sampler                                                             
      struct Sampler {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Sampler3;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// sampler of the same size                                            
      template<Count S>
      struct SamplerOfSize : Sampler {
         LANGULUS(CONCRETE) Math::TSampler<Math::TVector<Langulus::Real, S>>;
         LANGULUS_BASES(Sampler);
         static constexpr Count MemberCount {S};
         static_assert(S > 0, "Normal size must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// sampler of the same type                                            
      template<CT::Number T>
      struct SamplerOfType : Sampler {
         LANGULUS(CONCRETE) Math::TSampler<Math::TVector<T, 3>>;
         LANGULUS(TYPED) T;
         LANGULUS_BASES(Sampler);
      };

   } // namespace Langulus::A

   /// Custom name generator at compile-time for samplers                     
   template<CT::VectorBased T>
   consteval auto CustomName(Of<Math::TSampler<T>>&&) noexcept {
      using CLASS = Math::TSampler<T>;
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
      for (auto i : "Sampler")
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
      ///   A templated sampler                                               
      /// It's just a vector, specialized for accessing textures/volumes      
      ///                                                                     
      template<CT::VectorBased T>
      struct TSampler : T {
         using PointType = T;
         using T::MemberCount;
         using T::T;

         LANGULUS(NAME) CustomNameOf<TSampler>::Generate();
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(
            A::SamplerOfSize<MemberCount>,
            A::SamplerOfType<TypeOf<T>>,
            T
         );

         /// Construct a normal from a vector                                 
         ///   @param other - the vector to normalize                         
         constexpr TSampler(const T& other)
            : T {other} {}

         /// Convert from any sampler to code                                 
         NOD() explicit operator Flow::Code() const {
            return T::template Serialize<Flow::Code, TSampler>();
         }

         /// Convert from any sampler to text                                 
         NOD() explicit operator Anyness::Text() const {
            return T::template Serialize<Anyness::Text, TSampler>();
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus
