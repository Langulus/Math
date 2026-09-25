///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Numbers/TColorComponent.hpp"


namespace Langulus::Math
{
   template<CT::Vector>
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

namespace Langulus::Math
{
   ///                                                                        
   ///   Templated color                                                      
   ///                                                                        
   /// Unlike ordinary vectors, color vectors are based on integer types      
   /// and utilize saturation arithmetics.                                    
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::Vector T>
   struct TColor : T {
      using InnerT = TypeOf<T>;

      using T::r;
      using T::red;
      using T::g;
      using T::green;
      using T::b;
      using T::blue;
      using T::a;
      using T::alpha;

      using T::all;

      static constexpr InnerT Default = T::Default;
      static constexpr size_t MemberCount = T::MemberCount;
      static constexpr bool IsReal = T::IsReal;
      static constexpr bool CTTI_ColorTrait = true;
      static constexpr bool CTTI_SaturatedTrait = true;

      static_assert(MemberCount > 1 and MemberCount < 5,
         "Invalid number of channels");

   private:
      /// Custom name generator at compile-time for colors                    
      static constexpr auto GenerateToken() {
         constexpr auto defaultClassName = RTTI::LastCppNameOf<TColor>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         // Write prefix                                                
         switch (MemberCount) {
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

         if constexpr (not CT::Same<InnerT, ::std::uint8_t>) {
            if constexpr (CT::Same<InnerT, float>)
               name[offset++] = 'f';
            else if constexpr (CT::Same<InnerT, double>)
               name[offset++] = 'd';
            else for (auto i : SuffixOf<InnerT>())
               name[offset++] = i;
         }
         return name;
      }

   public:
      using CTTI_Named = Yes<GenerateToken()>;
      using CTTI_Bases = Types<ColorOfSize<MemberCount>, ColorOfType<InnerT>, T>;

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

      explicit operator Flow::Code() const;
      explicit operator Annies::Text() const;
      explicit operator Logger::Color() const;

      constexpr void MakeOpaque() noexcept;
   };
   #pragma pack(pop)
}