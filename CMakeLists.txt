cmake_minimum_required(VERSION 3.15)
project(LibrarySystem)
set(CMAKE_CXX_STANDARD 17)          # 声明：这个项目用 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制：编译器不支持就报错，别降级糊弄我
add_executable(Library c.cpp)