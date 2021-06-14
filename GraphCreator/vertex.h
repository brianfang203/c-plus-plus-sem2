#ifndef vertex_h
#define vertex_h

#include <iostream>

using namespace std;

class Vertex {
 public:
  Vertex(char);
  ~Vertex();
  char getLabel();
  int getDistance();
  Vertex* getPrevious();
  void setLabel(char);
  void setDistance(int);
  void setPrevious(Vertex*);
 private:
  char label;
  int distance;
  Vertex* previous;
};

#endif
