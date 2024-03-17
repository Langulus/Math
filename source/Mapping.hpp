///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
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
   struct MapMode {
      LANGULUS(POD) true;
      LANGULUS(NULLIFIABLE) true;
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
      constexpr MapMode() noexcept = default;
      constexpr MapMode(Type value) noexcept
         : mMode {value} {}

      constexpr bool operator == (const MapMode&) const = default;
   };

} // namespace Langulus::Math
