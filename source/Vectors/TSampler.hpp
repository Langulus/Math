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

   /// Commonly used samplers                                                 
   using Sampler1 = TSampler<Vec1>;
   using Sampler2 = TSampler<Vec2>;
   using Sampler3 = TSampler<Vec3>;
   using Sampler4 = TSampler<Vec4>;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as a    
   /// sampler                                                                
   struct Sampler {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::Sampler3;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// sampler of the same size                                               
   template<Count S>
   struct SamplerOfSize : public Sampler {
      LANGULUS(CONCRETE) Math::TSampler<Math::TVector<Real, S>>;
      LANGULUS_BASES(Sampler);
      static constexpr Count MemberCount {S};
      static_assert(S > 0, "Normal size must be greater than zero");
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// sampler of the same type                                               
   template<CT::DenseNumber T>
   struct SamplerOfType : public Sampler {
      LANGULUS(CONCRETE) Math::TSampler<Math::TVector<T, 3>>;
      LANGULUS_BASES(Sampler);
      using MemberType = T;
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   A templated sampler                                                  
   /// It's just a vector, specialized for accessing textures/volumes         
   ///                                                                        
   template<CT::ScalarOrVector T>
   struct TSampler : public T {
      using PointType = T;
      using typename T::MemberType;
      using T::MemberCount;
      static_assert(MemberCount > 0, "Sampler size must be greater than zero");
      LANGULUS_BASES(A::SamplerOfSize<MemberCount>, A::SamplerOfType<MemberType>);

   public:
      using T::T;
      using T::mArray;

      /// Convert from any sampler to text                                    
      NOD() explicit operator Flow::Code() const {
         return T::template Serialize<TSampler>();
      }
   };

} // namespace Langulus::Math
