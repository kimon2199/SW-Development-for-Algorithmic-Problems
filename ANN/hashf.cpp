#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include "hashf.hpp"

using namespace std;
/*-----------------function for binary exponentiation------------------------------*/
int modular_pow(unsigned int base, unsigned int exponent, unsigned int mod){
  int result = 1;
  base = base % mod;                              // Update x if it is more than or  equal to p
  if (base == 0)                                     // In case x is divisible by p;
    return 0;

  while(exponent > 0){
    if (exponent & 1)                             //This action is equivalent to exponent % 2
      result = (result*base) % mod;

    exponent = exponent >> 1;                     //This action is equivalent to exponent = exponent/2
    base = (base*base) % mod;
    }
    return result;
}
/*------------------------Constructor for class hi----------------------------------------*/
Hi::Hi(int _dimensions, int _m, float _w, int _k):dimensions(_dimensions),m(_m),w(_w),k(_k){

  s = new double[dimensions];

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);

  uniform_real_distribution <double> distribution(0.0,w);

  for(unsigned int i=0; i < dimensions; i++)            //produces random numbers in a range [0,w)
    this->s[i] = distribution(generator);               //generates number in the range we gave above
}
/*------------------------Destructor for class hi----------------------------------------*/
Hi::~Hi(){
  delete[] s;
}
/*--------------------Computing the hash function for a datapoint------------------------------*/
int Hi::compute_Hx(unsigned char* datapoint){
  int ai;
  const unsigned int M = pow(2,32/k);
  unsigned int am;                                    // the value of ai after the mod
  int mm;                                             // the value of m^(d-(i+1)) after the mod

  int result = 0;
  for(unsigned int i=0; i < dimensions; i++){         //produces random numbers in a range [0,w)
    ai = (int)(floor( (datapoint[i] - s[i]) / w) );
    am = ( (ai % M) + M ) % M;                        // in order to avoid negative values we add M to the result, if ai is positive it will stay the same number
    mm = modular_pow(m, dimensions-(i+1), M);         // a0*m^(d-1)+a1*m(d-2)+...+ ad-1*m^0 mod M
    result = (result + (am*mm)) % M;
  }
  return result;
}
/*--------------------Computing the hash function for a datapoint------------------------------*/
/*int Hi::compute_Hx(float* datapoint){
  int ai;
  const unsigned int M = pow(2,32/k);
  unsigned int am;                                    // the value of ai after the mod
  int mm;                                             // the value of m^(d-(i+1)) after the mod

  int result = 0;
  for(unsigned int i=0; i < dimensions; i++){         //produces random numbers in a range [0,w)
    ai = (int)(floor( (datapoint[i] - s[i]) / w) );
    am = ( (ai % M) + M ) % M;                        // in order to avoid negative values we add M to the result, if ai is positive it will stay the same number
    mm = modular_pow(m, dimensions-(i+1), M);         // a0*m^(d-1)+a1*m(d-2)+...+ ad-1*m^0 mod M
    result = (result + (am*mm)) % M;
  }
  return result;
}*/
