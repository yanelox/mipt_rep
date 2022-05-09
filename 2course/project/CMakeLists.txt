cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(gui)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(gui gui.cpp)
target_link_libraries(gui sfml-graphics sfml-audio)

# find_package(Torch REQUIRED)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# add_executable(mytorch torch.cpp)
# target_link_libraries(mytorch "${TORCH_LIBRARIES}")
# set_property(TARGET mytorch PROPERTY CXX_STANDARD 14)