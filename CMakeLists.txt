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
        srcs/list/List.hpp
        srcs/list/ListNode.hpp
        srcs/map/Map.hpp
        srcs/utils/MapNode.hpp
        srcs/multimap/MultiMap.hpp
        srcs/vector/Vector.hpp
        srcs/stack/Stack.hpp
        srcs/queue/Queue.hpp
        srcs/utils/Extra.hpp
        srcs/utils/Traits.hpp
        srcs/utils/Colours.h
        tests/list_main.cpp
        tests/vector_main.cpp
        tests/map_main.cpp
        tests/stack_main.cpp
        tests/queue_main.cpp
        tests/multimap_main.cpp)
