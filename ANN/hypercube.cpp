//hypercube.cpp
#include "hypercube.hpp"
#include <cmath>
#include <random>
#include <chrono>

Hypercube::Hypercube(Hi** _his, int _bits_num,int k,int _M):his(_his),bits_num(_bits_num),M(_M){
  int num_of_vertices = pow(2,bits_num);
  vertices = new Bucket*[num_of_vertices];
  for(int i=0; i < num_of_vertices; i++)
    vertices[i] = new Bucket();

  const unsigned int M = pow(2,32/k);
  computed_values = new bool*[bits_num];       // are set to 1 if the number has been computed before
  value_of_computation = new bool*[bits_num];   // the number that was computed if computed_values is set to 1
  for(int i=0; i<bits_num; i++){
    computed_values[i] = new bool[M]();
    value_of_computation[i] = new bool[M];
  }
}

Hypercube::~Hypercube(){
  for(int i=0; i<bits_num; i++){
    delete computed_values[i];
    delete value_of_computation[i];
  }
  delete[] computed_values;
  delete[] value_of_computation;

  for(int i=0; i < pow(2,bits_num); i++){
    delete vertices[i];
  }
  delete[] vertices;

/*  for(unsigned int i=0; i < k; i++){
    delete his[i];
  }
  delete[] his;*/
}

void Hypercube::add(Point* point){
  unsigned int f = compute_f(point);      // get hash function result
  vertices[f]->add(point);            // add it to bucket
}

unsigned int Hypercube::compute_f(Point* point){
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::bernoulli_distribution distribution(0.5);

  bool f;
  unsigned int _ret = 0;
  for (int i=0; i<bits_num; i++){
    int h = his[i]->compute_Hx(point->vec);
    if(has_been_computed(i,h)){
      f = prev_computed_value(i,h);
    }
    else{
      f = distribution(generator);
      set_value_of_distribution(i,h,f);
    }
    _ret = (_ret << 1) + f ;
  }
  return _ret;
}

unsigned int Hypercube::compute_f(Centroid* point){
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::bernoulli_distribution distribution(0.5);

  bool f;
  unsigned int _ret = 0;
  for (int i=0; i<bits_num; i++){
    int h = his[i]->compute_Hx(point->vec);
    if(has_been_computed(i,h)){
      f = prev_computed_value(i,h);
    }
    else{
      f = distribution(generator);
      set_value_of_distribution(i,h,f);
    }

    _ret = (_ret << 1) + f ;
  }
  return _ret;
}

Bucket* Hypercube::get_bucket(int index){
  return vertices[index];
}

int Hypercube::get_bits_num(){
  return bits_num;
}

bool Hypercube::has_been_computed(int i,int h){
  return computed_values[i][h];
}

bool Hypercube::prev_computed_value(int i,int h){
  return value_of_computation[i][h];
}
void Hypercube::set_value_of_distribution(int i,int h,bool f){
  computed_values[i][h] = 1;
  value_of_computation[i][h] = f;
}

int Hypercube::get_M(){
  return M;
}
