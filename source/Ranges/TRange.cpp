///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "TRange.inl"


namespace Langulus::Math
{

   /// Combines S and T... to form a vector type, and then a range from it    
   ///   @tparam S - size of the vector                                       
   template<Count S>
   struct RangeTypeGenerator {
      template<class...T>
      static void Register(Types<T...>&&) {
         (((void) MetaOf<TRange<TVector<T, S>>>()), ...);
      }
   };

   /// Register all commonly used vector types and constants, so they can be  
   /// instantiated from scripts                                              
   void RegisterRanges() {
      using AllTypes = Types<
         ::std::uint8_t, ::std::uint16_t, ::std::uint32_t, ::std::uint64_t,
         ::std::int8_t,  ::std::int16_t,  ::std::int32_t,  ::std::int64_t,
         Float, Double
      >;

      RangeTypeGenerator<1>::Register(AllTypes {});
      RangeTypeGenerator<2>::Register(AllTypes {});
      RangeTypeGenerator<3>::Register(AllTypes {});
      RangeTypeGenerator<4>::Register(AllTypes {});
   }

} // namespace Langulus::Math