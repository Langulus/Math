///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "TNormal.hpp"


namespace Langulus::Math
{

   /// Combines S and T... to form a normal type                              
   ///   @tparam S - size of the vector                                       
   template<Count S>
   struct NormalTypeGenerator {
      template<class...T>
      static void Register(Types<T...>&&) {
         (((void) MetaOf<TNormal<TVector<T, S>>>()), ...);
      }
   };


   /// Register all normal types                                              
   void RegisterNormals() {
      using RealTypes = Types<Float, Double>;

      NormalTypeGenerator<2>::Register(RealTypes {});
      NormalTypeGenerator<3>::Register(RealTypes {});
      NormalTypeGenerator<4>::Register(RealTypes {});
   }

} // namespace Langulus::Math