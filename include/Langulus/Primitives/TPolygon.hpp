///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Primitive.hpp"
#include <Langulus/Annies/Functional/Compare.hpp>
#include <Langulus/Annies/Functional/Remove.hpp>


namespace Langulus::Math
{
   template<CT::CustomVector T> requires (ExtentOf<T> > 1)
   struct TPolygon;

   using Polygon2 = TPolygon<Vec2>;
   using Polygon3 = TPolygon<Vec3>;

   /// An abstract polygon, also used as a topology type                      
   struct Polygon {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Math::Polygon3;
      using CTTI_Bases     = Math::Topology;
   };

   ///                                                                        
   ///   A templated polygon                                                  
   ///                                                                        
   /// A list of coplanar points that form a surface with a complex edge      
   ///                                                                        
   template<CT::CustomVector T> requires (ExtentOf<T> > 1)
   struct TPolygon : Annies::TMany<T> {
      using CTTI_ReflectAs = TPolygon;
      using CTTI_Deep      = No;
      using CTTI_Bases     = Math::Polygon;

      using Base           = Annies::TMany<T>;
      using PointType      = T;
      using Base::operator ==;
   };
}

namespace Langulus::CTTI
{
   /// Rule for serializing Recipe to Text                                    
   template<CT::CustomVector T> requires (ExtentOf<T> > 1)
   struct SerializationRule<Annies::Text, Math::TPolygon<T>> {
      using S = Serializer<Annies::Text>;
      using Context = typename S::Context;

      static void Serialize(Math::TPolygon<T> const& polygon, Annies::Text& out, Context* context) {
         out += NameOf<Math::TPolygon<T>>();
         out += Serial::OpenScope.Token;
         for (auto& point : polygon) {
            Langulus::Serialize(point, out, context);
            out += Serial::And.Token;
         }
         out -= Serial::And.Token.size();
         out += Serial::CloseScope.Token;
      }
   };
}