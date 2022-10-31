#include <cstring>
#include <fstream>
#include "print.hpp"

void print(unsigned char* query,Point** ans,vector<int>* distance,char* algo_name,int N,vector<int>* distance_true,
  std::chrono::duration<double> time_algo,std::chrono::duration<double> time_true,vector<int>* r_neighs,int query_id,ofstream* myfile){

  int a;
  (*myfile) << "Query: " << query_id << endl;
  int num_of_neighs_found = distance->size();
  //for (int l=num_of_neighs_found-1; l>=0; l--){
  for(int l= N-1; l>=0; l--){
    (*myfile) << "Nearest neighbor-" << N-l/*num_of_neighs_found-l*/ <<": ";
    (*myfile) << ans[l]->image_number << endl;
    (*myfile) << "distance" << algo_name <<": " << distance->at(l) << endl;
    (*myfile) << "distanceTrue: " << distance_true->at(l) <<  endl << endl;
  }
  ///////////
  (*myfile) << "t" << algo_name <<": " << time_algo.count() << endl;
  (*myfile) << "tTrue: " << time_true.count() << endl;
  (*myfile) << "R-near neighbors: " << endl;
  if (r_neighs->size() == 0)
    (*myfile) << "-"<< endl;
  for(vector<int>::iterator it = r_neighs->begin(); it != r_neighs->end(); it++)
    (*myfile) << *it << endl;
  (*myfile) << endl << endl;

}

void cluster_print(std::string algo_name,std::chrono::duration<double> time_algo,int clusters,int numberOfVectors,int dimensions,
  vector <Centroid*>* clusters_centers,double* sil,Cluster_member** members, ofstream* myfile){

  int a;
  (*myfile) << algo_name << endl;

  int* size = new int[clusters]();
  for(int i=0; i < numberOfVectors; i++){
    int cluster_id = members[i]->get_cnumber();
    size[cluster_id]++;
  }
  for (int l=0; l < clusters ; l++){
    (*myfile) << "CLUSTER-" << l+1 <<"{size: "<< size[l] <<" ,centroid:";
    (*myfile) << "[ ";
    for(int j=0; j < dimensions; j++){
      (*myfile) << (int)(*clusters_centers)[l]->vec[j];
      if (j!=dimensions-1)
        (*myfile) << ", ";
    }
    (*myfile) << "]" << endl;
  }
  (*myfile) << "clustering_time:" << time_algo.count() << endl;
  (*myfile) << "Silhouette: [";
  for (int i=0; i<= clusters; i++){
    (*myfile) << sil[i];
    if (i!=clusters)
      (*myfile) << ", ";
  }

  (*myfile) << "]" << endl;

  delete[] size;
}

void cluster_print(std::string algo_name,std::chrono::duration<double> time_algo,int clusters,int numberOfVectors,int dimensions,
  vector <small_Centroid*>* clusters_centers,double* sil,Cluster_member** members, ofstream* myfile){

  int a;
  (*myfile) << algo_name << endl;

  int* size = new int[clusters]();
  for(int i=0; i < numberOfVectors; i++){
    int cluster_id = members[i]->get_cnumber();
    size[cluster_id]++;
  }
  for (int l=0; l < clusters ; l++){
    (*myfile) << "CLUSTER-" << l+1 <<"{size: "<< size[l] <<" ,centroid:";
    (*myfile) << "[ ";
    for(int j=0; j < dimensions; j++){
      (*myfile) << (int)(*clusters_centers)[l]->vec[j];
      if (j!=dimensions-1)
        (*myfile) << ", ";
    }
    (*myfile) << "]" << endl;
  }
  (*myfile) << "clustering_time:" << time_algo.count() << endl;
  (*myfile) << "Silhouette: [";
  for (int i=0; i<= clusters; i++){
    (*myfile) << sil[i];
    if (i!=clusters)
      (*myfile) << ", ";
  }

  (*myfile) << "]" << endl;

  delete[] size;
}
