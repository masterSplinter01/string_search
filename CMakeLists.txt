cmake_minimum_required(VERSION 3.10)
project(string_search)

set(CMAKE_CXX_STANDARD 17)

add_executable(string_search main.cpp file_manager.cpp file_manager.h search_algorithm.h search_algorithm.cpp)

set(CMAKE_CXX_FLAGS "-lboost_program_options")
set(CMAKE_EXE_LINKER_FLAGS "-lboost_system -lboost_filesystem")

set(ST_CXXFS_LIBS stdc++fs)
target_link_libraries(${PROJECT_NAME} stdc++fs)
