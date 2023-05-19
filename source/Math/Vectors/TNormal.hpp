///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TVector.hpp"

namespace Langulus::Math
{

   template<CT::Vector T>
   struct TNormal;

   using Normal2      = TNormal<TVector<Real, 2>>;
   using Normal2f     = TNormal<TVector<Float, 2>>;
   using Normal2d     = TNormal<TVector<Double, 2>>;
   using Normal2i     = TNormal<TVector<signed, 2>>;
   using Normal2u     = TNormal<TVector<unsigned, 2>>;
   using Normal2i8    = TNormal<TVector<::std::int8_t, 2>>;
   using Normal2u8    = TNormal<TVector<uint8, 2>>;
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
   using Normal3u8    = TNormal<TVector<uint8, 3>>;
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
   using Normal4u8    = TNormal<TVector<uint8, 4>>;
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

namespace Langulus::A
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
      static_assert(S > 1, "Normal size must be greater than one");
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// normal of the same type                                                
   template<CT::DenseNumber T>
   struct NormalOfType : Normal {
      LANGULUS(CONCRETE) Math::TNormal<Math::TVector<T, 4>>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(Normal);
   };

} // namespace Langulus::A

namespace Langulus::Math
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

      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(
         A::NormalOfSize<MemberCount>, 
         A::NormalOfType<TypeOf<T>>,
         T
      );

   private:
      static constexpr auto DefaultClassName = RTTI::LastCppNameOf<TNormal>();
      using ClassName = ::std::array<char, DefaultClassName.size() + 1>;
      static constexpr ClassName GenerateClassName() noexcept;
      static constexpr ClassName GeneratedClassName = GenerateClassName();

   public:
      LANGULUS(NAME) GeneratedClassName.data();

      using T::T;
      using T::mArray;

      /// Construct a normal from a vector                                    
      ///   @param other - the vector to normalize                            
      constexpr TNormal(const T& other)
         : T {other.Normalize()} {}

      /// Convert from any normal to text                                     
      NOD() explicit operator Flow::Code() const {
         return T::template Serialize<TNormal>();
      }
   };

} // namespace Langulus::Math

#include "TNormal.inl"