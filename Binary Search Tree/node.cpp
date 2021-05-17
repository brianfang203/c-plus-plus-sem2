#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  parent = NULL;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  delete &value;
  parent = NULL;
  left = NULL;
  right = NULL;
}

Node* Node::getParent() {
  return parent;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

int Node::getValue() {
  return value;
}

void Node::setParent(Node* inParent) {
  parent = inParent;
}

void Node::setLeft(Node* inLeft) {
  left = inLeft;
}

void Node::setRight(Node* inRight) {
  right = inRight;
}

void Node::setValue(int inValue) {
  value = inValue;
}
