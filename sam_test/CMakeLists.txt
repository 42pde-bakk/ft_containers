project(test)

set(CMAKE_CXX_STANDARD 11)
include_directories(../srcs/list ../srcs ../srcs/vector ../srcs/stack ../srcs/queue ../srcs/map)
add_executable(test listTest.cpp Catch2.h catchMain.cpp vectorTest.cpp stackTest.cpp queueTest.cpp mapTest.cpp)