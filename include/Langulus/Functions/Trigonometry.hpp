///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
//#include <Langulus/Core.hpp>
#include <Langulus/CT/Real.hpp>
#include <cmath>


namespace Langulus::Math
{
   ///                                                                        
   /// MARK: Functions                                                        
   ///                                                                        

   /// Calculate cosine                                                       
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T> LANGULUS(INLINED)
   auto Cos(const T& a) noexcept {
      if constexpr (requires (T a) { {a.Cos()} -> CT::NotVoid; })
         return a.Cos();
      else if constexpr (CT::Real<T>)
         return ::std::cos(FundamentalCast(a));
      else
         return ::std::cos(static_cast<Real>(FundamentalCast(a)));
   }

   /// Calculate sine                                                         
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T> LANGULUS(INLINED)
   auto Sin(const T& a) noexcept {
      if constexpr (requires (T a) { {a.Sin()} -> CT::NotVoid; })
         return a.Sin();
      else if constexpr (CT::Real<T>)
         return ::std::sin(FundamentalCast(a));
      else
         return ::std::sin(static_cast<Real>(FundamentalCast(a)));
   }

   /// Returns the arc tangent of x                                           
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T> LANGULUS(INLINED)
   auto Atan(const T& a) noexcept {
      if constexpr (requires (T a) { {a.Atan()} -> CT::NotVoid; })
         return a.Atan();
      else if constexpr (CT::Real<T>)
         return ::std::atan(a);
      else
         return ::std::atan(static_cast<Real>(a));
   }

   /// Returns the arc tangent of y/x                                         
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T1, CT::Dense T2> LANGULUS(INLINED)
   auto Atan2(const T1& a, const T2& b) noexcept {
      if constexpr (requires (T1 a, T2 b) { {a.Atan2(b)} -> CT::NotVoid; })
         return a.Atan2(b);
      else if constexpr (CT::Real<T1, T2>)
         return ::std::atan2(b, a);
      else
         return ::std::atan2(static_cast<Real>(b), static_cast<Real>(a));
   }
}
