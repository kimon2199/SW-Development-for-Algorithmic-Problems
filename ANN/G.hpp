#ifndef G_HPP
#define G_HPP
#include "hashf.hpp"

class G{
  private:
    int k;          //number of hi functions used to define g
    Hi** his;
  public:
    G(int dimensions, int _m, float _w, int _k);
    ~G();
    unsigned int compute_Gx(unsigned char*);
    Hi** get_His();
};
#endif
