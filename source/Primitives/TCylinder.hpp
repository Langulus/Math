///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
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

      template<CT::Vector, CT::Dimension = Traits::Y>
      struct TCylinder;
      template<CT::Vector, CT::Dimension = Traits::Y>
      struct TCylinderCapped;

      using Cylinder3 = TCylinder<Point3>;
      using CylinderCapped3 = TCylinderCapped<Point3>;

      using Cylinder = Cylinder3;
      using CylinderCapped = CylinderCapped3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract cylinder                                                
      struct Cylinder : Primitive {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Cylinder;
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing cylinder primitives                      
      template<class... T>
      concept Cylinder = ((DerivedFrom<T, A::Cylinder>) && ...);

   } // namespace Langulus::CT

} // namespace Langulus

namespace Langulus::Math
{

   ///                                                                     |  
   /// Infinite 3D cylinder with varying radius, centered at origin        |  
   /// D determines the direction of the cylinder's height                 |  
   ///                                                                     |  
   ///                                                                     |  
   ///      ^     ^ +D  ^      ^                                           |  
   ///      |     |     |      |                                           |  
   ///      | _ _ | _ _ |      |                                           |  
   ///      |/    |    \|      |                                           |  
   ///      |     +     |      |                                           |  
   ///      |\_________/|      | infinite height                           |  
   ///      |           |      |                                           |  
   ///      |           |      v                                           |  
   ///      |     +     |   ----                                           |  
   ///      |   origin  |                                                  |  
   ///      | _ _ _ _ _ |                                                  |  
   ///      |/         \|                                                  |  
   ///      |     +     |                                                  |  
   ///      |\____|____/|                                                  |  
   ///      |     |     |                                                  |  
   ///      V     |<--->V mRadius                                          |  
   ///                                                                     |  
   template<CT::Vector T, CT::Dimension D>
   struct TCylinder : A::Cylinder {
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Cylinder);

      using PointType = T;
      using Dimension = D;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount >= 3, 
         "Can't have a cylinder with lower than 3 dimensions");
      static_assert(D::Index < 3, 
         "Can't extend cylinder in that dimension");

      TypeOf<T> mRadius {.5};

   public:
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };


   ///                                                                     |  
   /// Capped 3D cylinder with varying size, centered at origin            |  
   /// D determines the direction of the cylinder's height                 |  
   ///                                                                     |  
   ///            ^ +D                                                     |  
   ///            |                                                        |  
   ///        ____|____                                                    |  
   ///       /    |    \                                                   |  
   ///      |     +     |   ----                                           |  
   ///      |\_________/|      ^                                           |  
   ///      |           |      |   mHeight                                 |  
   ///      |           |      v                                           |  
   ///      |     +     |   ----                                           |  
   ///      |   origin  |                                                  |  
   ///      | _ _ _ _ _ |                                                  |  
   ///      |/         \|                                                  |  
   ///      |     +     |                                                  |  
   ///       \____|____/                                                   |  
   ///            |     |                                                  |  
   ///            |<--->| mRadius                                          |  
   ///                                                                     |  
   template<CT::Vector T, CT::Dimension D>
   struct TCylinderCapped : TCylinder<T, D> {
      LANGULUS(TYPED) TypeOf<T>;
      using Base = TCylinder<T, D>;
      using typename Base::PointType;
      using Base::MemberCount;
      using Base::mRadius;

      TypeOf<T> mHeight {.5};

   public:
      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
   };

} // namespace Langulus::Math