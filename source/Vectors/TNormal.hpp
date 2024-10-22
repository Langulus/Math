///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TVector.inl"


namespace Langulus
{
   namespace Math
   {

      LANGULUS_API(MATH) extern void RegisterNormals();

      template<CT::Vector T>
      struct TNormal;

      using Normal2   = TNormal<TVector<Real, 2>>;
      using Normal2f  = TNormal<TVector<Float, 2>>;
      using Normal2d  = TNormal<TVector<Double, 2>>;

      using Normal3   = TNormal<TVector<Real, 3>>;
      using Normal3f  = TNormal<TVector<Float, 3>>;
      using Normal3d  = TNormal<TVector<Double, 3>>;

      using Normal4   = TNormal<TVector<Real, 4>>;
      using Normal4f  = TNormal<TVector<Float, 4>>;
      using Normal4d  = TNormal<TVector<Double, 4>>;

      using Normal    = Normal3;
      using Normalf   = Normal3f;
      using Normald   = Normal3d;

   } // namespace Langulus::Math

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// normal                                                              
      struct Normal {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Normal;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// normal of the same size                                             
      template<Count S>
      struct NormalOfSize : Normal {
         LANGULUS(CONCRETE) Math::TNormal<Math::TVector<Langulus::Real, S>>;
         LANGULUS_BASES(Normal);

         static constexpr Count MemberCount {S};
         static_assert(MemberCount > 1,
            "Normal size must be greater than one");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// normal of the same type                                             
      template<CT::Number T>
      struct NormalOfType : Normal {
         LANGULUS(CONCRETE) Math::TNormal<Math::TVector<T, 4>>;
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(Normal);

         static_assert(CT::Real<T>,
            "Normal can be only made of real numbers");
      };

   } // namespace Langulus::A
   
   namespace Math
   {

      ///                                                                     
      ///   Templated normal                                                  
      ///                                                                     
      /// It is essentially a vector that gets normalized after any change    
      ///                                                                     
      template<CT::Vector T>
      struct TNormal : T {
         using PointType = T;
         using T::MemberCount;
         using T::T;

         static_assert(MemberCount > 1,
            "Normal size must be greater than one");
         static_assert(CT::Real<TypeOf<T>>,
            "Normal can be only made of real numbers");

      private:
         static consteval auto GenerateToken() {
            constexpr auto defaultClassName = RTTI::LastCppNameOf<TNormal>();
            ::std::array<char, defaultClassName.size() + 1> name {};
            ::std::size_t offset {};

            if constexpr (MemberCount > 4) {
               for (auto i : defaultClassName)
                  name[offset++] = i;
               return name;
            }

            // Write prefix                                             
            for (auto i : "Normal")
               name[offset++] = i;

            // Write size                                               
            --offset;
            name[offset++] = '0' + MemberCount;

            // Write suffix                                             
            for (auto i : SuffixOf<TypeOf<T>>())
               name[offset++] = i;
            return name;
         }

      public:
         LANGULUS(NAME)  GenerateToken();
         LANGULUS(TYPED) TypeOf<T>;
         LANGULUS_BASES(
            A::NormalOfSize<MemberCount>,
            A::NormalOfType<TypeOf<T>>,
            T
         );

         /// Construct a normal from a vector                                 
         ///   @param other - the vector to normalize                         
         LANGULUS(INLINED)
         constexpr TNormal(const T& other)
            : T {other.Normalize()} {}

         /// Manual construction via a variadic head-tail                     
         /// Excessive elements are ignored, missing elements are defaulted   
         template<class T1, class T2, class...TN> LANGULUS(INLINED)
         constexpr TNormal(const T1& t1, const T2& t2, const TN&...tn)
            : T {T {t1, t2, tn...}.Normalize()} {}

         /// Descriptor constructor                                           
         ///   @param describe - the descriptor                               
         TNormal(Describe&& describe)
            : T {::std::forward<Describe>(describe)} {
            const auto l = T::Length();
            LANGULUS_ASSERT(l != TypeOf<T> {0}, Arithmetic, "Degenerate normal");
            *this /= l;
         }

         /// Convert from any normal to code                                  
         LANGULUS(INLINED)
         explicit operator Flow::Code() const {
            return T::template Serialize<Flow::Code, TNormal>();
         }

         /// Convert from any normal to text                                  
         LANGULUS(INLINED)
         explicit operator Anyness::Text() const {
            return T::template Serialize<Anyness::Text, TNormal>();
         }
      };

   } // namespace Langulus::Math

} // namespace Langulus
