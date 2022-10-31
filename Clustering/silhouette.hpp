#ifndef SILHOUETTE_HPP
#define SILHOUETTE_HPP

#include <vector>
#include "Centroid.hpp"
#include "small_Centroid.hpp"
#include "point.hpp"
#include "small_point.hpp"
#include "cluster_member.hpp"
#include "manhattan_distance.hpp"

using namespace std;

double* silhouette(vector <Centroid*> *clusterp, Cluster_member** members, vector<Point*>* points, int numberOfVectors,int dimensions);
double* silhouette(vector <small_Centroid*> *clusterp, Cluster_member** members, vector<small_Point*>* points, int numberOfVectors,int dimensions);
#endif
