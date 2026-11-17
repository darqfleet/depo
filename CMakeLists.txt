cmake_minimum_required(VERSION 4.3)
project(depo VERSION 0.0.6 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(BuildOnWrongDir)

add_subdirectory(src bin)
add_subdirectory(tests)

add_executable(lab debug.cpp)
target_link_libraries(lab PRIVATE depocore )