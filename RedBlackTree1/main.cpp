/*
Sources:

https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/

https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

https://www.programiz.com/dsa/red-black-tree

Used green instead of black
*/

#include <iostream>
#include <cstring>
#include <fstream>

#include "node.h"

#define RESET   "\033[0m"
#define RED     "\033[91m"
#define GREEN   "\033[32m"

using namespace std;

//trunk struct
struct Trunk {
	Trunk *prev;
	char* str;
	Trunk(Trunk *prev, char* str) {
		this->prev = prev;
		this->str = str;
	}
};

void showTrunks(Trunk *p) {
	if (p == NULL){
		return;
	}
	showTrunks(p -> prev);
	cout << p -> str;
}

void ADD(Node* &head, Node* &curr, Node*& prev, int val);
void READ(Node* &head);
void PRINT(Node* root, Trunk *prev, bool isLeft);
void parse(char* in, int* modif, int &count);
void balance(Node* &head, Node* &curr);
void rotateLeft(Node* &head, Node* &curr);
void rotateRight(Node* &head, Node* &curr);

//main function
int main(){
	char input[10]; 
	char read[10000];  
	int modif[100]; 
	Node* head = NULL;
	bool run = true;
	while (run) {
		cout << endl << "Would you like to add, read, print, or quit: " << endl;
		cin.get(input, 10);
		cin.clear();
		cin.ignore(10000, '\n');

		//add to tree
		if (strcmp(input, "add") == 0) {
			int val;
			cout << "Add value: ";
			cin >> val;
			cin.clear();
			cin.ignore(10000, '\n');
			Node* curr = head;
			Node* prev = NULL;
			ADD(head, curr, prev, val);
			if(curr != head) balance(head, curr);
			cout << endl << val << " has been added:" << endl;
		}

		//read in file input
		else if (strcmp(input, "read") == 0) {
			READ(head);
		}

		//print tree
		else if (strcmp(input, "print") == 0) {
			PRINT(head, NULL, false);
		}

		//quit program
		else if (strcmp(input, "quit") == 0) {
			cout << endl << "Quitting program" << endl;
			run = false;
		}

		//invalid input
		else {
			cout << endl << "Invalid input" << endl;
		}
	}
	return 0;
}

//balance function
void balance(Node* &head, Node* &curr) {
	Node* parent = NULL;
	Node* grandparent = NULL;
	while ((curr != head) && (curr->getColor() != 0) && ((curr->getParent())->getColor() == 1)) {
		parent = curr->getParent();
		grandparent = parent->getParent();

		//parent = left child of grandparent
		if (parent == grandparent->getLeft()) {
			Node* uncle = grandparent->getRight();

			//uncle = red, only recolor
			if (uncle != NULL && uncle->getColor() != 0) {
				grandparent->setColor(1);
				parent->setColor(0);
				uncle->setColor(0);
				curr = grandparent;
			}
			else {

				//curr = right child of parent, rotate left
				if (curr == parent->getRight()) {
					rotateLeft(head, parent);
					curr = parent;
					parent =  curr->getParent();
				}

				//curr = left child of parent, rotate right
				rotateRight(head, grandparent);

				//swap colors of parent and grandparent
				int tempC = parent->getColor();
				parent->setColor(grandparent->getColor());
				grandparent->setColor(tempC);
				curr = parent;
			}
		}

		//parent = right child of grandparent
		else {
			Node* uncle = grandparent->getLeft();

			//uncle = red, only recolor
			if (uncle != NULL && uncle->getColor() != 0) {
				grandparent->setColor(1);
				parent->setColor(0);
				uncle->setColor(0);
				curr = grandparent;
			}
			else {

				//curr = left child of parent, rotate right
				if (curr == parent->getLeft()) {
					rotateRight(head, parent);
					curr = parent;
					parent = curr->getParent();
				}

				//curr = right child of parent, rotate left
				rotateLeft(head, grandparent);

				//swap color of parent and grandparent
				int tempC = parent->getColor();
				parent->setColor(grandparent->getColor());
				grandparent->setColor(tempC);
				curr = parent;
			}
		}
	}
	head->setColor(0);
}

//rotate tree to the left
void rotateLeft(Node* &head, Node* &curr) {
	Node* rightPtr = curr->getRight(); 
	curr->setRight(rightPtr->getLeft()); 
	if (curr->getRight() != NULL) {
		(curr->getRight())->setParent(curr); 
	}
	rightPtr->setParent(curr->getParent());
	if (curr->getParent() == NULL) {
		head = rightPtr; 
	} 
	else if (curr == (curr->getParent())->getLeft()) {
		(curr->getParent())->setLeft(rightPtr); 
	} 
	else{
		(curr->getParent())->setRight(rightPtr); 
	}  
	rightPtr->setLeft(curr); 
	curr->setParent(rightPtr);
}

//rotate tree to the right
void rotateRight(Node* &head, Node* &curr) {
	Node *leftPtr = curr->getLeft(); 
	curr->setLeft(leftPtr->getRight()); 
	if (curr->getLeft() != NULL) {
		(curr->getLeft())->setParent(curr); 
	}  
	leftPtr->setParent(curr->getParent());
	if (curr->getParent() == NULL) {
		head = leftPtr; 
	}
	else if (curr == (curr->getParent())->getLeft()) {
		(curr->getParent())->setLeft(leftPtr); 
	} 
	else {
		(curr->getParent())->setRight(leftPtr);
	}
	leftPtr->setRight(curr); 
	curr->setParent(leftPtr);
}

//add function
void ADD(Node* &head, Node* &curr, Node* &prev, int val) {
	if (head == NULL) {
		head = new Node();
		curr = head;
		head->setData(val);
		head->setColor(0);  
		return;
	} 
	else {
		if (val < curr->getData()) {  
			prev = curr;
			curr = curr->getLeft();

			//if empty
			if (curr == NULL) {  
				curr = new Node();
				curr->setData(val);
				prev->setLeft(curr);
				curr->setParent(prev);
				balance(head, curr); 
				return;
			} 

			//if not empty, keep going
			else {  
				ADD(head, curr, prev, val);
			}
		}
		else {
			prev = curr;
			curr = curr->getRight();

			//if empty
			if (curr == NULL) {
				curr = new Node();
				curr->setData(val);
				prev->setRight(curr);
				curr->setParent(prev);
				balance(head, curr); 
				return;
			} 

			//if not empty, keep going
			else {  
				ADD(head, curr, prev, val);
			}
		}
	}
}

//read from file
void READ(Node* &head) {
	char in[10000];
	char fileName[100];
	int modif[100];
	int siz = 0;
	int count = 0;
	memset(in, 0, 10000);
	memset(fileName, 0, 100);
	memset(modif, 0, 100);
	cout << endl << "What is the name of the file?" << endl;
	cin.get(fileName, 30);
	cin.clear();
	cin.ignore(100000, '\n');
	streampos size;
	ifstream file(fileName, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		size = file.tellg();
		file.seekg(0, ios::beg);
		file.read(in, size);
		file.close();
		parse(in, modif, count); 
		cout << "Input: ";
		for (int i = 0; i < 100; i++) {
			if (modif[i] != 0) {
				cout << modif[i] << " ";
				siz++;
			}
		}
		cout << endl << "Size: " << siz << endl;;
		Node* curr = NULL;
		Node* prev = NULL;
		for (int i = 0; i < siz; i++) {
			if(modif[i] == 0){
				break;
			} 
			curr = head;
			ADD(head, curr, prev, modif[i]);
		}
	} 
}

//print tree
void PRINT(Node* root, Trunk *prev, bool isLeft) {
	if (root == NULL) {
		return;
	}
	char* prev_str = (char*)("    ");
	Trunk *trunk = new Trunk(prev, prev_str);
	PRINT(root->getLeft(), trunk, true);
	if (!prev) {
		trunk -> str = (char*)("   ");
	}
	else if (isLeft){
		trunk -> str = (char*)("/ ");
		prev_str = (char*)("   |");
	}
	else {
		trunk -> str = (char*)("\\ ");
		prev -> str = prev_str;
	}
	showTrunks(trunk);
	if (root->getColor() == 0){  
		cout << GREEN << root->getData() << RESET << endl;
	} 
	else {  
		cout << RED << root->getData() << RESET << endl;
	}
	if (prev) {
		prev -> str = prev_str;
	}
	trunk -> str = (char*)("   |");
	PRINT(root->getRight(), trunk, false);
}

//parsing
void parse(char* in, int* modif, int &count) {
	int l = 0;  
	for (int i = 0; i < strlen(in); i++) {
		if (in[i] == ' ') {
			if (l == 1) {
				int temp = 0;
				temp = in[i-1] - '0';
				modif[count] = temp;
				count++;
				l = 0;
			} 
			else {
				int temp = 0;
				for (int a = 0; a < l; a++) {
					temp = 10 * temp + (in[i-l+a] - '0');
				}
				modif[count] = temp;
				count++;
				l = 0;
			}
		} 
		else {
			int temp = 0;
			l++;
			if (i == strlen(in) - 1) {  
				for (int a = 0; a < l; a++) {
					temp = 10 * temp + (in[i+a+1-l] - '0');
				}
				modif[count] = temp;
				count++;
			}
		}
	} 
}
