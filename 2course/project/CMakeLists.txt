# cmake_minimum_required(VERSION 3.13)
# project(Hello_SFML)

# # set(CMAKE_CPP_COMPILER clang)
# find_package(Torch REQUIRED)
# find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
# add_link_options(-fsanitize=address -fno-omit-frame-pointer)

# add_executable(gui gui.cpp)
# target_link_libraries(gui PRIVATE sfml-graphics sfml-audio "${TORCH_LIBRARIES}")
# set_property(TARGET gui PROPERTY CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(example-app)

find_package(Torch REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(example-app gui.cpp)
target_link_libraries(example-app "${TORCH_LIBRARIES}" sfml-graphics sfml-audio)
set_property(TARGET example-app PROPERTY CXX_STANDARD 14)