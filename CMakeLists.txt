cmake_minimum_required(VERSION 3.10)

project(singleton_mixin_for_cxx_example)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cxx)

target_link_libraries(${PROJECT_NAME})
