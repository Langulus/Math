///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TColor.hpp"
#include "../Vectors/TVector.inl"

#define TEMPLATE() template<CT::VectorBased T>


namespace Langulus::Math
{

   /// Construct from any vector (with conversion)                            
   ///   @param a - vector to use                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TColor<T>::TColor(const CT::Vector auto& source) noexcept {
      SIMD::Convert<0>(DeintCast(source), all);
   }

   /// Covert a console color to a 3-component color                          
   ///   @param from - the console color to create from                       
   TEMPLATE()
   constexpr TColor<T>::TColor(Logger::Color from) : T {} {
      constexpr bool IsReal = CT::Real<TypeOf<T>>;

      if constexpr (MemberCount == 4) {
         if constexpr (IsReal)
            alpha = 1;
         else
            alpha = 255;
      }

      reinterpret_cast<unsigned&>(from) &= 
         ~(static_cast<unsigned>(Logger::NextColor)
         | static_cast<unsigned>(Logger::PreviousColor)
      );

      switch (from) {
      case Logger::DarkBlue:
      case Logger::DarkBlueBgr:
         if constexpr (IsReal)
            blue = 0.5;
         else
            blue = 128;
         break;
      case Logger::Blue:
      case Logger::BlueBgr:
         if constexpr (IsReal)
            blue = 1.0;
         else
            blue = 255;
         break;
      case Logger::DarkGreen:
      case Logger::DarkGreenBgr:
         if constexpr (IsReal)
            green = 0.5;
         else
            green = 128;
         break;
      case Logger::DarkCyan:
      case Logger::DarkCyanBgr:
         if constexpr (IsReal) {
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
         if constexpr (IsReal) {
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
         if constexpr (IsReal)
            green = 1.0;
         else
            green = 255;
         break;
      case Logger::DarkRed:
      case Logger::DarkRedBgr:
         if constexpr (IsReal)
            red = 0.5;
         else
            red = 128;
         break;
      case Logger::DarkPurple:
      case Logger::DarkPurpleBgr:
         if constexpr (IsReal)
            red = blue = 0.5;
         else
            red = blue = 128;
         break;
      case Logger::Purple:
      case Logger::PurpleBgr:
         if constexpr (IsReal)
            red = blue = 1.0;
         else
            red = blue = 255;
         break;
      case Logger::DarkYellow:
      case Logger::DarkYellowBgr:
         if constexpr (IsReal) {
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
         if constexpr (IsReal)
            red = green = blue = 0.33333;
         else
            red = green = blue = 85;
         break;
      case Logger::Yellow:
      case Logger::YellowBgr:
         if constexpr (IsReal) {
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
         if constexpr (IsReal)
            red = 1.0;
         else
            red = 255;
         break;
      case Logger::White:
      case Logger::WhiteBgr:
         if constexpr (IsReal)
            red = green = blue = 1.0;
         else
            red = green = blue = 255;
         break;
      case Logger::Gray:
      case Logger::GrayBgr:
         if constexpr (IsReal)
            red = green = blue = 0.5;
         else
            red = green = blue = 128;
         break;
      case Logger::Black:
      case Logger::BlackBgr:
      case Logger::NoForeground:
      case Logger::NoBackground:
         if constexpr (IsReal)
            red = green = blue = 0.0;
         else
            red = green = blue = 0;
         break;
      default:
         // Not reachable, but avoid warnings                           
         break;
      }
   }

   /// Copy a channel                                                         
   TEMPLATE()
   template<CT::Number ALTT, CT::Dimension D>
   constexpr auto TColor<T>::operator = (const TColorComponent<ALTT, D>& com) noexcept -> TColor& {
      static_assert(D::Index < MemberCount, "Index out of bounds");
      Get(D::Index) = Adapt(com.mValue);
      return *this; 
   }

   /// Serialize the color to flow code                                       
   TEMPLATE()
   TColor<T>::operator Flow::Code() const {
      if constexpr (CT::Same<TypeOf<T>, ::std::uint8_t>) {
         // Write as hex, if standard unsigned 8 bit color component    
         using Flow::Code;
         Code result;
         result += NameOf<TColor>();
         result += Code::Operator::OpenScope;
         auto bytes = reinterpret_cast<const Byte*>(all);
         const auto bytesEnd = bytes + sizeof(TColor);
         while (bytes != bytesEnd)
            result += Code::Hex(*(bytes++));
         result += Code::Operator::CloseScope;
         return Abandon(result);
      }
      else return T::template Serialize<Flow::Code, TColor>();

   }

   /// Covert to a console color                                              
   TEMPLATE()
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

      constexpr bool IsReal = CT::Real<TypeOf<T>>;
      constexpr TypeOf<T> d3 {3};
      if constexpr (IsReal) {
         const auto rr = static_cast<::std::uint8_t>(Clamp01(r) * d3);
         const auto gg = static_cast<::std::uint8_t>(Clamp01(g) * d3);
         const auto bb = static_cast<::std::uint8_t>(Clamp01(b) * d3);
         return ColorMap[rr][gg][bb];
      }
      else {
         constexpr auto third = ::std::numeric_limits<TypeOf<T>>::max() / d3;
         return ColorMap[r / third][g / third][b / third];
      }
   }

} // namespace Langulus::Math

#undef TEMPLATE

namespace Langulus::Math
{

   /// Luma weights for BT.601 standard, used for convertion to grayscale     
   constexpr Vec3 LumaBT601  {0.299,  0.587,  0.114 };

   /// Luma weights for BT.709 standard, used for convertion to grayscale     
   constexpr Vec3 LumaBT709  {0.2126, 0.7152, 0.0722};

   /// Luma weights for BT.2100 standard, used for convertion to grayscale    
   constexpr Vec3 LumaBT2100 {0.2627, 0.6780, 0.0593};

} // namespace Langulus::Math

namespace Langulus::Colors
{

   using ::Langulus::Math::RGBA;

   constexpr RGBA White       { 255, 255, 255, 255 };
   constexpr RGBA Black       {   0,   0,   0, 255 };
   constexpr RGBA Grey        { 127, 127, 127, 255 };
   constexpr RGBA Red         { 255,   0,   0, 255 };
   constexpr RGBA Green       {   0, 255,   0, 255 };
   constexpr RGBA DarkGreen   {   0, 128,   0, 255 };
   constexpr RGBA Blue        {   0,   0, 255, 255 };
   constexpr RGBA DarkBlue    {   0,   0, 128, 255 };
   constexpr RGBA Cyan        { 128, 128, 255, 255 };
   constexpr RGBA DarkCyan    {  80,  80, 128, 255 };
   constexpr RGBA Orange      { 128, 128,   0, 255 };
   constexpr RGBA Yellow      { 255, 255,   0, 255 };
   constexpr RGBA Purple      { 255,   0, 255, 255 };
   constexpr RGBA DarkPurple  { 128,   0, 128, 255 };

} // namespace Langulus::Colors


LANGULUS_DEFINE_CONSTANT(ColorWhite, ::Langulus::Colors::White,
   "Colors::White", "An opaque white color")
LANGULUS_DEFINE_CONSTANT(ColorBlack, ::Langulus::Colors::Black,
   "Colors::Black", "An opaque black color")
LANGULUS_DEFINE_CONSTANT(ColorGrey, ::Langulus::Colors::Grey,
   "Colors::Grey", "An opaque gray color")
LANGULUS_DEFINE_CONSTANT(ColorRed, ::Langulus::Colors::Red,
   "Colors::Red", "An opaque red color")
LANGULUS_DEFINE_CONSTANT(ColorGreen, ::Langulus::Colors::Green,
   "Colors::Green", "An opaque green color")
LANGULUS_DEFINE_CONSTANT(ColorDarkGreen, ::Langulus::Colors::DarkGreen,
   "Colors::DarkGreen", "An opaque dark green color")
LANGULUS_DEFINE_CONSTANT(ColorBlue, ::Langulus::Colors::Blue,
   "Colors::Blue", "An opaque blue color")
LANGULUS_DEFINE_CONSTANT(ColorDarkBlue, ::Langulus::Colors::DarkBlue,
   "Colors::DarkBlue", "An opaque dark blue color")
LANGULUS_DEFINE_CONSTANT(ColorCyan, ::Langulus::Colors::Cyan,
   "Colors::Cyan", "An opaque cyan color")
LANGULUS_DEFINE_CONSTANT(ColorDarkCyan, ::Langulus::Colors::DarkCyan,
   "Colors::DarkCyan", "An opaque dark cyan color")
LANGULUS_DEFINE_CONSTANT(ColorOrange, ::Langulus::Colors::Orange,
   "Colors::Orange", "An opaque orange color")
LANGULUS_DEFINE_CONSTANT(ColorYellow, ::Langulus::Colors::Yellow,
   "Colors::Yellow", "An opaque yellow color")
LANGULUS_DEFINE_CONSTANT(ColorPurple, ::Langulus::Colors::Purple,
   "Colors::Purple", "An opaque purple color")
LANGULUS_DEFINE_CONSTANT(ColorDarkPurple, ::Langulus::Colors::DarkPurple,
   "Colors::DarkPurple", "An opaque dark purple color")
