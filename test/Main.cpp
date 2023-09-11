///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"
#include <Flow/Verbs/Associate.hpp>
#include <Flow/Verbs/Catenate.hpp>
#include <Flow/Verbs/Conjunct.hpp>
#include <Flow/Verbs/Create.hpp>
#include <Flow/Verbs/Do.hpp>
#include <Flow/Verbs/Interpret.hpp>
#include <Flow/Verbs/Select.hpp>

#include <Math/Verbs/Add.hpp>
#include <Math/Verbs/Exponent.hpp>
#include <Math/Verbs/Multiply.hpp>
#include <Math/Vectors.hpp>

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

LANGULUS_RTTI_BOUNDARY("Test")

template<Count S>
struct VectorTypeGenerator {
   template<class... T>
   static bool Register() {
      return ((nullptr != MetaOf<TVector<T, S>>()) && ...);
   }
};

int main(int argc, char* argv[]) {
   (void) MetaOf<Traits::Transform>();
   (void) MetaOf<Traits::Solid>();
   (void) MetaOf<Traits::Pickable>();
   (void) MetaOf<Traits::Signed>();
   (void) MetaOf<Traits::Bilateral>();
   (void) MetaOf<Traits::Static>();
   (void) MetaOf<Traits::Boundness>();
   (void) MetaOf<Traits::Relative>();
   (void) MetaOf<Traits::Place>();
   (void) MetaOf<Traits::Aim>();
   (void) MetaOf<Traits::Velocity>();
   (void) MetaOf<Traits::Acceleration>();
   (void) MetaOf<Traits::Sampler>();

   (void) MetaOf<Traits::X>();
   (void) MetaOf<Traits::Y>();
   (void) MetaOf<Traits::Z>();
   (void) MetaOf<Traits::W>();

   (void) MetaOf<Traits::R>();
   (void) MetaOf<Traits::G>();
   (void) MetaOf<Traits::B>();
   (void) MetaOf<Traits::A>();

   (void) MetaOf<Traits::U>();
   (void) MetaOf<Traits::V>();
   (void) MetaOf<Traits::S>();
   (void) MetaOf<Traits::T>();

   (void) MetaOf<Verbs::Add>();
   (void) MetaOf<Verbs::Associate>();
   (void) MetaOf<Verbs::Catenate>();
   (void) MetaOf<Verbs::Conjunct>();
   (void) MetaOf<Verbs::Create>();
   (void) MetaOf<Verbs::Do>();
   (void) MetaOf<Verbs::Exponent>();
   (void) MetaOf<Verbs::Interpret>();
   (void) MetaOf<Verbs::Multiply>();
   (void) MetaOf<Verbs::Select>();

   VectorTypeGenerator<1>::Register<ALL_TYPES>();
   VectorTypeGenerator<2>::Register<ALL_TYPES>();
   VectorTypeGenerator<3>::Register<ALL_TYPES>();
   VectorTypeGenerator<4>::Register<ALL_TYPES>();

	Catch::Session session;
	return session.run(argc, argv);
}
