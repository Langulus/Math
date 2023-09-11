///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TPlane.hpp"
#include "TPoint.hpp"
#include "../Ranges/TRange.hpp"

namespace Langulus
{
   namespace Math
   {

      template<CT::Vector T>
      struct TFrustum;

      using Frustum2 = TFrustum<Point2>;
      using Frustum3 = TFrustum<Point3>;

      using Frustum = Frustum3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract frustum                                                 
      struct Frustum : Primitive {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Frustum;
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing frustum primitives                       
      template<class... T>
      concept Frustum = ((DerivedFrom<T, A::Frustum>) && ...);

   } // namespace Langulus::CT

} // namespace Langulus

namespace Langulus::Math
{

   ///                                                                        
   ///   2D/3D frustum, centered around origin                                
   ///                                                                        
   template<CT::Vector T>
   struct TFrustum : A::Frustum {
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Frustum);

      static constexpr Count MemberCount = T::MemberCount;
      using PointType = T;
      using MatrixType = TMatrix<TypeOf<T>, MemberCount + 1>;
      static_assert(MemberCount > 1, "Can't have one-dimensional frustum");

      TPlane<T> mPlanes[MemberCount * 2];

      enum {Left = 0, Right, Top, Bottom, Near, Far};

   public:
      TFrustum() noexcept;
      TFrustum(const MatrixType&) noexcept;

      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;
      NOD() bool Intersects(const TRange<T>&) const noexcept;
   };

} // namespace Langulus::Math

#include "TFrustum.inl"