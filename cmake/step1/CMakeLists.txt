cmake_minimum_required(VERSION 3.0)

project(cmk1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(t1config.h.in t1config.h)

add_executable(main main.cpp)

target_include_directories(tutorial1 PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

