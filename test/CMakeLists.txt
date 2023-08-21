add_executable(LangulusMathTest
    Main.cpp
    TestFlow.cpp
    TestConstructors.cpp
    TestRTTI.cpp
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
	NAME		LangulusMathTest
	COMMAND		LangulusMathTest
)

langulus_copy_dlls(LangulusMathTest ON LangulusMathTest)
