cmake_minimum_required(VERSION 3.28)
project(LangulusMath
    VERSION         1.0.0
    DESCRIPTION     "Langulus math library"
    HOMEPAGE_URL    https://langulus.com
)

# Check if this project is built as standalone, or a part of something else 
if(PROJECT_IS_TOP_LEVEL OR NOT LANGULUS)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

    include(LangulusUtilities.cmake)

    # Add Langulus::Core/Logger/RTTI/SIMD/Fractalloc/Anyness/Flow libraries 
	fetch_langulus_module(Core    GIT_TAG 35756f11d2f9c475f27b094b8d4c82cd453969fc)
	fetch_langulus_module(Logger  GIT_TAG dafbeb825071ec60d8403254143f75606151a7e6)
	fetch_langulus_module(RTTI    GIT_TAG fc49750884ac943dff4261ac5b8dfb2c148423d7)
    if(LANGULUS_FEATURE_MANAGED_MEMORY)
        fetch_langulus_module(Fractalloc GIT_TAG 66408e8557b1bb3c80615909129342bcebd3fb9f)
    endif()
	fetch_langulus_module(SIMD    GIT_TAG ead5493049e2800b4c3c02d385c0c6314efac69c)
	fetch_langulus_module(Anyness GIT_TAG 46a6513d6bcf3d532e9bf746b50d1299692eb96a)
    fetch_langulus_module(Flow	  GIT_TAG 06000427afccf13016738140d09850f0b8cf837b)
endif()

file(GLOB_RECURSE
	LANGULUS_MATH_SOURCES 
	LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS
	source/*.cpp
)

# Build and install Math library                                            
add_langulus_library(LangulusMath
    $<TARGET_OBJECTS:LangulusLogger>
    $<TARGET_OBJECTS:LangulusRTTI>
    $<$<BOOL:${LANGULUS_FEATURE_MANAGED_MEMORY}>:$<TARGET_OBJECTS:LangulusFractalloc>>
    $<TARGET_OBJECTS:LangulusAnyness>
    $<TARGET_OBJECTS:LangulusFlow>
	${LANGULUS_MATH_SOURCES}
)

target_include_directories(LangulusMath PUBLIC include
    $<TARGET_PROPERTY:LangulusLogger,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:LangulusRTTI,INTERFACE_INCLUDE_DIRECTORIES>
    $<$<BOOL:${LANGULUS_FEATURE_MANAGED_MEMORY}>:$<TARGET_PROPERTY:LangulusFractalloc,INTERFACE_INCLUDE_DIRECTORIES>>
    $<TARGET_PROPERTY:LangulusSIMD,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:LangulusAnyness,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:LangulusFlow,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(LangulusMath
    PUBLIC      LangulusCore
                fmt
)

target_compile_definitions(LangulusMath
    PRIVATE     LANGULUS_EXPORT_ALL
)

if(LANGULUS_TESTING)
    enable_testing()
	add_subdirectory(test)
endif()
