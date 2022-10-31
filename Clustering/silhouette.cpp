#include <cfloat>
#include <iostream>
#include "silhouette.hpp"

int get_next_best_cluster(vector <Centroid*> *clusterp,Cluster_member* this_mem,vector<Point*>* points,int dimensions){
  Point* this_point = (*points)[this_mem->get_image_number()];
  int best_cluster = this_mem->get_cnumber();
  int second_best = -1;
  float dist_second = FLT_MAX;
  for (int i=0; i<clusterp->size(); i++)
    if (i!=best_cluster){
      float curr_dist = manhattan_distance((*clusterp)[i]->vec,this_point->vec,dimensions);
      if (dist_second > curr_dist){
        second_best = i;
        dist_second = curr_dist;
      }
    }
  return second_best;
}

double compute_ai(Cluster_member* this_mem,vector<Point*>* points,Cluster_member** members,int numberOfVectors,int dimensions){
  Point* this_point = (*points)[this_mem->get_image_number()];
  int vecs_in_cluster = 0;
  int tot_dist = 0;
  for (int i = 0; i < numberOfVectors; i++)
    if(members[i]->get_cnumber() == this_mem->get_cnumber() && members[i]!=this_mem){
      Point* other_point = (*points)[members[i]->get_image_number()];
      tot_dist += manhattan_distance(this_point->vec,other_point->vec,dimensions);
      vecs_in_cluster++;
    }
  return ((double)tot_dist) / vecs_in_cluster;
}

double compute_bi(vector <Centroid*> *clusterp, Cluster_member* this_mem, vector<Point*>* points, Cluster_member** members, int numberOfVectors,int dimensions){
  Point* this_point = (*points)[this_mem->get_image_number()];
  int next_best_cluster = get_next_best_cluster(clusterp,this_mem,points,dimensions);
  int vecs_in_cluster = 0;
  int tot_dist = 0;
  for (int i = 0; i < numberOfVectors; i++)
    if(members[i]->get_cnumber() == next_best_cluster){
      Point* other_point = (*points)[members[i]->get_image_number()];
      tot_dist += manhattan_distance(this_point->vec,other_point->vec,dimensions);
      vecs_in_cluster++;
    }
  //std::cout << "tot_dist: " << tot_dist <<std::endl;
  //std::cout << "vecs_in_cluster: " << vecs_in_cluster <<std::endl;
  return ((double)tot_dist) / vecs_in_cluster;
}

double compute_si(vector <Centroid*> *clusterp,Cluster_member* this_mem,vector<Point*>* points,Cluster_member** members, int numberOfVectors, int dimensions){
  double bi = compute_bi(clusterp,this_mem,points,members,numberOfVectors,dimensions);
  double ai = compute_ai(this_mem,points,members,numberOfVectors,dimensions);
    //std::cout << "bi: " << bi <<std::endl;
    //std::cout << "ai: " << ai <<std::endl;

  double max = (bi > ai) ? bi : ai;
  return (bi - ai) / max;

}

double* silhouette(vector <Centroid*> *clusterp, Cluster_member** members, vector<Point*>* points, int numberOfVectors,int dimensions){
  int num_clusters = clusterp->size();
  double* _ret = new double[num_clusters+1]();
  int* num = new int[clusterp->size()]();
  for (int i = 0; i < numberOfVectors ; i++) {
    double si = compute_si(clusterp,members[i],points,members,numberOfVectors,dimensions);
    _ret[members[i]->get_cnumber()] += si;
    num[members[i]->get_cnumber()]++;
    _ret[num_clusters] += si;
  }
  for (int i=0; i<num_clusters; i++)
    _ret[i] = _ret[i] / num[i];
  _ret[num_clusters] = _ret[num_clusters] / numberOfVectors;
  return _ret;
}


/*-----------------------------------------------------------------------------------*/


int get_next_best_cluster(vector <small_Centroid*> *clusterp,Cluster_member* this_mem,vector<small_Point*>* points,int dimensions){
  small_Point* this_point = (*points)[this_mem->get_image_number()];
  int best_cluster = this_mem->get_cnumber();
  int second_best = -1;
  float dist_second = FLT_MAX;
  for (int i=0; i<clusterp->size(); i++)
    if (i!=best_cluster){
      float curr_dist = manhattan_distance((*clusterp)[i]->vec,this_point->vec,dimensions);
      if (dist_second > curr_dist){
        second_best = i;
        dist_second = curr_dist;
      }
    }
  return second_best;
}

double compute_ai(Cluster_member* this_mem,vector<small_Point*>* points,Cluster_member** members,int numberOfVectors,int dimensions){
  small_Point* this_point = (*points)[this_mem->get_image_number()];
  int vecs_in_cluster = 0;
  int tot_dist = 0;
  for (int i = 0; i < numberOfVectors; i++)
    if(members[i]->get_cnumber() == this_mem->get_cnumber() && members[i]!=this_mem){
      small_Point* other_point = (*points)[members[i]->get_image_number()];
      tot_dist += manhattan_distance(this_point->vec,other_point->vec,dimensions);
      vecs_in_cluster++;
    }
  return ((double)tot_dist) / vecs_in_cluster;
}

double compute_bi(vector <small_Centroid*> *clusterp, Cluster_member* this_mem, vector<small_Point*>* points, Cluster_member** members, int numberOfVectors,int dimensions){
  small_Point* this_point = (*points)[this_mem->get_image_number()];
  int next_best_cluster = get_next_best_cluster(clusterp,this_mem,points,dimensions);
  int vecs_in_cluster = 0;
  int tot_dist = 0;
  for (int i = 0; i < numberOfVectors; i++)
    if(members[i]->get_cnumber() == next_best_cluster){
      small_Point* other_point = (*points)[members[i]->get_image_number()];
      tot_dist += manhattan_distance(this_point->vec,other_point->vec,dimensions);
      vecs_in_cluster++;
    }
  //std::cout << "tot_dist: " << tot_dist <<std::endl;
  //std::cout << "vecs_in_cluster: " << vecs_in_cluster <<std::endl;
  return ((double)tot_dist) / vecs_in_cluster;
}

double compute_si(vector <small_Centroid*> *clusterp,Cluster_member* this_mem,vector<small_Point*>* points,Cluster_member** members, int numberOfVectors, int dimensions){
  double bi = compute_bi(clusterp,this_mem,points,members,numberOfVectors,dimensions);
  double ai = compute_ai(this_mem,points,members,numberOfVectors,dimensions);
    //std::cout << "bi: " << bi <<std::endl;
    //std::cout << "ai: " << ai <<std::endl;

  double max = (bi > ai) ? bi : ai;
  return (bi - ai) / max;

}

double* silhouette(vector <small_Centroid*> *clusterp, Cluster_member** members, vector<small_Point*>* points, int numberOfVectors,int dimensions){
  int num_clusters = clusterp->size();
  double* _ret = new double[num_clusters+1]();
  int* num = new int[clusterp->size()]();
  for (int i = 0; i < numberOfVectors ; i++) {
    double si = compute_si(clusterp,members[i],points,members,numberOfVectors,dimensions);
    _ret[members[i]->get_cnumber()] += si;
    num[members[i]->get_cnumber()]++;
    _ret[num_clusters] += si;
  }
  for (int i=0; i<num_clusters; i++)
    _ret[i] = _ret[i] / num[i];
  _ret[num_clusters] = _ret[num_clusters] / numberOfVectors;
  return _ret;
}
