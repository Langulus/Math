///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Vectors/TVector.inl"

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
      template<class...T>
      concept Point = (DerivedFrom<T, A::Point> and ...);

      /// Concept for distinguishing primitives                               
      template<class...T>
      concept Primitive = ((DerivedFrom<T, A::Primitive> or Point<T>) and ...);

      /// Concept for distinguishing topologies                               
      template<class...T>
      concept Topology = ((DerivedFrom<T, A::Topology> or Point<T>) and ...);

   } // namespace Langulus::CT

   namespace Math
   {

      LANGULUS_API(MATH) extern void RegisterPrimitives();

   } // namespace Langulus::Math

} // namespace Langulus