file(GLOB_RECURSE
	LANGULUS_MATH_TEST_SOURCES 
	LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS
	*.cpp *.hpp
)

add_executable(LangulusMathTest ${LANGULUS_MATH_TEST_SOURCES})

target_link_libraries(LangulusMathTest
    PRIVATE     LangulusMath
                Catch2
)

add_test(
	NAME		LangulusMathTest
	COMMAND		LangulusMathTest
)