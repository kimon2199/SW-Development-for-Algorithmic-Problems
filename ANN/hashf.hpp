#include <cmath>
#ifndef HASHF_HPP
#define HASHF_HPP

class Hi{
  private:
    int dimensions,m,k;
    float w;
    double* s;                                      //Each hash function will have an array in order to store the s variables
  public:
    Hi(int dimensions, int _m = pow(2,29)-5, float _w = 50000 , int k = 4);
    ~Hi();
    int compute_Hx(unsigned char* datapoint);
    //int compute_Hx(float* datapoint);
    Hi** get_His();
};
#endif
