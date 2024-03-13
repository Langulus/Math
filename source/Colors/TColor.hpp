///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Numbers/TColorComponent.hpp"


namespace Langulus
{
   namespace Math
   {
      template<CT::VectorBased>
      struct TColor;

      template<CT::DenseNumber, CT::Dimension>
      struct TColorComponent;

      using RGB24 = TColor<Vec3u8>;
      using RGBA32 = TColor<Vec4u8>;
      using RGBA = RGBA32;
      using RGB = RGB24;

      using RGB96 = TColor<Vec3f>;
      using RGBA128 = TColor<Vec4f>;
      using RGBAf = RGBA128;
      using RGBf = RGB96;

      using Red8 = TColorComponent<::std::uint8_t, Traits::R>;
      using Green8 = TColorComponent<::std::uint8_t, Traits::G>;
      using Blue8 = TColorComponent<::std::uint8_t, Traits::B>;
      using Alpha8 = TColorComponent<::std::uint8_t, Traits::A>;

      using Red32 = TColorComponent<Float, Traits::R>;
      using Green32 = TColorComponent<Float, Traits::G>;
      using Blue32 = TColorComponent<Float, Traits::B>;
      using Alpha32 = TColorComponent<Float, Traits::A>;

      using Depth16 = TColorComponent<::std::uint16_t, Traits::D>;
      using Depth32 = TColorComponent<Float, Traits::D>;

      using Red = Red8;
      using Green = Green8;
      using Blue = Blue8;
      using Alpha = Alpha8;
      using Depth = Depth32;

   } // namespace Langulus::Math

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// color                                                               
      struct Color {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::RGBA;
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// color of the same size                                              
      template<Count S>
      struct ColorOfSize : Color {
         LANGULUS(CONCRETE) Math::TColor<Math::TVector<::std::uint8_t, S>>;
         LANGULUS_BASES(Color);
         static constexpr Count MemberCount {S};
         static_assert(S > 0, "Color size must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// color of the same type                                              
      template<CT::DenseNumber T>
      struct ColorOfType : Color {
         LANGULUS(CONCRETE) Math::TColor<Math::TVector<T, 4>>;
         LANGULUS_BASES(Color);
         LANGULUS(TYPED) T;
      };

   } // namespace Langulus::A

   
   /// Custom name generator at compile-time for colors                       
   template<CT::VectorBased T>
   constexpr auto CustomName(Of<Math::TColor<T>>&&) noexcept {
      constexpr auto defaultClassName = RTTI::LastCppNameOf<Math::TColor<T>>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      // Write prefix                                                   
      switch (T::MemberCount) {
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
      if constexpr (not CT::Same<TypeOf<T>, ::std::uint8_t>) {
         if constexpr (CT::Same<TypeOf<T>, float>)
            name[offset++] = 'f';
         else if constexpr (CT::Same<TypeOf<T>, double>)
            name[offset++] = 'd';
         else for (auto i : SuffixOf<TypeOf<T>>())
            name[offset++] = i;
      }
      return name;
   }
   
   namespace Math
   {

      ///                                                                     
      ///   Templated color                                                   
      ///                                                                     
      #pragma pack(push, 1)
      template<CT::VectorBased T>
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

         using T::MemberCount;
         static_assert(MemberCount > 1 and MemberCount < 5,
            "Invalid number of channels");
         static constexpr bool CTTI_ColorTrait = true;

         LANGULUS(NAME) CustomNameOf<TColor>::Generate();
         LANGULUS_BASES(
            A::ColorOfSize<MemberCount>, 
            A::ColorOfType<TypeOf<T>>,
            T
         );

         using T::T;
         constexpr TColor(Logger::Color);

         using T::Get;
         using T::GetRaw;

         template<CT::DenseNumber ALTT, CT::Dimension D>
         constexpr TColor<T>& operator = (const TColorComponent<ALTT, D>&) noexcept;

         operator Flow::Code() const;
         operator Logger::Color() const;
      };
      #pragma pack(pop)

   } // namespace Langulus::Math

} // namespace Langulus