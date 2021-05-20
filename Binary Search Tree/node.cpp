#include <iostream>
#include <cstring>

#include "node.h"

using namespace std;

Node::Node() {
  data = 0;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  left = NULL;
  right = NULL;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

int Node::getData() {
  return data;
}

void Node::setLeft(Node* newL) {
  left = newL;
}

void Node::setRight(Node* newR) {
  right = newR;
}

void Node::setData(int newD) {
  data = newD;
}
