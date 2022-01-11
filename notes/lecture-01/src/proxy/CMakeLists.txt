#
# CMake configuration file
#

cmake_minimum_required(VERSION 3.0)

project(ProxyPattern)

set(CMAKE_CXX_FLAGS "-Wall -Wconversion -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

add_executable(direct direct.cpp)
add_executable(pointer pointer.cpp)
add_executable(proxy proxy.cpp)
