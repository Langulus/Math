///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Numbers/TColorComponent.hpp"

namespace Langulus::Math
{

   template<CT::Vector>
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

   using Red8 = TColorComponent<uint8, Traits::R>;
   using Green8 = TColorComponent<uint8, Traits::G>;
   using Blue8 = TColorComponent<uint8, Traits::B>;
   using Alpha8 = TColorComponent<uint8, Traits::A>;

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

namespace Langulus::A
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
      LANGULUS(CONCRETE) Math::TColor<Math::TVector<Math::uint8, S>>;
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

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated color                                                      
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::Vector T>
   struct TColor : T {
      using T::MemberCount;
      using T::T;
      using T::mArray;

   private:
      static constexpr auto DefaultClassName = RTTI::LastNameOf<TColor>();
      using ClassName = ::std::array<char, DefaultClassName.size() + 1>;
      static constexpr ClassName GenerateClassName() noexcept;
      static constexpr ClassName GeneratedClassName = GenerateClassName();

   public:
      LANGULUS(NAME) GeneratedClassName.data();

      LANGULUS_BASES(
         A::ColorOfSize<MemberCount>, 
         A::ColorOfType<TypeOf<T>>,
         T
      );

      constexpr TColor(Logger::Color);

      template<CT::DenseNumber ALTT, CT::Dimension D>
      constexpr TColor<T>& operator = (const TColorComponent<ALTT, D>&) noexcept;

      operator Flow::Code() const;
      operator Logger::Color() const;
   };
   #pragma pack(pop)

} // namespace Langulus::Math

#include "TColor.inl"