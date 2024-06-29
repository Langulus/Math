///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           

/// INTENTIONALLY NOT GUARDED                                                 
/// Include this file once in each cpp file, after all other headers          
#ifdef TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
   #error Catch has been included prior to this header
#endif

#include "Main.hpp"
#include <catch2/catch.hpp>

/// See https://github.com/catchorg/Catch2/blob/devel/docs/tostring.md        
CATCH_TRANSLATE_EXCEPTION(::Langulus::Exception const& ex) {
   const Text serialized {ex};
   return ::std::string {Token {serialized}};
}

namespace Catch
{

   template<class T>
   concept StringifiableButNotRange = CT::Stringifiable<T> and not Catch::is_range<T>::value;

   template<StringifiableButNotRange T>
   struct StringMaker<T> {
      static std::string convert(T const& value) {
         return ::std::string {Token {static_cast<Text>(value)}};
      }
   };

   /// Save catch2 from doing infinite recursions with Block types            
   template<CT::Block T>
   struct is_range<T> {
      static const bool value = false;
   };

}

using timer = Catch::Benchmark::Chronometer;

template<class T>
using uninitialized = Catch::Benchmark::storage_for<T>;
