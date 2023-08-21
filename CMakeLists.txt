cmake_minimum_required(VERSION 3.24)
project(LangulusMath
    VERSION         1.0.0
    DESCRIPTION     "Langulus math library"
    HOMEPAGE_URL    https://langulus.com
    LANGUAGES       CXX
)

# Check if this project is built as standalone, or a part of something else 
if(PROJECT_IS_TOP_LEVEL OR NOT LANGULUS)
    # Populate the cmake directory											
    include(LangulusUtilities.cmake)
    langulus_fetch_cmake()

    # Handle feature flags and global definitions/requirements				
    include(HandleLangulusFeatures)
    handle_langulus_features()

    # Add Langulus::Core/Logger/RTTI/SIMD/Anynes/Flow libraries             
    include(FetchLangulusModule)
    fetch_langulus_module(Core)
    fetch_langulus_module(Logger)
    fetch_langulus_module(RTTI)
    if(LANGULUS_FEATURE_MANAGED_MEMORY)
        fetch_langulus_module(Fractalloc)
    endif()
    fetch_langulus_module(SIMD)
    fetch_langulus_module(Anyness)
    fetch_langulus_module(Flow)
endif()

# Build and install Math library                                            
add_library(LangulusMath ${LANGULUS_LIBRARY_TYPE}
    $<TARGET_OBJECTS:LangulusLogger>
    $<TARGET_OBJECTS:LangulusRTTI>
    $<$<BOOL:${LANGULUS_FEATURE_MANAGED_MEMORY}>:$<TARGET_OBJECTS:LangulusFractalloc>>
    $<TARGET_OBJECTS:LangulusAnyness>
    $<TARGET_OBJECTS:LangulusFlow>
)

target_include_directories(LangulusMath
    PUBLIC      source
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

target_compile_definitions(LangulusFlow
    PRIVATE     LANGULUS_EXPORT_ALL
)

if(LANGULUS_ENABLE_TESTING)
    enable_testing()
	add_subdirectory(test)
endif()
