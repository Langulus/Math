///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "Common.hpp"

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
      (void) MetaOf<Traits::X>();
      (void) MetaOf<Traits::Y>();
      (void) MetaOf<Traits::Z>();
      (void) MetaOf<Traits::W>();
             
      (void) MetaOf<Traits::U>();
      (void) MetaOf<Traits::V>();
      (void) MetaOf<Traits::S>();
      (void) MetaOf<Traits::T>();
             
      (void) MetaOf<Traits::R>();
      (void) MetaOf<Traits::G>();
      (void) MetaOf<Traits::B>();
      (void) MetaOf<Traits::A>();
      (void) MetaOf<Traits::D>();
             
      (void) MetaOf<Traits::Transform>();
      (void) MetaOf<Traits::View>();
      (void) MetaOf<Traits::Projection>();
      (void) MetaOf<Traits::Solid>();
      (void) MetaOf<Traits::Pickable>();
      (void) MetaOf<Traits::Signed>();
      (void) MetaOf<Traits::Bilateral>();
      (void) MetaOf<Traits::Static>();
      (void) MetaOf<Traits::Boundness>();
      (void) MetaOf<Traits::Relative>();
      (void) MetaOf<Traits::Place>();
      (void) MetaOf<Traits::Size>();
      (void) MetaOf<Traits::Aim>();
      (void) MetaOf<Traits::Velocity>();
      (void) MetaOf<Traits::Acceleration>();
      (void) MetaOf<Traits::Sampler>();
      (void) MetaOf<Traits::Level>();
      (void) MetaOf<Traits::Interpolator>();
      (void) MetaOf<Traits::Perspective>();
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

} // namespace Langulus::Math