#include <iostream>
#include <cstdlib>
#include <unistd.h>                   //we need it for getopt() function
#include <fstream>
#include <vector>
#include <cstring>
#include <chrono>
#include "k_means.hpp"
#include "Lloyd.hpp"
#include "cluster_member.hpp"
#include "Centroid.hpp"
#include "small_Centroid.hpp"
#include "print.hpp"
#include "silhouette.hpp"
#include "small_point.hpp"
#include "from_new_space_to_old.hpp"
#include "read_nn.hpp"
#include "objFunction.hpp"
using namespace std;
using namespace std::chrono;

void SwapBinary(std::uint32_t &value) {
    std::uint32_t tmp = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
    value = (tmp << 16) | (tmp >> 16);
}

void SwapBinary2(std::uint32_t &value) {
    value = ((value << 8) & 0xFF00) | ((value >> 8) & 0xFF);
}

int main(int argc, char *argv[]) {
  int k=4; //3?
  int clusters/*=10*/;
  int L = 3, N = 5 ;
  float R = 1000 ;

  //int m=10;
  char* input_file, *input_file_new, *configuration_file, *output_file, *nn_file;
  int option;
  while((option = getopt(argc, argv, "d:c:o:i:n:")) != -1){
    switch(option){
        case 'd':
          input_file = new char[strlen(optarg)+1];
          strcpy(input_file,optarg);
          break;
        case 'c':
          configuration_file = new char[strlen(optarg)+1];
          strcpy(configuration_file,optarg);
          break;
        case 'o':
          output_file = new char[strlen(optarg)+1];
          strcpy(output_file,optarg);
          break;
        case 'i':
          input_file_new = new char[strlen(optarg)+1];
          strcpy(input_file_new,optarg);
          break;
        case 'n':
          nn_file = new char[strlen(optarg)+1];
          strcpy(nn_file,optarg);
          break;
        default:
          cout << option << endl;
          cout << "You gave a wrong argument" << endl;
          return 1;
      }
    }
    /*-----------------Reding from file cluster.conf-----------------*/
    ifstream cluster_file;
    cluster_file.open(configuration_file);
    if (!cluster_file.is_open()){
      cout << "Error in opening the cluster file" << endl;
      return 1;
    }
    string word,word2;
    while (cluster_file >> word) {
      cluster_file >> word2;
      if (!word.compare("number_of_clusters:"))
        clusters = atoi(word2.c_str());
      else if (!word.compare("number_of_vector_hash_tables:"))
        L = atoi(word2.c_str());
      else if (!word.compare("number_of_vector_hash_functions:"))
        k = atoi(word2.c_str());
    }
    cluster_file.close();

    /*-----------------Reding input file old space-----------------*/
    ifstream input;
    input.open(input_file, ios::binary | ios::in);
    if (!input.is_open()){
      cout << "Error in opening the file (old space)" << endl;
      return 1;
    }

    int length, width, numberOfVectors;
    unsigned int i=0, num=0;

    input.seekg(0, ios::beg);         //start reading from the beginning of the file

    while(i<4)
    {
      input.read((char*)&num, sizeof(num));
      SwapBinary(num);

      if (i==1)
        numberOfVectors = num;
      else if (i==2)
        length = num;
      else if (i==3)
        width = num;
      i++;
    }
    cout << endl;

    int dimensions = length*width;
    int subdivisions = 4;

    unsigned char* vec;
    vector <Point*>* points = new vector<Point*>; //new
    int a;

    for (int i=0; i<numberOfVectors; i++){
      vec = new unsigned char[dimensions];
      for (int j=0; j<dimensions; j++){ // read a whole vector from dataset
        input.read((char*)&a, 1);
        vec[j] = a;
      }

      Point* point = new Point(i,vec);
      points->push_back(point);  //new,need it for brute_knn and for k_means++
    }
    //numberOfVectors = n; // <============================================
    /*-----------------Reding input file new space-----------------*/
    ifstream input1;
    input1.open(input_file_new, ios::binary | ios::in);
    if (!input1.is_open()){
      cout << "Error in opening the input file new space" << endl;
      return 1;
    }

    int numberOfVectorsNew;
    i=0, num=0;

    input1.seekg(0, ios::beg);
    while(i<4) {
      input1.read((char*)&num, sizeof(num));
      SwapBinary(num);
      if (i==1)
        numberOfVectorsNew = num;///= num; // <========================
      else if (i==2)
        length = num;
      else if (i==3)
        width = num;
      i++;
    }
    cout << endl;

    int small_dimensions = length * width;

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


    /*------------Opening file we are gonna print in-----------*/
    ofstream* myfile = new ofstream;
    myfile->open(output_file);


    /*--------Initialization of centroids for NEW space--------*/


    Cluster_member** small_members = new Cluster_member*[numberOfVectorsNew];

    vector <small_Centroid*>* small_clusters_centers = new vector<small_Centroid*>;
    high_resolution_clock::time_point start1 = high_resolution_clock::now();
    vector <small_Point*>* small_temp_centers = k_means(numberOfVectorsNew,small_dimensions,small_points,clusters,small_members);
    high_resolution_clock::time_point stop1 = high_resolution_clock::now();

    for (vector<small_Point*>::iterator it = small_temp_centers->begin(); it != small_temp_centers->end(); ++it){
      small_Centroid* cluster_cent = new small_Centroid((*it)->vec,small_dimensions);
      small_clusters_centers->push_back(cluster_cent);
    }

    /*----------Clustering and Silhuette for NEW space---------*/

    string name;
    cout << "Started Clustering (new space)"<< endl;
    high_resolution_clock::time_point start = high_resolution_clock::now();

    lloyd(small_clusters_centers,small_members,numberOfVectorsNew,clusters,small_dimensions,small_points);
    name = "NEW SPACE";

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    duration<double> duration = duration_cast<microseconds>((stop - start) + (stop1 - start1));
    cout << "Finished Clustering (new space)"<< endl;

    cout << "Starting calculating silhouette (new space)" << endl;
    vector <Centroid*>* big_small_clusters_centers = new vector<Centroid*>;
    Cluster_member** big_small_members = convert_small_to_big_members(small_members,numberOfVectorsNew,clusters,dimensions,big_small_clusters_centers,points);
    double* big_small_silh = silhouette(big_small_clusters_centers,big_small_members,points,numberOfVectorsNew,dimensions);
    cout << "Finished calculating silhouette (new space)" << endl;


    (*myfile) << endl << endl << endl;
    cluster_print(name,duration,clusters,numberOfVectorsNew,small_dimensions,small_clusters_centers,big_small_silh,small_members,myfile);
    (*myfile) << "Value of Objective Function: " << objFunction(big_small_members,numberOfVectorsNew) << endl;

    /*--------Initialization of centroids for old space--------*/


    Cluster_member** members = new Cluster_member*[numberOfVectors];

    vector <Centroid*>* clusters_centers = new vector<Centroid*>;
    start1 = high_resolution_clock::now();
    vector <Point*>* temp_centers = k_means(numberOfVectors,dimensions,points,clusters,members);
    stop1 = high_resolution_clock::now();

    for (vector<Point*>::iterator it = temp_centers->begin(); it != temp_centers->end(); ++it){
      Centroid* cluster_cent = new Centroid((*it)->vec,dimensions);
      clusters_centers->push_back(cluster_cent);
    }

    /*----------Clustering and Silhuette for old space---------*/

    cout << "Started Clustering (old space)"<< endl;
    start = high_resolution_clock::now();

    lloyd(clusters_centers, members,numberOfVectors,clusters,dimensions,points);
    name = "ORIGINAL SPACE";

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>((stop - start) + (stop1 - start1));
    cout << "Finished Clustering (old space)"<< endl;
    cout << "Starting calculating silhouette (old space)" << endl;
    double* silh = silhouette(clusters_centers,members,points,numberOfVectors,dimensions);
    cout << "Finished calculating silhouette (old space)" << endl;
    (*myfile) << endl << endl << endl;
    cluster_print(name,duration,clusters,numberOfVectors,dimensions,clusters_centers,silh,members,myfile);
    (*myfile) << "Value of Objective Function: " << objFunction(members,numberOfVectors) << endl;

    /*----------------Opening Neural File to read--------------*/

    Cluster_member** nn_old_members = read_nn(nn_file,clusters,numberOfVectors);

    cout << "Starting calculating silhouette (Neural Net)" << endl;
    vector <Centroid*>* nn_clusters_centers = new vector<Centroid*>;
    Cluster_member** nn_members = convert_small_to_big_members(nn_old_members,numberOfVectors,clusters,dimensions,nn_clusters_centers,points);
    double* nn_silh = silhouette(nn_clusters_centers,nn_members,points,numberOfVectors,dimensions);
    cout << "Finished calculating silhouette (Neural Net)" << endl;

    name = "CLASSES AS CLUSTERS";
    (*myfile) << endl << endl << endl;
    (*myfile) << "CLASSES AS CLUSTERS" << endl;
    (*myfile) << "Silhouette: [";
    for (int i=0; i<= clusters; i++){
      (*myfile) << nn_silh[i];
      if (i!=clusters)
        (*myfile) << ", ";
    }

    (*myfile) << "]" << endl;
    (*myfile) << "Value of Objective Function: " << objFunction(nn_members,numberOfVectors) << endl;
    cout << endl << endl;


    for (int l=0; l < clusters ; l++){
      for(int i=0; i < 28; i++){
        for(int j=0; j < 28; j++){
          if (((int)(*clusters_centers)[l]->vec[i*28+j]) != 0)
            printf("%3d ",(int)(*clusters_centers)[l]->vec[i*28+j]);
          else
            printf("    ");
        }
        cout << endl;
      }
    }

    cout << endl << endl << "--------------------------------------" << endl << endl;

    for (int l=0; l < clusters ; l++){
      for(int i=0; i < 28; i++){
        for(int j=0; j < 28; j++){
          if (((int)(*big_small_clusters_centers)[l]->vec[i*28+j]) != 0)
            printf("%3d ",(int)(*big_small_clusters_centers)[l]->vec[i*28+j]);
          else
            printf("    ");
        }
        cout << endl;
      }
    }

    cout << endl << endl << "--------------------------------------" << endl << endl;

    for (int l=0; l < clusters ; l++){
      for(int i=0; i < 28; i++){
        for(int j=0; j < 28; j++){
          if (((int)(*nn_clusters_centers)[l]->vec[i*28+j]) != 0)
            printf("%3d ",(int)(*nn_clusters_centers)[l]->vec[i*28+j]);
          else
            printf("    ");
        }
        cout << endl;
      }
    }




    //deleting zone

    delete[] input_file;
    delete[] input_file_new;
    delete[] configuration_file;
    delete[] output_file;
    myfile->close();
    delete myfile;
    for (int i=0; i < points->size(); i++)
      delete (*points)[i];
    delete points;

    return 0;
}
