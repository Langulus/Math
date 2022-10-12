///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Common.hpp"

LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(X, "X (first) vector component",
   static constexpr Offset Index = 0);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(Y, "Y (second) vector component",
   static constexpr Offset Index = 1);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(Z, "Z (third) vector component",
   static constexpr Offset Index = 2);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(W, "W (fourth) vector component",
   static constexpr Offset Index = 3);

LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(U, "U (first) vector component",
   static constexpr Offset Index = 0);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(V, "V (second) vector component",
   static constexpr Offset Index = 1);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(S, "S (third) vector component",
   static constexpr Offset Index = 2);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(T, "T (fourth) vector component",
   static constexpr Offset Index = 3);

LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(R, "Red (first) color component",
   static constexpr Offset Index = 0);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(G, "Green (second) color component",
   static constexpr Offset Index = 1);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(B, "Blue (third) color component",
   static constexpr Offset Index = 2);
LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(A, "Alpha (fourth) color component",
   static constexpr Offset Index = 3);

LANGULUS_DEFINE_TRAIT_WITH_PROPERTIES(D, "Depth (first) component",
   static constexpr Offset Index = 0);

namespace Langulus::CT
{

   namespace Inner
   {
      template<class T>
      concept Dimension = Trait<T> && requires { {T::Index} -> CT::Same<Offset>; };
   }

   /// Dimension is any trait, defined with an Index property                 
   /// Used for accessing individual vector components, for example           
   template<class... T>
   concept Dimension = (Inner::Dimension<T> && ...);

} // namespace Langulus::CT