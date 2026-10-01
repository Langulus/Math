///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"
#include "../Numbers/TColorComponent.hpp"


namespace Langulus::Math
{
   template<CT::CustomVector>
   struct TColor;

   template<CT::Number, CT::Dimension>
   struct TColorComponent;

   using RGB24   = TColor<Vec3u8>;
   using RGBA32  = TColor<Vec4u8>;
   using RGBA    = RGBA32;
   using RGB     = RGB24;

   using RGB96   = TColor<Vec3f>;
   using RGBA128 = TColor<Vec4f>;
   using RGBAf   = RGBA128;
   using RGBf    = RGB96;

   using Red8    = TColorComponent<uint8_t,  Tags::R>;
   using Green8  = TColorComponent<uint8_t,  Tags::G>;
   using Blue8   = TColorComponent<uint8_t,  Tags::B>;
   using Alpha8  = TColorComponent<uint8_t,  Tags::A>;

   using Red32   = TColorComponent<float,    Tags::R>;
   using Green32 = TColorComponent<float,    Tags::G>;
   using Blue32  = TColorComponent<float,    Tags::B>;
   using Alpha32 = TColorComponent<float,    Tags::A>;

   using Depth16 = TColorComponent<uint16_t, Tags::D>;
   using Depth32 = TColorComponent<float,    Tags::D>;

   using Red     = Red8;
   using Green   = Green8;
   using Blue    = Blue8;
   using Alpha   = Alpha8;
   using Depth   = Depth32;
}

namespace Langulus
{
   /// Abstract color                                                         
   struct Color {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::RGBA;
   };

   /// Abstract color of specific size                                        
   template<size_t S>
   struct ColorOfSize : Color {
      using CTTI_Concrete  = Math::TColor<Math::TVector<::std::uint8_t, S>>;
      using CTTI_Bases     = Color;
      using CTTI_Array     = Yes<S>;
      static_assert(S > 0, "Color size must be greater than zero");
   };

   /// Abstract color of specific type                                        
   template<CT::Number T>
   struct ColorOfType : Color {
      using CTTI_Concrete  = Math::TColor<Math::TVector<T, 4>>;
      using CTTI_Bases     = Color;
      using CTTI_Typed     = T;
   };
}

#define TEMPLATE() template<CT::CustomVector T>

namespace Langulus::Math
{
   ///                                                                        
   ///   Templated color                                                      
   ///                                                                        
   /// Unlike ordinary vectors, color vectors are based on integer types      
   /// and utilize saturation arithmetics.                                    
   ///                                                                        
   #pragma pack(push, 1)
   TEMPLATE()
   struct TColor : T {
      using T::r;
      using T::red;
      using T::g;
      using T::green;
      using T::b;
      using T::blue;
      using T::a;
      using T::alpha;
      using T::all;

      static_assert(ExtentOf<T> > 1 and ExtentOf<T> < 5,
         "Invalid number of channels");

   private:
      /// Custom name generator at compile-time for colors                    
      static constexpr auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TColor>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         // Write prefix                                                
         switch (ExtentOf<T>) {
         case 2:
            for (auto i : "Grayscale")
               name[offset++] = i;
            break;
         case 3:
            for (auto i : "RGB")
               name[offset++] = i;
            break;
         case 4:
            for (auto i : "RGBA")
               name[offset++] = i;
            break;
         }

         // Write suffix                                                
         --offset;

         using InnerT = TypeOf<T>;
         if constexpr (not Same<InnerT, ::std::uint8_t>) {
            if constexpr (Same<InnerT, float>)
               name[offset++] = 'f';
            else if constexpr (Same<InnerT, double>)
               name[offset++] = 'd';
            else for (auto i : SuffixOf<InnerT>())
               name[offset++] = i;
         }
         return name;
      }

   public:
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Bases     = Types<ColorOfSize<ExtentOf<T>>, ColorOfType<TypeOf<T>>, T>;
      using CTTI_Color     = Yup;
      using CTTI_Saturated = Yup;

   public:
      constexpr TColor() noexcept;

      template<class T1> requires ::std::constructible_from<T, T1>
      constexpr TColor(T1&&) noexcept;

      template<class T1, class...TN> requires ::std::constructible_from<T, T1, TN...>
      constexpr TColor(T1&&, TN&&...) noexcept;

      constexpr TColor(Logger::Color) noexcept;
      TColor(Describe&&);

      using T::Get;
      using T::operator =;

      template<CT::Number ALTT, CT::Dimension D>
      constexpr auto operator = (const TColorComponent<ALTT, D>&) noexcept -> TColor&;

      /*explicit operator Flow::Code() const;
      explicit operator Annies::Text() const;*/
      explicit operator Logger::Color() const;

      constexpr void MakeOpaque() noexcept;
   };
   #pragma pack(pop)
}

#include "TColor.inl"

#undef TEMPLATE

namespace Langulus::Math
{
   /// Luma weights for BT.601 standard, used for convertion to grayscale     
   constexpr Vec3 LumaBT601  {0.299,  0.587,  0.114 };

   /// Luma weights for BT.709 standard, used for convertion to grayscale     
   constexpr Vec3 LumaBT709  {0.2126, 0.7152, 0.0722};

   /// Luma weights for BT.2100 standard, used for convertion to grayscale    
   constexpr Vec3 LumaBT2100 {0.2627, 0.6780, 0.0593};
}

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
}

namespace Langulus::CTTI
{
   /// RGBA color constants                                                   
   struct DefineConstant<Math::RGBA> : Types<
      NamedValue<Colors::White,     "Colors::White",     "An opaque white color">,
      NamedValue<Colors::Black,     "Colors::Black",     "An opaque black color">,
      NamedValue<Colors::Grey,      "Colors::Grey",      "An opaque grey color">,
      NamedValue<Colors::Red,       "Colors::Red",       "An opaque red color">,
      NamedValue<Colors::Green,     "Colors::Green",     "An opaque green color">,
      NamedValue<Colors::DarkGreen, "Colors::DarkGreen", "An opaque dark green color">,
      NamedValue<Colors::Blue,      "Colors::Blue",      "An opaque blue color">,
      NamedValue<Colors::DarkBlue,  "Colors::DarkBlue",  "An opaque dark blue color">,
      NamedValue<Colors::Cyan,      "Colors::Cyan",      "An opaque cyan color">,
      NamedValue<Colors::DarkCyan,  "Colors::DarkCyan",  "An opaque dark cyan color">,
      NamedValue<Colors::Orange,    "Colors::Orange",    "An opaque orange color">,
      NamedValue<Colors::Yellow,    "Colors::Yellow",    "An opaque yellow color">,
      NamedValue<Colors::Purple,    "Colors::Purple",    "An opaque purple color">,
      NamedValue<Colors::DarkPurple,"Colors::DarkPurple","An opaque dark purple color">,
   > {};
}