#
# In order to execute this "Makefile" just type "make"
#

OBJS1 	= brute_nn.o brute_knn.o Bucket.o compute_w.o G.o hashf.o HashTable.o lsh_nn.o knn.o main_search.o manhattan_distance.o point.o print.o cluster_member.o hypercube.o small_point.o Neighb_arr.o
SOURCE1	= brute_nn.cpp brute_knn.cpp Bucket.cpp compute_w.cpp G.cpp hashf.cpp HashTable.cpp lsh_nn.cpp knn.cpp main_search.cpp manhattan_distance.cpp point.cpp print.cpp cluster_member.cpp hypercube.cpp small_point.cpp Neighb_arr.cpp
OUT1  	= search

CC	= g++
FLAGS   = -c -O3 --std=c++11
# -g option enables debugging mode
# -c flag generates object code for separate files

all: $(OUT1)

$(OUT1): $(OBJS1)
	$(CC) $(OBJS1) -o $@



# create/compile the individual files separately
main_search.o: main_search.cpp
	$(CC) $(FLAGS) main_search.cpp

Bucket.o: Bucket.cpp
	$(CC) $(FLAGS) Bucket.cpp

G.o: G.cpp
	$(CC) $(FLAGS) G.cpp

hashf.o: hashf.cpp
	$(CC) $(FLAGS) hashf.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

cluster_member.o: cluster_member.cpp
	$(CC) $(FLAGS) cluster_member.cpp

compute_w.o: compute_w.cpp
	$(CC) $(FLAGS) compute_w.cpp

hypercube.o: hypercube.cpp
	$(CC) $(FLAGS) hypercube.cpp

lsh_nn.o: lsh_nn.cpp
	$(CC) $(FLAGS) lsh_nn.cpp

knn.o: knn.cpp
	$(CC) $(FLAGS) knn.cpp

manhattan_distance.o: manhattan_distance.cpp
	$(CC) $(FLAGS) manhattan_distance.cpp

print.o: print.cpp
	$(CC) $(FLAGS) print.cpp

point.o: point.cpp
	$(CC) $(FLAGS) point.cpp

small_point.o: small_point.cpp
	$(CC) $(FLAGS) small_point.cpp

brute_nn.o: brute_nn.cpp
	$(CC) $(FLAGS) brute_nn.cpp

brute_knn.o: brute_knn.cpp
	$(CC) $(FLAGS) brute_knn.cpp

Neighb_arr.o: Neighb_arr.cpp
	$(CC) $(FLAGS) Neighb_arr.cpp



# clean house
clean:
	rm -f $(OBJS1)
