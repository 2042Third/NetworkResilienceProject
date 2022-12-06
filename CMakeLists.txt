cmake_minimum_required(VERSION 3.23)
project(research)

set(CMAKE_CXX_STANDARD 20)

add_executable(research main.cpp src/Graph.cpp src/Graph.h src/Node.h src/NetConstructs.h src/GraphOperations.cpp src/GraphOperations.h src/RandomGraph.cpp src/RandomGraph.h src/LinkRep.cpp src/LinkRep.h src/Algorithms.h src/output.h)

add_compile_definitions(research DEBUG_NET)
