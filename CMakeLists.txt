cmake_minimum_required(VERSION 3.24)
project(LangulusMath
    VERSION         1.0.0
    DESCRIPTION     "Langulus math library"
    HOMEPAGE_URL    https://langulus.com
)

# Check if this project is built as standalone, or a part of something else 
if(PROJECT_IS_TOP_LEVEL OR NOT LANGULUS)
    include(LangulusUtilities.cmake)

    # Add Langulus::Core/Logger/RTTI/SIMD/Fractalloc/Anyness/Flow libraries 
	fetch_langulus_module(Core    GIT_TAG d52feac3e995e3eeac44fadd7812361919b73a11)
	fetch_langulus_module(Logger  GIT_TAG 3314fbe3bf5611a5bd9ee649f2a6ba5c43f6b4c4)
	fetch_langulus_module(RTTI    GIT_TAG 8c735514612820f76da494421baccaaea0d4d5e1)
    if(LANGULUS_FEATURE_MANAGED_MEMORY)
        fetch_langulus_module(Fractalloc GIT_TAG 0126c1750d9101ab29227a735d2a7a06da672e02)
    endif()
	fetch_langulus_module(SIMD    GIT_TAG 4aadc7d243c10a09e8095bf502909931b6ec6122)
	fetch_langulus_module(Anyness GIT_TAG 2922d043c686826d39e710ab7be5358b47c1f66f)
    fetch_langulus_module(Flow	  GIT_TAG 9c3f62a53f3e0c2b9d0c684e3f08aad86b925f68)
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
    PUBLIC      include
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

if(LANGULUS_TESTING)
    enable_testing()
	add_subdirectory(test)
endif()
