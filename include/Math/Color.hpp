///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../../source/Colors/TColor.inl"


namespace Langulus::Math
{

   /// Luma weights for BT.601 standard, used for convertion to grayscale     
   constexpr Vec3 LumaBT601  {0.299,  0.587,  0.114 };

   /// Luma weights for BT.709 standard, used for convertion to grayscale     
   constexpr Vec3 LumaBT709  {0.2126, 0.7152, 0.0722};

   /// Luma weights for BT.2100 standard, used for convertion to grayscale    
   constexpr Vec3 LumaBT2100 {0.2627, 0.6780, 0.0593};

} // namespace Langulus::Math

namespace Langulus
{
   namespace Colors
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

} // namespace Langulus
