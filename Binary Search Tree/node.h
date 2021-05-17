#ifndef Node_h
#define Node_h

#include <iostream>

using namespace std;

class Node {
 public:
  Node();
  ~Node();
  Node* getParent();
  Node* getLeft();
  Node* getRight();
  int getValue();
  void setParent(Node*);
  void setLeft(Node*);
  void setRight(Node*);
  void setValue(int);
 private:
  Node* parent;
  Node* left;
  Node* right;
  int value;
};

#endif
