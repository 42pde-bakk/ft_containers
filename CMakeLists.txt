cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(srcs)
include_directories(srcs/Iterators)
include_directories(srcs/utils)
include_directories(srcs/list)
include_directories(srcs/vector)
include_directories(srcs/map)
include_directories(srcs/stack)
include_directories(srcs/queue)
include_directories(srcs/deque)
include_directories(srcs/set)
include_directories(srcs/multiset)
include_directories(srcs/multimap)

add_executable(ft_containers
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
        srcs/set/Set.hpp
        srcs/multiset/MultiSet.hpp
        tests/list_main.cpp
        tests/vector_main.cpp
        tests/map_main.cpp
        tests/stack_main.cpp
        tests/queue_main.cpp
        tests/deque_main.cpp
        tests/set_main.cpp
        tests/multiset_main.cpp
        tests/multimap_main.cpp
        srcs/Iterators/DequeIterator.hpp srcs/Iterators/ReverseIterator.hpp srcs/utils/Pair.hpp)
