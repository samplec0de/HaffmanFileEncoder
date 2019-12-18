cmake_minimum_required(VERSION 3.15)
project(Haffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(Haffman main.cpp)
add_executable(encoder encoder.cpp)

add_executable(generator generator.cpp)
add_executable(decoder decoder.cpp)
add_executable(v2_generator v2_generator.cpp)
add_executable(v2_encoder v2_encoder.cpp)
add_executable(v2_decoder v2_decoder.cpp)
add_executable(sonya_generator sonya_generator.cpp)