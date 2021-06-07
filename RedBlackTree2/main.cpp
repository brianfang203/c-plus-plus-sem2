/*
Sources:

https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/

https://www.programiz.com/dsa/deletion-from-a-red-black-tree

Used green instead of black
*/

#include <iostream>
#include <cstring>
#include <fstream>

#include "node.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
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
	if (p == NULL) {
		return;
	}
	showTrunks(p -> prev);
	cout << p -> str;
}

//prototypes
void ADD(Node* &head, Node* &curr, Node*& prev, int val);
void READ(Node* &head);
void PRINT(Node* root, Trunk *prev, bool isLeft);
void parse(char* in, int* modif, int &count);
bool SEARCH(Node* curr, int val);
void balance(Node* &head, Node* &curr);
void rotateLeft(Node* &head, Node* &curr);
void rotateRight(Node* &head, Node* &curr);
void DELETE(Node* &head, Node* &v);
Node* getSibling(Node* &x);
Node* successor(Node* &x);
Node* replaceNode(Node* &x);
void fixDoubleBlack(Node* &head, Node* &x);
bool hasRedChild(Node* &x);
void swapNodeValues(Node* &u, Node* &v);

//main function
int main() {
	char input[10]; 
	char read[10000];  
	int modif[100];
	Node* head = NULL;
	bool run = true;
	while (run) {
		cout << endl << "Would you like to add, delete, read, print, search, or quit: " << endl;
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
			cout << endl << val << " has been added" << endl;
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

		//search tree
		else if (strcmp(input, "search") == 0) {
			int val;
			cout << "Enter value to search for: ";
			cin >> val;
			cin.clear();
			cin.ignore(10000, '\n');
			bool s = SEARCH(head, val);
			if (s == true) {
				cout << val << " is in the tree" << endl;
			} 
			else {
				cout << val << " is not in the tree" << endl;
			}
		}

		//delete from tree
		else if (strcmp(input, "delete") == 0) {
			while (true) {
				int val = 0;
				cout << "Enter value to delete: ";
				cin >> val;
				cin.clear();
				cin.ignore(10000, '\n');
				bool d = SEARCH(head, val);
				if (d == false) {
					cout << endl << "Value not found" << endl;
				} 
				else {
					Node* v = head;
					while (v->getData() != val) {
						if (val < v->getData()) {
							v = v->getLeft();
						} 
						else if (val > v->getData()) {
							v = v->getRight();
						}
					}
					DELETE(head, v);
					break;
				}
			}
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

			//uncle = red, then only recolor
			if (uncle != NULL && uncle->getColor() != 0) {
				grandparent->setColor(1);
				parent->setColor(0);
				uncle->setColor(0);
				curr = grandparent;
			}
			else {

				//curr = right child of parent, then rotate left
				if (curr == parent->getRight()) {
					rotateLeft(head, parent);
					curr = parent;
					parent =  curr->getParent();
				}

				//curr = left child of parent, then rotate right
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

			//uncle = red, then only recolor
			if (uncle != NULL && uncle->getColor() != 0) {
				grandparent->setColor(1);
				parent->setColor(0);
				uncle->setColor(0);
				curr = grandparent;
			}
			else {

				//curr = left child of parent, then rotate right
				if (curr == parent->getLeft()) {
					rotateRight(head, parent);
					curr = parent;
					parent = curr->getParent();
				}

				//curr = right child of parent, then rotate left
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

//search in tree
bool SEARCH(Node* curr, int val) {
	if (val == curr->getData()) {
		return true;
	}
	else if (val < curr->getData()) {  
		if (curr->getLeft() != NULL) {
			SEARCH(curr->getLeft(), val);  
		} 
		else {
			return false;
		}
	}
	else {  
		if (curr->getRight() != NULL) {
			SEARCH(curr->getRight(), val);  
		} 
		else {
			return false;
		}
	}
}

//swap between 2 nodes
void swapValues(Node* &u, Node* &v) { 
	int temp; 
	temp = u->getData(); 
	u->setData(v->getData()); 
	v->setData(temp); 
}

//get sibling
Node* getSibling(Node* &v) {
	if (v->getParent() == NULL) {
		return NULL;
	}
	if (v == v->getParent()->getLeft()) {
		return v->getParent()->getRight();
	} 
	else {
		return v->getParent()->getLeft();
	}
}

//replace node
Node* replaceNode(Node* &x) {
	if (x->getLeft() != NULL && x->getRight() != NULL) {
		Node* r = x->getRight();
		return successor(r); 
	}
	else if (x->getLeft() == NULL && x->getRight() == NULL) {
		return NULL;
	}
	else {
		if (x->getLeft() != NULL) { 
			return x->getLeft();
		} 
		else {
			return x->getRight();
		}
	}
}

//successor node
Node* successor(Node* &x) {
	Node* a = x;
	while (a->getLeft() != NULL) {
		a = a->getLeft();
	}
	return a;
}

//delete function
void DELETE(Node* &head, Node* &v) {
	Node* u = replaceNode(v);
	Node* parent = v->getParent();
	bool bothBlack = ((u==NULL || u->getColor()==0) && (v==NULL || v->getColor()==0));
	if (u == NULL) {
		if (v == head) {
			head = NULL;
		} 
		else {
			if (bothBlack) {
				fixDoubleBlack(head, v);
			} 
			else {
				if (getSibling(v) != NULL)
					getSibling(v)->setColor(1);
			}
			if (v == parent->getLeft()) {
				parent->setLeft(NULL);
			} 
			else {
				parent->setRight(NULL);
			}
		}
		v->~Node();
		return;
	}

	if (v->getRight() == NULL || v->getLeft() == NULL) {
		if (v == head) {
			v->setData(u->getData());
			v->setLeft(NULL);
			v->setRight(NULL);
			u->~Node();
		} 
		else {
			if (v == parent->getLeft()) {
				parent->setLeft(u);
			} 
			else {
				parent->setRight(u);
			}
			v->~Node();
			u->setParent(parent);
			if(bothBlack) {
				fixDoubleBlack(head, u);
			} 
			else {
				u->setColor(0);
			}
		}
		return;
	}
	swapValues(u, v);
	DELETE(head, u);
}

//insert double black
void fixDoubleBlack(Node* &head, Node* &x) {
	if (x == head)
		return;
	Node* sibling = getSibling(x);
	Node* parent = x->getParent();
	if (sibling == NULL) {
		fixDoubleBlack(head, parent);
	} 
	else {
		if (sibling->getColor() == 1) {
			parent->setColor(1); 
			sibling->setColor(0); 
			if (sibling == parent->getLeft()) {
				rotateRight(head, parent);
			} 
			else {
				rotateLeft(head, parent);
			}
			fixDoubleBlack(head, x);
		}  
		else {
			if (hasRedChild(sibling)) {
				if (sibling->getLeft() != NULL && sibling->getLeft()->getColor() == 1) {
					if (sibling == parent->getLeft()) {
						sibling->getLeft()->setColor(sibling->getColor());
						sibling->setColor(parent->getColor());
						rotateRight(head, parent);
					} 
					else {
						sibling->getLeft()->setColor(parent->getColor());
						rotateRight(head, sibling);
						rotateLeft(head, parent);
					}
				} 
				else {
					if (sibling == parent->getLeft()) {
						sibling->getRight()->setColor(parent->getColor());
						rotateLeft(head, sibling);
						rotateRight(head, parent);
					} 
					else {
						sibling->getRight()->setColor(sibling->getColor());
						sibling->setColor(parent->getColor());
						rotateLeft(head, parent);
					}
				}
				parent->setColor(0); 
			} 
			else {
				sibling->setColor(1); 
				if (parent->getColor() == 0) {
					fixDoubleBlack(head, parent); 
				} 
				else {
					parent->setColor(0); 
				}
			}
		}
	}
}

//has red child
bool hasRedChild(Node* &x) { 
	if (x->getLeft() != NULL && x->getLeft()->getColor() == 1) {
		return true;
	}
	else if (x->getRight() != NULL && x->getRight()->getColor() == 1) {
		return true;
	} 
	else {
		return false;
	}
}
