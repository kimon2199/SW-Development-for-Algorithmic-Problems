#ifndef CLUSTER_MEMBER_HPP
#define CLUSTER_MEMBER_HPP

class Cluster_member{
  int image_number;
  int distance;
  int cluster_number;
public:
  Cluster_member(int,int,int);
  ~Cluster_member();
  int get_dist();
  void set_distance(int);
  void set_cluster_number(int);
  void set_image_id(int);
  int get_cnumber();
  int get_image_number();
};

#endif
