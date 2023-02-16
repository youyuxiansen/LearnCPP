# cmake_minimum_required(VERSION 3.19)
project(LearnCPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(variadicTemplate
        try/variadicTemplate.cpp)
add_executable(myarray
        try/myarray.cpp)
add_executable(static
        try/static.cpp)
add_executable(bind_n_function
        try/bind_n_function.cpp)
add_executable(thread
        try/thread.cpp)


add_subdirectory(designPattern)


