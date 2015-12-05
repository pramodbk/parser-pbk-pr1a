#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<fstream>
#include"NetlistGraph.hpp"
#include"ReadNetlist.hpp"

using namespace std;

int main(int argc, char *argv[]) {

if (argc < 2) { 
cerr << "Please provide a netlist filename\n" ; 
return 0;
}
string FileInput = argv[1];

string Output;
stringstream FileInput_s(FileInput);
getline(FileInput_s,Output,'.');
Output = Output + ".out" ;


NetlistGraph* myNetlist = new NetlistGraph(); 
	
//Read netlist into a graph
read_netlist(myNetlist,FileInput);

//Print all required info from the graph
myNetlist->print_info(Output);

return 0;

}
 
