// Point.cpp
#include "point.hpp"

Point::Point(int n,unsigned char* _vec):image_number(n),vec(_vec){}

Point::Point(unsigned char* _vec,int dimensions):image_number(-1),vec(_vec){
  vec = new unsigned char[dimensions];
  for(int i=0; i<dimensions; i++){
    vec[i] = _vec[i];
  }
}

Point::~Point(){
  delete[] vec;
}
