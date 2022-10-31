#include <iostream>
#include <cstdlib>
#include <fstream>
#include "read_nn.hpp"

using namespace std;


int readNum(ifstream* file,char* a){
	int sum = 0;
	*a = (char)file->get();
	while (*a==' ' || *a=='\n' || *a=='\t' || *a==',' || *a=='}'){
		*a = (char)file->get();
	}
	while (*a!=' ' && *a!='\n' && *a!='\t' && *a!=',' && *a!='}'){
		sum = sum*10 + atoi(a);
		*a = (char)file->get();
	}
	return sum;
}

Cluster_member** read_nn(char* nn_file,int clusters,int numberOfVectors){
	/* numberOfVectors: is a number of how many vectors were in the dataset of the original space */

	Cluster_member** members = new Cluster_member*[numberOfVectors];
	int ind = 0;

	ifstream* nn_input = new ifstream;
    nn_input->open(nn_file);
    if (!nn_input->is_open()){
    	cout << "Problem reading NN file" << endl;
    	std::exit(EXIT_FAILURE);
    }
    char a;

    for (int i = 0; i < clusters; ++i){
    	nn_input->ignore(20,'-');
    	int clusterNum = readNum(nn_input,&a);
    	//cout << "This cluster: " << clusterNum << endl;
    	while(a != '{')
    		a = (char)nn_input->get();
    	nn_input->ignore(10,':');
    	int size = readNum(nn_input,&a);
    	for (int j = 0; j < size; ++j){
    		int num = readNum(nn_input,&a);
    		if (num < numberOfVectors){
    			//cout << num << endl;
    			members[ind] = new Cluster_member(num,0,i);
    			ind++; 
    		}

    	}
    	cout << endl << endl << endl;
    }

    return members;
}