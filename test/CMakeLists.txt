project(Langulus::Math::Test)

add_executable(LangulusMathTest
    Main.cpp
    TestFlow.cpp
    TestFunctions.cpp
    TestMatrices.cpp
    TestQuaternions.cpp
    TestTypeCorrectness.cpp
    TestVectors.cpp
)

target_link_libraries(LangulusMathTest
    PRIVATE     LangulusMath
                Catch2
)

add_test(
	NAME		Langulus::Math::Test
	COMMAND		LangulusMathTest
)

langulus_copy_dlls(LangulusMathTest ON LangulusMathTest)
