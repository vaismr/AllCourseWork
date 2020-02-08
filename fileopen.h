#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <istream>
#include <stdio.h>
#include "sorting.h"
#include "ctpl.h"

using namespace std;


class fileopen :public sorting
{
public:


	virtual int indexOf(int x, int y) {
		return x + y * N;
	}

	//creat random puzzle by randomly pick up numbers from an array containing 1-20
	void random_input(vector<int>& dp) {

		int arr[20];

		int flag[20] = { 0 };
		int arr_size = sizeof(arr) / sizeof(int);
		int m = N * N - 1;
		int t;
		int n = 20;
		for (int i = 0; i < arr_size; i++)
			arr[i] = i + 1;


		for (int i = 0; i < m; ++i) {

			t = rand() % arr_size;
			if (flag[t] == 0) {
				flag[t] = 1;//set a flag when this number is choosed to avoid repeated number

				dp.push_back(arr[t]);
			}
			else
				i--;
		}
		dp.erase(dp.begin());
		dp.push_back(0);
	}

	//creat a new txt file to sotre the puzzle created
	//Let the user choose either randomly or manually build a puzzle
	void openthefile(vector <int> ui) {
		int choose;
		int num;
		int threadP;
		int k = 0;
		int n = 0;
		sorting sorttest;
		ofstream outfile;
		outfile.open("data.txt");

		int puzzle_num = 0;
		cout << "please input how many puzzles you want:" << endl;
		cin >> puzzle_num;
		outfile << puzzle_num << endl;
		vector<int>* ui_container = new vector<int>[puzzle_num];

		cout << "choose how to build the puzzle:" << "\n" << "1:Manually 2:Automatically" << endl;
		cin >> choose;

		ctpl::thread_pool p(2);


		switch (choose)
		{
		case 1:
		{
			cout << "please build your puzzle:( Any number from 1-20 but with a 0 at the end)" << endl;
			for (k = 0; k < puzzle_num; k++) {
				for (n = 0; n < N * N; n++) {
					cin >> num;
					ui_container[k].push_back(num);
				}
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						outfile << ui_container[k][indexOf(j, i)] << " ";
					}
					outfile << endl;
				}
				outfile << endl;
			}
			break;
		case 2:
		{
			int count1 = puzzle_num / 2;
			auto f = [&](int, int begin, int end)
			{


				for (k = begin; k < end; k++) {

					vector<int>* ui = new vector<int>;
					(*ui).push_back(0);
					random_input(*ui);
					ui_container[k] = *ui;



				}

			};

			auto f1 = p.push(f, 0, count1);
			auto f2 = p.push(f, count1, puzzle_num);
			f1.get();
			f2.get();
			for (k = 0; k < puzzle_num; k++) {
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						outfile << ui_container[k][indexOf(j, i)] << " ";
					}

					outfile << endl;
				}
				outfile << endl;
			}
			delete[] ui_container;

			break;
		}
		default:
			cout << "invalid input.Please try again" << endl;
			cin >> choose;
		}

		outfile.close();
		return;

		}

	}
};