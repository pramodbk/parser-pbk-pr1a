
#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#ifndef NODE_H
#define NODE_H

using namespace std;
class node{
 public:   
  	vector<node*> Inputs;			
  	vector<node*> Outputs;
   	string GateName;
	string GateType;	
	int Fanout;
	int GateIndex;
	bool isPO;
 	bool isPI;	
  	
	node(string gate_name);				// constructor
	~node() {};                                 	// destructor
	bool check_fanout();
 	bool check_fanin();
	void add_input(node* input);
};

#endif
