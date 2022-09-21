project(Langulus_Test_Math)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)

# Configure Catch2 library
message(STATUS "Configuring external project: Catch2...")
download_project(
	PROJ                Catch2
	GIT_REPOSITORY      https://github.com/catchorg/Catch2.git
	GIT_TAG             v2.x
	UPDATE_DISCONNECTED 1
)

add_subdirectory(${Catch2_SOURCE_DIR} ${Catch2_BINARY_DIR})
add_executable(Test.Math ${SOURCE_FILES})
target_link_libraries(Test.Math PRIVATE Catch2 Langulus.Math)

if(MSVC)
	target_compile_options(Test.Math PRIVATE /bigobj)
endif()

add_test(NAME Test.Math COMMAND Test.Math)
