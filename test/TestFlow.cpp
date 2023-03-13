#include "Main.hpp"
#include <catch2/catch.hpp>

/// See https://github.com/catchorg/Catch2/blob/devel/docs/tostring.md        
CATCH_TRANSLATE_EXCEPTION(::Langulus::Exception const& ex) {
   const Text serialized {ex};
   return ::std::string {Token {serialized}};
}

/// Dump parse results and requirements                                       
template<class INPUT, class OUTPUT, class REQUIRED>
void DumpResults(const INPUT& in, const OUTPUT& out, const REQUIRED& required) {
   Logger::Special() << "-------------";
   Logger::Special() << "Script:   " << in;
   Logger::Special() << "Parsed:   " << out;
   Logger::Special() << "Required: " << required;
   Logger::Special() << "-------------";
}

SCENARIO("Parsing scripts", "[code]") {
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
}
