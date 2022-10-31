// Neighb_arr.cpp
#include "Neighb_arr.hpp"
#include <limits>


Neighb_arr::Neighb_arr(int K):size(K){
  additions = 0;
  neighbours = new Point*[size];
  mins = new int[size];
  for (int i=0; i<size; i++)
    mins[i] = std::numeric_limits <int>::max();
}

bool Neighb_arr::fitsBetter(int dist){
  return dist < mins[0];
}

void Neighb_arr::add(int dist,Point* new_neigh){
  int i;
  for (i=0; i < size; i++)
    if(dist > mins[i])
      break;
  this->shift(i-1);
  neighbours[i-1] = new_neigh;
  mins[i-1] = dist;
  additions++;
}

void Neighb_arr::shift(int z){
  for (int i=1; i<=z; i++){
    neighbours[i-1] = neighbours[i];
    mins[i-1] = mins[i];
  }
}

Point** Neighb_arr::getNeighs(){
  return neighbours;
}

int* Neighb_arr::get_mins(){
  return this->mins;
}

bool Neighb_arr::not_in(Point* point){
  for (int i=0; i < size; i++)
    if(point == neighbours[i])
      return false;
  return true;
}

int Neighb_arr::get_additions(){
  return additions;
}

Neighb_arr::~Neighb_arr(){
  /*for(unsigned int i=0; i < size ; i++){
    delete neighbours[i];
  }*/
  delete[] neighbours;
  delete[] mins;
}
