cmake_minimum_required(VERSION 3.5)

project(test_subscribe)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} sourceFiles)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/C1.cpp PROPERTIES COMPILE_FLAGS -ffixed-r15)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

endif()

add_executable(${PROJECT_NAME} ${sourceFiles})

target_link_libraries(${PROJECT_NAME} cpp_c_subscribe)