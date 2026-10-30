///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TVector.hpp"
#include <Langulus/Math/Adaptive.hpp>
#include <Langulus/CT/Force.hpp>


namespace Langulus::Math
{
   template<CT::CustomVector T>
   using TForce    = Adaptive<T>;

   using Force1    = TForce<TVector<Real, 1>>;
   using Force1f   = TForce<TVector<float, 1>>;
   using Force1d   = TForce<TVector<double, 1>>;
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
   using Force2f   = TForce<TVector<float, 2>>;
   using Force2d   = TForce<TVector<double, 2>>;
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
   using Force3f   = TForce<TVector<float, 3>>;
   using Force3d   = TForce<TVector<double, 3>>;
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
   using Force4f   = TForce<TVector<float, 4>>;
   using Force4d   = TForce<TVector<double, 4>>;
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


   /// Abstract force that relies on the context to pick the proper type.     
   /// A 2D world will work with Force2, a 3D world will work with Force3.    
   /// Some contexts will demand integer forces, while others will require    
   /// real ones. If context lacks definition, this will default to Force3,   
   /// as it's the most versatile type, albeit a bit bigger.                  
   struct Force {
      using CTTI_Abstract = Yup;
      using CTTI_Concrete = Force3;
   };

   /// Similar as the above, but the size is explicitly defined.              
   /// Only the type is decided by the context, defaulting to real.           
   template<size_t S> requires (S>0)
   struct ForceOfSize : Force {
      using CTTI_Concrete = TForce<TVector<Real, S>>;
      using CTTI_Bases    = Force;
   };

   /// Similar as the above, but the type is explicitly defined.              
   /// Only the size is decided by the context, defaulting to 4.              
   template<CT::Number T>
   struct ForceOfType : Force {
      using CTTI_Concrete = TForce<TVector<T, 4>>;
      using CTTI_Bases    = Force;
   };
}

namespace Langulus::CTTI
{
   /// Reflect all adaptives made with custom vectors as forces               
   template<CT::CustomVector T>
   struct Force<Math::Adaptive<T>> {};
}