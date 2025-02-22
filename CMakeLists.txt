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
    fetch_langulus_module(Flow GIT_TAG efb162243a69aac2cf0e72772f343a479ca439c9)
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

target_include_directories(LangulusMath 
	PUBLIC		$<TARGET_PROPERTY:LangulusLogger,INTERFACE_INCLUDE_DIRECTORIES>
				$<TARGET_PROPERTY:LangulusRTTI,INTERFACE_INCLUDE_DIRECTORIES>
				$<$<BOOL:${LANGULUS_FEATURE_MANAGED_MEMORY}>:$<TARGET_PROPERTY:LangulusFractalloc,INTERFACE_INCLUDE_DIRECTORIES>>
				$<TARGET_PROPERTY:LangulusSIMD,INTERFACE_INCLUDE_DIRECTORIES>
				$<TARGET_PROPERTY:LangulusAnyness,INTERFACE_INCLUDE_DIRECTORIES>
				$<TARGET_PROPERTY:LangulusFlow,INTERFACE_INCLUDE_DIRECTORIES>
				include
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
