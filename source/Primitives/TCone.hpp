///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
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
      LANGULUS_BASES(A::Primitive);

      using PointType = T;
      using typename T::MemberType;
      using Dimension = D;
      using T::MemberCount;
      static_assert(MemberCount == 3, "Can't have a non-3D cone");
      static_assert(D::Index < 3, "Can't extend cone in that dimension");

      // Size of the cone                                               
      MemberType mHeight {.5};

      // Angle of the cone's slope                                      
      TRadians<MemberType> mAngle {HALFPI<MemberType>};

   public:
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };

} // namespace Langulus::Math

#include "TCone.inl"