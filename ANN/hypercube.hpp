#ifndef HYPERCUBE_HPP
#define HYPERCUBE_HPP
#include <vector>
#include "Bucket.hpp"
#include "hashf.hpp"
#include "Centroid.hpp"

class Hypercube{
  int bits_num;                //d'
  Bucket** vertices;
  Hi** his;
  bool** computed_values;      // are set to 1 if the h value image has already been given a f value
  bool** value_of_computation; // the number that was computed if computed_values is set to 1
  int M;
  public:
    Hypercube(Hi**,int,int,int);
    void add(Point*);
    unsigned int compute_f(Point*);
    unsigned int compute_f(Centroid*);
    ~Hypercube();
    int get_bits_num();
    Bucket* get_bucket(int);
    bool has_been_computed(int,int);
    bool prev_computed_value(int,int);
    void set_value_of_distribution(int,int,bool);
    int get_M();
};

#endif
