///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/TTag.hpp>


namespace Langulus::CT
{
   namespace Inner
   {
      template<class T>
      concept Dimension = CT::DefineTag<T> and requires {
         {T::Index} -> Same<size_t>;
      };
   }

   /// Dimension is any tag, defined with a Dimension property.               
   /// Used for accessing individual vector components.                       
   template<class... T>
   concept Dimension = (CT::Inner::Dimension<T> and ...);
}

LANGULUS_DEFINE_TAG(X, "X (first) vector component",
   static constexpr size_t Index = 0);
LANGULUS_DEFINE_TAG(Y, "Y (second) vector component",
   static constexpr size_t Index = 1);
LANGULUS_DEFINE_TAG(Z, "Z (third) vector component",
   static constexpr size_t Index = 2);
LANGULUS_DEFINE_TAG(W, "W (fourth) vector component",
   static constexpr size_t Index = 3);

LANGULUS_DEFINE_TAG(U, "U (first) vector component",
   static constexpr size_t Index = 0);
LANGULUS_DEFINE_TAG(V, "V (second) vector component",
   static constexpr size_t Index = 1);
LANGULUS_DEFINE_TAG(S, "S (third) vector component",
   static constexpr size_t Index = 2);
LANGULUS_DEFINE_TAG(T, "T (fourth) vector component",
   static constexpr size_t Index = 3);

LANGULUS_DEFINE_TAG(R, "Red (first) color component",
   static constexpr size_t Index = 0);
LANGULUS_DEFINE_TAG(G, "Green (second) color component",
   static constexpr size_t Index = 1);
LANGULUS_DEFINE_TAG(B, "Blue (third) color component",
   static constexpr size_t Index = 2);
LANGULUS_DEFINE_TAG(A, "Alpha (fourth) color component",
   static constexpr size_t Index = 3);

LANGULUS_DEFINE_TAG(D, "Depth (first) component",
   static constexpr size_t Index = 0);
