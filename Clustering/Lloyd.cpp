#include <iostream>
#include "Lloyd.hpp"
#include "manhattan_distance.hpp"
#include "sort.hpp"
using namespace std;


void lloyd(vector <Centroid*> *clusterp, Cluster_member** members, int numberOfVectors, int k, int dimensions, vector <Point*>* points ){

  unsigned char* coordinates;

  int* summ = new int[k]();
  while(1){
    for (int i=0; i<k; i++)
      summ[i] = 0;

    for(int i=0; i < k; i++){                   //do this loop for every centroid/cluster
      int vectors_in_cluster = 0;
      int summact = 0; //-----
      coordinates = new unsigned char[dimensions] ();
      vector <Point*>* points_of_cluster = new vector <Point*>;
      for(int j=0; j < numberOfVectors; j++)
        if(members[j]->get_cnumber() == i)
          points_of_cluster->push_back((*points)[j]);
      for(int l=0; l < dimensions; l++){
        quickSort(points_of_cluster,0,points_of_cluster->size()-1,l);
        unsigned char coord = (*points_of_cluster)[points_of_cluster->size()/2]->vec[l];
        coordinates[l] = coord;
      }
      delete points_of_cluster;
      for(int p=0; p < dimensions; p++){
        if ((*clusterp)[i]->vec[p] != coordinates[p]){
          summ[i]++;
          summact += abs((*clusterp)[i]->vec[p]-coordinates[p]);
        }
      }
        delete[] (*clusterp)[i]->vec;
        (*clusterp)[i]->vec = coordinates;           //assign the new centroid
        //std::cout << "Cluster " <<i<< " had a change in "<<summ[i]<< " dimensions, and changed by "<< summact  << std::endl;
    } //end of updating the centroids


    std::cout << std::endl;
    // condition to stop the while loop
    int summm = 0;
    for (int i=0; i<k; i++)
      summm += summ[i];
    if (summm < 1000)
      break;
    //calculate new distances(and new vectors in each cluster)
    for(int i=0; i < k; i++){

      Centroid* centroid_point = (*clusterp)[i];
      unsigned char* centroid = centroid_point->vec;

      for(int l=0; l < numberOfVectors; l++){
        Point* point = (*points)[l];
        int new_dist = manhattan_distance(centroid,point->vec,dimensions);
        if(new_dist < members[l]->get_dist()){
          members[l]->set_distance(new_dist);
          members[l]->set_cluster_number(i);
        }
      }
    }
  }
  delete[] summ;
}  









void lloyd(vector <small_Centroid*> *clusterp, Cluster_member** members, int numberOfVectors, int k, int dimensions, vector <small_Point*>* points ){

  unsigned short* coordinates;

  int* summ = new int[k]();
  while(1){
    for (int i=0; i<k; i++)
      summ[i] = 0;

    for(int i=0; i < k; i++){                   //do this loop for every centroid/cluster
      int vectors_in_cluster = 0;
      int summact = 0; //-----
      coordinates = new unsigned short[dimensions] ();
      vector <small_Point*>* points_of_cluster = new vector <small_Point*>;
      for(int j=0; j < numberOfVectors; j++)
        if(members[j]->get_cnumber() == i)
          points_of_cluster->push_back((*points)[j]);
      for(int l=0; l < dimensions; l++){
        quickSort(points_of_cluster,0,points_of_cluster->size()-1,l);
        unsigned short coord = (*points_of_cluster)[points_of_cluster->size()/2]->vec[l];
        coordinates[l] = coord;
      }
      delete points_of_cluster;
      for(int p=0; p < dimensions; p++){
        if ((*clusterp)[i]->vec[p] != coordinates[p]){
          summ[i]++;
          summact += abs((*clusterp)[i]->vec[p]-coordinates[p]);
        }
      }
        delete[] (*clusterp)[i]->vec;
        (*clusterp)[i]->vec = coordinates;           //assign the new centroid
        //std::cout << "Cluster " <<i<< " had a change in "<<summ[i]<< " dimensions, and changed by "<< summact  << std::endl;
    } //end of updating the centroids


    std::cout << std::endl;
    // condition to stop the while loop
    int summm = 0;
    for (int i=0; i<k; i++)
      summm += summ[i];
    if (summm < 1000)
      break;
    //calculate new distances(and new vectors in each cluster)
    for(int i=0; i < k; i++){

      small_Centroid* centroid_point = (*clusterp)[i];
      unsigned short* centroid = centroid_point->vec;

      for(int l=0; l < numberOfVectors; l++){
        small_Point* point = (*points)[l];
        int new_dist = manhattan_distance(centroid,point->vec,dimensions);
        if(new_dist < members[l]->get_dist()){
          members[l]->set_distance(new_dist);
          members[l]->set_cluster_number(i);
        }
      }
    }
  }
  delete[] summ;
}  

