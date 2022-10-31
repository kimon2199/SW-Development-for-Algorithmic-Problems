// small_Point.cpp
#include "small_point.hpp"

small_Point::small_Point(int n,unsigned short* _vec):image_number(n),vec(_vec){}

small_Point::small_Point(unsigned short* _vec,int dimensions):image_number(-1),vec(_vec){
  vec = new unsigned short[dimensions];
  for(int i=0; i<dimensions; i++){
    vec[i] = _vec[i];
  }
}

small_Point::~small_Point(){
  delete[] vec;
}
