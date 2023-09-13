///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Primitive.hpp"

namespace Langulus::Math
{

   ///                                                                        
   /// 3D cone with varying dimensions, centered around origin                
   /// D determines the direction of the cone's pointy side                   
   ///                                                                        
   template<CT::Vector T, CT::Dimension D = Traits::Y>
   struct TCone {
      LANGULUS(POD) true;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Primitive);

      using PointType = T;
      using Dimension = D;
      using T::MemberCount;
      static_assert(MemberCount == 3, "Can't have a non-3D cone");
      static_assert(D::Index < 3, "Can't extend cone in that dimension");

      // Size of the cone                                               
      TypeOf<T> mHeight {.5};

      // Angle of the cone's slope                                      
      TRadians<TypeOf<T>> mAngle {HALFPI<TypeOf<T>>};

   public:
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };

} // namespace Langulus::Math