///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TPoint.hpp"

namespace Langulus::Math
{

   template<CT::Vector>
   struct TPolygon;

   using Polygon2 = TPolygon<Point2>;
   using Polygon3 = TPolygon<Point3>;

   using Polygon = Polygon3;

} // namespace Langulus::Math

namespace Langulus::A
{

   ///   An abstract polygon, also used as a topology type                    
   struct Polygon {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::Polygon;
      LANGULUS_BASES(Topology);
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   A templated polygon                                                  
   /// A list of coplanar points that form a surface with a complex edge      
   ///                                                                        
   template<CT::Vector T>
   struct TPolygon : TAny<T> {
      LANGULUS(DEEP) false;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Polygon);

      using Base = TAny<T>;
      using PointType = T;
      using typename T::MemberType;
      using T::MemberCount;
      static_assert(MemberCount > 1, "Polygons don't exist below two dimensions");

      /// Calculate signed distance                                           
      NOD() auto SignedDistance(const T&) const {
         TODO();
      }
   };

} // namespace Langulus::Math

