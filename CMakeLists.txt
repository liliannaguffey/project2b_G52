cmake_minimum_required(VERSION 3.30)
project(project2b_G52)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(project2b_G52
    src/Food.cpp
    src/Food.h)
configure_file("food.csv" "${CMAKE_BINARY_DIR}/food.csv" COPYONLY)