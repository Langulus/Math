///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Vectors/TVector.inl"


namespace Langulus::Math
{
   ///                                                                        
   ///   An abstract primitive                                                
   ///                                                                        
   struct Primitive {
      using CTTI_Abstract  = Yup;
      using CTTI_Info      = Yes<"An abstract primitive">;
   };

   ///                                                                        
   ///   An abstract topology                                                 
   ///                                                                        
   struct Topology : Primitive {
      using CTTI_Bases     = Primitive;
      using CTTI_Info      = Yes<"An abstract topology">;
   };
}

namespace Langulus::CT
{
   /// Concept for distinguishing primitives                                  
   template<class...T>
   concept Point = (DerivedFrom<T, Math::Point> and ...);

   /// Concept for distinguishing primitives                                  
   template<class...T>
   concept Primitive = ((DerivedFrom<T, Math::Primitive> or Point<T>) and ...);

   /// Concept for distinguishing topologies                                  
   template<class...T>
   concept Topology = ((DerivedFrom<T, Math::Topology> or Point<T>) and ...);
}