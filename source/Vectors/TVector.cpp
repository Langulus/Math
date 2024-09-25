///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "TVector.inl"


namespace Langulus::Math
{

   /// Combines S and T... to form a vector type                              
   ///   @tparam S - size of the vector                                       
   template<Count S>
   struct VectorTypeGenerator {
      template<class...T>
      static void Register(Types<T...>&&) {
         (((void) MetaOf<TVector<T, S>>()), ...);
      }
   };

   /// Register all commonly used vector types and constants, so they can be  
   /// instantiated from scripts                                              
   void RegisterVectors() {
      using AllTypes = Types<
         ::std::uint8_t, ::std::uint16_t, ::std::uint32_t, ::std::uint64_t,
         ::std::int8_t,  ::std::int16_t,  ::std::int32_t,  ::std::int64_t,
         Float, Double
      >;

      VectorTypeGenerator<1>::Register(AllTypes {});
      VectorTypeGenerator<2>::Register(AllTypes {});
      VectorTypeGenerator<3>::Register(AllTypes {});
      VectorTypeGenerator<4>::Register(AllTypes {});

      (void) MetaOf<Constants::Backward>();
      (void) MetaOf<Constants::Forward>();
      (void) MetaOf<Constants::Left>();
      (void) MetaOf<Constants::Right>();
      (void) MetaOf<Constants::Up>();
      (void) MetaOf<Constants::Down>();

      (void) MetaOf<Constants::X>();
      (void) MetaOf<Constants::Y>();
      (void) MetaOf<Constants::Z>();
      (void) MetaOf<Constants::W>();

      (void) MetaOf<Constants::Origin>();
   }

} // namespace Langulus::Math