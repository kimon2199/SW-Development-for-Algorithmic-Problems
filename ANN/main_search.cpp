#include <iostream>
#include <unistd.h>                   //we need it for getopt() function
#include <vector>
#include <fstream>
#include <chrono>
#include <cstring>
#include <cassert>
#include "HashTable.hpp"
#include "lsh_nn.hpp"
#include "brute_nn.hpp"
#include "print.hpp"
#include "small_point.hpp"
#include "compute_w.hpp"
#include "manhattan_distance.hpp"
using namespace std;
using namespace std::chrono;

void SwapBinary(std::uint32_t &value) {
    std::uint32_t tmp = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
    value = (tmp << 16) | (tmp >> 16);
}

void SwapBinary2(std::uint32_t &value) {
    value = ((value << 8) & 0xFF00) | ((value >> 8) & 0xFF);
}

int main(int argc, char *argv[])
{
  int k = 4, L = 5, N = 1;

  char* input_file,*query_file, *output_file, *input_file_new_space, *query_file_new_space;
  int option;
  while((option = getopt(argc, argv, "d:q:k:L:o:i:s:")) != -1){
    switch(option){
        case 'd':
          input_file = new char[strlen(optarg)+1];
          strcpy(input_file,optarg);
          break;
        case 'q':
          query_file = new char[strlen(optarg)+1];
          strcpy(query_file,optarg);
          break;
        case 'i':
          input_file_new_space = new char[strlen(optarg)+1];
          strcpy(input_file_new_space,optarg);
          break;
        case 's':
          query_file_new_space = new char[strlen(optarg)+1];
          strcpy(query_file_new_space,optarg);
          break;
        case 'k':
          k = atoi(optarg);
          break;
        case 'L':
          L = atoi(optarg);
          break;
        case 'o':
          output_file = new char[strlen(optarg)+1];
          strcpy(output_file,optarg);
          break;
        default:
          cout << "You gave a wrong argument" << endl;
          return 1;
      }
    }
    /*+---------------------------------------------------+*/
    /*|        Processing input file original space       |*/
    /*+---------------------------------------------------+*/
    /*-----------------opening the input file--------------*/
    ifstream input;
    input.open(input_file, ios::binary | ios::in);
    if (!input.is_open()){
      cout << "Error in opening the file" << endl;
      return 1;
    }

    int length, width, numberOfVectors;
    unsigned int i=0, num=0;

    /*----------------reading the first 4 ints of the input file--------------*/
    input.seekg(0, ios::beg);
    while(i<4) {
      input.read((char*)&num, sizeof(num));
      SwapBinary(num);
      //cout << "Integer: " << num << endl;
      if (i==1)
        numberOfVectors = num; // <========================
      else if (i==2)
        length = num;
      else if (i==3)
        width = num;
      i++;
    }
    cout << endl;

    int dimensions = length * width;

    /*-----------reading the points from the input file-------------------------*/
    unsigned char* vec;
    vector <Point*>* points = new vector<Point*>; //new
    int a;
    for (int i=0; i<numberOfVectors; i++){
      vec = new unsigned char[dimensions];
      for (int j=0; j<dimensions; j++){     // read a whole vector from dataset
        input.read((char*)&a, 1);
        vec[j] = a;
      }
      Point* point = new Point(i,vec);
      points->push_back(point);       //need it for brute_knn and for k_means++
    }

    int subdivisions = 16;            //the size of the hash table is equal to numberOfVectors / subdivisions

    /*---------------Creating the L hash tables----------------*/
    HashTable** hts = new HashTable*[L];
    int w = compute_w(numberOfVectors,dimensions,points);
    int m = 255/w + 1;
    for (int i=0; i < L; i++)
      hts[i] = new HashTable(numberOfVectors,m,w,k,dimensions,subdivisions);

    cout << "Adding points in the hash tables:" << endl;
    for (int i=0; i< numberOfVectors; i++){
      for (int j=0; j < L; j++)
        hts[j]->add((*points)[i]);
      if ((i+1) % 1000 == 0)
        cout << " "<< i+1 << " / " << numberOfVectors << endl;
    }
    /*+---------------------------------------------------+*/
    /*|          Processing input file new space          |*/
    /*+---------------------------------------------------+*/
    /*--------------opening the new space file-------------*/
    ifstream input1;
    input1.open(input_file_new_space, ios::binary | ios::in);
    if (!input1.is_open()){
      cout << "Error in opening the input file new space" << endl;
      return 1;
    }

    int numberOfVectorsNew;
    i=0, num=0;

    /*------reading the first 4 ints of the input file-------*/
    input1.seekg(0, ios::beg);
    while(i<4) {
      input1.read((char*)&num, sizeof(num));
      SwapBinary(num);
      if (i==1)
        numberOfVectorsNew = num; // <========================
      else if (i==2)
        length = num;
      else if (i==3)
        width = num;
      i++;
    }
    cout << endl;

    int small_dimensions = length * width;

    /*-----------reading the points from the input file-------------------------*/
    unsigned short* small_vec;
    vector <small_Point*>* small_points = new vector<small_Point*>; //new
    unsigned int aa;
    for (int i=0; i<numberOfVectorsNew; i++){
      small_vec = new unsigned short[small_dimensions];
      for (int j=0; j<small_dimensions; j++){     // read a whole vector from dataset
        input1.read((char*)&aa, 2);
        SwapBinary2(aa);
        small_vec[j] = aa;
      }
      small_Point* small_point = new small_Point(i,small_vec);
      small_points->push_back(small_point);       //need it for brute_knn and for k_means++
    }


    /*+---------------------------------------------------+*/
    /*|         Opening query file original space         |*/
    /*+---------------------------------------------------+*/
    /*-------------------opening the query file------------*/
    ifstream input2;
    input2.open(query_file, ios::binary | ios::in);
    if (!input2.is_open()){
      cout << "Error in opening the file" << endl;
      return 1;
    }

    int length2, width2, numberOfVectors2;
    num = 0;
    i = 0;
    /*----------------reading the first queries from the query file--------------*/
    input2.seekg(0, ios::beg);

    while(i<4)
    {
      input2.read((char*)&num, sizeof(num));
      SwapBinary(num);

      //cout << "Integer: " << num << endl;
      if (i==1)
        numberOfVectors2 = num;
      else if (i==2)
        length2 = num;
      else if (i==3)
        width2 = num;
      i++;
    }


    /*+---------------------------------------------------+*/
    /*|            Opening query file new space           |*/
    /*+---------------------------------------------------+*/

    ifstream input3;
    input3.open(query_file_new_space, ios::binary | ios::in);
    if (!input3.is_open()){
      cout << "Error in opening query file new space" << endl;
      return 1;
    }

    int numberOfVectors2New;
    num=0;
    i=0;
    /*---------reading the first queries from the query file---------*/
    input3.seekg(0, ios::beg);

    while(i<4)
    {
      input3.read((char*)&num, sizeof(num));
      SwapBinary(num);

      //cout << "Integer: " << num << endl;
      if (i==1)
        numberOfVectors2New = num;
      else if (i==2)
        length2 = num;
      else if (i==3)
        width2 = num;
      i++;
    }

    /*---------make sure all is good in order to move on-------------*/
    assert (numberOfVectors == numberOfVectorsNew);
    assert (numberOfVectors2 == numberOfVectors2New);

    /*+---------------------------------------------------+*/
    /*|                    Running Queries                |*/
    /*+---------------------------------------------------+*/

    unsigned char* query;
    unsigned short* small_query;
    ofstream* myfile = new ofstream;
    myfile->open(output_file);

    cout << "Finding neighbours of query vectors:" << endl;
    double approxLSH = 0.0;
    double approxRED = 0.0;
    int validQueries = 0;
    duration<double> time_reduced = duration_cast<microseconds>(high_resolution_clock::now() - high_resolution_clock::now());
    duration<double> time_lsh = time_reduced, time_brute = time_reduced;
    for (int i=0; i < numberOfVectors2; i++){
      if ((i+1) % 1000 == 0)
        cout << " "<< i+1 << " / " << numberOfVectors2 << endl;
      //myfile << "Query: " << i+1 << endl;

      /* Reading old space query from file */
      query = new unsigned char[dimensions];
      for (int j=0; j<dimensions; j++){
        input2.read((char*)&a, 1);
        query[j] = a;
      }
      /* Reading new space query from file */
      small_query = new unsigned short[small_dimensions];
      for (int j=0; j<small_dimensions; j++){
        input3.read((char*)&aa, 2);
        SwapBinary2(aa);
        small_query[j] = aa;
      }

      /*time*/ high_resolution_clock::time_point start_nn = high_resolution_clock::now();
      Point* answer_LSH = lsh_nn(L,query,dimensions,hts);
      /*time*/ high_resolution_clock::time_point stop_nn = high_resolution_clock::now();
      /*time*/ duration<double> duration_nn = duration_cast<microseconds>(stop_nn - start_nn);
      time_lsh += duration_nn;

      /*time*/ high_resolution_clock::time_point start_brute = high_resolution_clock::now();
      Point* answer_true = brute_nn(query,dimensions,numberOfVectors,points);
      /*time*/ high_resolution_clock::time_point stop_brute = high_resolution_clock::now();
      /*time*/ duration<double> duration_brute = duration_cast<microseconds>(stop_brute - start_brute);
      time_brute += duration_brute;

      /*time*/ high_resolution_clock::time_point start_brute_small = high_resolution_clock::now();
      small_Point* answer_true_small = small_brute_nn(small_query,small_dimensions,numberOfVectors,small_points);
      /*time*/ high_resolution_clock::time_point stop_brute_small = high_resolution_clock::now();
      /*time*/ duration<double> duration_brute_small = duration_cast<microseconds>(stop_brute_small - start_brute_small);
      time_reduced += duration_brute_small;

      if (answer_LSH && answer_true && answer_true_small){ /* if there is no NULL */
        int dist_lsh = manhattan_distance(query,answer_LSH->vec,dimensions);
        int dist_brute = manhattan_distance(query,answer_true->vec,dimensions);
        int dist_reduced = manhattan_distance(query,(*points)[answer_true_small->image_number]->vec,dimensions);

        print(i, answer_LSH->image_number, answer_true->image_number, answer_true_small->image_number,
          dist_lsh, dist_brute, dist_reduced,
          duration_nn, duration_brute, duration_brute_small, myfile);

        approxLSH += ((double) dist_lsh) / dist_brute;
        approxRED += ((double) dist_reduced) / dist_brute;
        validQueries++;
      }

      delete[] query;
      delete[] small_query;
    }

    (*myfile) << "We calculated the average time for every method" << endl;
    (*myfile) << "tReduced: " << time_reduced.count() * 1000 / numberOfVectors2 << " milliseconds" << endl;
    (*myfile) << "tLSH: "     << time_lsh.count()     * 1000 / numberOfVectors2 << " milliseconds " << endl;
    (*myfile) << "tTrue: "    << time_brute.count()   * 1000 / numberOfVectors2 << " milliseconds " << endl;

    approxLSH = approxLSH / validQueries;
    approxRED = approxRED / validQueries;
    (*myfile) << endl;
    (*myfile) << "Approximation Factor LSH: " << approxLSH << endl;
    (*myfile) << "Approximation Factor Reduced: " << approxRED << endl;

    //deleting zone
    for (int i=0; i < L; i++)
      delete hts[i];
    myfile->close();
    delete myfile;
    delete[] input_file;
    delete[] query_file;
    delete[] input_file_new_space;
    delete[] query_file_new_space;
    delete[] output_file;
    for (int i=0; i < points->size(); i++)
      delete (*points)[i];
    delete points;
    return 0;
}
