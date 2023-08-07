///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Common.hpp"

LANGULUS_DEFINE_TRAIT(Topology, "Topology type");

namespace Langulus
{
   namespace A
   {

      ///                                                                     
      ///   An abstract primitive                                             
      ///                                                                     
      struct Primitive {
         LANGULUS(INFO) "An abstract primitive";
         LANGULUS(ABSTRACT) true;
      };

      ///                                                                     
      ///   An abstract topology                                              
      ///                                                                     
      struct Topology : Primitive {
         LANGULUS(INFO) "An abstract topology";
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing primitives                               
      template<class... T>
      concept Primitive = ((DerivedFrom<T, A::Primitive>) && ...);

      /// Concept for distinguishing topologies                               
      template<class... T>
      concept Topology = ((DerivedFrom<T, A::Topology>) && ...);

   } // namespace Langulus::CT

} // namespace Langulus