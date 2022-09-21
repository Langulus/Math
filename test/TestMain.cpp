///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#include "TestMain.hpp"

PC_MONOPOLIZE_MEMORY(0)

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>


int main(int argc, char* argv[]) {
	Logger::pcInitLogger();
	Memory::pcInitMemory();
	Flow::pcInitGASM();
	Math::pcInitPCMath();

	Catch::Session session;
	return session.run(argc, argv);
}
