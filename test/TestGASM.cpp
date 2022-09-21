///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"
#include <catch2/catch.hpp>

#define DUMP_STUFF \
	pcLogSpecial << "-------------"; \
	pcLogSpecial << "Script: " << gasm; \
	pcLogSpecial << "Parsed: " << parsed; \
	pcLogSpecial << "Requir: " << required; \
	pcLogSpecial << "-------------";

///																									
SCENARIO("Parsing GASM", "[gasm]") {
	GIVEN("1) The GASM script: - 4 ^ 2") {
		const GASM gasm = "- 4 ^ 2";

		WHEN("Parsed without optimization") {
			Any required = Verb::From<Verbs::Add>(
				Verb::From<Verbs::Exponent>(real(4), real(2))
			).SetMass(-1);

			const auto parsed = gasm.Parse(false);
			DUMP_STUFF;
			THEN("The parsed contents must match the requirements") {
				REQUIRE(parsed == required);
			}
		}

		WHEN("Parsed with optimization") {
			Any required = real(-16);

			const auto parsed = gasm.Parse();
			DUMP_STUFF;
			THEN("The parsed contents must match the requirements") {
				REQUIRE(parsed == required);
			}
		}
	}

	GIVEN("2) The GASM script: - .utSampler.y ^ 2") {
		const GASM gasm = "- .utSampler.y ^ 2";

		WHEN("Parsed without optimization") {
			Any required = Verb::From<Verbs::Add>(
				Verb::From<Verbs::Exponent>(
					Verb::From<Verbs::Select>(
						Verb::From<Verbs::Select>(
							{},
							Traits::Sampler::ID
						),
						Traits::Y::ID
					), 
					real(2)
				)
			).SetMass(-1);

			const auto parsed = gasm.Parse();
			DUMP_STUFF;
			THEN("The parsed contents must match the requirements") {
				REQUIRE(parsed == required);
			}
		}
	}

	GIVEN("3) The GASM script: vec2(.utSampler.x, -(.Time * 8.75 - .utSampler.y ^ 2))") {
		const GASM gasm = "vec2f(.utSampler.x, -(.Time * 8.75 - .utSampler.y ^ 2))";

		WHEN("Parsed without optimization") {
			Any required = Construct::From<vec2>(
				Any::WrapOne(
					Verb::From<Verbs::Select>(
						Verb::From<Verbs::Select>(
							{},
							Traits::Sampler::ID
						),
						Traits::X::ID
					), 
					Verb::From<Verbs::Add>(
						Verb::From<Verbs::Add>(
							Verb::From<Verbs::Multiply>(
								Verb::From<Verbs::Select>(
									{},
									Traits::Time::ID
								), 
								real(8.75)
							),
							Verb::From<Verbs::Exponent>(
								Verb::From<Verbs::Select>(
									Verb::From<Verbs::Select>(
										{},
										Traits::Sampler::ID
									),
									Traits::Y::ID
								), 
								real(2)
							)
						).SetMass(-1)
					).SetMass(-1)
				)
			);

			const auto parsed = gasm.Parse();
			DUMP_STUFF;
			THEN("The parsed contents must match the requirements") {
				REQUIRE(parsed == required);
			}
		}
	}
}
