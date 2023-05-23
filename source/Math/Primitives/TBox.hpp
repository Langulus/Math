///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TPoint.hpp"

namespace Langulus
{
   namespace Math
   {

      template<CT::Vector>
      struct TBox;

      template<CT::Vector>
      struct TBoxRounded;

      using Box2 = TBox<Point2>;
      using Box3 = TBox<Point3>;

      using BoxRounded2 = TBoxRounded<Point2>;
      using BoxRounded3 = TBoxRounded<Point3>;

      using Box = Box3;
      using BoxRounded = BoxRounded3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract box                                                     
      struct Box {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Box;
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing box primitives                           
      template<class... T>
      concept Box = (DerivedFrom<T, A::Box> && ...);

   } // namespace Langulus::CT

} // namespace Langulus

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
   struct TBox : A::Box {
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Box);

      using PointType = T;
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
   struct TBoxRounded : TBox<T> {
      using Base = TBox<T>;
      using typename Base::PointType;
      using Base::MemberCount;
      using Base::mOffsets;

      TypeOf<T> mRadius;

   public:
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };

} // namespace Langulus::Math

#include "TBox.inl"