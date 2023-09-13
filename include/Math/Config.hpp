///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../../source/Common.hpp"

#include "../../source/Verbs/Add.inl"
#include "../../source/Verbs/Cerp.inl"
#include "../../source/Verbs/Exponent.inl"
#include "../../source/Verbs/Lerp.inl"
#include "../../source/Verbs/Modulate.inl"
#include "../../source/Verbs/Multiply.inl"
#include "../../source/Verbs/Randomize.inl"
#include "../../source/Verbs/Move.inl"


namespace Langulus::Math
{

   using RTTI::MetaVerb;

   /// Register traits                                                        
   inline void RegisterTraits() {
      (void)MetaOf<Traits::X>();
      (void)MetaOf<Traits::Y>();
      (void)MetaOf<Traits::Z>();
      (void)MetaOf<Traits::W>();

      (void)MetaOf<Traits::U>();
      (void)MetaOf<Traits::V>();
      (void)MetaOf<Traits::S>();
      (void)MetaOf<Traits::T>();

      (void)MetaOf<Traits::R>();
      (void)MetaOf<Traits::G>();
      (void)MetaOf<Traits::B>();
      (void)MetaOf<Traits::A>();
      (void)MetaOf<Traits::D>();

      (void)MetaOf<Traits::Transform>();
      (void)MetaOf<Traits::View>();
      (void)MetaOf<Traits::Projection>();
      (void)MetaOf<Traits::Solid>();
      (void)MetaOf<Traits::Pickable>();
      (void)MetaOf<Traits::Signed>();
      (void)MetaOf<Traits::Bilateral>();
      (void)MetaOf<Traits::Static>();
      (void)MetaOf<Traits::Boundness>();
      (void)MetaOf<Traits::Relative>();
      (void)MetaOf<Traits::Place>();
      (void)MetaOf<Traits::Size>();
      (void)MetaOf<Traits::Aim>();
      (void)MetaOf<Traits::Velocity>();
      (void)MetaOf<Traits::Acceleration>();
      (void)MetaOf<Traits::Sampler>();
      (void)MetaOf<Traits::Level>();
      (void)MetaOf<Traits::Interpolator>();
      (void)MetaOf<Traits::Perspective>();
   }

   /// Register verbs                                                         
   inline void RegisterVerbs() {
      (void)MetaVerb::Of<Verbs::Exponent>();
      (void)MetaVerb::Of<Verbs::Multiply>();
      (void)MetaVerb::Of<Verbs::Modulate>();
      (void)MetaVerb::Of<Verbs::Randomize>();
      (void)MetaVerb::Of<Verbs::Add>();
      (void)MetaVerb::Of<Verbs::Lerp>();
      (void)MetaVerb::Of<Verbs::Cerp>();
      (void)MetaVerb::Of<Verbs::Move>();
   }

} // namespace Langulus::Math