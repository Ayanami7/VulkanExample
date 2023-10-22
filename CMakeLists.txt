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

if(WIN32)
    if(NOT Vulkan_FOUND)
        find_library(Vulkan_LIBRARY NAMES vulkan-1 vulkan PATHS ${CMAKE_SOURCE_DIR}/libs/vulkan)

        if(Vulkan_LIBRARY)
            set(Vulkan_FOUND ON)
            MESSAGE("Using bundled Vulkan library version")
        endif()
    endif()
endif()

add_subdirectory(basic)
add_subdirectory(test)
add_subdirectory(examples)