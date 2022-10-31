#ifndef SILHOUETTE_HPP
#define SILHOUETTE_HPP

#include <vector>
#include "Centroid.hpp"
#include "point.hpp"
#include "cluster_member.hpp"
#include "manhattan_distance.hpp"

using namespace std;

double* silhouette(vector <Centroid*> *clusterp, Cluster_member** members, vector<Point*>* points, int numberOfVectors,int dimensions);

#endif
