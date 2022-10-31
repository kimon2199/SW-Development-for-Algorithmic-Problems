#include "Bucket.hpp"

Bucket::Bucket(){
  points = new std::vector<Point*>;
}

Bucket::~Bucket(){
  delete points;
}
/*-------------------add a point in the bucket----------------------*/
void Bucket::add(Point* point){
  points->push_back(point);
}
/*-------------------checking if a bucket is empty--------------------*/
bool Bucket::isEmpty(){
  return points->empty();
}
/*-------------------get a point by its position in the bucket---------*/
Point* Bucket::get_point(int j){
  return (*points)[j];
}
/*-------------------get the number of points in this Bucket---------*/
int Bucket::length(){
  return points->size();
}
