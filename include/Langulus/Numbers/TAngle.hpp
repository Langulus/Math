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
#include <Langulus/Math/Tags.hpp>
#include <Langulus/CT/Lossless.hpp>
#include <Langulus/Describe.hpp>


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
   /// MARK: Constants                                                        
   ///                                                                        
   template<CT::Real T = Real>
   constexpr T PI {static_cast<T>(3.1415926535897932385L)};

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


   /// MARK: Functions                                                        
   /// Degrees to radians conversion                                          
   ///   @param degrees - degrees to convert to radians                       
   template<CT::Dense T> LANGULUS(INLINED)
   constexpr auto DegToRad(T const& degrees) noexcept {
      if constexpr (CT::Real<T>)
         return degrees * PIxI180<T>;
      else
         return static_cast<Real>(degrees) * PIxI180<Real>;
   }

   /// Radians to degrees conversion                                          
   ///   @param radians - radians to convert to degrees                       
   template<CT::Dense T> LANGULUS(INLINED)
   constexpr auto RadToDeg(T const& radians) noexcept {
      if constexpr (CT::Real<T>)
         return radians * PIix180<T>;
      else
         return static_cast<Real>(radians) * PIxI180<Real>;
   }


   template<CT::Number> struct TDegrees;
   template<CT::Number> struct TRadians;

   ///                                                                        
   /// MARK: Degrees                                                          
   /// Type used for representing angles in degrees                           
   template<CT::Number T>
   struct TDegrees : TNumber<T> {
      using Base = TNumber<T>;
      using Base::mValue;
      using Base::TNumber;
      using Base::operator =;
      using Base::operator bool;

      static constexpr bool Radians = false;

      template<CT::Number N> LANGULUS(ALWAYS_INLINED)
      constexpr TDegrees(const TDegrees<N>& d) noexcept
         : Base {d.mValue} {}

      template<CT::Number N> LANGULUS(ALWAYS_INLINED)
      constexpr TDegrees(const TRadians<N>& r) noexcept
         : Base {r.GetDegrees()} {}

      LANGULUS(ALWAYS_INLINED)
      constexpr T GetRadians() const noexcept {
         return DegToRad(mValue);
      }

      LANGULUS(ALWAYS_INLINED)
      constexpr T GetDegrees() const noexcept {
         return mValue;
      }

      LANGULUS(ALWAYS_INLINED)
      constexpr auto Cos() const noexcept -> Lossless<Real, T> {
         return ::std::cos(DegToRad(mValue));
      }

      LANGULUS(ALWAYS_INLINED)
      constexpr auto Sin() const noexcept -> Lossless<Real, T> {
         return ::std::sin(DegToRad(mValue));
      }
   };


   ///                                                                        
   /// MARK: Radians                                                          
   /// Type used for representing angles in radians                           
   template<CT::Number T>
   struct TRadians : TNumber<T> {
      using Base = TNumber<T>;
      using Base::mValue;
      using Base::TNumber;
      using Base::operator =;
      using Base::operator bool;

      static constexpr bool Radians = true;

      template<CT::Number N> LANGULUS(ALWAYS_INLINED)
      constexpr TRadians(const TDegrees<N>& d) noexcept
         : Base {d.GetRadians()} {}

      template<CT::Number N> LANGULUS(ALWAYS_INLINED)
      constexpr TRadians(const TRadians<N>& r) noexcept
         : Base {r.mValue} {}

      LANGULUS(ALWAYS_INLINED)
      constexpr T GetRadians() const noexcept {
         return mValue;
      }

      LANGULUS(ALWAYS_INLINED)
      constexpr T GetDegrees() const noexcept {
         return RadToDeg(mValue);
      }

      LANGULUS(ALWAYS_INLINED)
      constexpr auto Cos() const noexcept -> Lossless<Real, T> {
         return ::std::cos(mValue);
      }

      LANGULUS(ALWAYS_INLINED)
      constexpr auto Sin() const noexcept -> Lossless<Real, T> {
         return ::std::sin(mValue);
      }
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

      /// Describe-constructor                                                
      TAngle(Describe&& describe) {
         LglsAssumeUser(describe, "Empty descriptor for TAngle");

         // Attempt initializing without any conversion                 
         if (not describe.ExtractData(mValue)) {
            // Attempt converting anything to T                         
            if (not describe.ExtractDataAs(mValue)) {
               // Nothing was initialized. This is always an error in   
               // the context of the describe-constructor. If descriptor
               // was empty, the default constructor would've been      
               // explicitly called, instead of this one. This way we   
               // can find out whether or not an angle instance was     
               // initialized or not.                                   
               LglsError("Bad TAngle descriptor, nothing was initialized: ", *describe);
            }
         }
      }
   };


   /// Add two similar angles                                                 
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator + (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      if constexpr (Same<LHST, RHST>)
         return lhs.mValue + rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue + DegToRad(rhs.mValue);
      else 
         return lhs.mValue + RadToDeg(rhs.mValue);
   }

   /// Subtract two similar angles                                            
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator - (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      if constexpr (Same<LHST, RHST>)
         return lhs.mValue - rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue - DegToRad(rhs.mValue);
      else
         return lhs.mValue - RadToDeg(rhs.mValue);
   }

   /// Multiply two similar angles                                            
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator * (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      if constexpr (Same<LHST, RHST>)
         return lhs.mValue * rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue * DegToRad(rhs.mValue);
      else
         return lhs.mValue * RadToDeg(rhs.mValue);
   }
      
   /// Divide two similar angles                                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D> operator / (
      const TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) {
      if constexpr (Same<LHST, RHST>)
         return lhs.mValue / rhs.mValue;
      else if constexpr (LHST::Radians)
         return lhs.mValue / DegToRad(rhs.mValue);
      else
         return lhs.mValue / RadToDeg(rhs.mValue);
   }

   /// Destructively add two similar angles                                   
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator += (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs + rhs;
      return lhs;
   }
      
   /// Destructively subtract two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator -= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs - rhs;
      return lhs;
   }
      
   /// Destructively multiply two similar angles                              
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator *= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) noexcept {
      lhs = lhs * rhs;
      return lhs;
   }

   /// Destructively divide two similar angles                                
   template<CT::Angle LHST, CT::Angle RHST, CT::Dimension D> LANGULUS(INLINED)
   constexpr TAngle<LHST, D>& operator /= (
      TAngle<LHST, D>& lhs,
      const TAngle<RHST, D>& rhs
   ) {
      lhs = lhs / rhs;
      return lhs;
   }

   /// Real number of degrees literal                                         
   LANGULUS(INLINED)
   constexpr Degrees operator""_deg(long double n) noexcept {
      return {n};
   }

   /// Real number of degrees literal (from unsigned)                         
   LANGULUS(INLINED)
   constexpr Degrees operator""_deg(unsigned long long n) noexcept {
      return {n};
   }

   /// Real number of radians literal                                         
   LANGULUS(INLINED)
   constexpr Radians operator""_rad(long double n) noexcept {
      return {n};
   }

   /// Real number of radians literal (from unsigned)                         
   LANGULUS(INLINED)
   constexpr Radians operator""_rad(unsigned long long n) noexcept {
      return {n};
   }
}


   /// Convert from any angle to text                                         
   /*template<CT::Angle T, CT::Dimension D> LANGULUS(INLINED)
   TAngle<T, D>::operator Annies::Text() const {
      Annies::Text result;
      result += NameOf<TAngle>();
      result += Flow::Code::Operator::OpenScope;
      result += static_cast<Annies::Text>(mValue);
      result += Flow::Code::Operator::CloseScope;
      return result;
   }

   /// Convert from any angle to code                                         
   template<CT::Angle T, CT::Dimension D> LANGULUS(INLINED)
   TAngle<T, D>::operator Flow::Code() const {
      Flow::Code result;
      result += NameOf<TAngle>();
      result += Flow::Code::Operator::OpenScope;
      result += static_cast<Flow::Code>(mValue);
      result += Flow::Code::Operator::CloseScope;
      return result;
   }*/