///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Ranges/TRange.hpp>


namespace Langulus::Math
{
   /// Combines S and T... to form a vector type, and then a range from it    
   ///   @tparam S size of the vector                                         
   template<size_t S>
   struct RangeTypeGenerator {
      template<class...T>
      static void Register(Types<T...>&&) {
         (((void) MetaOf<TRange<TVector<T, S>>>()), ...);
      }
   };

   /// Register all commonly used range types and constants, so they can be   
   /// instantiated from scripts                                              
   void RegisterRanges() {
      RangeTypeGenerator<1>::Register(Typelists::Arithmetic {});
      RangeTypeGenerator<2>::Register(Typelists::Arithmetic {});
      RangeTypeGenerator<3>::Register(Typelists::Arithmetic {});
      RangeTypeGenerator<4>::Register(Typelists::Arithmetic {});
      
      // Constants                                                      
      /*(void) MetaOf<Constants::RangeIn>();
      (void) MetaOf<Constants::RangeOn>();
      (void) MetaOf<Constants::RangeUnder>();
      (void) MetaOf<Constants::RangeAbove>();
      (void) MetaOf<Constants::RangeBelow>();
      (void) MetaOf<Constants::RangeCenter>();
      (void) MetaOf<Constants::RangeMiddle>();
      (void) MetaOf<Constants::RangeRear>();
      (void) MetaOf<Constants::RangeBehind>();
      (void) MetaOf<Constants::RangeFront>();
      (void) MetaOf<Constants::RangeAhead>();
      (void) MetaOf<Constants::RangeLeft>();
      (void) MetaOf<Constants::RangeRight>();*/
   }
}