///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include <Langulus/Verbs/Associate.hpp>
#include <Langulus/Verbs/Catenate.hpp>
#include <Langulus/Verbs/Conjunct.hpp>
#include <Langulus/Verbs/Create.hpp>
#include <Langulus/Verbs/Do.hpp>
#include <Langulus/Verbs/Interpret.hpp>
#include <Langulus/Verbs/Select.hpp>

#include <Langulus/Math/Config.hpp>
#include <Langulus/Math/Vector.hpp>
#include <Langulus/Math/Normal.hpp>
#include <Langulus/Math/Range.hpp>
#include <Langulus/Math/Number.hpp>
#include <Langulus/Math/Color.hpp>

#define CATCH_CONFIG_RUNNER
#include "Common.hpp"

LANGULUS_RTTI_BOUNDARY(RTTI::MainBoundary)


int main(int argc, char* argv[]) {
   Math::RegisterTraits();
   Math::RegisterVerbs();
   Math::RegisterVectors();
   Math::RegisterNormals();
   Math::RegisterRanges();
   Math::RegisterColors();

	Catch::Session session;
	return session.run(argc, argv);
}
