#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <cmath>

using namespace std;

void parseIn(int*& parsed, char input[], int &counter);
void heapify(int*& arr, int n, int i);
void buildHeap(int*& arr, int n);
void visualPrint(int* arr, int n);

//main function
int main() {
  int num;
	char fileName[20];
	char input[1000];
	int* parsed;
	int parsedSize;

  	//taking in user input
	cout << endl << "Enter 1 for console input, 2 for file input: " << endl;
	cin >> num;
	cin.clear();
	cin.ignore(1000000, '\n');

  	//console input
	if (num == 1) {
		cout << endl << "Enter numbers with spaces in between:  " << endl;
		cin.get(input, 1000);
		cin.clear();
		cin.ignore(1000000, '\n');
	}

  	//file input
	else if (num == 2) {
		cout << endl << "Enter file name: " << endl;
		cin.get(fileName, 20);
		cin.clear();
		cin.ignore(1000000, '\n');
		streampos size;
		ifstream file(fileName, ios::in | ios::binary | ios::ate);
		if (file.is_open()) {
			size = file.tellg();
			file.seekg(0, ios::beg);
			file.read(input, size);
			file.close();
		}
	}
	else {
		return 0;
	}
	parseIn(parsed, input, parsedSize);
	buildHeap(parsed, parsedSize);
	visualPrint(parsed, parsedSize);
	return 0;
}

void parseIn(int*& parsed, char input[], int &counter) {
	int pointers[2];
	int value;
	int* temp;
	counter = 1;
	pointers[0] = -1;
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == ' ') {
			pointers[1] = i;
			int j = 0;
			char* newArray = new char[pointers[1] - pointers[0]];
			for (int i = pointers[0] + 1; i < pointers[1]; i++) {
				newArray[j] = input[i];
				j = j + 1;
			}
			newArray[j] = '\0';
			temp = parsed;
			parsed = new int[counter];
			if (counter > 1) {
				for (int i = 0; i < counter - 1; i++) {
					parsed[i] = temp[i];
				}
			}
			parsed[counter - 1] = atoi(newArray);
			counter = counter + 1;
			pointers[0] = pointers[1];
		}
	}
	char* newArray = new char[strlen(input) - pointers[0]];
	int j = 0;
	for (int i = pointers[0] + 1; i < strlen(input); i++) {
		newArray[j] = input[i];
		j = j + 1;
	}
	newArray[j] = '\0';
	temp = parsed;
	parsed = new int[counter];
	if (counter > 1) {
		for (int i = 0; i < counter - 1; i++) {
			parsed[i] = temp[i];
		}
	}
	parsed[counter - 1] = atoi(newArray);
}

//sorting numbers into heap
void heapify(int*& arr, int n, int i) {
	int largest = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

  	//left is larger than root
	if (l < n && arr[l] > arr[largest]) {
		largest = l;
	}

  	//right is larger than root
	if (r < n && arr[r] > arr[largest]) {
		largest = r;
	}

  	//largest is not root
	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

//building heap
void buildHeap(int*& arr, int n) {
	int start = (n / 2) - 1;
	for (int i = start; i >= 0; i--)
	{
		heapify(arr, n, i);
	}
}

//printing out heap
void visualPrint(int* parsed, int n) {
	int* temp = parsed;
	parsed = new int[n + 1];
	for (int i = 0; i < n; i++) {
		parsed[i + 1] = temp[i];
	}
	int levels = ceil(log2(n)); 
	int index = 1;

  	//printing out each number
	for (int i = 0; i < levels; i++) {
		int num = index;
		for (int j = 0; j < num; j++) {
			if (index <= n) {
				cout << parsed[index] << " ";
				index = index + 1;
			}
		}
		cout << endl;
    
    		//adding lines between parent and child
		if (i < levels - 1) {
			for (int k = 0; k < pow(2, i); k++) {
				cout << "/\\";
			}
			cout << endl;
		}
	}
	cout << endl;
}
