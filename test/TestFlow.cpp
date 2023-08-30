#include "Main.hpp"
#include <Math/Vectors.hpp>
#include <Flow/Verbs/Create.hpp>
#include <Flow/Verbs/Select.hpp>
#include <Math/Verbs/Add.hpp>
#include <Math/Verbs/Exponent.hpp>
#include <Math/Verbs/Multiply.hpp>
#include <catch2/catch.hpp>

LANGULUS_EXCEPTION_HANDLER

SCENARIO("Parsing scripts", "[code]") {
   Any pastMissing;
   pastMissing.MakePast();

   Any futureMissing;
   futureMissing.MakeFuture();

   GIVEN("The script: - 4 ^ 2") {
      const auto code = "- 4 ^ 2"_code;

      WHEN("Parsed without optimization") {
         Any required = Verbs::Add {
            Any {Verbs::Exponent {Real(2)}
               .SetSource(Real(4))
            }
         }.SetMass(-1);

         const auto parsed = code.Parse(false);
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }

      WHEN("Parsed with optimization") {
         Any required = Real(-16);

         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }

   GIVEN("The script: - .Sampler.y ^ 2") {
      const auto code = "- .Sampler.y ^ 2"_code;

      WHEN("Parsed without optimization") {
         Any required = Verbs::Add {
            Any {Verbs::Exponent {Real(2)}
               .SetSource(Verbs::Select {MetaOf<Traits::Y>()}
                  .SetSource(Verbs::Select {MetaOf<Traits::Sampler>()})
               )
            }
         }.SetMass(-1);

         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }

   GIVEN("The script: Vec2(.Sampler.x, -(.Time * 8.75 - .Sampler.y ^ 2))") {
      const auto code = "Vec2(.Sampler.x, -(.Time * 8.75 - .Sampler.y ^ 2))"_code;

      WHEN("Parsed without optimization") {
         Any required = Construct::From<Vec2>(
            Any::WrapAs<Verb>(
               Verbs::Select {MetaOf<Traits::X>()}
                  .SetSource(
                     Verbs::Select {MetaOf<Traits::Sampler>()}
                  ),
               Verbs::Add {
                  Any {Verbs::Add {
                     Any {Verbs::Exponent {Real(2)}
                        .SetSource(
                           Verbs::Select {MetaOf<Traits::Y>()}
                              .SetSource(Verbs::Select {MetaOf<Traits::Sampler>()})
                        )}
                  }.SetSource(
                     Verbs::Multiply {Real(8.75)}
                        .SetSource(
                           Verbs::Select {MetaOf<Traits::Time>()}
                        )
                  ).SetMass(-1)}
               }.SetMass(-1)
            )
         );

         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }
   
   GIVEN("The script: Create^1(Count(1)) Add^3 2") {
      const Code code = "Create^1(Count(1)) Add^3 2";
      const Any required = Verbs::Add {Real(2)}
         .SetSource(
            Verbs::Create {Traits::Count {Real(1)}}
               .SetRate(1))
         .SetRate(3);

      WHEN("Parsed") {
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }

   GIVEN("The script: Create^1(Count(1)) Add^3(2)") {
      const Code code = "Create^1(Count(1)) Add^3(2)";
      const Any required = Verbs::Add {Real(2)}
         .SetSource(
            Verbs::Create {Traits::Count {Real(1)}}
               .SetRate(1))
         .SetRate(3);

      WHEN("Parsed") {
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }

   GIVEN("The script: Create^1(Count(1)) Add^2(2) Multiply^3(4)") {
      const Code code = "Create^1(Count(1)) Add^2(2) Multiply^3(4)";
      const Any multiply = Verbs::Multiply {Real(4)}
         .SetSource(Real(2))
         .SetRate(3);
      const Any required = Verbs::Add {multiply}
         .SetRate(2)
         .SetSource(
            Verbs::Create {Traits::Count {Real(1)}}
               .SetRate(1)
         );

      WHEN("Parsed") {
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }

   GIVEN("The script: Create^1(Count(1)) + 2 * 4") {
      const Code code = "Create^1(Count(1)) + 2 * 4";
      const Any required = Verbs::Add {Real(8)}
         .SetSource(
            Verbs::Create {Traits::Count {Real(1)}}
               .SetRate(1)
         );

      WHEN("Parsed") {
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }

   GIVEN("The script: -(2 * 8.75 - 14 ^ 2)") {
      const Code code = "-(2 * 8.75 - 14 ^ 2)";
      const Any exponent = Verbs::Exponent {Real(2)}
         .SetSource(Real(14));
      const Any addition = Verbs::Add {exponent}
         .SetMass(-1)
         .SetSource(
            Verbs::Multiply {Real(8.75)}
               .SetSource(Real(2))
         );
      const Any required = Verbs::Add {addition}
         .SetMass(-1);

      WHEN("Parsed without optimization") {
         const auto parsed = code.Parse(false);
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }

      WHEN("Parsed with optimization") {
         Any required2 = Real(178.5);
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required2);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required2);
         }
      }
   }
   
   GIVEN("The script: (number? + Fraction(number??)) or (? Conjunct!8 ??)") {
      const Code code = "(number? + Fraction(number??)) or (? Conjunct!8 ??)";
      Any pastNumber {pastMissing};
      pastNumber << MetaOf<A::Number>();
      Any futrNumber {futureMissing};
      futrNumber << MetaOf<A::Number>();

      Verbs::Add add {Construct::From<Fraction>(futrNumber)};
      add.SetSource(pastNumber);

      Verbs::Conjunct conjunct {futureMissing};
      conjunct.SetSource(pastMissing);
      conjunct.SetPriority(8);

      Any required = Any::WrapAs<Verb>(add, conjunct);
      required.MakeOr();

      WHEN("Parsed") {
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }

   GIVEN("The script: (? + Fraction(number??)) or (? Conjunct!8 ??)") {
      const Code code = "(? + Fraction(number??)) or (? Conjunct!8 ??)";
      Any futrNumber {futureMissing};
      futrNumber << MetaData::Of<A::Number>();

      Verbs::Add add {Construct::From<Fraction>(futrNumber)};
      add.SetSource(pastMissing);

      Verbs::Conjunct conjunct {futureMissing};
      conjunct.SetSource(pastMissing);
      conjunct.SetPriority(8);

      Any required = Any::WrapAs<Verb>(add, conjunct);
      required.MakeOr();

      WHEN("Parsed") {
         const auto parsed = code.Parse();
         DumpResults(code, parsed, required);
         THEN("The parsed contents must match the requirements") {
            REQUIRE(parsed == required);
         }
      }
   }
}
