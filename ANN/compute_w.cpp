#include "compute_w.hpp"
#include <cstdlib>
#include <ctime>

int compute_w(int numberOfVectors,int dimensions,vector <Point*>* points){
  srand (time(NULL));
  vector<int>* brute_result;
  int distances_sum = 0;

  for(int i=0; i < 50; i++){
    int image_id = rand() % numberOfVectors;   //[0,numberOfVectors-1]
    unsigned char* query = (*points)[image_id]->vec;
    brute_result = brute_knn(query, dimensions,2,numberOfVectors,points);
    distances_sum += (*brute_result)[0];
  }
  int average = distances_sum / 50;
  return average*7;
}
