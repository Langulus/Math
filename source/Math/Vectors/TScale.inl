///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TScale.hpp"

#define TEMPLATE() template<CT::ScalarOrVector T>

namespace Langulus::Math
{

   /// Pick a shorter token, based on member count and type                   
   /// This should be made more elegant when true constexpr string literals   
   /// become available in the standard                                       
   TEMPLATE()
   constexpr typename TScale<T>::ClassName TScale<T>::GenerateClassName() noexcept {
      ClassName name {};
      ::std::size_t offset {};

      if constexpr (MemberCount > 4) {
         for (auto i : DefaultClassName)
            name[offset++] = i;
         return name;
      }

      // Write prefix                                                   
      for (auto i : "Scale")
         name[offset++] = i;

      // Write size                                                     
      --offset;
      name[offset++] = '0' + MemberCount;

      // Write suffix                                                   
      for (auto i : SuffixOf<TypeOf<T>>())
         name[offset++] = i;
      return name;
   }

} // namespace Langulus::Math

#undef TEMPLATE