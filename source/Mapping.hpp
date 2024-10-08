///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Common.hpp"

LANGULUS_DEFINE_TRAIT(MapMode, "Mapping mode");


namespace Langulus::Math
{

   ///                                                                        
   ///   General mapper                                                       
   ///                                                                        
   /// Represents different tactics for mapping two properties to each other  
   ///                                                                        
   struct MapModeType {
      LANGULUS(POD) true;
      LANGULUS(NULLIFIABLE) true;
      LANGULUS(NAME) "MapMode";
      LANGULUS(INFO) "Mapping mode";

      using Type = uint8_t;

      enum Enum : Type {
         // Let context determine the mapping                           
         Auto = 0,
         // Map to the global position (after object transformation)    
         // This generally means any coordinates in the range of a      
         // single Math::Level                                          
         World,
         // Map to the local position (before any transformations)      
         // This usually means in the range of [0; 1] if model was made 
         // in the AssetGeometry module, but there are exceptions.      
         Model,
         // Map to position after object and view transformations       
         Projector,
         // Map to position after object, view and projection           
         Screen,
         // Map to a provided primitive, like plane, sphere, box, etc.  
         Primitive,
         // Triplanar (aka box mapping)                                 
         Triplanar,
         // Cube mapping (aka skybox mapping)                           
         Cube,
         // Face mapping, where each face maps to the same unit region  
         Face,
         // Packing each face in a unique location, but generate lots   
         // of seams                                                    
         Pack,
         // Packing each face in a unique location, trying to keep the  
         // relative surface area uniform; generates lots of seams, too 
         AdaptivePack,
         // Contour projection, mapping texture along a spline          
         Contour,
         // Unfold projection, unwrapping texture along precut seams    
         Unfold,
         // Texture coordinates inside the generated geometry are used  
         // If any of the above mappings are used at generation time,   
         // the mapping transits to this state                          
         Custom,

         Counter
      };

   protected:
      Type mMode = Enum::Auto;

      LANGULUS_NAMED_VALUES(
         Auto,
         World,
         Model,
         Projector,
         Screen,
         Primitive,
         Triplanar,
         Cube,
         Face,
         Pack,
         AdaptivePack,
         Contour,
         Unfold,
         Custom
      );

   public:
      constexpr MapModeType() noexcept = default;
      constexpr MapModeType(Type value) noexcept
         : mMode {value} {}

      constexpr bool operator == (const MapModeType&) const = default;
   };

   namespace MapMode
   {

      constexpr MapModeType Auto          {MapModeType::Auto         };
      constexpr MapModeType World         {MapModeType::World        };
      constexpr MapModeType Model         {MapModeType::Model        };
      constexpr MapModeType Projector     {MapModeType::Projector    };
      constexpr MapModeType Screen        {MapModeType::Screen       };
      constexpr MapModeType Primitive     {MapModeType::Primitive    };
      constexpr MapModeType Triplanar     {MapModeType::Triplanar    };
      constexpr MapModeType Cube          {MapModeType::Cube         };
      constexpr MapModeType Face          {MapModeType::Face         };
      constexpr MapModeType Pack          {MapModeType::Pack         };
      constexpr MapModeType AdaptivePack  {MapModeType::AdaptivePack };
      constexpr MapModeType Contour       {MapModeType::Contour      };
      constexpr MapModeType Unfold        {MapModeType::Unfold       };
      constexpr MapModeType Custom        {MapModeType::Custom       };

   } // namespace Langulus::Math::MapMode

} // namespace Langulus::Math
