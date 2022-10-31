// lsh_nn.cpp
#include <iostream>
#include <limits>
#include "lsh_nn.hpp"
#include "manhattan_distance.hpp"

using namespace std;


Point* lsh_nn(int L, unsigned char* query, int dimensions, HashTable** hts){
  Bucket* curr_bucket;
  int min_dist = std::numeric_limits<int>::max();
  Point* min_point = NULL;
  for(int i=0; i < L; i++){                       //do the loop for each hash table
    unsigned int query_G;
    curr_bucket = hts[i]->get_bucket(query,&query_G);
    for(int j=0; j<curr_bucket->length(); j++){
      Point* point = curr_bucket->get_point(j);
      if (hts[i]->get_G(point->image_number) == query_G){
        int temp_dist = manhattan_distance(query,point->vec,dimensions);
        if (point == 0)
          cout << "yahhooo" << endl;
        if (temp_dist < min_dist){
          min_dist = temp_dist;
          min_point = point;
        }
      }
    }
  }

  return min_point;
}

