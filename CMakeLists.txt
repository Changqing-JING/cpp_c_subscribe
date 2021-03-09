cmake_minimum_required(VERSION 3.5)
project(cpp_c_subscribe)
set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src SourceFiles)

add_executable(${PROJECT_NAME} ${SourceFiles})