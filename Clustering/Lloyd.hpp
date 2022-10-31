#ifndef LLOYD_HPP
#define LLOYD_HPP

#include <vector>
#include "point.hpp"
#include "small_point.hpp"	
#include "cluster_member.hpp"
#include "Centroid.hpp"
#include "small_Centroid.hpp"

void lloyd(std::vector <Centroid*> *,Cluster_member**,int,int,int, std::vector <Point*>*);
void lloyd(std::vector <small_Centroid*> *,Cluster_member**,int,int,int, std::vector <small_Point*>*);

#endif
