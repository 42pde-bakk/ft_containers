cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(srcs)
include_directories(srcs/Iterators)
include_directories(srcs/List)
include_directories(srcs/Map)
include_directories(srcs/Vector)

add_executable(ft_containers
        srcs/Iterators/BidirectionalIterator.hpp
        srcs/Iterators/RandomAccessIterator.hpp
        srcs/List/List.hpp
        srcs/List/ListNode.hpp
        srcs/Map/Map.hpp
        srcs/Map/MapNode.hpp
        srcs/Vector/Vector.hpp
        srcs/Stack/Stack.hpp
        srcs/Queue/Queue.hpp
        srcs/Extra.hpp
        srcs/Traits.hpp
        colors.h
        tests/list_main.cpp
        tests/vector_main.cpp
        tests/map_main.cpp
        tests/stack_main.cpp
        tests/queue_main.cpp
        )
