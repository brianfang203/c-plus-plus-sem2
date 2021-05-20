#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

#include "node.h"

using namespace std;

//trunk struct
struct Trunk {
	Trunk *prev;
	char* str;
	Trunk(Trunk *prev, char* str) {
		this -> prev = prev;
		this -> str = str;
	}
};

void showTrunks(Trunk *p) {
	if (p == NULL){
		return;
	}
	showTrunks(p -> prev);
	cout << p -> str;
}

void parse(char* in, int* modif, int &count);
void insert(Node* &head, Node* &curr, Node* &prev, int val);
void printTree(Node* root, Trunk *prev, bool isLeft);
Node* search(Node* curr, int val);
Node* remove(Node* &head, int val);

//main function
int main() {
	char inp[10];
	char fileName[30];
	char input[10000];
	int count = 0; 
	int modif[100];
	int siz = 0; 
	bool run = true;
	while (run) {
		memset(input, 0, 10000);
		memset(modif, 0, 100);
		siz = 0;
		count = 0;  

    		//getting user input
		cout << endl << "What would you like to do(tree/quit): " << endl;
		cin.get(inp, 10);
		cin.clear();
		cin.ignore(10000, '\n');
		if (strcmp(inp, "tree") == 0) {

      			//console or file input
			cout << "Enter \"type\" for console input or \"file\" for file input: " << endl;
			cin.get(inp, 10);
			cin.clear();
			cin.ignore(10000, '\n');
			bool tr = false;

      			//if file input
			if (strcmp(inp, "file") == 0) {
				tr = true;
				cout << endl << "Enter the name of the file: " << endl << ">> ";
				cin.get(fileName, 30);
				cin.clear();
				cin.ignore(100000, '\n');
				streampos size;
				ifstream file(fileName, ios::in | ios::binary | ios::ate);
				if (file.is_open()) {
					size = file.tellg();
					file.seekg(0, ios::beg);
					file.read(input, size);
					file.close();
					parse(input, modif, count); 
					for (int i = 0; i < 100; i++) {
						if (modif[i] != 0) {
							siz++;
						}
					}
					cout << endl;
				}
			}

      			//if console input
			else if (strcmp(inp, "type") == 0) {
				tr = true;
				cout << "Enter numbers with spaces inbetween: " << endl;
				char in[10000];
				cin.get(in, 10000);
				cin.clear();
				cin.ignore(1000000, '\n');
				parse(in, modif, count);  

        			//find size
				for (int i = 0; i < 100; i++) {
					if (modif[i] != 0) {
						siz++;
					}
				}
				cout << endl;      
			}

      			//invalid input
			else {
				tr = false;
				cout << "Invalid input" << endl;
			}

      			//creating tree
			if (tr) {
				Node* head = NULL;  
				Node* curr = NULL;  
				Node* prev = NULL;  
				for (int i = 0; i < siz; i++) {
					if (modif[i] != 0) {
						curr = head;
						insert(head, curr, prev, modif[i]);
					}
				}

        			//print tree
				printTree(head, NULL, false);
				cout << endl;
				bool r = true;
				char resp[10];

        			//while program is still running
				while (r) {
					cout << endl << "Would you like to search, add, remove, or done: " << endl;
					cin.get(resp, 10);
					cin.clear();
					cin.ignore(10000, '\n');

          				//search in tree
					if (strcmp(resp, "search") == 0) {
						int val;
						cout << "Search value: ";
						cin >> val;
						cin.clear();
						cin.ignore(10000, '\n');
						Node* temp = search(head, val);

            					//in tree
						if (temp != NULL) {
							cout << endl << val << " is part of the tree" << endl;
						} 
            					//not in tree
            					else {
							cout << endl << val << " is not par of the tree" << endl;
						}
					} 

          				//remove from tree
          				else if (strcmp(resp, "remove") == 0) {
						int val;
						cout << "Remove value: ";
						cin >> val;
						cin.clear();
						cin.ignore(10000, '\n');
						head = remove(head, val);
						cout << endl;
						printTree(head, NULL, false);
						cout << endl;
					} 

          				//add to tree
          				else if (strcmp(resp, "add") == 0) {
						int val;
						cout << "Add value: ";
						cin >> val;
						cin.clear();
						cin.ignore(10000, '\n');
						Node* curr = NULL;
						Node* prev = NULL;
						curr = head;
						insert(head, curr, prev, val);
						cout << endl;
						printTree(head, NULL, false);
						cout << endl;
					} 

          				//finish tree
          				else if (strcmp(resp, "done") == 0) {
						r = false;
					} 

          				//invalid input
          				else {
						cout << endl << "Invalid input" << endl;
					}
				}
			}
		}

    		//quitting program
		else if (strcmp(inp, "quit") == 0) {
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

//parse function
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

//insert in tree
void insert(Node* &head, Node* &curr, Node*& prev, int val) {
	if (head == NULL) {
		head = new Node();
		head->setData(val);
		return;
	} 
  	else {
		if (val < curr->getData()) {  
			prev = curr;
			curr = curr->getLeft();
			if (curr == NULL) {  
				curr = new Node();
				curr->setData(val);
				prev->setLeft(curr);
				return;
			} 
      			else {  
				insert(head, curr, prev, val);
			}
		} 
    		else {
			prev = curr;
			curr = curr->getRight();  
			if (curr == NULL) {  
				curr = new Node();
				curr->setData(val);
				prev->setRight(curr);
				return;
			} 
      			else { 
				insert(head, curr, prev, val);
			}
		}
	}
}

//show current tree
void printTree(Node* root, Trunk *prev, bool isLeft) {
	if (root == NULL) {
		return;
	}
	char* prev_str = (char*)("    ");
	Trunk *trunk = new Trunk(prev, prev_str);
	printTree(root->getLeft(), trunk, true);
	if (!prev) {
		trunk -> str = (char*)("   ");
	}
	else if (isLeft) {
		trunk -> str = (char*)("/ ");
		prev_str = (char*)("   |");
	}
	else {
		trunk -> str = (char*)("\\ ");
		prev -> str = prev_str;
	}
	showTrunks(trunk);
	cout << root->getData() << endl;

	if (prev) {
		prev -> str = prev_str;
	}
	trunk -> str = (char*)("   |");
	printTree(root->getRight(), trunk, false);
}

//search in tree
Node* search(Node* curr, int val) {
	if (val == curr->getData()) {
		return curr;
	}
	else if (val < curr->getData()) { 
		if (curr->getLeft() != NULL) {
			search(curr->getLeft(), val); 
		} 
    		else {
			return NULL; 
		}
	} 
  	else {
		if (curr->getRight() != NULL) {
			search(curr->getRight(), val); 
		} 
    		else {
			return NULL;  
		}
	} 
}

//remove from tree
Node* remove(Node* &root, int val) {
	Node* L = root->getLeft();
	Node* R = root->getRight();
	if(root == NULL) return root;
	else if(val < root->getData()) root->setLeft(remove(L, val));
	else if(val > root->getData()) root->setRight(remove(R, val));
	else {  
		if (root->getRight() == NULL && root->getLeft() == NULL) {  
			root->~Node();
			root = NULL;
			return root;
		}
		else if (root->getLeft() == NULL) {  
			Node* temp = root;
			root = root->getRight();
			temp->~Node();
			return root;
		}
		else if (root->getRight() == NULL) {  
			Node* temp = root;
			root = root->getLeft();
			temp->~Node();
			return root;
		}
		else {
			Node* temp = root->getRight();
			while (temp->getLeft() != NULL) temp = temp->getLeft();
			root->setData(temp->getData());
			Node* r = root->getRight();
			root->setRight(remove(r, temp->getData()));
		}
	}
	return root;
}
