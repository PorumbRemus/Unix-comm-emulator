cmake_minimum_required(VERSION 3.24)
project(Project_OS)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_OS main.cpp)
add_executable(ls ls.cpp)
add_executable(dirname dirname.cpp)
add_executable(tac tac.cpp)
target_link_libraries(Project_OS /lib/x86_64-linux-gnu/libreadline.so)
