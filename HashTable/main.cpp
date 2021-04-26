#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

//student struct
struct student {
	char Fname[81];
	char Lname[81];
	int id;
	float gpa;
	student* next;
	student* prev;
};

void ADD(student** list, student* newStudent, int size);
void PRINT(student** list, int size);
void DELETE(student** list, int id, int size);
bool COLL(student** list, int size);

//main function
int main() {
	bool run = true;
	char input[10];
	int randid = 123; 
	student** list = new student*[100];
	int size = 100;

  	//while keep running
	while (run) {

    		//asking for user input
		cout << endl << "Would you like to ADD, ADDRAND, DELETE, PRINT, or QUIT: " << endl;
		cin.get(input, 10);
		cin.clear();
		cin.ignore(10000, '\n');

    		//adding student
		if (strcmp(input, "ADD") == 0) {  
			student* newStudent = new student();
			newStudent->next = NULL;
			newStudent->prev = NULL;
			cout << "Enter first name: " << endl;
			cin >> newStudent->Fname;
			cin.clear();
			cin.ignore(81,'\n');
			cout << "Enter last name: " << endl;
			cin >> newStudent->Lname;
			cin.clear();
			cin.ignore(81,'\n');
			cout << "Enter ID: " << endl;
			cin >> newStudent->id;
			cin.clear();
			cin.ignore(81,'\n');
			cout << "Enter GPA: " << endl;
			cin >> newStudent->gpa;
			cin.clear();
			cin.ignore(81, '\n');
			ADD(list, newStudent, size);
			cout << endl << "New student added to hash table" << endl;
			if (COLL(list, size)) {
				student** temp = new student*[size];  
				for (int m = 0; m < size; m++) {
					temp[m] = list[m];
				}
				int newsize = 2*size;
				list = new student*[newsize];
				for (int c = 0; c < newsize; c++) {
					list[c] = NULL;
				}
				for (int a = 0; a < size; a++) {
					if (temp[a] != NULL) {
						student* move = temp[a];
						if (move->next != NULL) {
							student* nxt = move->next;
							move->next = NULL;
							nxt->prev = NULL;
							ADD(list, nxt, newsize);
							if (nxt->next != NULL) {
								student* dnxt = nxt->next;
								nxt->next = NULL;
								dnxt->prev = NULL;
								ADD(list, dnxt, newsize);
							}
						}
						ADD(list, move, newsize);
					}
				}
				delete[] temp;
				size = newsize; 
			}
		}

    		//deleting student
		else if (strcmp(input, "DELETE") == 0) { 
			cout << "Enter the ID of the student to delete: ";
			int in;
			cin >> in;
			cin.clear();
			cin.ignore(10000, '\n');
			DELETE(list, in, size);
		}

    		//printing students
		else if (strcmp(input, "PRINT") == 0) {  
			PRINT(list, size);
		}

    		//adding random students
		else if (strcmp(input, "ADDRAND") == 0) {  
			int num;
			char** namef = new char*[20];
			char** namel = new char*[20];
			for (int i = 0; i < 20; i++) {
				namef[i] = new char[81];
				namel[i] = new char[81];
			}
			cout << endl << "Enter the number of random students to be added: ";
			cin >> num;
			cin.clear();
			cin.ignore(10000, '\n');
			ifstream myfile("fnames.txt");
			int linenr = 0;
			char first[81];
			while (linenr < 20) {
				myfile.getline(first, 81);
				strcpy(namef[linenr], first);
				linenr++;
			}
			ifstream myfile1("lnames.txt");
			char last[81];
			linenr = 0; 
			while (linenr < 20) {
				myfile1.getline(last, 81);
				strcpy(namel[linenr], last);
				linenr++;
			}
			while (num > 0) {
				student* newStudent = new student();
				int randomf = rand() % 19;
				int randoml = rand() % 19;
				strcpy(newStudent->Fname, namef[randomf]);
				strcpy(newStudent->Lname, namel[randoml]);
				newStudent->id = randid;
				newStudent->gpa = (float)rand()/(RAND_MAX)*5;
				randid = randid + 100;
				ADD(list, newStudent, size);
				if (COLL(list, size)) {
					student** temp = new student*[size];  
					for (int m = 0; m < size; m++) {
						temp[m] = list[m];
					}
					int newsize = 2*size;
					list = new student*[newsize]; 
					for (int c = 0; c < newsize; c++) {
						list[c] = NULL;
					}
					for (int a = 0; a < size; a++) {
						if (temp[a] != NULL) {
							student* move = temp[a];
							if (move->next != NULL) {
								student* nxt = move->next;
								move->next = NULL;
								nxt->prev = NULL;
								ADD(list, nxt, newsize);
								if (nxt->next != NULL) {
									student* dnxt = nxt->next;
									nxt->next = NULL;
									dnxt->prev = NULL;
									ADD(list, dnxt, newsize);
								}
							}
							ADD(list, move, newsize);
						}
					}
					delete[] temp;
					size = newsize; 
				}
				num--;
			}
		}

    		//quitting program
		else if (strcmp(input, "QUIT") == 0) {
			cout << endl << "Quitting" << endl;
			run = false;
		} 

    //invalid input
    else {
			cout << endl << "Invalid input" << endl;
		}
	}
	return 0;
}

//adding student
void ADD(student** list, student* newStudent, int size) {
	int index = (newStudent->id) % size;
	if (list[index] == NULL) {
		list[index] = newStudent;
	} 
  	else {
		if ((list[index])->next == NULL) {
			(list[index])->next = newStudent;
			(list[index]->next)->prev = (list[index])->next;
		} 
    		else {
			((list[index])->next)->next = newStudent;
			(((list[index])->next)->next)->prev = ((list[index])->next)->next;
		}
	}
}

//collision
bool COLL(student** list, int size) {
	bool newlist = false;  
	int ctr = 0;
	while (newlist == false && ctr < size) {
		if (list[ctr] != NULL) {
			if ((list[ctr])->next != NULL) {
				if (((list[ctr])->next)->next != NULL) {
					newlist = true;
				}
			}
		}
		ctr++;
	}
	return newlist;
}

//printing students
void PRINT(student** list, int size) {
	for (int i = 0; i < size; i++) {
		student* curr = list[i];
		if (curr != NULL) {
			cout << curr->Fname << " ";
			cout << curr->Lname;
			cout << " #" << curr->id << " GPA: ";
			cout << fixed << setprecision(2) << curr->gpa;
			student* nxt = curr->next;
			if (nxt != NULL) {
				cout << '\t' << nxt->Fname << " ";
				cout << nxt->Lname;
				cout << "#" << nxt->id << " GPA: ";
				cout << fixed << setprecision(2) << nxt->gpa;
			}
			cout << endl;
		} 
	}
}

//removing student
void DELETE(student** list, int id, int size) {
	int i = id % size;
	if (list[i] == NULL) {
		cout << endl << "Does not exist" << endl;
	} 
  	else {
		if (list[i]->id == id) {
			if (list[i]->next == NULL) {
				list[i] = NULL; 
			} 
      			else {
				student* newcurr = list[i]->next;
				newcurr->prev = NULL;
				list[i] = newcurr;
			}
		} 
    		else {
			if (list[i]->next == NULL) {
				cout << endl << "Does not exist" << endl;
			} 
      			else {
				if (list[i]->next->id == id) {
					list[i]->next = NULL;
				} 
        			else {
					cout << "Does not exist" << endl;
				}
			}
		}
	}
}
