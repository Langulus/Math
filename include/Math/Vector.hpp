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


namespace Langulus::Math
{
   namespace Inner
   {

      /// Combines S and T... to form a vector type                           
      ///   @tparam S - size of the vector                                    
      template<Count S>
      struct VectorTypeGenerator {
         template<class... T>
         static void Register(TTypeList<T...>&&) {
            (((void) MetaOf<TVector<T, S>>()), ...);
         }
      };

   } // namespace Langulus::Math::Inner


   /// Register all commonly used vector types, so they can be instantiated   
   /// from a flow                                                            
   inline void RegisterVectors() {
      using AllTypes = TTypeList<
         ::std::uint8_t, ::std::uint16_t, ::std::uint32_t, ::std::uint64_t,
         ::std::int8_t,  ::std::int16_t,  ::std::int32_t,  ::std::int64_t,
         Float, Double
      >;

      Inner::VectorTypeGenerator<1>::Register(AllTypes {});
      Inner::VectorTypeGenerator<2>::Register(AllTypes {});
      Inner::VectorTypeGenerator<3>::Register(AllTypes {});
      Inner::VectorTypeGenerator<4>::Register(AllTypes {});
   }

} // namespace Langulus::Math