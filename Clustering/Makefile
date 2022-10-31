#
# In order to execute this "Makefile" just type "make"
#
OBJS3 	= Bucket.o Centroid.o cluster_main.o cluster_member.o G.o hashf.o k_means.o Lloyd.o manhattan_distance.o point.o print.o Neighb_arr.o silhouette.o sort.o small_point.o small_Centroid.o from_new_space_to_old.o read_nn.o objFunction.o
SOURCE3	= Bucket.cpp Centroid.cpp cluster_main.cpp cluster_member.cpp G.cpp hashf.cpp k_means.cpp Lloyd.cpp manhattan_distance.cpp point.cpp print.cpp Neighb_arr.cpp silhouette.cpp sort.cpp small_point.cpp small_Centroid.cpp from_new_space_to_old.cpp read_nn.cpp objFunction.cpp
OUT3  	= cluster

CC	= g++
FLAGS   = -c -O3 --std=c++11
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OUT3)

$(OUT3): $(OBJS3)
	$(CC) $(OBJS3) -o $@ 




# create/compile the individual files separately
Bucket.o: Bucket.cpp
	$(CC) $(FLAGS) Bucket.cpp

G.o: G.cpp
	$(CC) $(FLAGS) G.cpp 

hashf.o: hashf.cpp
	$(CC) $(FLAGS) hashf.cpp

Centroid.o: Centroid.cpp
	$(CC) $(FLAGS) Centroid.cpp

small_Centroid.o: small_Centroid.cpp
	$(CC) $(FLAGS) small_Centroid.cpp

cluster_main.o: cluster_main.cpp
	$(CC) $(FLAGS) cluster_main.cpp

cluster_member.o: cluster_member.cpp
	$(CC) $(FLAGS) cluster_member.cpp

k_means.o: k_means.cpp
	$(CC) $(FLAGS) k_means.cpp

Lloyd.o: Lloyd.cpp
	$(CC) $(FLAGS) Lloyd.cpp

manhattan_distance.o: manhattan_distance.cpp
	$(CC) $(FLAGS) manhattan_distance.cpp

point.o: point.cpp
	$(CC) $(FLAGS) point.cpp

small_point.o: small_point.cpp
	$(CC) $(FLAGS) small_point.cpp

print.o: print.cpp
	$(CC) $(FLAGS) print.cpp

Neighb_arr.o: Neighb_arr.cpp
	$(CC) $(FLAGS) Neighb_arr.cpp

silhouette.o: silhouette.cpp
	$(CC) $(FLAGS) silhouette.cpp

sort.o: sort.cpp
	$(CC) $(FLAGS) sort.cpp

from_new_space_to_old.o: from_new_space_to_old.cpp
	$(CC) $(FLAGS) from_new_space_to_old.cpp

read_nn.o: read_nn.cpp
	$(CC) $(FLAGS) read_nn.cpp

objFunction.o: objFunction.cpp
	$(CC) $(FLAGS) objFunction.cpp

# clean house
clean:
	rm -f $(OBJS3) 
