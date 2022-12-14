///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TVector.hpp"

namespace Langulus::Math
{

   using Scale3 = TScale<TVector<Real, 3, 1>>;
   using Scale2 = TScale<TVector<Real, 2, 1>>;
   using Scale = Scale3;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as a    
   /// size                                                                   
   struct Scale {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::Scale;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// size of the same size                                                  
   template<Count S>
   struct ScaleOfSize : public Scale {
      LANGULUS(CONCRETE) Math::TScale<Math::TVector<::Langulus::Real, S, 1>>;
      LANGULUS_BASES(Scale);
      static constexpr Count MemberCount {S};
      static_assert(S > 0, "Scale must be greater than zero");
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// size of the same type                                                  
   template<CT::DenseNumber T>
   struct ScaleOfType : public Scale {
      LANGULUS(CONCRETE) Math::TScale<Math::TVector<T, 3, 1>>;
      LANGULUS_BASES(Scale);
      using MemberType = T;
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated size                                                       
   /// Vector specialization that defaults to 1 and is used for scaling       
   ///                                                                        
   template<CT::ScalarOrVector T>
   struct TScale : public T {
      using PointType = T;
      using typename T::MemberType;
      using T::MemberCount;
      static_assert(T::DefaultMember == MemberType {1},
         "Size type does not default to 1");
      LANGULUS_BASES(A::ScaleOfSize<MemberCount>, A::ScaleOfType<MemberType>);

   public:
      using T::T;
      using T::mArray;

      /// Convert from any size to text                                       
      NOD() explicit operator Flow::Code() const {
         return T::template Serialize<TScale>();
      }
   };

} // namespace Langulus::Math