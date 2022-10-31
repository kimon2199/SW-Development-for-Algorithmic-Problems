#include <cstring>
#include <fstream>
#include "print.hpp"



void print(int query_id, int id_lsh, int id_brute, int id_reduced, int dist_lsh, int dist_brute,
  int dist_reduced, duration<double> time_lsh, duration<double> time_brute,
  duration<double> time_reduced, ofstream* myfile){


  (*myfile) << "Query: " << query_id << endl;
  (*myfile) << "Nearest neighbour Reduced: " << id_reduced << endl;
  (*myfile) << "Nearest neighbour LSH: " << id_lsh << endl;
  (*myfile) << "Nearest neighbour True: " << id_brute << endl;
  (*myfile) << "distanceReduced: " << dist_reduced << endl; 
  (*myfile) << "distanceLSH: " << dist_lsh << endl;      
  (*myfile) << "distanceTrue: " << dist_brute << endl << endl; 

  //(*myfile) << "tReduced: " << time_reduced.count() << endl;
  //(*myfile) << "tLSH: " << time_lsh.count() << endl;
  //(*myfile) << "tTrue: " << time_brute.count() << endl << endl;

}