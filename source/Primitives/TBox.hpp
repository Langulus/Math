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

   ///                                                                     |  
   /// 2D/3D box with varying dimensions, centered around origin           |  
   ///                                                                     |  
   /// An example unit 2D quad, centered at origin:                        |  
   ///           ^ +Y                                                      |  
   ///           |                                                         |  
   ///   +-------+-------+   (.5, .5) mOffsets from origin                 |  
   ///   |               |                                                 |  
   ///   |               |                                                 |  
   ///   |       +       |--> +X                                           |  
   ///   |     origin    |                                                 |  
   ///   |               |                                                 |  
   ///   +---------------+                                                 |  
   ///                                                                     |  
   template<CT::Vector T>
   struct TBox {
      LANGULUS(POD) true;
      LANGULUS_BASES(A::Primitive);

      using PointType = T;
      using typename T::MemberType;
      using T::MemberCount;
      static_assert(MemberCount > 1, "Can't have one-dimensional box");

      T mOffsets {.5};

   public:
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };


   ///                                                                     |  
   /// 2D/3D rounded box with varying dimensions, centered around origin   |  
   ///                                                                     |  
   ///           ^ +Y                                                      |  
   ///           |                                                         |  
   ///    /------+------\+   (.5, .5) mOffsets from origin                 |  
   ///   /               \                                                 |  
   ///  |                 |                                                |  
   ///  |        +        |--> +X                                          |  
   ///  |     origin      |                                                |  
   ///   \               /                                                 |  
   ///    \-------------/   <- mRadius from origin of rounded parts        |  
   ///                                                                     |  
   template<CT::Vector T>
   struct TBoxRounded : public TBox<T> {
      using Base = TBox<T>;
      using typename Base::PointType;
      using typename Base::MemberType;
      using Base::MemberCount;
      using Base::mOffsets;

      MemberType mRadius;

   public:
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };

} // namespace Langulus::Math

#include "TBox.inl"