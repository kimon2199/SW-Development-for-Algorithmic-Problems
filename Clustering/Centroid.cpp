#include "Centroid.hpp"

Centroid::Centroid(unsigned char* _vec,int dimensions){
  vec = new unsigned char[dimensions];
  for(int i=0; i<dimensions; i++){
    vec[i] = _vec[i];
  }
}

Centroid::~Centroid(){
  delete[] vec;
}
