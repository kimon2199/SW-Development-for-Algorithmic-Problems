// Neighb_arr.hpp
#include "point.hpp"

class Neighb_arr{
  Point** neighbours;
  int* mins;                    //minimun distance
  int size;  //πληθος γειτονων
  int additions;
  void shift(int);
public:
  Neighb_arr(int);
  bool fitsBetter(int);
  void add(int,Point*);
  Point** getNeighs();
  ~Neighb_arr();
  int* get_mins();
  bool not_in(Point*);
  int get_additions();
};
