///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Math/Export.hpp>
#include "Verbs/Add.inl"
#include "Verbs/Cerp.inl"
#include "Verbs/Exponent.inl"
#include "Verbs/Lerp.inl"
#include "Verbs/Modulate.inl"
#include "Verbs/Multiply.inl"
#include "Verbs/Randomize.inl"
#include "Verbs/Move.inl"


namespace Langulus::Math
{
   using RTTI::MetaVerb;

   /// Register traits                                                        
   void RegisterTraits() {
      (void) MetaOf<Tags::X>();
      (void) MetaOf<Tags::Y>();
      (void) MetaOf<Tags::Z>();
      (void) MetaOf<Tags::W>();
             
      (void) MetaOf<Tags::U>();
      (void) MetaOf<Tags::V>();
      (void) MetaOf<Tags::S>();
      (void) MetaOf<Tags::T>();
             
      (void) MetaOf<Tags::R>();
      (void) MetaOf<Tags::G>();
      (void) MetaOf<Tags::B>();
      (void) MetaOf<Tags::A>();
      (void) MetaOf<Tags::D>();
             
      (void) MetaOf<Tags::Transform>();
      (void) MetaOf<Tags::View>();
      (void) MetaOf<Tags::Projection>();
      (void) MetaOf<Tags::Solid>();
      (void) MetaOf<Tags::Pickable>();
      (void) MetaOf<Tags::Signed>();
      (void) MetaOf<Tags::Bilateral>();
      (void) MetaOf<Tags::Static>();
      (void) MetaOf<Tags::Boundness>();
      (void) MetaOf<Tags::Relative>();
      (void) MetaOf<Tags::Place>();
      (void) MetaOf<Tags::Size>();
      (void) MetaOf<Tags::Aim>();
      (void) MetaOf<Tags::Velocity>();
      (void) MetaOf<Tags::Acceleration>();
      (void) MetaOf<Tags::Sampler>();
      (void) MetaOf<Tags::Level>();
      (void) MetaOf<Tags::Interpolator>();
      (void) MetaOf<Tags::Perspective>();
   }

   /// Register verbs                                                         
   void RegisterVerbs() {
      (void) MetaOf<Verbs::Exponent>();
      (void) MetaOf<Verbs::Multiply>();
      (void) MetaOf<Verbs::Modulate>();
      (void) MetaOf<Verbs::Randomize>();
      (void) MetaOf<Verbs::Add>();
      (void) MetaOf<Verbs::Lerp>();
      (void) MetaOf<Verbs::Cerp>();
      (void) MetaOf<Verbs::Move>();
   }
}