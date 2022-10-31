//brute-knn.cpp
#include <iostream>
#include "brute_knn.hpp"
#include "Neighb_arr.hpp"
#include "knn.hpp"            //μηπως να βαζαμε την manh. distance σε αλλο αρχειο
#include "manhattan_distance.hpp"

using namespace std;

std::vector<int>* brute_knn(unsigned char* query, int dimensions, int N,int numberOfVectors, vector <Point*>* points){
  Neighb_arr* neighbours;
  neighbours = new Neighb_arr(N);
  std::vector<int>* distance = new vector<int>;

  for(int i=0; i < numberOfVectors; i++){

      Point* point = (*points)[i];

      int temp_dist = manhattan_distance(query,point->vec,dimensions);

      if (neighbours->fitsBetter(temp_dist))
        neighbours->add(temp_dist,point);
  }
  int* temp;
  temp = neighbours->get_mins();
  for(int i=0; i<N; i++){
    distance->push_back(temp[i]);
  }

  delete neighbours;
  return distance;
}
