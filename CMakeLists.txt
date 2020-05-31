cmake_minimum_required(VERSION 3.16)
project(ebml_debugger)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(LOG_LEVEL=2)

add_subdirectory(ubjsonStorage)

add_executable(ebml_debugger main.cpp)

target_link_libraries(ebml_debugger PRIVATE ubjsonStorage)
