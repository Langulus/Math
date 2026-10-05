///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TVector.hpp"


namespace Langulus::Math
{
   template<CT::CustomVector>
   struct TNormal;

   using Normal2   = TNormal<TVector<Real, 2>>;
   using Normal2f  = TNormal<TVector<float, 2>>;
   using Normal2d  = TNormal<TVector<double, 2>>;

   using Normal3   = TNormal<TVector<Real, 3>>;
   using Normal3f  = TNormal<TVector<float, 3>>;
   using Normal3d  = TNormal<TVector<double, 3>>;

   using Normal4   = TNormal<TVector<Real, 4>>;
   using Normal4f  = TNormal<TVector<float, 4>>;
   using Normal4d  = TNormal<TVector<double, 4>>;

   /// Abstract normal, used to pick a concrete type depending on context  
   struct Normal {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Normal3;
   };

   /// Abstract normal of specific size                                    
   template<size_t S>
   struct NormalOfSize : Normal {
      using CTTI_Concrete  = Math::TNormal<Math::TVector<Langulus::Real, S>>;
      using CTTI_Bases     = Normal;
      using CTTI_Array     = Yes<S>;
      static_assert(S > 1, "Normal size must be greater than one");
   };

   /// Abstract normal of specific type                                    
   template<CT::Scalar T>
   struct NormalOfType : Normal {
      using CTTI_Concrete  = Math::TNormal<Math::TVector<T, 4>>;
      using CTTI_Typed     = T;
      using CTTI_Bases     = Normal;
      static_assert(CT::Real<T>, "Normals can be only made of real numbers");
   };
   

   ///                                                                     
   ///   Templated normal                                                  
   ///                                                                     
   /// It is essentially a vector that gets normalized after any change    
   ///                                                                     
   template<CT::CustomVector T>
   struct TNormal : T {
      using ScalarType = typename T::ScalarType;
      static_assert(ExtentOf<T> > 1,
         "Normal size must be greater than one");
      static_assert(CT::Real<ScalarType>,
         "Normal can be only made of real numbers");

   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TNormal>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (ExtentOf<T> > 4) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                             
         for (auto i : "Normal")
            name[offset++] = i;

         // Write size                                               
         --offset;
         name[offset++] = '0' + ExtentOf<T>;

         // Write suffix                                             
         for (auto i : SuffixOf<ScalarType>())
            name[offset++] = i;
         return name;
      }

   public:
      using CTTI_Normalized   = Yup;
      using CTTI_Named        = Yes<GenerateToken()>;
      using CTTI_Bases        = Types<NormalOfSize<ExtentOf<T>>, NormalOfType<ScalarType>, T>;

      /// A default normal doesn't make sense - it will be degenerate      
      TNormal() = delete("A default normal doesn't make sense - it will end up degenerate");

      /// Any constructor for a vector should go through this constructor, 
      /// so that the vector is later normalized                           
      constexpr TNormal(auto&&...tn)
         : T {T {LglsFwd(tn)...}.Normalize()} {}

//TODO normalize on assignment?
      /// Convert from any normal to code                                  
      /*LANGULUS(INLINED)
      explicit operator Flow::Code() const {
         return T::template Serialize<Flow::Code, TNormal>();
      }

      /// Convert from any normal to text                                  
      LANGULUS(INLINED)
      explicit operator Annies::Text() const {
         return T::template Serialize<Annies::Text, TNormal>();
      }*/

      /// Check if all components are zero                                 
      LANGULUS(INLINED)
      constexpr bool IsDegenerate() const noexcept {
         bool result;
         SIMD::Equals(T::all, ScalarType {0}, result);
         return result;
      }
   };
}
