#include "from_new_space_to_old.hpp"

Cluster_member** convert_small_to_big_members(Cluster_member** old_members,int numberOfVectors,
	int num_of_clusters,int dimensions,vector <Centroid*> *clusterp, vector <Point*>* points){
	

	Cluster_member** new_members = new Cluster_member*[numberOfVectors];
	for (int i=0; i < numberOfVectors; i++){
		/* distance will be given as 0 to the constructor but changed after we find the centroid */
		new_members[i] = new Cluster_member(old_members[i]->get_image_number(),0,old_members[i]->get_cnumber());
	}

	unsigned char* coordinates;

	for(int i=0; i < num_of_clusters; i++){         //do this loop for every centroid/cluster
		int vectors_in_cluster = 0;
		coordinates = new unsigned char[dimensions] ();
		vector <Point*>* points_of_cluster = new vector <Point*>;
		for(int j=0; j < numberOfVectors; j++)
			if(new_members[j]->get_cnumber() == i)
				points_of_cluster->push_back((*points)[new_members[j]->get_image_number()]);

		for(int l=0; l < dimensions; l++){
			quickSort(points_of_cluster,0,points_of_cluster->size()-1,l);
			unsigned char coord = (*points_of_cluster)[points_of_cluster->size()/2]->vec[l];
			coordinates[l] = coord;
		}

		delete points_of_cluster;

		/* set the distance for each member */
		for(int j=0; j < numberOfVectors; j++)
			if(new_members[j]->get_cnumber() == i)
				new_members[j]->set_distance(manhattan_distance(coordinates,(*points)[new_members[j]->get_image_number()]->get_vec(),dimensions));

		clusterp->push_back(new Centroid(coordinates,dimensions));   //assign the new centroid


		delete coordinates;
	} //end of updating the centroids

	return new_members;
}
