#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#include<fstream>
#include"node.hpp"
#include"NetlistGraph.hpp"

using namespace std;

// function to create placeholder nodes
void NetlistGraph::add_gate(string gate_name) {
	node *new_gate = new node(gate_name);
	node_map[gate_name] = new_gate;
	new_gate->GateIndex = -1;
}
// function to add a gate to the graph along with input/output connections	
void NetlistGraph::add_gate(string gate_name,string gate_type,string inputs){
	    // Assign index to nodes
	    if ( gate_type == "OutputDefault") { 
		// Output node has only 1 input
	        output_map.push_back(gate_index);
	    	node_map[gate_name]->add_input(node_map[inputs]);	
	        node_map[gate_name]->GateType=gate_type;
	    	node_map[gate_name]->GateIndex = gate_index;
		node_map[gate_name]->isPO = true;
		if ( find(gate_types.begin(), gate_types.end(), gate_type) == gate_types.end() ) {
			 gate_types.push_back(gate_type); 
		}
	    	gate_index++;
		return;
	    }
	    // No inputs for input node 
	    if ( gate_type == "InputDefault") { 
	        input_map.push_back(gate_index);
		node_map[gate_name]->isPI = true;
	    }
	    if (node_map[gate_name]->GateIndex == -1) { 
	    	node_map[gate_name]->GateIndex = gate_index;
	    	gate_index++;
	    }	
	    stringstream gate_s(inputs);
	    string node_s;
	    // Create/assign inputs to the node
	    while(getline(gate_s,node_s,',')) {
	    	if (node_map[node_s]->GateIndex == -1) { 
	    	node_map[node_s]->GateIndex = gate_index; 
	    	gate_index++;
	    	}
	    	node_map[gate_name]->add_input(node_map[node_s]);	
	    }
	    // Track gate types
	    node_map[gate_name]->GateType=gate_type;
	if ( find(gate_types.begin(), gate_types.end(), gate_type) == gate_types.end() ) { gate_types.push_back(gate_type); }

}




void NetlistGraph::print_info(string FileOutput) {

    int maxFanout=0; 

    vector<int> fanout_map;
    fanout_map.push_back(0); 

    map<string,GateTypeData*> gate_map;

    ofstream OFile (FileOutput.c_str());
    if (OFile.is_open()) { 
	// Initialize numbers for each gate type
	for (int i=0; i<gate_types.size(); i++) {
		GateTypeData* gate_data = new GateTypeData ;
		gate_data->num_gates = 0;gate_data->similar_fanin = 0;gate_data->similar_fanout = 0;
		gate_map[gate_types[i]] = gate_data;			
	}

	// For each gate collect data of Fanout
	for (map<string,node*>::iterator it=node_map.begin() ; it!=node_map.end(); ++it) {
		string print_gate = (it->first).c_str();
		node* print_gate_ptr = it->second;
		
		// Fanout calculation 
		int gate_fanout = print_gate_ptr->Fanout; 	
		
		if (gate_fanout > maxFanout) { maxFanout =  gate_fanout;}
		
		if (gate_fanout >= fanout_map.size()) { 
			int i = gate_fanout-fanout_map.size() + 1 ;
			while(i) { fanout_map.push_back(0); i--; }
		}
		fanout_map[gate_fanout]++;
		//cout << fanout_map.size() <<":" << gate_fanout<<":"  << maxFanout<<":"  << fanout_map[gate_fanout]<< "\n";
		
	        GateTypeData* gate_data = gate_map[print_gate_ptr->GateType]; 
		gate_data->num_gates++;
		if (print_gate_ptr->check_fanin()) {
			gate_data->similar_fanin++;
		}
		if (print_gate_ptr->check_fanout()) {
			gate_data->similar_fanout++;
		}

	} 

	// Max Fanout
	OFile << maxFanout << "\n" ;	
	
	// Print Fanout
	for (int i=0; i<fanout_map.size(); i++) {
	OFile << fanout_map[i] << "\n" ;
	}
	// Print PI
	int numInputs=input_map.size();
	OFile << numInputs << " ";
	for (int i=0; i<input_map.size(); i++) {
	OFile << input_map[i] << " ";
	}
	OFile << "\n" ;
	// Print PO
	int numOutputs=output_map.size();
	OFile << numOutputs << " ";
	for (int i=0; i<output_map.size(); i++) {
	OFile << output_map[i] << " ";
	}
	OFile << "\n" ;
	// Print Gates
	for (int i=0; i<gate_types.size(); i++) {
		if (gate_types[i] != "OutputDefault" && gate_types[i] != "InputDefault") {
		OFile << gate_types[i] <<" "<< gate_map[gate_types[i]]->num_gates <<" "<<  gate_map[gate_types[i]]->similar_fanout <<" "<<  gate_map[gate_types[i]]->similar_fanin << "\n";
		}
	}
    } else { 
	cerr << "Unable to open file for writing\n" ;
    }
}

