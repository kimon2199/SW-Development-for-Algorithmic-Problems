// HashTable.hpp
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "G.hpp"
#include "Bucket.hpp"


class HashTable {
  int size;         //the number of the buckets
  int k;            //number of hi functions used to define g
  G* gFunc;
  Bucket** buckets;
  unsigned int* Gs;        //keeping the value of g for every datapoint/image
public:
  HashTable(int,int,float,int,int,int);
  ~HashTable();
  void add(Point*);
  Bucket* get_bucket(unsigned char*,unsigned int*);
  //Bucket* get_bucket(float*, unsigned int*);
  Hi** get_His();
  unsigned int get_G(int);
};

#endif
