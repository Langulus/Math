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

   using rgb24 = TColor<vec3u8>;
   using rgba32 = TColor<vec4u8>;
   using rgb96 = TColor<vec3f>;
   using rgba128 = TColor<vec4f>;

   using rgba = rgba32;
   using rgb = rgb24;

   template<CT::DenseNumber, CT::Dimension>
   struct TColorComponent;

   using red8 = TColorComponent<uint8, Traits::R>;
   using green8 = TColorComponent<uint8, Traits::G>;
   using blue8 = TColorComponent<uint8, Traits::B>;
   using alpha8 = TColorComponent<uint8, Traits::A>;
   using red32 = TColorComponent<Float, Traits::R>;
   using green32 = TColorComponent<Float, Traits::G>;
   using blue32 = TColorComponent<Float, Traits::B>;
   using alpha32 = TColorComponent<Float, Traits::A>;
   using depth16 = TColorComponent<::std::uint16_t, Traits::D>;
   using depth32 = TColorComponent<Float, Traits::D>;

   using red = red8;
   using green = green8;
   using blue = blue8;
   using alpha = alpha8;
   using depth = depth32;

} // namespace Langulus::Math

namespace Langulus::A
{

   /// Used as an imposed base for any type that can be interpretable as a    
   /// color                                                                  
   struct Color {
      LANGULUS(ABSTRACT) true;
      LANGULUS(CONCRETE) Math::rgba;
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// color of the same size                                                 
   template<Count S>
   struct ColorOfSize : public Color {
      LANGULUS(CONCRETE) Math::TColor<Math::TVector<Math::uint8, S>>;
      LANGULUS_BASES(Color);
      static constexpr Count MemberCount {S};
      static_assert(S > 0, "Color size must be greater than zero");
   };

   /// Used as an imposed base for any type that can be interpretable as a    
   /// color of the same type                                                 
   template<CT::DenseNumber T>
   struct ColorOfType : public Color {
      LANGULUS(CONCRETE) Math::TColor<Math::TVector<T, 4>>;
      LANGULUS_BASES(Color);
      using MemberType = T;
   };

} // namespace Langulus::A

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated color                                                      
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::Vector T>
   struct TColor : public T {
   public:
      using PointType = T;
      using MemberType = typename T::MemberType;
      static constexpr Count MemberCount = T::MemberCount;
      LANGULUS_BASES(A::ColorOfSize<MemberCount>, A::ColorOfType<MemberType>);

   public:
      using T::T;
      using T::mArray;

      constexpr TColor(Logger::Color);

      template<CT::DenseNumber ALTT, CT::Dimension D>
      constexpr TColor<T>& operator = (const TColorComponent<ALTT, D>&) noexcept;

      NOD() explicit operator Flow::Code() const;
      NOD() explicit operator Logger::Color() const;
   };
   #pragma pack(pop)

} // namespace Langulus::Math

#include "TColor.inl"