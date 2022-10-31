// Point.hpp
#ifndef POINT_HPP
#define POINT_HPP


struct Point{
  unsigned char* vec;
  int image_number;
  Point(int,unsigned char*);  //this constructor just sets the fields od the class
  Point(unsigned char*,int);    //initializes the image_number to -1
  ~Point();
};

#endif
