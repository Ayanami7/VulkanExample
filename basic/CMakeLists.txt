file(GLOB BASIC_SRC "*.cpp" "*.hpp" "*.h")
file(GLOB BASIC_HEADERS "*.hpp" "*.h")

add_library(basic
STATIC
    ${BASIC_SRC}
)

target_include_directories(basic PUBLIC ${CMAKE_SOURCE_DIR}/ext/glm)
target_include_directories(basic PUBLIC ${CMAKE_SOURCE_DIR}/ext)

target_link_directories(basic PUBLIC ${Vulkan_LIABRARY})