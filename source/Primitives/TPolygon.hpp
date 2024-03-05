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

      template<CT::Vector>
      struct TPolygon;

      using Polygon2 = TPolygon<Point2>;
      using Polygon3 = TPolygon<Point3>;

      using Polygon = Polygon3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract polygon, also used as a topology type                   
      struct Polygon {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Polygon;
         LANGULUS_BASES(Topology);
      };

   } // namespace Langulus::A

   namespace Math
   {

      ///                                                                     
      ///   A templated polygon                                               
      ///                                                                     
      /// A list of coplanar points that form a surface with a complex edge   
      ///                                                                     
      template<CT::Vector T>
      struct TPolygon : TAny<T> {
         LANGULUS(DEEP) false;
         LANGULUS_BASES(A::Polygon);

         using Base = TAny<T>;
         using PointType = T;
         static constexpr auto MemberCount = T::MemberCount;
         static_assert(MemberCount > 1, "Polygons don't exist below two dimensions");

         /// Calculate signed distance                                        
         NOD() LANGULUS(INLINED)
         auto SignedDistance(const T&) const {
            TODO();
         }

         /// Compare two polygon sequences                                    
         LANGULUS(INLINED)
         bool operator == (const TPolygon& rhs) const {
            return Block::Compare<false, TAny<T>>(static_cast<const TAny<T>&>(rhs));
         }
      };

   } // namespace Langulus::Math
} // namespace Langulus
