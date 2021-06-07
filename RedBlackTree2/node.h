#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  Node();
  ~Node();
  void setData(int);
  void setRight(Node*);
  void setLeft(Node*);
  void setColor(int);
  void setParent(Node*);
  int getData();
  Node* getRight();
  Node* getLeft();
  int getColor();
  Node* getParent();
private:
  int data;
  Node* right;
  Node* left;
  int color;  
  Node* parent;
};
#endif
