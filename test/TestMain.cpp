///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

int main(int argc, char* argv[]) {
   (void) MetaOf<Traits::Transformation>();
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

	Catch::Session session;
	return session.run(argc, argv);
}
