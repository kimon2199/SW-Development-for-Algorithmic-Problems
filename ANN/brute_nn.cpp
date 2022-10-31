//brute_nn.cpp
#include <iostream>
#include "brute_nn.hpp"
#include "lsh_nn.hpp"
#include "manhattan_distance.hpp"
#include <limits>

using namespace std;

Point* brute_nn(unsigned char* query, int dimensions,int numberOfVectors, vector <Point*>* points){
  int min_dist = std::numeric_limits<int>::max();
  Point* min_point = NULL;

  for(int i=0; i < numberOfVectors; i++){

      Point* point = (*points)[i];

      int temp_dist = manhattan_distance(query,point->vec,dimensions);

      if (temp_dist < min_dist){
        min_dist = temp_dist;
        min_point = point;
      }
  }
  return min_point;
}

small_Point*  small_brute_nn(unsigned short* query, int dimensions,int numberOfVectors, vector <small_Point*>* points){
  int min_dist = std::numeric_limits<int>::max();
  small_Point* min_point = NULL;

  for(int i=0; i < numberOfVectors; i++){

      small_Point* point = (*points)[i];

      int temp_dist = manhattan_distance(query,point->vec,dimensions);

      if (temp_dist < min_dist){
        min_dist = temp_dist;
        min_point = point;
      }
  }
  return min_point;
}
