# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

set(NAME vulkanExample)
project(${NAME})

# #编译glfw3
# add_subdirectory(${CMAKE_SOURCE_DIR}/ext/glfw)

set(CMAKE_CXX_STANDARD 17)

file(MAKE_DIRECTORY shaders)
file(MAKE_DIRECTORY bin/Debug)
file(MAKE_DIRECTORY bin/Release)

add_subdirectory(basic)
add_subdirectory(examples)