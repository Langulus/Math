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
	fetch_langulus_module(Core    GIT_TAG 393d95b6ab13fc5846bda8a3044e4ca62f02fd5a)
	fetch_langulus_module(Logger  GIT_TAG 69626cd4c738195df0929a1cd867317422506e61)
	fetch_langulus_module(RTTI    GIT_TAG 720e675b1ea114156c309fe44871e03557e0a64f)
    if(LANGULUS_FEATURE_MANAGED_MEMORY)
        fetch_langulus_module(Fractalloc GIT_TAG b4917194b18c139969fb9d0a14bf993ee5f2582a)
    endif()
	fetch_langulus_module(SIMD    GIT_TAG 6611cf422e3c8157b88c086f30966afbf4e7dc6c)
	fetch_langulus_module(Anyness GIT_TAG 7e433990052d2cf4c1dbd73afdddb1c697d92c56)
    fetch_langulus_module(Flow	  GIT_TAG 4a0b0f349e5a6f543114b9269f96f55adc025a60)
endif()

file(GLOB_RECURSE
	LANGULUS_MATH_SOURCES 
	LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS
	source/*.cpp
)

# Build and install Math library                                            
add_library(LangulusMath ${LANGULUS_LIBRARY_TYPE}
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
    #enable_testing()
	#add_subdirectory(test)
endif()
