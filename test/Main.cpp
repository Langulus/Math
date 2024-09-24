///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
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
#include <Math/Range.hpp>
#include <Math/Number.hpp>

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

LANGULUS_RTTI_BOUNDARY(RTTI::MainBoundary)


int main(int argc, char* argv[]) {
   Math::RegisterTraits();
   Math::RegisterVerbs();
   Math::RegisterVectors();
   Math::RegisterRanges();

	Catch::Session session;
	return session.run(argc, argv);
}
