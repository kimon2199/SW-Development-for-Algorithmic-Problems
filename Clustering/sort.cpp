#include "sort.hpp"

// A utility function to swap two elements
void swap(Point** a, Point** b) {
    Point* t = *a;
    *a = *b;
    *b = t;
}

int partition (vector <Point*>* arr, int low, int high,int dim) {
    Point* pivot = (*arr)[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++) {
        if ((*arr)[j]->vec[dim] <= pivot->vec[dim]) {
            i++;
            swap(&((*arr)[i]), &((*arr)[j]));
        }
    }
    swap(&((*arr)[i+1]), &((*arr)[high]));
    return (i + 1);
}

void quickSort(vector <Point*>* arr, int low, int high,int dim){
    if (low < high) {
        int pi = partition(arr, low, high,dim);
        quickSort(arr, low, pi - 1,dim);
        quickSort(arr, pi + 1, high,dim);
    }
}

void swap(small_Point** a, small_Point** b) {
    small_Point* t = *a;
    *a = *b;
    *b = t;
}

int partition (vector <small_Point*>* arr, int low, int high,int dim) {
    small_Point* pivot = (*arr)[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++) {
        if ((*arr)[j]->vec[dim] <= pivot->vec[dim]) {
            i++;
            swap(&((*arr)[i]), &((*arr)[j]));
        }
    }
    swap(&((*arr)[i+1]), &((*arr)[high]));
    return (i + 1);
}

void quickSort(vector <small_Point*>* arr, int low, int high,int dim){
    if (low < high) {
        int pi = partition(arr, low, high,dim);
        quickSort(arr, low, pi - 1,dim);
        quickSort(arr, pi + 1, high,dim);
    }
}
