///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Vectors/TVector.hpp"


namespace Langulus::Math
{

   template<class T, Count S = 2>
   class TGradient;

   template<class T, Count S = 2>
   using TGrad = TGradient<T, S>;

   template<class T>
   using TGrad2 = TGradient<T, 2>;

   using Grad2v1 = TGrad2<Vec1>;
   using Grad2v1f = TGrad2<Vec1f>;
   using Grad2v1d = TGrad2<Vec1d>;
   using Grad2v1i = TGrad2<Vec1i>;
   using Grad2v1u = TGrad2<Vec1u>;

   using Grad2v2 = TGrad2<Vec2>;
   using Grad2v2f = TGrad2<Vec2f>;
   using Grad2v2d = TGrad2<Vec2d>;
   using Grad2v2i = TGrad2<Vec2i>;
   using Grad2v2u = TGrad2<Vec2u>;

   using Grad2v3 = TGrad2<Vec3>;
   using Grad2v3f = TGrad2<Vec3f>;
   using Grad2v3d = TGrad2<Vec3d>;
   using Grad2v3i = TGrad2<Vec3i>;
   using Grad2v3u = TGrad2<Vec3u>;

   using Grad2v4 = TGrad2<Vec4>;
   using Grad2v4f = TGrad2<Vec4f>;
   using Grad2v4d = TGrad2<Vec4d>;
   using Grad2v4i = TGrad2<Vec4i>;
   using Grad2v4u = TGrad2<Vec4u>;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as      
   /// a gradient                                                             
   struct Gradient {
      LANGULUS(ABSTRACT) true;
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated gradient                                                   
   ///                                                                        
   /// Useful for capsulating continuous properties and getting their         
   /// derivatives. Can capsulate anything, as long as it is arithmetic.      
   ///                                                                        
   template<class T, Count S>
   class TGradient : A::Gradient {
   protected:
      T mBuffer[S] {};
      Offset mIndex {};

   public:
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS_BASES(A::Gradient);

      using PointType = T;
      static constexpr Count StateCount = S;
      static_assert(S > 1, "Can't have a gradient with less than two states");

      constexpr TGradient() noexcept = default;
      constexpr TGradient(const T&) noexcept;
      constexpr TGradient(CT::NotSemantic auto&&...) noexcept;

      NOD() constexpr auto& operator [](const Offset&) const noexcept;
      NOD() constexpr auto& operator [](const Offset&) noexcept;

      NOD() constexpr bool operator == (const TGradient&) const noexcept;

      constexpr T& Revert() noexcept;
      constexpr T& Update() noexcept;

      NOD() constexpr const T& Current() const noexcept;
      NOD() constexpr T& Current() noexcept;

      NOD() constexpr const T& Previous() const noexcept;
      NOD() constexpr T& Previous() noexcept;

      NOD() constexpr T Delta() const;
      NOD() constexpr T Project(const T&) const;

      constexpr void Reset(const T&) noexcept;

      NOD() constexpr T Sum() const noexcept;

      void Integrate(Flow::Verb&);

      NOD() explicit operator Flow::Code() const;
   };

} // namespace Langulus::Math
