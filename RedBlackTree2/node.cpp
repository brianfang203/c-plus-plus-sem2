#include <iostream>

#include "node.h"

using namespace std;

Node::Node() {
  data = 0;
  right = NULL;
  left = NULL;
  color = 1; 
  parent = NULL;
}

Node::~Node() {
  if (this->getParent() != NULL) {
    if (this == this->getParent()->getLeft()) {
      this->getParent()->setLeft(NULL);
    } 
    else if (this == this->getParent()->getRight()) {
      this->getParent()->setRight(NULL);
    }
  }
  right = NULL;
  left = NULL;
  parent = NULL;
  data = 0;
}

void Node::setData(int newD) {
  data = newD;
}

void Node::setRight(Node* newR) {
  right = newR;
}

void Node::setLeft(Node* newL) {
  left = newL;
}

void Node::setColor(int newC) {
  color = newC;
}

void Node::setParent(Node* newP) {
  parent = newP;
}

int Node::getData() {
  return data;
}

Node* Node::getRight() {
  return right;
}

Node* Node::getLeft() {
  return left;
}

int Node::getColor() {
  return color;
}

Node* Node::getParent() {
  return parent;
}
