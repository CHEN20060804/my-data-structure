cmake_minimum_required(VERSION 3.31)
project(my_data_structure)

set(CMAKE_CXX_STANDARD 23)

add_executable(my_data_structure main.cpp
        Stack.h
        Queue.h
        Array.h
        String.h
        Vector.h)
