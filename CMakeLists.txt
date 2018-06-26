cmake_minimum_required(VERSION 3.10)
project(string_search)

set(CMAKE_CXX_STANDARD 17)

add_executable(string_search src/main.cpp src/file_manager.cpp src/file_manager.h src/search_algorithm.h src/search_algorithm.cpp)

set(CMAKE_CXX_FLAGS "-lboost_program_options")
set(CMAKE_EXE_LINKER_FLAGS "-lboost_system -lboost_filesystem")


target_link_libraries(${PROJECT_NAME} stdc++fs)
