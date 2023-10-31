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
#include "../Numbers/Level.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::ScalarOrVector T>
      struct TForce;

      using Force1    = TForce<TVector<Real, 1>>;
      using Force1f   = TForce<TVector<Float, 1>>;
      using Force1d   = TForce<TVector<Double, 1>>;
      using Force1i   = TForce<TVector<signed, 1>>;
      using Force1u   = TForce<TVector<unsigned, 1>>;
      using Force1i8  = TForce<TVector<::std::int8_t, 1>>;
      using Force1u8  = TForce<TVector<uint8, 1>>;
      using Force1i16 = TForce<TVector<::std::int16_t, 1>>;
      using Force1u16 = TForce<TVector<::std::uint16_t, 1>>;
      using Force1i32 = TForce<TVector<::std::int32_t, 1>>;
      using Force1u32 = TForce<TVector<::std::uint32_t, 1>>;
      using Force1i64 = TForce<TVector<::std::int64_t, 1>>;
      using Force1u64 = TForce<TVector<::std::uint64_t, 1>>;

      using Force2    = TForce<TVector<Real, 2>>;
      using Force2f   = TForce<TVector<Float, 2>>;
      using Force2d   = TForce<TVector<Double, 2>>;
      using Force2i   = TForce<TVector<signed, 2>>;
      using Force2u   = TForce<TVector<unsigned, 2>>;
      using Force2i8  = TForce<TVector<::std::int8_t, 2>>;
      using Force2u8  = TForce<TVector<uint8, 2>>;
      using Force2i16 = TForce<TVector<::std::int16_t, 2>>;
      using Force2u16 = TForce<TVector<::std::uint16_t, 2>>;
      using Force2i32 = TForce<TVector<::std::int32_t, 2>>;
      using Force2u32 = TForce<TVector<::std::uint32_t, 2>>;
      using Force2i64 = TForce<TVector<::std::int64_t, 2>>;
      using Force2u64 = TForce<TVector<::std::uint64_t, 2>>;

      using Force3    = TForce<TVector<Real, 3>>;
      using Force3f   = TForce<TVector<Float, 3>>;
      using Force3d   = TForce<TVector<Double, 3>>;
      using Force3i   = TForce<TVector<signed, 3>>;
      using Force3u   = TForce<TVector<unsigned, 3>>;
      using Force3i8  = TForce<TVector<::std::int8_t, 3>>;
      using Force3u8  = TForce<TVector<uint8, 3>>;
      using Force3i16 = TForce<TVector<::std::int16_t, 3>>;
      using Force3u16 = TForce<TVector<::std::uint16_t, 3>>;
      using Force3i32 = TForce<TVector<::std::int32_t, 3>>;
      using Force3u32 = TForce<TVector<::std::uint32_t, 3>>;
      using Force3i64 = TForce<TVector<::std::int64_t, 3>>;
      using Force3u64 = TForce<TVector<::std::uint64_t, 3>>;

      using Force4    = TForce<TVector<Real, 4>>;
      using Force4f   = TForce<TVector<Float, 4>>;
      using Force4d   = TForce<TVector<Double, 4>>;
      using Force4i   = TForce<TVector<signed, 4>>;
      using Force4u   = TForce<TVector<unsigned, 4>>;
      using Force4i8  = TForce<TVector<::std::int8_t, 4>>;
      using Force4u8  = TForce<TVector<uint8, 4>>;
      using Force4i16 = TForce<TVector<::std::int16_t, 4>>;
      using Force4u16 = TForce<TVector<::std::uint16_t, 4>>;
      using Force4i32 = TForce<TVector<::std::int32_t, 4>>;
      using Force4u32 = TForce<TVector<::std::uint32_t, 4>>;
      using Force4i64 = TForce<TVector<::std::int64_t, 4>>;
      using Force4u64 = TForce<TVector<::std::uint64_t, 4>>;

      using Force     = Force3;
      using Forcef    = Force3f;
      using Forced    = Force3d;
      using Forcei    = Force3i;
      using Forceu    = Force3u;
      using Forcei8   = Force3i8;
      using Forceu8   = Force3u8;
      using Forcei16  = Force3i16;
      using Forceu16  = Force3u16;
      using Forcei32  = Force3i32;
      using Forceu32  = Force3u32;
      using Forcei64  = Force3i64;
      using Forceu64  = Force3u64;

   } // namespace Langulus::Math

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// force                                                               
      struct Force {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Force;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// force of the same size                                              
      template<Count S>
      struct ForceOfSize : Force {
         LANGULUS(CONCRETE) Math::TForce<Math::TVector<Real, S>>;
         LANGULUS_BASES(Force);
         static constexpr Count MemberCount {S};
         static_assert(S > 0, "Force size must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// force of the same type                                              
      template<CT::DenseNumber T>
      struct ForceOfType : Force {
         LANGULUS(CONCRETE) Math::TForce<Math::TVector<T, 3>>;
         LANGULUS(TYPED) T;
         LANGULUS_BASES(Force);
      };

   } // namespace Langulus::A

   /// Custom name generator at compile-time for forces                       
   template<CT::ScalarOrVector T>
   constexpr auto CustomName(Of<Math::TForce<T>>&&) noexcept {
      using CLASS = Math::TForce<T>;
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
      for (auto i : "Force")
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
      ///   Templated force                                                   
      ///                                                                     
      template<CT::ScalarOrVector T>
      struct TForce : T {
         using PointType = T;
         using T::T;
         using T::mArray;
         using T::MemberCount;

         LANGULUS(NAME) CustomNameOf<TForce>::Generate();
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(
            A::ForceOfSize<MemberCount>,
            A::ForceOfType<TypeOf<T>>,
            T
         );

         // The level in which the force operates                       
         Level mLevel {};

         /// Construct force from vector and level                            
         ///   @param force - the direction times magnitude of the force      
         ///   @param level - the level in which the force acts               
         constexpr TForce(const T& force, Level level = {}) noexcept
            : T {force}
            , mLevel {level} {}

         /// Convert from any force to text                                   
         NOD() explicit operator Flow::Code() const {
            Flow::Code result;
            result += NameOf<TForce>();
            result += Flow::Code::OpenScope;
            auto& asVector = static_cast<const T&>(*this);
            for (auto& x : asVector) {
               result += x;
               result += ", ";
            }
            result += static_cast<Flow::Code>(mLevel);
            result += Flow::Code::CloseScope;
            return result;
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus
