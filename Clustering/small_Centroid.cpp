#include "small_Centroid.hpp"

small_Centroid::small_Centroid(unsigned short* _vec,int dimensions){
  vec = new unsigned short[dimensions];
  for(int i=0; i<dimensions; i++){
    vec[i] = _vec[i];
  }
}

small_Centroid::~small_Centroid(){
  delete[] vec;
}
