file(GLOB BASIC_SRC "*.cpp" "*.hpp" "*.h")
file(GLOB BASIC_HEADERS "*.hpp" "*.h")

set(KTX_DIR ${CMAKE_SOURCE_DIR}/ext/ktx)
# we need a part of ktx library
set(KTX_SOURCES
    ${KTX_DIR}/lib/texture.c
    ${KTX_DIR}/lib/hashlist.c
    ${KTX_DIR}/lib/checkheader.c
    ${KTX_DIR}/lib/swap.c
    ${KTX_DIR}/lib/memstream.c
    ${KTX_DIR}/lib/filestream.c)

add_library(basic
STATIC
    ${BASIC_SRC}
    ${KTX_SOURCES}
)

target_include_directories(basic PUBLIC ${CMAKE_SOURCE_DIR}/ext)

target_include_directories(basic 
PUBLIC 
${CMAKE_SOURCE_DIR}/ext/glm
${CMAKE_SOURCE_DIR}/ext/ktx/include
${CMAKE_SOURCE_DIR}/ext/ktx/other_include)

target_link_directories(basic PUBLIC ${Vulkan_LIABRARY})
target_link_directories(basic PUBLIC ${KTX_DIR}/include ${KTX_DIR}/other_include)