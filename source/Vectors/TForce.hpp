///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Adaptive.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::VectorBased T>
      using TForce    = Adaptive<T>;

      using Force1    = TForce<TVector<Real, 1>>;
      using Force1f   = TForce<TVector<Float, 1>>;
      using Force1d   = TForce<TVector<Double, 1>>;
      using Force1i   = TForce<TVector<signed, 1>>;
      using Force1u   = TForce<TVector<unsigned, 1>>;
      using Force1i8  = TForce<TVector<::std::int8_t, 1>>;
      using Force1u8  = TForce<TVector<::std::uint8_t, 1>>;
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
      using Force2u8  = TForce<TVector<::std::uint8_t, 2>>;
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
      using Force3u8  = TForce<TVector<::std::uint8_t, 3>>;
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
      using Force4u8  = TForce<TVector<::std::uint8_t, 4>>;
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

} // namespace Langulus
