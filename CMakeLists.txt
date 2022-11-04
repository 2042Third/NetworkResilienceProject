cmake_minimum_required(VERSION 3.23)
project(research)

set(CMAKE_CXX_STANDARD 14)

add_executable(research main.cpp src/Graph.cpp src/Graph.h src/Node.cpp src/Node.h src/NetConstructs.h src/GraphOperations.cpp src/GraphOperations.h)
