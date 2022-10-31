//knn.cpp
// KNN + RANGE SEARCH
#include <iostream>
#include <algorithm> // for function find()
#include "knn.hpp"
#include "Neighb_arr.hpp"
#include "manhattan_distance.hpp"

using namespace std;

vector<int>* compute_ham_neighbours(int num, int bits,int ham_dist){             //num == bucket_index
  vector<int>* _ret = new vector<int>;
  vector<int>* this_iter = new vector<int>;
  _ret->push_back(num);
  for (int i=0; i<ham_dist; i++){
    for(vector<int>::iterator it = _ret->begin(); it != _ret->end(); it++){
      for (int z=0; z<bits; z++){
        int tmp = *it;
        tmp ^= 1UL << z;
        this_iter->push_back(tmp);
      }
    }
    for (vector<int>::iterator it = this_iter->begin(); it != this_iter->end(); it++){
      vector<int>::iterator it2 = find(_ret->begin(), _ret->end(), *it);
      if (it2 == _ret->end())
        _ret->push_back(*it);
    }
    delete this_iter;
    this_iter = new vector<int>;
  }
  delete this_iter;
  return _ret;
}

Point** knn(int L, unsigned char* query, int dimensions, HashTable** hts, int N, vector<int>* r_neigh, float R,vector<int>* distance){
  //float c =1.2;
  Neighb_arr* neighbours;
  neighbours = new Neighb_arr(N);
  Bucket* curr_bucket;

  for(int i=0; i < L; i++){                       //do the loop for each hash table
    unsigned int query_G;
    curr_bucket = hts[i]->get_bucket(query,&query_G);
    for(int j=0; j<curr_bucket->length(); j++){
      Point* point = curr_bucket->get_point(j);
      if (hts[i]->get_G(point->image_number) == query_G){
        int temp_dist = manhattan_distance(query,point->vec,dimensions);
        if (point == 0)
          cout << "yahhooo" << endl;
        if (neighbours->fitsBetter(temp_dist) && neighbours->not_in(point))
          neighbours->add(temp_dist,point);
        if (temp_dist < R){
          std::vector<int>::iterator it;
          it = std::find (r_neigh->begin(), r_neigh->end(), point->image_number);
          if (it == r_neigh->end())
            r_neigh->push_back(point->image_number);
        }
      }
    }
  }
  int* temp;
  temp = neighbours->get_mins();
  for(int i=0; i<N; i++){
  //  cout <<temp[i] <<endl;
    distance->push_back(temp[i]);
  }

  /* delete zone */
  Point** neighb_list = new Point*[N]; // i make copy to return in order to delete neighbours underneath
  Point** neighb_list_ex = neighbours->getNeighs();
  for(int i=0; i<N;i++)
    neighb_list[i] = neighb_list_ex[i];
  delete neighbours;
  return neighb_list;
}

Point** knn_hyper(unsigned char* query, int dimensions, Hypercube* hypercube, int N, vector<int>* r_neigh, float R, vector<int>* distance,int probes){
  float c = 1.2;
  Neighb_arr* neighbours;
  neighbours = new Neighb_arr(N);
  Bucket* curr_bucket;

  unsigned char* query_clone = new unsigned char[dimensions]; //making clone that will be destroyed with ~Point()
  for (int i=0; i<dimensions; i++){
    query_clone[i] = query[i];
  }
  Point* point = new Point(0,query_clone);
  unsigned int bucket_index = hypercube->compute_f(point);
  vector<int>* hum_neigbours = compute_ham_neighbours(bucket_index,hypercube->get_bits_num(),1);
  Point* pp = 0;
  int curr_probes = 0;
  int curr_M = 0;
  for (vector<int>::iterator it = hum_neigbours->begin(); it != hum_neigbours->end() && curr_probes < probes && curr_M < hypercube->get_M(); it++,curr_probes++){
    curr_bucket = hypercube->get_bucket(*it);
    for(int j=0; j<curr_bucket->length(); j++){
      Point* point = curr_bucket->get_point(j);
      int temp_dist = manhattan_distance(query,point->vec,dimensions);
      if (neighbours->fitsBetter(temp_dist))
        neighbours->add(temp_dist,point);
      if (temp_dist < c*R)
        r_neigh->push_back(point->image_number);
      curr_M++;
      if (curr_M > hypercube->get_M())
        break;
    }
  }

  int* temp;
  temp = neighbours->get_mins();
  for(int i=0; i<N; i++){
    distance->push_back(temp[i]);
  }

  /* delete zone */
  Point** neighb_list = new Point*[N]; // i make copy to return in order to delete neighbours underneath
  Point** neighb_list_ex = neighbours->getNeighs();
  for(int i=0; i<N;i++)
    neighb_list[i] = neighb_list_ex[i];
  delete neighbours;
  delete point;
  delete hum_neigbours;
  return neighb_list;
}
