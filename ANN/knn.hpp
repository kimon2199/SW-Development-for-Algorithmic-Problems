#ifndef  KNN_HPP
#define  KNN_HPP

#include "HashTable.hpp"
#include "hypercube.hpp"
#include <vector>

std::vector<int>* compute_ham_neighbours(int, int ,int );

Point** knn(int, unsigned char*, int, HashTable**, int, std::vector <int>* ,float,std::vector<int>*);

Point** knn_hyper(unsigned char*, int, Hypercube*, int N, std::vector<int>*, float, std::vector<int>*,int);

#endif
