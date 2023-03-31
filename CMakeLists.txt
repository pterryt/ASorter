cmake_minimum_required(VERSION 3.24)
project(asorter)

set(CMAKE_CXX_STANDARD 20)



find_package(yaml-cpp REQUIRED)
add_executable(asorter main.cpp init.cpp init.h monitor.cpp monitor.h mover.cpp mover.h daemonizer.cpp daemonizer.h)
target_link_libraries(asorter yaml-cpp)
