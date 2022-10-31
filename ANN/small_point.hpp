// small_Point.hpp
#ifndef SMALL_POINT_HPP
#define SMALL_POINT_HPP


struct small_Point{
  unsigned short* vec;
  int image_number;
  small_Point(int,unsigned short*);  //this constructor just sets the fields od the class
  small_Point(unsigned short*,int);    //initializes the image_number to -1
  ~small_Point();
};

#endif
