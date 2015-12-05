
all:
	g++ ReadNetlist.cpp NetlistGraph.cpp node.cpp main.cpp -o parser

clean: 
	rm parser

