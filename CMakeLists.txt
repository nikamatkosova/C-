cmake_minimum_required(VERSION 3.15)
project(Lib)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(--coverage)
link_libraries(gcov)

add_library(mLib
        Base.h
        Matrix.h
        Vector.h Matrix.cpp Vector.cpp catch.h)
add_executable(Lib main.cpp)

target_link_libraries(Lib mLib)