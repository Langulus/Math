cmake_minimum_required(VERSION 3.22)
project(Langulus.Math)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if this project is built as standalone, or a part of something else
if(PROJECT_IS_TOP_LEVEL)
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init -- cmake 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    include(FetchLangulusModule)
    include(HandleLangulusFeatures)

    handle_langulus_features()

    fetch_langulus_module(Core)
    fetch_langulus_module(Logger)
    fetch_langulus_module(RTTI)
    fetch_langulus_module(SIMD)
    fetch_langulus_module(Anyness)
    fetch_langulus_module(Flow)

    add_compile_definitions(LANGULUS_ENABLE_TESTING)
    enable_testing()
	add_subdirectory(test)
endif()

# Build and install Math library
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Colors SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Functions SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Matrices SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Primitives SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Quaternions SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Randomness SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Ranges SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Vectors SOURCE_FILES)
add_library(Langulus.Math INTERFACE)

target_include_directories(Langulus.Math INTERFACE include)
target_link_libraries(Langulus.Math 
    INTERFACE   Langulus.RTTI 
                Langulus.SIMD 
                Langulus.Anyness
                Langulus.Flow
)
