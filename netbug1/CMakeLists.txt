cmake_minimum_required(VERSION 3.0)
project(netbug1)

set(CMAKE_CXX_STANDARD 11)

# 添加 curl 头文件路径
include_directories(../curl)

# 添加 curl 库文件
link_directories(.)

add_executable(main main.cpp)

# 链接 curl 库
target_link_libraries(main libcurl-x64.dll)