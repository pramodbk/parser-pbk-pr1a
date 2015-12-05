#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#include"node.hpp"

using namespace std;

node::node(string gate_name) 
{
	GateName = gate_name;  
	isPO = false;
	isPI = false;
	Fanout = 0;
};   						// constructor
void node::add_input(node* input)
{
	Inputs.push_back(input);
	input->Outputs.push_back(this);
	input->Fanout++;
}						// add input
bool  node::check_fanin() { 
	for (int i=0; i<Inputs.size(); i++) {
		if (GateType==(Inputs[i])->GateType) {
			return true;
		}
	}
}						// check fanin for similar gates
bool  node::check_fanout() { 
	for (int i=0; i<Outputs.size(); i++) {
		if (GateType==(Outputs[i])->GateType) {
			return true;
		}
	}
}						// check fanout for similar gates


