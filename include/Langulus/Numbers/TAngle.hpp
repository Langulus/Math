///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TNumber.hpp"
#include "Dimension.hpp"
#include "../Math/Tags.hpp"
#include <Langulus/CT/Lossless.hpp>


namespace Langulus::CT
{
   /// Concept for an angle                                                   
   template<class...T>
   concept Angle = Number<T...> and (requires {
         {Decay<T>::Radians} -> Bool;
      } and ...);

   /// Concept for angle in degrees                                           
   template<class...T>
   concept Degrees = Angle<T...> and ((not Decay<T>::Radians) and ...);

   /// Concept for angle in radians                                           
   template<class...T>
   concept Radians = Angle<T...> and (Decay<T>::Radians and ...);
}

namespace Langulus::Math
{
   template<CT::Number> struct TDegrees;
   template<CT::Number> struct TRadians;


   ///                                                                        
   ///   Type used for representing angles in degrees                         
   ///                                                                        
   template<CT::Number T>
   struct TDegrees : TNumber<T, TDegrees<T>> {
      using Base = TNumber<T, TDegrees<T>>;
      using Base::mValue;
      static constexpr bool Radians = false;

      constexpr TDegrees() noexcept = default;
      constexpr TDegrees(const TDegrees&) noexcept = default;
      constexpr TDegrees(TDegrees&&) noexcept = default;

      template<CT::Number N>
      constexpr TDegrees(const TDegrees<N>&) noexcept;

      template<CT::Number N>
      constexpr TDegrees(const TRadians<N>&) noexcept;

      constexpr TDegrees(const CT::Number auto&) noexcept;

      TDegrees& operator = (const TDegrees&) noexcept = default;
      TDegrees& operator = (TDegrees&&) noexcept = default;

      constexpr T GetRadians() const noexcept;
      constexpr T GetDegrees() const noexcept;

      Lossless<Real, T> Cos() const noexcept;
      Lossless<Real, T> Sin() const noexcept;

      using Base::operator bool;
   };


   ///                                                                        
   ///   Type used for representing angles in radians                         
   ///                                                                        
   template<CT::Number T>
   struct TRadians : TNumber<T, TRadians<T>> {
      using Base = TNumber<T, TRadians<T>>;
      using Base::mValue;
      static constexpr bool Radians = true;

      constexpr TRadians() noexcept = default;
      constexpr TRadians(const TRadians&) noexcept = default;
      constexpr TRadians(TRadians&&) noexcept = default;

      template<CT::Number N>
      constexpr TRadians(const TRadians<N>&) noexcept;

      template<CT::Number N>
      constexpr TRadians(const TDegrees<N>&) noexcept;

      constexpr TRadians(const CT::Number auto&) noexcept;

      TRadians& operator = (const TRadians&) noexcept = default;
      TRadians& operator = (TRadians&&) noexcept = default;

      constexpr T GetRadians() const noexcept;
      constexpr T GetDegrees() const noexcept;

      Lossless<Real, T> Cos() const noexcept;
      Lossless<Real, T> Sin() const noexcept;

      using Base::operator bool;
   };

   using Degrees = TDegrees<Real>;
   using Radians = TRadians<Real>;

   template<CT::Angle T, CT::Dimension D>
   struct TAngle;

   template<CT::Angle T> using TYaw    = TAngle<T, Tags::Y>;
   template<CT::Angle T> using TPitch  = TAngle<T, Tags::X>;
   template<CT::Angle T> using TRoll   = TAngle<T, Tags::Z>;

   using Yawdf   = TYaw<TDegrees<float>>;
   using Yawdd   = TYaw<TDegrees<double>>;
   using Yawrf   = TYaw<TRadians<float>>;
   using Yawrd   = TYaw<TRadians<double>>;

   using Pitchdf = TPitch<TDegrees<float>>;
   using Pitchdd = TPitch<TDegrees<double>>;
   using Pitchrf = TPitch<TRadians<float>>;
   using Pitchrd = TPitch<TRadians<double>>;

   using Rolldf  = TRoll<TDegrees<float>>;
   using Rolldd  = TRoll<TDegrees<double>>;
   using Rollrf  = TRoll<TRadians<float>>;
   using Rollrd  = TRoll<TRadians<double>>;
                  
   using Yawd    = TYaw<Degrees>;
   using Yawr    = TYaw<Radians>;
   using Pitchd  = TPitch<Degrees>;
   using Pitchr  = TPitch<Radians>;
   using Rolld   = TRoll<Degrees>;
   using Rollr   = TRoll<Radians>;
                  
   using Yaw     = TYaw<Radians>;
   using Pitch   = TPitch<Radians>;
   using Roll    = TRoll<Radians>;

   constexpr Degrees operator""_deg(long double n) noexcept;
   constexpr Degrees operator""_deg(unsigned long long n) noexcept;
   constexpr Radians operator""_rad(long double n) noexcept;
   constexpr Radians operator""_rad(unsigned long long n) noexcept;
}

namespace Langulus
{
   /// Used as an imposed base for any type that can be interpretable as   
   /// an angle                                                            
   struct Angle {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::Radians;
   };

   /// Used as an imposed base for any type that can be interpretable as   
   /// an angle of the same dimension                                      
   template<CT::Dimension D>
   struct AngleOfDimension : Angle {
      LANGULUS(CONCRETE) Math::TAngle<Math::Radians, D>;
      LANGULUS_BASES(Angle);
   };

   /// Used as an imposed base for any type that can be interpretable as   
   /// an angle of the same type                                           
   template<CT::Angle T>
   struct AngleOfType : Angle {
      LANGULUS(CONCRETE) T;
      LANGULUS(TYPED) T;
      LANGULUS_BASES(Angle);
   };
}
   
namespace Langulus::Math
{
   ///                                                                     
   ///   Templated angle                                                   
   ///                                                                     
   template<CT::Angle T, CT::Dimension D>
   struct TAngle : T {
   private:
      static constexpr auto GenerateToken() {
         constexpr auto defaultClassName = RTTI::LastCppNameOf<TAngle>();
         // Provision a bit more in case default class name turns out
         // to be too small (g++-14 complains for some reason)       
         ::std::array<char, defaultClassName.size() + 16> name {};
         ::std::size_t offset = 0;

         // Write dimension name                                     
         if constexpr (D::Index == 0) {
            for (auto i : "Pitch")
               name[offset++] = i;
         }
         else if constexpr (D::Index == 1) {
            for (auto i : "Yaw")
               name[offset++] = i;
         }
         else if constexpr (D::Index == 2) {
            for (auto i : "Roll")
               name[offset++] = i;
         }
         else static_assert(false, "Unsupported dimension");

         // Write angle suffix if degrees                            
         // Radians have no suffix by default                        
         if constexpr (CT::Degrees<T>)
            name[offset++] = 'd';

         // Write type suffix                                        
         for (auto i : SuffixOf<T>())
            name[offset++] = i;
         return name;
      }

   public:
      LANGULUS(NAME) GenerateToken();
      LANGULUS_BASES(T, A::AngleOfDimension<D>, A::AngleOfType<T>);
      LANGULUS_CONVERTS_TO(Annies::Text, Flow::Code);

      using Dimension = D;
      using T::mValue;
      using T::T;
      using T::operator =;
      TAngle(Describe&&);

      explicit operator Annies::Text() const;
      explicit operator Flow::Code() const;
   };
}
