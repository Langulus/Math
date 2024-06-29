///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"


namespace Langulus
{
   namespace CT
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

   } // namespace Langulus::CT

   namespace Math
   {

      LANGULUS_API(MATH) extern void RegisterAngles();

      template<CT::Number>
      struct TDegrees;

      template<CT::Number>
      struct TRadians;


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

         NOD() constexpr T GetRadians() const noexcept;
         NOD() constexpr T GetDegrees() const noexcept;

         NOD() Lossless<Real, T> Cos() const noexcept;
         NOD() Lossless<Real, T> Sin() const noexcept;

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

         NOD() constexpr T GetRadians() const noexcept;
         NOD() constexpr T GetDegrees() const noexcept;

         NOD() Lossless<Real, T> Cos() const noexcept;
         NOD() Lossless<Real, T> Sin() const noexcept;

         using Base::operator bool;
      };

      using Degrees = TDegrees<Real>;
      using Radians = TRadians<Real>;

      template<CT::Angle T, CT::Dimension D>
      struct TAngle;

      template<CT::Angle T>
      using TYaw    = TAngle<T, Traits::Y>;
      template<CT::Angle T>
      using TPitch  = TAngle<T, Traits::X>;
      template<CT::Angle T>
      using TRoll   = TAngle<T, Traits::Z>;

      using Yawdf   = TYaw<TDegrees<Float>>;
      using Yawdd   = TYaw<TDegrees<Double>>;
      using Yawrf   = TYaw<TRadians<Float>>;
      using Yawrd   = TYaw<TRadians<Double>>;

      using Pitchdf = TPitch<TDegrees<Float>>;
      using Pitchdd = TPitch<TDegrees<Double>>;
      using Pitchrf = TPitch<TRadians<Float>>;
      using Pitchrd = TPitch<TRadians<Double>>;

      using Rolldf  = TRoll<TDegrees<Float>>;
      using Rolldd  = TRoll<TDegrees<Double>>;
      using Rollrf  = TRoll<TRadians<Float>>;
      using Rollrd  = TRoll<TRadians<Double>>;
                    
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

   } // namespace Langulus::Math

   namespace A
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

   } // namespace Langulus::A
   
   /// Custom name generator at compile-time for angles                       
   template<CT::Angle T, CT::Dimension D>
   constexpr auto CustomName(Of<Math::TAngle<T,D>>&&) noexcept {
      constexpr auto defaultClassName = RTTI::LastCppNameOf<Math::TAngle<T, D>>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

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
      else LANGULUS_ERROR("Unsupported dimension");

      // Write angle suffix if degrees                                  
      // Radians have no suffix by default                              
      if constexpr (CT::Degrees<T>)
         name[offset++] = 'd';

      // Write type suffix                                              
      for (auto i : SuffixOf<T>())
         name[offset++] = i;
      return name;
   }

   namespace Math
   {

      ///                                                                     
      ///   Templated angle                                                   
      ///                                                                     
      template<CT::Angle T, CT::Dimension D>
      struct TAngle : T {
         LANGULUS(NAME) CustomNameOf<TAngle>::Generate();
         LANGULUS_BASES(T, A::AngleOfDimension<D>, A::AngleOfType<T>);
         LANGULUS_CONVERTS_TO(Anyness::Text, Flow::Code);
         using Dimension = D;

         using T::mValue;

         using T::T;
         using T::operator =;
         TAngle(Describe&&);

         NOD() explicit operator Anyness::Text() const;
         NOD() explicit operator Flow::Code() const;
      };

   } // namespace Langulus::Math

} // namespace Langulus