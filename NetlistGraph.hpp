#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#include"node.hpp"

#ifndef NETLISTGRAPH_H
#define NETLISTGRAPH_H

using namespace std;
class NetlistGraph {
    struct GateTypeData { 
    	int num_gates ;
    	int similar_fanin ; 
    	int similar_fanout ; 
    };
    public: 
	NetlistGraph() { gate_index=0; };

	// Create a map of gate names to gate nodes  
    	map<string,node*> node_map; 
 	int gate_index ;	

	// Store the index of each input/output in the order that they are read
    	vector<int> input_map; 
    	vector<int> output_map; 
	
	// Store the index of each gate type in the order that they are read
    	vector<string> gate_types; 
	void add_gate(string gate_name,string gate_type,string inputs);
	void add_gate(string gate_name);

	void print_info(string FileOutput);

};

#endif
