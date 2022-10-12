///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TVector.hpp"
#include "../Numbers/Level.hpp"

namespace Langulus::Math
{

   using Force2 = TForce<vec2>;
   using Force3 = TForce<vec3>;
   using Force = Force3;


   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// force                                                               
      struct Force {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) ::Langulus::Math::Force;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// force of the same size                                              
      template<Count S>
      struct ForceOfSize : public Force {
         LANGULUS(CONCRETE) TForce<TVector<Real, S>>;
         LANGULUS_BASES(Force);
         static constexpr Count MemberCount {S};
         static_assert(S > 0, "Force size must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// force of the same type                                              
      template<CT::DenseNumber T>
      struct ForceOfType : public Force {
         LANGULUS(CONCRETE) TForce<TVector<T, 3>>;
         LANGULUS_BASES(Force);
         using MemberType = T;
      };

   } // namespace Langulus::Math::A


   ///                                                                        
   ///   Templated force                                                      
   ///                                                                        
   template<CT::Vector T>
   struct TForce : public T {
      using PointType = T;
      using MemberType = typename T::MemberType;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 0, "Force size must be greater than zero");
      LANGULUS_BASES(A::ForceOfSize<MemberCount>, A::ForceOfType<MemberType>);

      // The level in which the force operates                          
      Level mLevel {};

   public:
      using T::T;
      using T::mArray;

      /// Construct force from vector and level                               
      ///   @param force - the direction times magnitude of the force         
      ///   @param level - the level in which the force acts                  
      constexpr TForce(const T& force, Level level = {}) noexcept
         : T {force}
         , mLevel {level} {}

      /// Convert from any force to text                                      
      NOD() explicit operator Flow::Code() const {
         Flow::Code result;
         result += MetaOf<TForce>();
         result += Flow::Code::OpenScope;
         auto& asVector = static_cast<const T&>(*this);
         for (auto& x : asVector) {
            result += x;
            result += ", ";
         }
         result += mLevel;
         result += Flow::Code::CloseScope;
         return result;
      }
   };

} // namespace Langulus::Math