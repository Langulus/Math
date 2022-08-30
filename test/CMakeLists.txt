project(PCTestMath)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)

add_executable(PCTestMath ${SOURCE_FILES}) 
target_link_libraries(PCTestMath PRIVATE PCMemory PCMath Catch2)

install(TARGETS PCTestMath DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})