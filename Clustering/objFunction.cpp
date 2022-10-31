#include "objFunction.hpp"

int objFunction(Cluster_member** members,int numberOfVectors){
	int sum = 0;
	for (int i = 0; i < numberOfVectors; ++i)
		sum += members[i]->get_dist();
	return sum;
}