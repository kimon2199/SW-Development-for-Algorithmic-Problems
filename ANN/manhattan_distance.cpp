#include "manhattan_distance.hpp"

unsigned char abs(unsigned char i,unsigned char j){
	int x = i;
	int y = j;
	int z = (x > y) ? x-y : y-x;
	return (unsigned char) z;
}

unsigned short abs(unsigned short i,unsigned short j){
  int x = i;
  int y = j;
  int z = (x > y) ? x-y : y-x;
  return (unsigned short) z;
}

float abs(float i,float j){
	float x = i;
	float y = j;
	float z = (x > y) ? x-y : y-x;
	return z;
}

float abs(float i,unsigned char j){
	float x = i;
	float y = j;
	float z = (x > y) ? x-y : y-x;
	return z;
}

float manhattan_distance(float* q, float* p, int dimensions){
  float result = 0;

  for(int i=0; i < dimensions ; i++)
    result += abs(q[i],p[i]);

  return result;
}

int manhattan_distance(unsigned char* q, unsigned char* p, int dimensions){
  int result = 0;

  for(int i=0; i < dimensions ; i++)
    result += abs(q[i],p[i]);

  return result;
}

int manhattan_distance(unsigned short* q, unsigned short* p, int dimensions){
  int result = 0;

  for(int i=0; i < dimensions ; i++)
    result += abs(q[i],p[i]);

  return result;
}

float manhattan_distance(float* q, unsigned char* p, int dimensions){
  float result = 0;

  for(int i=0; i < dimensions ; i++)
    result += abs(q[i],p[i]);

  return result;
}
