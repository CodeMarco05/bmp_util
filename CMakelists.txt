cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

project(bmp)

add_executable(
        bmp
        src/main.cpp
        src/bmp.cpp
)

target_include_directories(bmp PRIVATE ${PROJECT_SOURCE_DIR}/headers)

add_library(bmp_lib src/bmp.cpp headers/bmp.h)