//NAME: Shihui Li 
//STUDENT NUMBER:190206187
//EMAIL:b9020618@newcastle.ac.uk
//ctpl being used here is from https://github.com/vit-vit/CTPL

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "sorting.h"
#include "fileopen.h"

using namespace std;



int main() {
	srand(time(NULL));
	vector<int>test_vec;
	fileopen testfile;
	puzzleInput testsort;
	int m;
	int ifContinue=1;
	cout << "Now you are dealing with " << N << "x" << N << " puzzle"<<endl;
	cout << "please input the partial :" << endl;
	cin >> m;

	while (ifContinue!=0) {
		testfile.openthefile(test_vec);
		testsort.read_file(N, m);
		cout << "\n" <<"Go on?" << endl;
		cout << "(1 for continue" << "\t" << "0 for exit)" << endl;
		cin >> ifContinue;
	}

}

