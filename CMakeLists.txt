cmake_minimum_required(VERSION 3.5)
project(cpp_c_subscribe)
set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src SourceFiles)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/src/CCPPProxy.cpp PROPERTIES COMPILE_FLAGS -ffixed-r15)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

endif()



add_executable(${PROJECT_NAME} ${SourceFiles})