cmake_minimum_required(VERSION 3.22)
project(Langulus.Math)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if this project is built as standalone, or a part of something else 
if(PROJECT_IS_TOP_LEVEL)
    include(LangulusUtilities.cmake)
    langulus_init_git_submodule(cmake)
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
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Colors LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Functions LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Matrices LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Numbers LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Primitives LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Quaternions LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Randomness LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Ranges LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/SignedDistance LANGULUS_MATH_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/source/Vectors LANGULUS_MATH_SOURCES)
add_library(Langulus.Math INTERFACE)

target_include_directories(Langulus.Math
    INTERFACE   include
)

target_link_libraries(Langulus.Math 
    INTERFACE   Langulus.Core
                Langulus.Logger
                Langulus.RTTI
                Langulus.SIMD
                Langulus.Anyness
                Langulus.Flow
)
