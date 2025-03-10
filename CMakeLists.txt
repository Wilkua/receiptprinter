cmake_minimum_required(VERSION 3.26)

project(librp VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CPP_STANDARD 20)
set(CMAKE_CPP_STANDARD_REQUIRED true)

add_library(rp "src/Receipt.cpp")
target_include_directories(rp PUBLIC "include")

add_executable(test "test/main.cpp")
target_link_libraries(test rp)

