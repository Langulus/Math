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

#include <Math/Config.hpp>
#include <Math/Vector.hpp>

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

LANGULUS_RTTI_BOUNDARY(RTTI::MainBoundary)


int main(int argc, char* argv[]) {
   Math::RegisterTraits();
   Math::RegisterVerbs();
   Math::RegisterVectors();

	Catch::Session session;
	return session.run(argc, argv);
}
