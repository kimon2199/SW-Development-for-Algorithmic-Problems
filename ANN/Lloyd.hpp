#ifndef LLOYD_HPP
#define LLOYD_HPP

#include <vector>
#include "knn.hpp"
#include "point.hpp"
#include "cluster_member.hpp"
#include "Centroid.hpp"

void lloyd(std::vector <Centroid*> *,Cluster_member**,int,int,int, std::vector <Point*>*);
void lloyd_for_reverse(std::vector <Centroid*> *,int, int, Point*,Cluster_member*);

#endif
