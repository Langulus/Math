///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
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
         // Map to the global position (after object transformation)    
         // This generally means any coordinates in the range of a      
         // single Math::Level                                          
         World = 0,
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
         // Cube mapping                                                
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
      Type mMode {Enum::World};

      LANGULUS_NAMED_VALUES(Enum) {
         {
            "World",
            Enum::World,
            "Map to the global position (after object transformation). "
            "This generally means any coordinates in the range of a "
            "single Math::Level"
         },
         {
            "Model",
            Enum::Model,
            "Map to the local position (before any transformations). "
            "This usually means in the range of[0; 1] if model was made "
            "in the AssetGeometry module, but there are exceptions"
         },
         {
            "Projector",
            Enum::Projector,
            "Map to position after object and view transformations"
         },
         {
            "Screen",
            Enum::Screen,
            "Map to position after object, view and projection"
         },
         {  
            "Primitive",
            Enum::Primitive,
            "Map to a provided primitive, like plane, sphere, box, etc."
         },
         {  
            "Triplanar",
            Enum::Triplanar,
            "Triplanar (aka box mapping)"
         },
         {  
            "Cube",
            Enum::Cube,
            "Map to a cube"
         },
         {  
            "Face",
            Enum::Face,
            "Face mapping, where each face maps to the same unit region"
         },
         {
            "Pack",
            Enum::Pack,
            "Packing each face in a unique location, but generate lots "
            "of seams; this is costly and is available only at design time"
         },
         {
            "AdaptivePack",
            Enum::AdaptivePack,
            "Packing each face in a unique location, trying to keep the "
            "relative surface area uniform; generates lots of seams, too; "
            "this is costly and is available only at design time"
         },
         {
            "Contour",
            Enum::Contour,
            "Contour projection, mapping texture along a spline; "
            "this is costly and is available only at design time"
         },
         {
            "Unfold",
            Enum::Unfold,
            "Unfold projection, unwrapping texture along precut seams; "
            "this is costly and is available only at design time"
         },
         {
            "Custom",
            Enum::Custom,
            "No mapping is done - you truly trust the raw data, "
            "even if it is invalid or non-existent"
         }
      };

   public:
      constexpr MapMode() noexcept = default;
      constexpr MapMode(Type value) noexcept
         : mMode {value} {}

      constexpr bool operator == (const MapMode&) const = default;
   };

} // namespace Langulus::Math
