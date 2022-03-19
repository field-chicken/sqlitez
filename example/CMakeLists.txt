cmake_minimum_required(VERSION 3.5)

find_package(SQLite3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(example main.cpp)

