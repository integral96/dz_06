cmake_minimum_required(VERSION 3.5)

project(dz_06_mtrx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dz_06_mtrx main.cpp
    my_iterator.hpp
    my_vector.hpp
    my_spatial.hpp)


