///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../../source/Vectors/TVector.inl"
#include "../../source/Vectors/TNormal.hpp"


namespace Langulus::Math
{
   namespace Inner
   {
      /// Combines S and T... to form a normal type                           
      ///   @tparam S - size of the vector                                    
      template<Count S>
      struct NormalTypeGenerator {
         template<class... T>
         static void Register(Types<T...>&&) {
            (((void)MetaOf<TNormal<TVector<T, S>>>()), ...);
         }
      };
   } // namespace Langulus::Math::Inner

   /// Register all normal types                                              
   inline void RegisterNormals() {
      using RealTypes = Types<Float, Double>;

      Inner::NormalTypeGenerator<2>::Register(RealTypes {});
      Inner::NormalTypeGenerator<3>::Register(RealTypes {});
      Inner::NormalTypeGenerator<4>::Register(RealTypes {});
   }

} // namespace Langulus::Math