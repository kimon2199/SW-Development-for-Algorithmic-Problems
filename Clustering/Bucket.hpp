#ifndef BUCKET_HPP
#define BUCKET_HPP

#include <vector>
#include "point.hpp"

class Bucket{
  std::vector <Point*>* points;
public:
  Bucket();
  ~Bucket();
  void add(Point*);
  bool isEmpty();
  Point* get_point(int);
  int length();
};

#endif
