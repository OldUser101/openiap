cmake_minimum_required(VERSION 3.16)
project(openiap_project)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src/libopeniap)
add_subdirectory(src/openiap)