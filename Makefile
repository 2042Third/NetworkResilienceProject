src_dir = ./src
src_files = $(src_dir)/Graph.cpp \
	$(src_dir)/RandomGraph.cpp

all:
	clang++ -std=c++20 -O3 -I$(src_dir) $(src_files) -o netout main.cpp
debug:
	g++ -std=c++20 -g -DDEBUG_NET -Wall -I$(src_dir) $(src_files) -o netout main.cpp

