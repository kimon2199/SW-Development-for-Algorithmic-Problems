#include "Centroid.hpp"
#include "manhattan_distance.hpp"
#include "point.hpp"
#include "cluster_member.hpp"
#include <vector>
#include "sort.hpp"

Cluster_member** convert_small_to_big_members(Cluster_member**,int,int,int,vector <Centroid*>*,vector <Point*>*);
