#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include "vertex.h"
#include "edge.h"

using namespace std;

//colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

//storing verticies/edges
vector<Vertex*> vertices; 
vector<Edge*> edges; 

//prototypes
void addVertex(char label);
void addEdge(char firstLabel, char secondLabel, int weight);
void removeEdge(char firstLabel, char secondLabel, bool user);
void removeVertex(char label);
void findShortest(char startLabel, char  endLabel);
void printAdjacency();

//main function
int main() {
	int numInput;
	char charInput;
	char charInput2;
	while (true) {

		//user input
		cout << endl << "Enter a number:" << endl;
		cout << "1: Add vertex" << endl;
		cout << "2: Add edge" << endl;
		cout << "3: Remove a vertex" << endl;
		cout << "4: Remove an edge" << endl;
		cout << "5: Shortest path between two vertices" << endl;
		cout << "6: Print adjacency matrix" << endl;
		cout << "7: Quit program" << endl;
		cout << endl << GREEN << ">> " << RESET;
		cin >> numInput;
		cin.clear();
		cin.ignore(1000000, '\n');

		if (numInput == 1) {
			cout << endl << "Enter the character to assign the vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput;
			cin.clear();
			cin.ignore(1000000, '\n');
			addVertex(charInput);
		}

		//adding edge
		else if (numInput == 2) {
			cout << endl << "Enter the character of the first vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput;
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << endl << "Enter the character of the second vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput2;
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << endl << "Enter the weight of the edge: " << endl << GREEN ">> " << RESET;
			cin >> numInput;
			cin.clear();
			cin.ignore(1000000, '\n');
			addEdge(charInput, charInput2, numInput);
		}

		//removing vertex
		else if (numInput == 3) {
			cout << endl << "Enter the label of the vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput;
			cin.clear();
			cin.ignore(1000000, '\n');
			removeVertex(charInput);
		}

		//removing edge
		else if (numInput == 4) {
			cout << endl << "Enter the label of the first vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput;
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << endl << "Enter the label of the second vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput2;
			cin.clear();
			cin.ignore(1000000, '\n');
			removeEdge(charInput, charInput2, true);
		}

		//shortest path
		else if (numInput == 5) {
			cout << endl << "Enter the label of the starting vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput;
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << endl << "Enter the label of the ending vertex: " << endl << GREEN << ">> " << RESET;
			cin >> charInput2;
			cin.clear();
			cin.ignore(1000000, '\n');
			findShortest(charInput, charInput2);
		}

		//print adjacency matrix
		else if (numInput == 6) {
			printAdjacency();
		}

		//quitting program
		else if (numInput == 7) {
			break;
		}

		//invalid input
		else {
			cout << endl << RED << "Invalid input" << RESET << endl;
		}
	}
	return 0;
}

//add vertex function
void addVertex(char label) {
	Vertex* temp = new Vertex(label);
	bool exists = false;
	vector<Vertex*>::iterator v;
	for (v = vertices.begin(); v != vertices.end(); v++) {
		if ((*v) -> getLabel() == label){
			exists = true;
		}
	}
	if (!exists) {
		vertices.push_back(temp);
		cout << endl << GREEN << "Vertex has been added" << RESET << endl;
	}
	else {
		cout << endl << RED << "Cannot have duplicate labels" << RESET << endl;
	}
	temp = NULL;
	delete temp;
}

//add edge function
void addEdge(char firstLabel, char secondLabel, int weight) {
	Edge* temp = new Edge();
	Vertex* first = NULL;
	Vertex* second = NULL;
	bool exists = false;
	vector<Vertex*>::iterator v;
	for (v = vertices.begin(); v != vertices.end(); v++) {
		if ((*v) -> getLabel() == firstLabel) {
			first = *v;
		}
		if ((*v) -> getLabel() == secondLabel) {
			second = *v;
		}
	}
	if (first == second) {
		cout << endl << RED << "Cannot connect a vertex to itself" << RESET << endl;
		return;
	}
	vector<Edge*>::iterator e;
	for (e = edges.begin(); e != edges.end(); e++) {
		if (((*e) -> getFirst() == first && (*e) -> getSecond() == second))
			exists = true;
	}
	if (first != NULL && second != NULL && !exists) {
		temp -> setFirst(first);
		temp -> setSecond(second);
		temp -> setWeight(weight);
		edges.push_back(temp);
		cout << endl << GREEN << "Edge has been added" << RESET << endl;
	}
	else if (exists) {
		cout << endl << RED << "There is an edge already connecting these two vertices" << RESET << endl;
	}
	else {
		cout << endl << RED << "One of the vertices does not exist" << RESET << endl;
	}
	first = NULL;
	second = NULL;
	temp = NULL;
	delete first;
	delete second;
	delete temp;
}

//remove edge function
void removeEdge(char firstLabel, char secondLabel, bool user) {
	if (edges.empty()) {
		if (user) {
			cout << endl << RED << "There are no edges" << RESET << endl;
		}
		return;
	}
	Vertex* first = NULL;
	Vertex* second = NULL;
	vector<Vertex*>::iterator v;
	vector<Edge*>::iterator e;
	for (v = vertices.begin(); v != vertices.end(); v++) {
		if ((*v) -> getLabel() == firstLabel) {
			first = *v;
		}
		if((*v) -> getLabel() == secondLabel) {
			second = *v;
		}
	}
	if (first == second) {
		cout << endl << RED << "Cannot connect vertex to itself" << RESET << endl;
		return;
	}
	for (e = edges.begin(); e != edges.end(); e++) {
		if (((*e) -> getFirst() == first && (*e) -> getSecond() == second)) {
			edges.erase(e);
			if (user) 
				cout << endl << GREEN << "The edge has been removed" << RESET << endl;
			return;
		}
	}
	if (first != NULL && second != NULL && user)
		cout << endl << RED << "This edge does not exists" << RESET << endl;
	else 
		if (user)
			cout << endl << RED << "One of the vertices does not exist" << RESET << endl;
	first = NULL;
	second = NULL;
	delete first;
	delete second;
}

//remove vertex function
void removeVertex(char label) {
	vector<Vertex*>::iterator v;
	vector<Edge*>::iterator e;
	bool edged = false;
	char yesno;
	if (vertices.empty()) {
		cout << endl << RED << "There are no vertices" << RESET << endl;
		return;
	}
	for (v = vertices.begin(); v != vertices.end(); v++) {
		if ((*v) -> getLabel() == label) {
			for (e = edges.begin(); e != edges.end(); e++) {
				if ((*e) -> getFirst() == *v || (*e) -> getSecond() == *v) {
					edged = true;
				}
			}
			if (edged) {
				cout << endl << YELLOW << "The vertex is connected to an edge, would you still like to remove(y/n): ";
				cout << endl << GREEN << ">> " << RESET;
				cin >> yesno;
				cin.clear();
				cin.ignore(1000000, '\n');
				if (yesno == 'y') {
					bool finished = false;
					while(!finished) {
						for (e = edges.begin(); e != edges.end(); e++) {
							if (e == edges.end() - 1)
								finished = true;
							if ((*e) -> getFirst() == *v || (*e) -> getSecond() == *v) {
								removeEdge((*e) -> getFirst() -> getLabel(), (*e) -> getSecond() -> getLabel(), false);
								removeEdge((*e) -> getSecond() -> getLabel(), (*e) -> getFirst() -> getLabel(), false);
								break;
							}
						}
					}
					vertices.erase(v);
					cout << endl << GREEN << "The vertex was removed" << RESET << endl; 
					return;
				}
				else {
					cout << endl << GREEN << "The vertex was not removed" << RESET << endl;
					return;
				}
			}
			else {
				vertices.erase(v);
				cout << endl << GREEN << "The vertex has been removed" << RESET << endl;
				return;
			}
		}
	}
	cout << endl << RED << "There is no vertex with that label" << RESET << endl;

}

//find shortest path function
void findShortest(char startLabel, char  endLabel) {
	Vertex* start = NULL;
	Vertex* end = NULL;
	vector<Vertex*>::iterator v;
	vector<Edge*>::iterator e;
	for (v = vertices.begin(); v != vertices.end(); v++) {
		if ((*v) -> getLabel() == startLabel) {
			start = *v;
		}
		if ((*v) -> getLabel() == endLabel) {
			end = *v;
		}
	}
	if (start == NULL || end == NULL) {
		cout << endl << RED << "One of these vertices does not exist" << RESET << endl;
		return;
	}
	if (start == end) {
		cout << endl << RED << "There is no distance between a vertex and itself" << RESET << endl;
		return;
	}
	if (start != NULL && end != NULL && !edges.empty()) {
		vector<Vertex*> visited;
		vector<Vertex*> unvisited = vertices;
		Vertex* current = NULL;
		for (v = unvisited.begin(); v != unvisited.end(); v++) {
			if ((*v) == start) {
				(*v) -> setDistance(0);
				current = (*v);
				break;
			}
		}
		while (!unvisited.empty()) {
			int distance = current -> getDistance();
			for (v = unvisited.begin(); v != unvisited.end(); v++) {
				if ((*v) -> getLabel() != current -> getLabel()) {
					for (e = edges.begin(); e != edges.end(); e++) {
						if ((*e) -> getFirst() -> getLabel() == current -> getLabel() && (*e) -> getSecond() -> getLabel() == (*v) -> getLabel()) {
							if ((*v) -> getDistance() == -1 || (*v) -> getDistance() > distance + (*e) -> getWeight()) {
								(*v) -> setDistance(distance + (*e) -> getWeight());
							}
						}
					}
				}
			}
			Vertex* newCurrent = NULL;
			for (v = unvisited.begin(); v != unvisited.end(); v++) {
				if ((*v) -> getLabel() == current -> getLabel()) {
					unvisited.erase(v);
					visited.push_back(current);
					break;
				}
			} 
			for (v = unvisited.begin(); v != unvisited.end(); v++) {
				if (newCurrent == NULL)
					newCurrent = *v;
				if (newCurrent -> getDistance() > (*v) -> getDistance())
					if ((*v) -> getDistance() > 0)
						newCurrent = *v;
			}

			current = newCurrent;
		}
    		cout << endl << GREEN << "Path: ";
		for (v = visited.begin(); v != visited.end(); v++) {
      
      			//print out path
      			cout << GREEN << (*v)->getLabel() << " ";
			if ((*v) -> getLabel() == endLabel) {
				if ((*v) -> getDistance() > 0) {
					cout << endl << GREEN << "The distance between " << startLabel << " and " << endLabel << " is: " << (*v) -> getDistance() << endl << RESET;
					break;
				}
				else if ((*v) -> getDistance() == -1) 
					cout << endl << RED << "The vertices are not connected" << RESET << endl;
			}
		}
	}
	else if (edges.empty()) 
		cout << endl << RED << "There are no edges" << RESET << endl;
	else 
		cout << endl << RED << "One of the vertices does not exist" << RESET << endl;
	for (v = vertices.begin(); v != vertices.end(); v++) 
		(*v) -> setDistance(-1);
		start = NULL;
		end = NULL;
		delete start;
		delete end;
}

//print adjacency matrix function
void printAdjacency() {
	if (vertices.empty()) {
		cout << endl << RED << "There are no vertices" << RESET << endl;
		return;
	}
	cout << "\t";
	vector<Vertex*>::iterator v;
	for (v = vertices.begin(); v != vertices.end(); v++) {
		cout << (*v) -> getLabel() << "\t";
	}
	cout << endl;
	vector<Vertex*>::iterator v2;
	vector<Edge*>::iterator e; 
	for (v = vertices.begin(); v != vertices.end(); v++) {
		cout << (*v) -> getLabel() << "\t";
		for (v2 = vertices.begin(); v2 != vertices.end(); v2++) {
			bool connection = false;
			if (v2 == v) {
				cout << YELLOW << "n/a" << RESET;
				connection = true;
			}
			else {
				for (e = edges.begin(); e != edges.end(); e++) {
					if ((*e) -> getFirst() == *v) {
						if ((*e) -> getSecond() == *v2) {
							cout << CYAN << (*e) -> getWeight() << RESET;
							connection = true;
						}
					}
				}
			}
			if (!connection) 
				cout << RED << "none" << RESET;
			cout << "\t";
		}
		cout << endl;
	}
}
