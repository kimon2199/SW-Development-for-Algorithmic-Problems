#ifndef SORT_HPP
#define SORT_HPP

#include <iostream>
#include <vector>
#include "point.hpp"
#include "small_point.hpp"
using namespace std;



void quickSort(vector <Point*>* arr, int low, int high,int dim);
void quickSort(vector <small_Point*>* arr, int low, int high,int dim);

#endif
