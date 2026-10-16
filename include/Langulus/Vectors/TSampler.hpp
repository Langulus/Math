///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TVector.hpp"


namespace Langulus::Math
{
   template<CT::CustomVector T>
   struct TSampler;

   using Sampler1    = TSampler<TVector<Real, 1>>;
   using Sampler1f   = TSampler<TVector<float, 1>>;
   using Sampler1d   = TSampler<TVector<double, 1>>;
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
   using Sampler2f   = TSampler<TVector<float, 2>>;
   using Sampler2d   = TSampler<TVector<double, 2>>;
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
   using Sampler3f   = TSampler<TVector<float, 3>>;
   using Sampler3d   = TSampler<TVector<double, 3>>;
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
   using Sampler4f   = TSampler<TVector<float, 4>>;
   using Sampler4d   = TSampler<TVector<double, 4>>;
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


   /// Used as an imposed base for any type that can be interpretable as a    
   /// sampler                                                                
   struct Sampler {
      using CTTI_Abstract = Yup;
      using CTTI_Concrete = Math::Sampler3;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// sampler of the same size                                               
   template<size_t S>
   struct SamplerOfSize : Sampler {
      using CTTI_Concrete  = Math::TSampler<Math::TVector<Langulus::Real, S>>;
      using CTTI_Bases     = Math::Sampler;
      
      static constexpr size_t MemberCount {S};
      static_assert(S > 0, "Normal size must be greater than zero");
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// sampler of the same type                                               
   template<CT::Number T>
   struct SamplerOfType : Sampler {
      using CTTI_Concrete  = Math::TSampler<Math::TVector<T, 3>>;
      using CTTI_Typed     = T;
      using CTTI_Bases     = Math::Sampler;
   };


   ///                                                                        
   ///   A templated sampler                                                  
   /// It's just a vector, specialized for accessing textures/volumes         
   ///                                                                        
   template<CT::CustomVector T>
   struct TSampler : T {
      using T::T;

   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TSampler>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (ExtentOf<T> > 4) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "Sampler")
            name[offset++] = i;

         // Write size                                                  
         --offset;
         name[offset++] = '0' + ExtentOf<T>;

         // Write suffix                                                
         for (auto i : SuffixOf<TypeOf<T>>())
            name[offset++] = i;
         return name;
      }

   public:
      using CTTI_Named = Yes<GenerateToken()>;
      using CTTI_Bases = Types<
         Math::SamplerOfSize<ExtentOf<T>>,
         Math::SamplerOfType<TypeOf<T>>,
         T
      >;

      /// Construct a normal from a vector                                    
      ///   @param other - the vector to normalize                            
      constexpr TSampler(T const& other)
         : T {other} {}

      /// Convert from any sampler to code                                    
      /*explicit operator Flow::Code() const {
         return T::template Serialize<Flow::Code, TSampler>();
      }

      /// Convert from any sampler to text                                    
      explicit operator Annies::Text() const {
         return T::template Serialize<Annies::Text, TSampler>();
      }*/
   };
}
