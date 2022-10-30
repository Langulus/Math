///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Arithmetics.hpp"

namespace Langulus::CT
{

   ///                                                                        
   /// All Langulus::Math arithmetic types have these properties              
   ///                                                                        

   /// Checks for a Cos() method                                              
   template<class T>
   concept HasCos = requires (const Decay<T> a) {
      {a.Cos()} -> CT::Data;
   };

   /// Checks for a Sin() method                                              
   template<class T>
   concept HasSin = requires (const Decay<T> a) {
      {a.Sin()} -> CT::Data;
   };

   /// Checks for a Atan() method                                             
   template<class T>
   concept HasAtan = requires (const Decay<T> a) {
      {a.Atan()} -> CT::Data;
   };

   /// Checks for a Atan2() method                                            
   template<class T1, class T2>
   concept HasAtan2 = requires (const Decay<T1> a, const Decay<T2> b) {
      {a.Atan2(b)} -> CT::Data;
   };

} // namespace Langulus::CT


namespace Langulus::Math
{

   ///                                                                        
   ///   Constants                                                            
   ///                                                                        
   template<CT::Real T = Real>
   constexpr T PI {3.1415926535897932385L};

   template<CT::Real T = Real>
   constexpr T TAU {PI<T> * T {2}};

   template<CT::Real T = Real>
   constexpr T HALFPI {PI<T> * T {0.5}};

   template<CT::Real T = Real>
   constexpr T PIi {T {1} / PI<T>};

   template<CT::Real T = Real>
   constexpr T TAUi {T {1} / TAU<T>};

   template<CT::Real T = Real>
   constexpr T HALFPIi {T {1} / HALFPI<T>};

   template<CT::Real T = Real>
   constexpr T LOGHALF {-0.30102999566L};

   template<CT::Real T = Real>
   constexpr T LOGHALFi {T {1} / LOGHALF<T>};

   template<CT::Real T = Real>
   constexpr T I180 {T {1} / T {180}};

   template<CT::Real T = Real>
   constexpr T PIxI180 {PI<T> * I180<T>};

   template<CT::Real T = Real>
   constexpr T PIix180 {PIi<T> * T {180}};

   template<CT::Real T = Real>
   constexpr T GOLDEN_ANGLE {(T {3} - Sqrt(T {5})) * PI<T>};
   
   /// Degree to radian conversion                                            
   ///   @param degrees - degrees to convert to radians                       
   template<CT::Dense T>
   NOD() LANGULUS(ALWAYSINLINE) constexpr auto DegToRad(const T& degrees) noexcept {
      if constexpr (CT::Real<T>)
         return degrees * PIxI180<T>;
      else
         return static_cast<Real>(degrees) * PIxI180<Real>;
   }

   /// Radians to degrees conversion                                          
   ///   @param radians - radians to convert to degrees                       
   template<CT::Dense T>
   NOD() LANGULUS(ALWAYSINLINE) constexpr auto RadToDeg(const T& radians) noexcept {
      if constexpr (CT::Real<T>)
         return radians * PIix180<T>;
      else
         return static_cast<Real>(radians) * PIxI180<Real>;
   }

   /// Calculate cosine                                                       
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T>
   NOD() LANGULUS(ALWAYSINLINE) auto Cos(const T& a) noexcept {
      if constexpr (CT::HasCos<T>)
         return a.Cos();
      else if constexpr (CT::Real<T>)
         return ::std::cos(BuiltinCast(a));
      else
         return ::std::cos(static_cast<Real>(BuiltinCast(a)));
   }

   /// Calculate sine                                                         
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T>
   NOD() LANGULUS(ALWAYSINLINE) auto Sin(const T& a) noexcept {
      if constexpr (CT::HasSin<T>)
         return a.Sin();
      else if constexpr (CT::Real<T>)
         return ::std::sin(BuiltinCast(a));
      else
         return ::std::sin(static_cast<Real>(BuiltinCast(a)));
   }

   /// Returns the arc tangent of x                                           
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T>
   NOD() LANGULUS(ALWAYSINLINE) auto Atan(const T& a) noexcept {
      if constexpr (CT::HasAtan<T>)
         return a.Atan();
      else if constexpr (CT::Real<T>)
         return ::std::atan(a);
      else
         return ::std::atan(static_cast<Real>(a));
   }

   /// Returns the arc tangent of y/x                                         
   ///   @attention if angle is not Radians or Degrees, it is assumed radians 
   ///   @param a - the angle                                                 
   template<CT::Dense T1, CT::Dense T2>
   NOD() LANGULUS(ALWAYSINLINE) auto Atan2(const T1& a, const T2& b) noexcept {
      if constexpr (CT::HasAtan2<T1, T2>)
         return a.Atan2(b);
      else if constexpr (CT::Real<T1, T2>)
         return ::std::atan2(b, a);
      else
         return ::std::atan2(static_cast<Real>(b), static_cast<Real>(a));
   }

} // namespace Langulus::Math
