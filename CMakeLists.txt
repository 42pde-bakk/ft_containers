cmake_minimum_required(VERSION 2.6)
set(PROJECT_NAME ft_containers)
set(PROJ_VERSION 1.0.0)
project(${PROJECT_NAME} CXX)

file(GLOB_RECURSE SOURCES srcs/**.hpp)
set(CMAKE_CXX_STANDARD 98)

ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)
