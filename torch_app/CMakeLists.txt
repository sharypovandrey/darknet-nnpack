cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(custom_ops)

find_package(Torch REQUIRED)

add_executable(torch_app torch_app.cpp)
target_link_libraries(torch_app "${TORCH_LIBRARIES}")
set_property(TARGET torch_app PROPERTY CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")