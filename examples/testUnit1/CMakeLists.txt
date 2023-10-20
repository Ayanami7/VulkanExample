add_executable(testUnit1
main.cpp
)

target_include_directories(testUnit1 PUBLIC ${CMAKE_SOURCE_DIR}/basic)
target_link_libraries(testUnit1 PUBLIC basic)