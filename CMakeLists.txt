cmake_minimum_required(VERSION 3.24)
project(asorter)

set(CMAKE_CXX_STANDARD 20)

add_executable(asorter main.cpp init.cpp init.h monitor.cpp monitor.h mover.cpp mover.h)
