#ifndef REVERSE_ASSIGN_HPP
#define REVERSE_ASSIGN_HPP

#include <vector>
#include <iostream>
#include "point.hpp"
#include "cluster_member.hpp"
#include "Centroid.hpp"
#include "k_means.hpp"
#include "HashTable.hpp"
#include "hypercube.hpp"
#include "Lloyd.hpp"

using namespace std;

void reverse_Lsh(vector <Centroid*>*,Cluster_member**, int, HashTable**, int, int,vector <Point*>*,int);
void reverse_Hyper(vector <Centroid*>*,Cluster_member**, Hypercube*, int, int,vector <Point*>*,int,int);


#endif
