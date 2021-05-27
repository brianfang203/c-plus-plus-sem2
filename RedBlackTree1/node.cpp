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
  right = NULL;
  left = NULL;
  parent = NULL;
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
