#include "cluster_member.hpp"



Cluster_member::Cluster_member(int _image_number, int _distance, int _cluster_number)
:image_number(_image_number),distance(_distance),cluster_number(_cluster_number){}

Cluster_member::~Cluster_member(){}

int Cluster_member::get_dist(){
  return this->distance;
}

void Cluster_member::set_distance(int dist){
  this->distance = dist;
}
void Cluster_member::set_cluster_number(int number){
  this->cluster_number = number;
}

void Cluster_member::set_image_id(int id){
  this->image_number = id;
}

int Cluster_member::get_cnumber(){
  return this->cluster_number;
}

int Cluster_member:: get_image_number(){
  return this->image_number;
}
