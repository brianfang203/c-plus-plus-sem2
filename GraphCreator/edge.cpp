#include <iostream>
#include "edge.h"
#include "vertex.h"

using namespace std;

Edge::Edge() {
  first = NULL;
  second = NULL;
}

Edge::~Edge() {
  first = NULL;
  second = NULL;
  delete &weight;
}

Vertex* Edge::getFirst() {
  return first;
}

Vertex* Edge::getSecond() {
  return second;
}

int Edge::getWeight() {
  return weight;
}

void Edge::setFirst(Vertex* inFirst) {
  first = inFirst;
}

void Edge::setSecond(Vertex* inSecond) {
  second = inSecond;
}

void Edge::setWeight(int inWeight) {
  weight = inWeight;
}
