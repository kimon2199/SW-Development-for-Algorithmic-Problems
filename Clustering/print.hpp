#ifndef PRINT_HPP
#define PRINT_HPP
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include "point.hpp"
#include "Centroid.hpp"
#include "small_Centroid.hpp"
#include "cluster_member.hpp"

using namespace std;


void print(unsigned char*,Point** ans,std::vector<int>* distance, char* algo_name,int N, std::vector<int>* distance_true,
  chrono::duration<double>,chrono::duration<double>,vector<int>*,int,ofstream*);

void cluster_print(std::string algo_name,std::chrono::duration<double> time_algo,int clusters,int numberOfVectors,int dimensions,
    vector <Centroid*>* clusters_centers,double* sil,Cluster_member**,ofstream*);

void cluster_print(std::string algo_name,std::chrono::duration<double> time_algo,int clusters,int numberOfVectors,int dimensions,
    vector <small_Centroid*>* clusters_centers,double* sil,Cluster_member**,ofstream*);

#endif
