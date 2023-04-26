///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../IncludeMemory.hpp"

namespace Langulus::Math
{

   template<class T>
   void pcDefaultConcat(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultConcat<T>);

      T result = *static_cast<T*>(what);
      verb.GetArgument().ForEachDeep([&result](const Block& group) {
         for (pcptr i = 0; i < group.GetCount(); ++i) {
            T temp = group.AsCast<T>(i);
            result *= static_cast<T>(pcPow(pcptr(10), pcNumDigits(temp)));
            result += temp;
         }
      });
      verb << result;
   }

   template<class T>
   void pcDefaultAdd(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultAdd<T>);
      TODO();
   }

   template<class T>
   void pcDefaultMultiply(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultMultiply<T>);
      //TODO();
   }

   template<class T>
   void pcDefaultLerp(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultLerp<T>);
      TODO();
   }

   template<class T>
   void pcDefaultCerp(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultCerp<T>);
      TODO();
   }

   template<class T>
   void pcDefaultExponent(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultExponent<T>);
      TODO();
   }

   template<class T>
   void pcDefaultModulate(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultModulate<T>);
      TODO();
   }

   template<class T>
   void pcDefaultIntegrate(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultIntegrate<T>);
      TODO();
   }

   template<class T>
   void pcDefaultRandomize(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultRandomize<T>);
      TODO();
   }

   template<class T>
   void pcDefaultCompare(void* what, Verb& verb) {
      PC_ASSERT_VERB_SIGNATURE(pcDefaultCompare<T>);
      TODO();
   }

} // namespace Langulus::Math

/// Convenience macro to be used for reflecting common mathematical abilities 
#define ALL_PCMATH_ABILITIES(a) \
   MEMBER_VERB_EXT(Catenate, pcDefaultConcat<a>), \
   MEMBER_VERB_EXT(Lerp, pcDefaultLerp<a>), \
   MEMBER_VERB_EXT(Cerp, pcDefaultCerp<a>), \
   MEMBER_VERB_EXT(Exponent, pcDefaultExponent<a>), \
   MEMBER_VERB_EXT(Modulate, pcDefaultModulate<a>), \
   MEMBER_VERB_EXT(Integrate, pcDefaultIntegrate<a>), \
   MEMBER_VERB_EXT(Randomize, pcDefaultRandomize<a>), \
   MEMBER_VERB_EXT(Compare, pcDefaultCompare<a>), \
   MEMBER_VERB_EXT(Add, pcDefaultAdd<a>), \
   MEMBER_VERB_EXT(Multiply, pcDefaultMultiply<a>)
