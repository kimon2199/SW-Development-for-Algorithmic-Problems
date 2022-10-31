#include "HashTable.hpp"
#include <iostream>
//#include <cmath>

using namespace std;

HashTable::HashTable(int numOfDatapoints,int m, float w, int _k, int dimensions,int subdivisions):k(_k),size(numOfDatapoints/subdivisions){
  gFunc = new G(dimensions,m,w,k);              //we need one G function for each Hash Table
  buckets = new Bucket*[size];                  //we will have n/16 buckets
  for(int i=0; i < size;i++)
    buckets[i] = new Bucket();
  Gs = new unsigned int[numOfDatapoints];
}

HashTable::~HashTable(){
  delete gFunc;
  delete[] Gs;
  for(int i=0; i < size; i++){
    delete buckets[i];
  }
  delete[] buckets;
}
/*--------------------adding a datapoint in the right bucket--------------------*/
void HashTable::add(Point* point){
  unsigned int g = gFunc->compute_Gx(point->vec);       // get hash function result
  int smallG = g % size;                                // make it fit in the hashtable
  buckets[smallG]->add(point);                          // add it to bucket
  Gs[point->image_number] = g;
}
/*----------------------Getting the bucket of a datapoint----------------------*/
Bucket* HashTable::get_bucket(unsigned char* query, unsigned int* g){   //g is an argument here because we can't return two things in a function
  *g = gFunc->compute_Gx(query);                      // get hash function result for query
  int smallG = *g % size;                              // make it fit in the hashtable
  return buckets[smallG];                             //get query bucket
}

/*Bucket* HashTable::get_bucket(float* query, unsigned int* g){  // we need the value of g for our search
  *g = gFunc->compute_Gx(query);                      // get hash function result for query
  int smallG = *g % size;                              // make it fit in the hashtable
  return buckets[smallG];                             //get query bucket
}*/

Hi** HashTable::get_His(){
  return gFunc->get_His();
}

unsigned int HashTable::get_G(int a){
  return Gs[a];
}
