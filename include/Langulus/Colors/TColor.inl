///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TColor.hpp"
#include <Langulus/CT/Akin.hpp>


namespace Langulus::Math
{
   /// A default color is always opaque white                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr TColor<T>::TColor() noexcept
      : TColor<T> {255} {}

   /// Any single-parameter constructor for a color should go through         
   /// this constructor, so that the color is properly converted              
   ///   @attention color normalization relies on the type of the argument    
   ///      - if it is an integer and this color is based on a real number,   
   ///        then the entire color will be normalized in [0;1]               
   ///      - if it is a real and this color is based on an integer number,   
   ///        then the entire color will be scaled up by a factor if 255      
   ///      - if both types are the same category, no conversion will happen  
   TEMPLATE() template<class T1>
   requires ::std::constructible_from<T, T1> LANGULUS(INLINED)
   constexpr TColor<T>::TColor(T1&& t1) noexcept {
      using ALT_T = TypeOf<Deint<T1>>;
      if constexpr (T::IsReal and CT::Integer<ALT_T>) {
         // Make sure we normalize color if initializing a color made   
         // of real numbers with integers                               
         T::operator = (T {Math::Positive(t1)});
         *this /= ScalarType {255};
      }
      else if constexpr (not T::IsReal and CT::Real<ALT_T>) {
         // Make sure we scale up color if initializing a color made    
         // of integers with reals                                      
         SIMD::Multiply<true>(DeintCast(t1), ALT_T {255}, all);
      }
      else T::operator = (T {LglsFwd(t1)});

      // Make sure alpha channel is always opaque by default            
      // if not explicitly specified                                    
      if constexpr (ExtentOf<T1> < 4)
         MakeOpaque();
   }

   /// Any multi-parameter constructor for a color should go through          
   /// this constructor, so that the color is properly converted              
   ///   @attention color normalization relies on the type of the 1st argument
   ///      - if it is an integer and this color is based on a real number,   
   ///        then the entire color will be normalized in [0;1]               
   ///      - if it is a real and this color is based on an integer number,   
   ///        then the entire color will be scaled up by a factor if 255      
   ///      - if both types are the same category, no conversion will happen  
   TEMPLATE() template<class T1, class...TN>
   requires ::std::constructible_from<T, T1, TN...> LANGULUS(INLINED)
   constexpr TColor<T>::TColor(T1&& t1, TN&&...tn) noexcept {
      if constexpr (T::IsReal and CT::Integer<TypeOf<Deint<T1>>>) {
         // If we're initializing real color using integers,            
         // we have to divide by 255 and saturate (TODO)                
         T::operator = (T {Math::Positive(t1), Math::Positive(tn)...});
         *this /= ScalarType {255};
      }
      else if constexpr (not T::IsReal and CT::Real<TypeOf<Deint<T1>>>) {
         // If we're initializing integer color using reals,            
         // we have to multiply by 255 and saturate                     
         T::operator = (T {
            SIMD::Multiply<true>(Math::Positive(t1), T1 {255}),
            SIMD::Multiply<true>(Math::Positive(tn), TN {255})...
         });
      }
      else T::operator = (T {Math::Positive(t1), Math::Positive(tn)...});

      // Make sure alpha channel is always opaque by default            
      // if not explicitly specified                                    
      if constexpr (ExtentOf<T1, TN...> < 4)
         MakeOpaque();
   }
   
   /// Construct from a descriptor                                            
   ///   @param describe - the descriptor to scan                             
   TEMPLATE()
   TColor<T>::TColor(Describe&& describe) {
      LglsAssumeUser(*describe, "Empty descriptor for TVector");

      // Attempt initializing without any conversion                    
      auto initialized = describe.ExtractData(all);
      if constexpr (T::IsReal) {
         if (initialized) {
            // It was initialized from similar data, but we still have  
            // to saturate if real, or in other words clamp in [0;1]    
            SIMD::Min(all, ScalarType {1}, all);
            SIMD::Max(all, ScalarType {0}, all);
         }
      }

      if (not initialized) {
         // Attempt converting from any other kinds of numbers          
         ForEachOr(Typelists::Arithmetic{}, [&]<class AS>{
            if constexpr (not Same<ScalarType, AS>) {
               AS all_as[ExtentOf<T>];
               initialized = describe.ExtractData(all_as);
               if (initialized) {
                  if constexpr (T::IsReal and CT::Integer<AS>) {
                     // If we're initializing real color using integers,
                     // we have to divide by 255 and saturate (TODO)    
                     SIMD::Convert<T::Default>(all_as, this->all);
                     *this /= ScalarType {255};
                  }
                  else if constexpr (not T::IsReal and CT::Real<AS>) {
                     // If we're initializing integer color using reals,
                     // we have to multiply by 255 and saturate         
                     SIMD::Multiply(all_as, AS {255}, all_as);
                     SIMD::Min(all_as, ScalarType {255}, all_as);
                     SIMD::Max(all_as, ScalarType {  0}, all_as);
                     SIMD::Convert<T::Default>(all_as, this->all);
                  }
                  else SIMD::Convert<T::Default>(all_as, this->all);
               }
               return initialized > 0;
            }
            else return false;
         });
      }

      switch (initialized) {
      case 0:
         // Nothing was initialized. This is always an error in the     
         // context of the descriptor-constructor. If descriptor was    
         // empty, the default constructor would've been explicitly     
         // called, instead of this one. This way we can differentiate  
         // whether or not a vector object was successfully initialized.
         LglsError("Bad TVector descriptor", 
            ", nothing was initialized: ", *describe);
      case 1:
         // Only one provided element is handled as scalar constructor  
         // Copy first element in array to the rest                     
         for (; initialized < ExtentOf<T>; ++initialized)
            all[initialized] = all[0];
         break;
      default:
         // Initialize unavailable elements to the vector's default     
         for (; initialized < ExtentOf<T>; ++initialized)
            all[initialized] = T::Default;
         break;
      }

      // If alpha isn't initialized, make sure color is opaque          
      if (initialized < 4)
         MakeOpaque();
   }

   /// Covert a console color to a 3-component color                          
   ///   @param from - the console color to create from                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TColor<T>::TColor(Logger::Color from) noexcept 
      : TColor<T> {255} {
      reinterpret_cast<unsigned&>(from) &= 
         ~(static_cast<unsigned>(Logger::NextColor)
         | static_cast<unsigned>(Logger::PreviousColor)
      );

      switch (from) {
      case Logger::DarkBlue:
      case Logger::DarkBlueBgr:
         if constexpr (T::IsReal)
            blue = 0.5;
         else
            blue = 128;
         break;
      case Logger::Blue:
      case Logger::BlueBgr:
         if constexpr (T::IsReal)
            blue = 1.0;
         else
            blue = 255;
         break;
      case Logger::DarkGreen:
      case Logger::DarkGreenBgr:
         if constexpr (T::IsReal)
            green = 0.5;
         else
            green = 128;
         break;
      case Logger::DarkCyan:
      case Logger::DarkCyanBgr:
         if constexpr (T::IsReal) {
            red = green = 0.33333;
            blue = 0.5;
         }
         else {
            red = green = 85;
            blue = 128;
         }
         break;
      case Logger::Cyan:
      case Logger::CyanBgr:
         if constexpr (T::IsReal) {
            red = green = 0.5;
            blue = 1.0;
         }
         else {
            red = green = 128;
            blue = 255;
         }
         break;
      case Logger::Green:
      case Logger::GreenBgr:
         if constexpr (T::IsReal)
            green = 1.0;
         else
            green = 255;
         break;
      case Logger::DarkRed:
      case Logger::DarkRedBgr:
         if constexpr (T::IsReal)
            red = 0.5;
         else
            red = 128;
         break;
      case Logger::DarkPurple:
      case Logger::DarkPurpleBgr:
         if constexpr (T::IsReal)
            red = blue = 0.5;
         else
            red = blue = 128;
         break;
      case Logger::Purple:
      case Logger::PurpleBgr:
         if constexpr (T::IsReal)
            red = blue = 1.0;
         else
            red = blue = 255;
         break;
      case Logger::DarkYellow:
      case Logger::DarkYellowBgr:
         if constexpr (T::IsReal) {
            red = 0.5;
            green = 0.333333;
         }
         else {
            red = 128;
            green = 85;
         }
         break;
      case Logger::DarkGray:
      case Logger::DarkGrayBgr:
         if constexpr (T::IsReal)
            red = green = blue = 0.33333;
         else
            red = green = blue = 85;
         break;
      case Logger::Yellow:
      case Logger::YellowBgr:
         if constexpr (T::IsReal) {
            red = 1.0;
            green = 0.5;
         }
         else {
            red = 255;
            green = 128;
         }
         break;
      case Logger::Red:
      case Logger::RedBgr:
         if constexpr (T::IsReal)
            red = 1.0;
         else
            red = 255;
         break;
      case Logger::White:
      case Logger::WhiteBgr:
         if constexpr (T::IsReal)
            red = green = blue = 1.0;
         else
            red = green = blue = 255;
         break;
      case Logger::Gray:
      case Logger::GrayBgr:
         if constexpr (T::IsReal)
            red = green = blue = 0.5;
         else
            red = green = blue = 128;
         break;
      case Logger::Black:
      case Logger::BlackBgr:
      case Logger::NoForeground:
      case Logger::NoBackground:
         if constexpr (T::IsReal)
            red = green = blue = 0.0;
         else
            red = green = blue = 0;
         break;
      default:
         // Not reachable, but avoid warnings                           
         break;
      }
   }

   /// Fill the alpha channel                                                 
   /// Colors that do not have an alpha channel are implicitly opaque         
   TEMPLATE() LANGULUS(INLINED)
   constexpr void TColor<T>::MakeOpaque() noexcept {
      if constexpr (ExtentOf<T> >= 4) {
         if constexpr (T::IsReal)
            alpha = ScalarType {1};
         else
            alpha = ScalarType {255};
      }
      else LANGULUS(NOOP);
   }

   /// Copy a channel                                                         
   TEMPLATE() template<CT::Number ALTT, CT::Dimension D> LANGULUS(INLINED)
   constexpr auto TColor<T>::operator = (const TColorComponent<ALTT, D>& com) noexcept -> TColor& {
      static_assert(D::Index < ExtentOf<T>, "Index out of bounds");
      Get(D::Index) = Adapt(com.mValue);
      return *this; 
   }

   /// Convert from any color to code                                         
   /*TEMPLATE() LANGULUS(INLINED)
   TColor<T>::operator Flow::Code() const {
      return T::template Serialize<Flow::Code, TColor>();
   }

   /// Convert from any color to text                                         
   TEMPLATE() LANGULUS(INLINED)
   TColor<T>::operator Annies::Text() const {
      return T::template Serialize<Annies::Text, TColor>();
   }*/

   /// Covert to a console color                                              
   TEMPLATE() LANGULUS(INLINED)
   TColor<T>::operator Logger::Color() const {
      constexpr Logger::Color ColorMap[3][3][3] = {
         {
            // 0 Red                                                    
            { Logger::Black,     Logger::DarkBlue,    Logger::Blue   }, // 0 Green   
            { Logger::DarkGreen, Logger::DarkCyan,    Logger::Cyan   }, // 1 Green   
            { Logger::Green,     Logger::Cyan,        Logger::Cyan   }, // 2 Green   
            // ^ 0 blue       |   ^ 1 blue         |   ^ 2 blue         
         },
         {
            // 1 Red                                                    
            { Logger::DarkRed,   Logger::DarkPurple,  Logger::Purple }, // 0 Green   
            { Logger::DarkYellow,Logger::Gray,        Logger::Cyan   }, // 1 Green   
            { Logger::Yellow,    Logger::Green,       Logger::Cyan   }, // 2 Green   
            // ^ 0 blue       |   ^ 1 blue         |   ^ 2 blue         
         },
         {
            // 2 Red                                                    
            { Logger::Red,       Logger::Red,         Logger::Purple }, // 0 Green   
            { Logger::Yellow,    Logger::Red,         Logger::Purple }, // 1 Green   
            { Logger::Yellow,    Logger::Yellow,      Logger::White   },// 2 Green   
            // ^ 0 blue       |   ^ 1 blue         |   ^ 2 blue         
         }
      };

      constexpr bool IsReal = CT::Real<ScalarType>;
      constexpr ScalarType d3 {3};
      if constexpr (IsReal) {
         const auto rr = static_cast<::std::uint8_t>(Clamp01(r) * d3);
         const auto gg = static_cast<::std::uint8_t>(Clamp01(g) * d3);
         const auto bb = static_cast<::std::uint8_t>(Clamp01(b) * d3);
         return ColorMap[rr][gg][bb];
      }
      else {
         constexpr auto third = ::std::numeric_limits<ScalarType>::max() / d3;
         return ColorMap[r / third][g / third][b / third];
      }
   }
}