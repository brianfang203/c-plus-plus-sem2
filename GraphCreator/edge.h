#ifndef edge_h
#define edge_h

#include <iostream>
#include "vertex.h"

using namespace std;

class Edge {
 public:
  Edge();
  ~Edge();
  Vertex* getFirst();
  Vertex* getSecond();
  int getWeight();
  void setFirst(Vertex*);
  void setSecond(Vertex*);
  void setWeight(int);
 private:
  Vertex* first;
  Vertex* second;
  int weight;
};

#endif
