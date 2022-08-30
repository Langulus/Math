add_subdirectory(Test)

project(PCMath)

add_definitions(-DPC_EXPORT_MATH)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Colors SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Functions SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Matrices SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Primitives SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Quaternions SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Randomness SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Ranges SOURCE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Vectors SOURCE_FILES)

add_library(PCMath SHARED ${SOURCE_FILES})

target_include_directories(PCMath
	PRIVATE		${CMAKE_CURRENT_SOURCE_DIR}
	INTERFACE	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(PCMath 
	PUBLIC PCMemory Flow
)

install(TARGETS PCMath DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})