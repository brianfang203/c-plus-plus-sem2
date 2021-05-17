#include <iostream>
#include <cstring>
#include <iomanip>
#include <stack>
#include "Node.h"

using namespace std;

//prototypes
void doPrefix(Node* t);
void doPostfix(Node* t);
void doInfix(Node* t);
int precedence(char* op);
void pushT(Node* &tree, Node* &add);
void popT(Node* &tree);
void enqueue(Node* &front, Node* &rear, char* val);
void dequeue(Node* &front, Node* &rear);
bool isEmpty(Node* front, Node* rear);
void showFront(Node* front, Node* rear);
void displayQueue(Node* front, Node* rear);
void push(Node* &top, char* val);
void pop(Node* &top);
Node* peek(Node* top);
bool isempty(Node* top);

//main function
int main() {
	int countSigns = 0;
	int countNum = 0;
	Node* top = NULL;
	Node* front = NULL;  
	Node* rear = NULL;
	bool run = true;
	char input[100];
	char in[10];

	//while program running
	while(run) {

		//getting user input
		cout << endl << "What would you like to do(calc/quit): " << endl;
		cin.get(in, 10);
		cin.clear();
		cin.ignore(10000, '\n');

		//if input is calc
		if (strcmp(in, "calc") == 0) {
			cout << "Enter equation in infix notation: " << endl;
			cin.get(input, 100);
			cin.clear();
			cin.ignore(10000, '\n');
			char** modif = new char*[100];  
			top = front = rear = NULL;  
			int l = 0;  
			int count = 0; 
			for (int i = 0; i < strlen(input); i++) {
				if (input[i] == ' ') {
					if (l == 1) {
						char *temp = new char[10];
						for (int z = 0; z < sizeof(temp); z++) {  
							temp[z] = 0;
						}
						temp[0] = input[i-1];
						modif[count] = temp;
						count++;
						l = 0;
					}
					else {
						char *temp = new char[10];
						for (int z = 0; z < sizeof(temp); z++) {
							temp[z] = 0;
						}
						for (int a = 0; a < l; a++) {
							temp[a] = input[i-l+a]; 
						}
						modif[count] = temp;
						count++;
						l = 0;
					}
				}
				else {
					char *temp = new char[10];
					for (int z = 0; z < sizeof(temp); z++) {  
						temp[z] = 0;
					}
					l++;
					if (i == strlen(input) - 1) {  
						for (int a = 0; a < l; a++) {
							temp[a] = input[i+a+1-l];
						}
						modif[count] = temp;
						count++;
					}
				}
			}
			int c = 0;

			while (c < count) {
				//if number
				if (precedence(modif[c]) == 0) {  
					enqueue(front, rear, modif[c]);
				}
				//if operator
				if (precedence(modif[c]) == 1 || precedence(modif[c]) == 2) {
					if (top != NULL) {
						while (precedence(top->getData()) >= precedence(modif[c]) &&
								*top->getData() != '(') {
							enqueue(front, rear, top->getData());
							pop(top);
							if (top == NULL){
								break;
							} 
						}
					}
					push(top, modif[c]);
				}

        //if exponent
        if (*modif[c] == '^') { 
					push(top, modif[c]);
				}

				//if left parenthesis
				if (*modif[c] == '(') { 
					push(top, modif[c]);
				}

				//if right parenthesis
				if (*modif[c] == ')') {  
					while (*top->getData() != '(') { 
						enqueue(front, rear, top->getData());
						pop(top);
					}
					if (*top->getData() == '(') {
						pop(top);
					}
				}
				c++; 
			}

			//no tokens left
			if (c == count) {
				while(top != NULL) {  
					enqueue(front, rear, top->getData());
					pop(top);
				}
			}
			Node* tree = NULL;  
			while (front != rear) {
				Node* n = new Node();
				n->setData(front->getData());
				pushT(tree, n);
				front = front->getNext();
			}
			Node* n = new Node();
			n->setData(rear->getData());
			pushT(tree, n);

			//user input for printing notation
			cout << "What notation do you want to print(pre/post/in): " << endl;
			char in[5];
			cin.get(in, 5);
			cin.clear();
			cin.ignore(10000,'\n');

			//if prefix
			if (strcmp(in, "pre") == 0) {
				doPrefix(tree);  
			} 

			//if postfix
			else if (strcmp(in, "post") == 0) {
				doPostfix(tree);  
			} 

			//if infix
			else if (strcmp(in, "in") == 0) {
				doInfix(tree); 
			} 

			//invalid input
			else {
				cout << "Invalid input" << endl;
			}
			cout << endl;
		}

		//quitting program
		else if (strcmp(in, "quit") == 0) {
			cout << endl << "Quitting" << endl;
			run = false;
		}

		//unknown command
		else {
			cout << endl << "Unknown command" << endl;
		}
	}
}

//check precedence
int precedence(char* op) {

	//order of precedence
	if (*op == '(' || *op == ')') {
		return 4; 
	}
	else if (*op == '^') {
		return 3;  
	} 
	else if (*op == '*' || *op == '/') {
		return 2; 
	} 
	else if (*op == '+' || *op == '-') {
		return 1; 
	} 
	else {
		return 0; 
	}
}

//check stack
bool isempty(Node* top) {
	if (top == NULL) {
		return true;
	} 
  	else {
		return false;
	}
}

//push function
void push (Node* &top, char* val) {
	Node* ptr = new Node();
	ptr->setData(val);
	ptr->setNext(top);
	top = ptr;
}

//pop function
void pop(Node* &top) {
	if (isempty(top)) {
		cout << "Empty" << endl;
	} 
  	else {
		Node* ptr = top;
		top = top->getNext();
		ptr->setNext(NULL);
	}
}

//check stack
Node* peek(Node* &top) {
	if (isempty(top)) {
		cout << "Empty" << endl;
		Node* no = new Node();
		return no;
	} 
	else {
		return top;
	}
}

//add node to queue
void enqueue(Node* &front, Node* &rear, char* val) {
	Node* ptr = new Node();
	ptr->setData(val);
	ptr->setNext(NULL);
	if (front == NULL) { 
		front = ptr;
		rear = ptr;
	} 
	else {  
		rear->setNext(ptr);
		rear = ptr;
	}
}

//check queue
bool isEmpty (Node* front, Node* rear) {
	if (front == NULL && rear == NULL) {
		return true;
	} 
	else {
		return false;
	}
}

//push function
void pushT(Node* &tree, Node* &add) {
	if (tree == NULL) {  
		add->setNext(tree);
		tree = add;
	} 
	else {

		//if number
		if (precedence(add->getData()) == 0) { 
			add->setNext(tree);
			tree = add;
		} 

		//if operator
		else {  
			Node* l = tree;
			popT(tree);
			l->setNext(NULL);
			Node* r = tree;
			popT(tree);
			r->setNext(NULL);
			add->setNext(tree);
			tree = add;
			tree->setLeft(r);
			tree->setRight(l);
		}
	}
}

//pop function
void popT(Node* &tree) {
	if (tree == NULL) {
		cout << "Empty" << endl;
	} 
	else {
		Node* ptr = tree;
		tree = tree->getNext();
		ptr->setNext(NULL);
	}
}

//prefix notation
void doPrefix(Node* t) {
	if (t != NULL) {
		cout << t->getData() << " ";
		doPrefix(t->getLeft());
		doPrefix(t->getRight());
	}
}

//postfix notation
void doPostfix(Node* t) {
	if(t != NULL) {
		doPostfix(t->getLeft());
		doPostfix(t->getRight());
		cout << t->getData() << " ";
	}
}

//infix notation
void doInfix(Node* t) {
	if (t != NULL) {
		if (precedence(t->getData()) != 0) {
			cout << "( ";
		}
		doInfix(t->getLeft());
		cout << t->getData() << " ";
		doInfix(t->getRight());
		if (precedence(t->getData()) != 0) {
			cout << ") ";
		}
	}
}
