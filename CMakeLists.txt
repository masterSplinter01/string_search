cmake_minimum_required(VERSION 3.10)
project(string_search)

set(CMAKE_CXX_STANDARD 17)

add_executable(string_search src/main.cpp src/rabin_karp_search.h src/rabin_karp_search.cpp)

set(CMAKE_CXX_FLAGS "-lboost_program_options")
set(CMAKE_EXE_LINKER_FLAGS "-lboost_system -lboost_filesystem -lpthread ")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


target_link_libraries(${PROJECT_NAME} stdc++fs)


