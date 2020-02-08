#pragma once
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <ctime>



using namespace std;
const int N = 3;

class sorting
{public:
	
	//Cause the vector should be printed as a two-dimentional matrix, so it needs to caculate the position of elements in the vector
	virtual int indexOf(int x, int y)
	{
		return x + y * N;
	}

	//Counting the number of inversion in the puzzle, in order to judge whether the puzzle can be replaced to the original one, that is 1,2,3,...,n
	//if t isn't an even number, the puzzle can't be replaced. It is mathmatically proved.
	//This is the abstraction of the puzzle. Because whatever numbers the user input, their numerical order are always the same.
	//So what is operated in this function is the numerical order of the puzzle(1,2,3,...,n), same as the permuSort function.
	bool t_counting(vector <int>arr) {

		//counting the number of t  of each line and add them up. 
		int inv_count = 0;
		for (int i = 0; i < N * N - 1; i++)
			for (int j = i + 1; j < N * N; j++)

				if (arr[j] && arr[i] && arr[i] > arr[j])
					inv_count++;


		if (inv_count % 2 != 0)
			return false;
		else
			return true;
	}

	//judge whether a puzzle will has continuous line or not. 
	//If the number of elements in the longest continuous line is less than m, obviously it is impossible to find a continuous line  of m-partial in the puzzle.
	bool judge_continuous_line(vector<int>dp, int m) {
		int maxCount = 0;
		int recordCount = 1;

		for (int i = 0; i < dp.size() - 1; i++) {
			
			if (dp[i] == dp[i + 1] - 1)
				recordCount++;
			else {
                recordCount = 1;
				continue;
			}
			if (recordCount > maxCount)
				maxCount = recordCount;
		}

		if (maxCount < m)
			return false;
		else
			return true;
	}

	//judge if this line is continuous, and add to the total.
	//m is the number of partial,it can be 2,3,...,n 
	int continuous_row(int arr[N], int m) {
		for (int i = 0; i < m - 1; i++) {
			if (arr[i] != arr[i + 1] - 1)
				return 0;
		}
		return 1;
	}

	//using full permutation to generate diffirent configurations, and cut off those that can't be reached using t_counting function.
	//just like the t_counting function, what is operated here is the numerical order of each element that user inputed
	//which means that I concentrated on the BROAD itself, regardless which number on it.
	//it is the puzzle but not their numerical order that be output to the file.
	void permuSort(vector<int> dp,int x) {
		int count = 1;
		int row = 1;
		int row_container[N];//contain one line of the puzzle
		vector<int> temp;
        vector<int>dp_container;//contain the numerical order

		for (int i = 0; i < N * N; i++)
			temp.push_back(dp[i]);

		sort(temp.begin(),temp.end());//sort the puzzle that user input to judge that if it is possible to generate cpmtinuous line
		if (!judge_continuous_line(temp, x)||dp[N*N-1]!=0) {//the program requires the user to put a 0 at the end of their puzzle. Else, it breaks.
			cout << "invalied enter" << endl;
			return;
		}

		
		ofstream outfile;
		outfile.open("data_container.txt");

		for (int i = 0; i < N * N; i++) {
			dp_container.push_back(i + 1);
		}


			while (next_permutation(dp_container.begin(), dp_container.end())) {
				if (t_counting(dp_container) && dp[dp_container[N * N - 1] - 1] == 0) {

					count++;


					for (int m = 0; m < N; m++) {
						for (int n = 0; n < N; n++) {
							
							row_container[n] = dp[dp_container[indexOf(n, m)] - 1];
							outfile << dp[dp_container[indexOf(n, m)] - 1] << " ";
						}
						
						outfile << endl;
						row += continuous_row(row_container, x);
					}
					
					outfile << endl;
				}

			}
			cout << "counting:" << count << endl;
			cout << "number of continuous rows:" << row << endl;
			cout << "number of reverse continuous rows:" << row << endl;
			cout << "number of continuous columns:" << row << endl;
			cout << "number of reverse continuous columns:" << row << endl;
			return;
			outfile.close();
		
	}
	

};

class puzzleInput:public sorting
{
public:
	//this function is used to read the puzzles that are stored in the txt file
	void read_file(int N,int x) {
		ifstream infile;
		infile.open("data.txt", ios::in);

		int puzzle_num;
		infile >> puzzle_num;

		int block_num;

		vector <int> s;

		for (int k = 0; k < puzzle_num; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					infile >> block_num;
					s.push_back(block_num);
				}
			}
			permuSort(s,x);
			s.clear();
		}
		infile.close();
		return;
	}





};