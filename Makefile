src_dir = ./src
src_files = $(src_dir)/Graph.cpp \
	$(src_dir)/RandomGraph.cpp \
	$(src_dir)/Node.cpp
all:
	g++ -std=c++14 -g -I$(src_dir) $(src_files) -o netout main.cpp