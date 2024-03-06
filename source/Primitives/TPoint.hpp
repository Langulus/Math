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
#include "../Vectors/TVector.hpp"

namespace Langulus
{
   namespace Math
   {

      template<CT::VectorBased>
      struct TPoint;

      using Point1 = TPoint<Vec1>;
      using Point2 = TPoint<Vec2>;
      using Point3 = TPoint<Vec3>;

      using Point1f = TPoint<Vec1f>;
      using Point2f = TPoint<Vec2f>;
      using Point3f = TPoint<Vec3f>;

      using Point = Point3;

   } // namespace Langulus::CT

   namespace A
   {

      /// An abstract point, also used as a topology type                     
      struct Point : Topology {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Point;
         LANGULUS_BASES(Topology);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing point primitives                         
      template<class...T>
      concept Point = CT::Vector<T...> or (DerivedFrom<T, A::Point> and ...);

   } // namespace Langulus::CT
   
   /// Custom name generator at compile-time for points                       
   template<class T>
   consteval auto CustomName(Of<Math::TPoint<T>>&&) noexcept {
      using CLASS = Math::TPoint<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      if constexpr (T::MemberCount > 3) {
         for (auto i : defaultClassName)
            name[offset++] = i;
         return name;
      }

      // Write prefix                                                   
      for (auto i : "Point")
         name[offset++] = i;

      // Write size                                                     
      --offset;
      name[offset++] = '0' + T::MemberCount;

      // Write suffix                                                   
      for (auto i : SuffixOf<TypeOf<T>>())
         name[offset++] = i;
      return name;
   }
   
   namespace Math
   {

      ///                                                                     
      ///   A concrete point                                                  
      ///                                                                     
      #pragma pack(push, 1)
      template<CT::VectorBased T>
      struct TPoint : T {
         LANGULUS(NAME) CustomNameOf<TPoint>::Generate();
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(A::Point, T);

         using T::MemberCount;
         using T::T;
         using T::operator =;

         /// Convert from any point to text                                   
         NOD() explicit operator Flow::Code() const {
            return T::template Serialize<TPoint>();
         }

         /// Calculate signed distance                                        
         ///   @param point - point to check distance from                    
         ///   @return the distance to the primitive                          
         NOD() auto SignedDistance(const T& point) const {
            return (point - *this).Length();
         }
      };
      #pragma pack(pop)

   } // namespace Langulus::Math

} // namespace Langulus

