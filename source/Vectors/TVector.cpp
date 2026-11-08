///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Math/Vector.hpp>
#include <Langulus/MetaOf.hpp>


namespace Langulus::Math
{
   /// Combines S and T... to form a vector type                              
   ///   @tparam S - size of the vector                                       
   template<size_t S>
   struct VectorTypeGenerator {
      template<class...T>
      static void Register(Types<T...>&&) {
         (((void) MetaDataOf<TVector<T, S>>()), ...);
      }
   };

   /// Register all commonly used vector types and constants, so they can be  
   /// instantiated from scripts                                              
   void RegisterVectors() {
      VectorTypeGenerator<1>::Register(Typelists::Arithmetic {});
      VectorTypeGenerator<2>::Register(Typelists::Arithmetic {});
      VectorTypeGenerator<3>::Register(Typelists::Arithmetic {});
      VectorTypeGenerator<4>::Register(Typelists::Arithmetic {});

      /*(void) MetaOf<Constants::AxisBackward>();
      (void) MetaOf<Constants::AxisForward>();
      (void) MetaOf<Constants::AxisLeft>();
      (void) MetaOf<Constants::AxisRight>();
      (void) MetaOf<Constants::AxisUp>();
      (void) MetaOf<Constants::AxisDown>();

      (void) MetaOf<Constants::AxisX>();
      (void) MetaOf<Constants::AxisY>();
      (void) MetaOf<Constants::AxisZ>();
      (void) MetaOf<Constants::AxisW>();

      (void) MetaOf<Constants::AxisOrigin>();*/
   }
}

namespace Langulus::Math
{
   template struct LANGULUS_EXPORT() TVector<float, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<double, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 1, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 1, 0>;

   template struct LANGULUS_EXPORT() TVector<float, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<double, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 2, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 2, 0>;

   template struct LANGULUS_EXPORT() TVector<float, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<double, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 3, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 3, 0>;

   template struct LANGULUS_EXPORT() TVector<float, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<double, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 4, 0>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 4, 0>;

   template struct LANGULUS_EXPORT() TVector<float, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<double, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 1, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 1, 1>;

   template struct LANGULUS_EXPORT() TVector<float, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<double, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 2, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 2, 1>;

   template struct LANGULUS_EXPORT() TVector<float, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<double, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 3, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 3, 1>;

   template struct LANGULUS_EXPORT() TVector<float, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<double, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int8_t, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint8_t, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int16_t, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint16_t, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int32_t, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint32_t, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::int64_t, 4, 1>;
   template struct LANGULUS_EXPORT() TVector<::std::uint64_t, 4, 1>;
}

namespace Langulus::RTTI
{
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 1, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 1, 0>>();

   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 2, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 2, 0>>();

   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 3, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 3, 0>>();

   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 4, 0>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 4, 0>>();

   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 1, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 1, 1>>();

   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 2, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 2, 1>>();

   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 3, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 3, 1>>();

   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<float, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<double, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int8_t, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint8_t, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int16_t, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint16_t, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int32_t, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint32_t, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::int64_t, 4, 1>>();
   template LANGULUS_EXPORT() DefinitionData const* DefinitionData::Reflect<Math::TVector<::std::uint64_t, 4, 1>>();
}