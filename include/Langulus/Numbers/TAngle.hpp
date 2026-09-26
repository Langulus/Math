///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Langulus/CT/Convertible.hpp"
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
   /// Abstract angle                                                         
   struct Angle {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Radians;
   };

   /// Abstract angle of specific dimension                                   
   template<CT::Dimension D>
   struct AngleOfDimension : Angle {
      using CTTI_Concrete  = Math::TAngle<Math::Radians, D>;
      using CTTI_Bases     = Angle;
   };

   /// Abstract angle of specific type                                        
   template<CT::Angle T>
   struct AngleOfType : Angle {
      using CTTI_Concrete  = T;
      using CTTI_Typed     = T;
      using CTTI_Bases     = Angle;
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
         constexpr auto defaultClassName = LastCppNameOf<TAngle>();
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
      using CTTI_Typed = Yes<GenerateToken()>;
      using CTTI_Bases = Types<T, AngleOfDimension<D>, AngleOfType<T>>;

      using Dimension = D;
      using T::mValue;
      using T::T;
      using T::operator =;
      TAngle(Describe&&);
   };
}