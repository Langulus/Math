///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Vectors/TVector.hpp>


namespace Langulus::Math
{
   /// Combines S and T... to form a vector type                              
   ///   @tparam S - size of the vector                                       
   template<size_t S>
   struct VectorTypeGenerator {
      template<class...T>
      static void Register(Types<T...>&&) {
         (((void) MetaOf<TVector<T, S>>()), ...);
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

