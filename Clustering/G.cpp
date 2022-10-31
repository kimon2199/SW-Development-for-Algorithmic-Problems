#include <iostream>
#include "G.hpp"

using namespace std;

/*------------------------Constructor for G function----------------------------------------*/
G::G(int _dimensions, int _m, const float _w, int _k):k(_k) {

  his = new Hi*[k];
  for (unsigned int i=0; i < k; i++)
    his[i] = new Hi(_dimensions,_m,_w,k);
}
/*------------------------Destructor for G function----------------------------------------*/
G::~G(){
  for(unsigned int i=0; i < k; i++){
    delete his[i];
  }
  delete[] his;
}

unsigned int G::compute_Gx(unsigned char* datapoint){
  int bitsInH = 32/k;
  unsigned int g = 0;

  for (int i=0; i < k; i++){
    int h = his[i]->compute_Hx(datapoint);
    g = (g << bitsInH) | h;
  }
  return g;
}

Hi** G::get_His(){
  return his;
}
