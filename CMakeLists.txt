cmake_minimum_required(VERSION 3.12)

project(buffon_needle)

add_subdirectory(raylib)

add_executable(buffon_needle main.cpp)

target_link_libraries(buffon_needle raylib)
