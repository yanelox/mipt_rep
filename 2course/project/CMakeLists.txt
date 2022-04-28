cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(gui)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(gui gui.cpp)
target_link_libraries(gui sfml-graphics sfml-audio)