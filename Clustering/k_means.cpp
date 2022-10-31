#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "k_means.hpp"
#include "manhattan_distance.hpp"


std::vector <Point*> * k_means(int numberOfVectors,int dimensions, std::vector <Point*>* points,int k, Cluster_member** members ){
  srand (time(NULL));
  int first_centroid_id = rand() % numberOfVectors;   //[0,numberOfVectors-1]
  Point* first_centroid_point = (*points)[first_centroid_id];
  unsigned char* first_centroid = first_centroid_point->vec;

  int max = 0;

  for(int i=0; i< numberOfVectors; i++){    //loop only for the first centroid
    Point* point = (*points)[i];
    int dist = manhattan_distance(first_centroid,point->vec,dimensions);
    int result = 0;

    if(max < dist)
      max = dist;
    members[i] = new Cluster_member(i, dist, 0);
  }

  std::vector <Point*> *clusterp = new std::vector<Point*>; //new
  clusterp->push_back(first_centroid_point);

  for (int j=1; j<k; j++){
    float sum_dists = 0.0;

    for(int i=0; i < numberOfVectors; i++){
      sum_dists += (float)members[i]->get_dist() / max;
    }
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/sum_dists);
    int i; //epitides ektos
    for (i=0; i< numberOfVectors; i++){
      x -= (float)members[i]->get_dist() / max;
      if (x <=0 )
        break;
    }
    int new_centroid_id = i;
    Point* new_centroid_point = (*points)[new_centroid_id];
    clusterp->push_back(new_centroid_point);
    unsigned char* new_centroid = new_centroid_point->vec;

     for(int l=0; l< numberOfVectors; l++){
       Point* point = (*points)[l];
       int new_dist = manhattan_distance(new_centroid,point->vec,dimensions);
       if( new_dist < members[l]->get_dist() ){
         members[l]->set_distance(new_dist);
         members[l]->set_cluster_number(j);
       }
     }
   }
   return clusterp;
 }

 std::vector <small_Point*> * k_means(int numberOfVectors,int dimensions, std::vector <small_Point*>* points,int k, Cluster_member** members ){
  srand (time(NULL));
  int first_centroid_id = rand() % numberOfVectors;   //[0,numberOfVectors-1]
  small_Point* first_centroid_point = (*points)[first_centroid_id];
  unsigned short* first_centroid = first_centroid_point->vec;

  int max = 0;

  for(int i=0; i< numberOfVectors; i++){    //loop only for the first centroid
    small_Point* point = (*points)[i];
    int dist = manhattan_distance(first_centroid,point->vec,dimensions);
    int result = 0;

    if(max < dist)
      max = dist;
    members[i] = new Cluster_member(i, dist, 0);
  }

  std::vector <small_Point*> *clusterp = new std::vector<small_Point*>; //new
  clusterp->push_back(first_centroid_point);

  for (int j=1; j<k; j++){
    float sum_dists = 0.0;

    for(int i=0; i < numberOfVectors; i++){
      sum_dists += (float)members[i]->get_dist() / max;
    }
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/sum_dists);
    int i; //epitides ektos
    for (i=0; i< numberOfVectors; i++){
      x -= (float)members[i]->get_dist() / max;
      if (x <=0 )
        break;
    }
    int new_centroid_id = i;
    small_Point* new_centroid_point = (*points)[new_centroid_id];
    clusterp->push_back(new_centroid_point);
    unsigned short* new_centroid = new_centroid_point->vec;

     for(int l=0; l< numberOfVectors; l++){
       small_Point* point = (*points)[l];
       int new_dist = manhattan_distance(new_centroid,point->vec,dimensions);
       if( new_dist < members[l]->get_dist() ){
         members[l]->set_distance(new_dist);
         members[l]->set_cluster_number(j);
       }
     }
   }
   return clusterp;
 }
