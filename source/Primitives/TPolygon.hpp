///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::Vector>
      struct TPolygon;

      using Polygon2 = TPolygon<Vec2>;
      using Polygon3 = TPolygon<Vec3>;

      using Polygon  = Polygon3;

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
      struct TPolygon : TMany<T> {
         LANGULUS(DEEP) false;
         LANGULUS_BASES(A::Polygon);

         using Base = TMany<T>;
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
            return Base::operator == (static_cast<const Base&>(rhs));
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus
