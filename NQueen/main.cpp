#include <iostream>
#include "climbHill.h"
#include "geneticAlgorithm.h"
#include "simulatedAnnealing.h"
#include <vector>
#include <time.h>
#include <string>
#include <stdlib.h>

using namespace std;
   // 定义N皇后问题，皇后数目为N
#define random(x) (rand()%x)  // 定义产生随机数的函数

int N;

// 初始化棋盘
void initChessboard(vector<int>& chessboard) {
	for (int i = 0; i < N; i++) {
		chessboard.push_back(i);
	}
	
	srand((unsigned)time(0));
	for (int row1 = 0; row1 < N; row1++) {
		int row2 = random(N);
		// 随机交换行，打散棋盘，但保证皇后都在不同列
		swap(chessboard[row1], chessboard[row2]);
	}	
}

// 打印棋盘
void printChessboard(vector<int>& chessboard) {
	for (int i = 0; i < N; i++) {
		int num = chessboard[i];
		for (int j = 0; j < num; j++) {
			cout << " = ";
		}
		cout << " Q ";
		for (int k = num + 1; k < N; k++) {
			cout << " = ";
		}
		cout << endl;
	}
}

// 转换数字string 为int
int stringToInt(string choose) {
	if (choose == "1") return 1;
	if (choose == "2") return 2;
	if (choose == "3") return 3;
	if (choose == "4") return 4;
}

int main() {
	//定义数据结构Vector<int> 下标代表行数，值代表列数，表示一个棋盘
	N = 0;
	cout << "输入你要解决的N皇后问题的N值（建议8以上）" << endl;
	cin >> N;
	cout << N << " queens Problems =============== " << endl;
	cout << "Choose one algorithhm to solve the problem " << endl;
	cout << "1. HillClimbing Algorithm " << endl;
	cout << "2. Simulated Annealing Alogrithm " << endl;
	cout << "3. Genetic Algorithm " << endl;
	cout << "4. quit " << endl;
	string choose;

	// 初始化对象
	// 1. 三种算法对应三个棋盘
	vector<int> temp1_chessboard; 
	vector<int> temp2_chessboard;
	vector<int> temp3_chessboard;
	// 2.统计时间
	clock_t startTime;
	clock_t endTime;
	double totalTime;

	// 3.解决算法的对象
	climbHill sol1(N);
	simulatedAnnealing sol2(N);
	geneticAlgorithm sol3(N);

	
	while (1) {
		cin >> choose;
		int num = stringToInt(choose);
		int t = 0;   // 执行算法的次数
		double average = 0;  // 算法平均时间
		int big = 0;      // 算法最长时间
		int small = 100;     // 算法最短时间
		int sum = 0;          // 时间和
		switch (num)
		{
		case 1:
			cout << "Solution 1 --- Hill Climbing Algorithm " << endl;
			cout << "输入执行算法的次数" << endl;
			cin >> t;

			for (int i = 0; i < t; i++) {
				cout << "棋盘初始化并打印" << endl;
				initChessboard(temp1_chessboard);
				printChessboard(temp1_chessboard);
				startTime = clock();

				// 求解部分	
				temp1_chessboard = *sol1.solve(&temp1_chessboard);

				endTime = clock();
				totalTime = (double)(endTime - startTime);
				if (totalTime > big) {
					big = totalTime;
				}
				if (totalTime < small) {
					small = totalTime;
				}
				sum += totalTime;
				cout << "[ " << i << "]" << " total time: " << totalTime << " ms." << endl;
				printChessboard(temp1_chessboard);
				cout << "-----------------------------------------------------------" << endl;
			}
			average = sum * 1.0 / t;
			cout << "average time： " << average << " ms" << endl;
			cout << "longest time:  " << big << " ms" << endl;
			cout << "shortest time:  " << small << " ms" << endl;
  			
			break;
		case 2:
			cout << "Solution 2 --- Simulated Annealing Algorithm " << endl;
			cout << "输入执行算法的次数" << endl;
			cin >> t;

			for (int i = 0; i < t; i++) {
				cout << "棋盘初始化并打印" << endl;
				initChessboard(temp2_chessboard);
				printChessboard(temp2_chessboard);
				startTime = clock();
				// 求解部分	
				temp2_chessboard = *sol2.solve(&temp2_chessboard);

				endTime = clock();
				totalTime = (double)(endTime - startTime);
				if (totalTime > big) {
					big = totalTime;
				}
				if (totalTime < small) {
					small = totalTime;
				}
				sum += totalTime;
				cout << "[ " << i << "]" << " total time: " << totalTime << " ms." << endl;
				printChessboard(temp2_chessboard);
				cout << "-----------------------------------------------------------" << endl;

			}
			average = sum * 1.0 / t;
			cout << "average time： " << average << " ms" << endl;
			cout << "longest time:  " << big << " ms" << endl;
			cout << "shortest time:  " << small << " ms" << endl;

			break;
		case 3:
			cout << "Solution 3 --- Genetic Algorithm " << endl;
			cout << "棋盘初始化并打印" << endl;
			cout << "输入执行算法的次数" << endl;
			cin >> t;

			for (int i = 0; i < t; i++) {
				initChessboard(temp3_chessboard);
				printChessboard(temp3_chessboard);
				startTime = clock();

				// 求解部分	
				temp3_chessboard = *sol3.solve(temp3_chessboard);

				endTime = clock();
				totalTime = (double)(endTime - startTime); 
				if (totalTime > big) {
					big = totalTime;
				}
				if (totalTime < small) {
					small = totalTime;
				}
				sum += totalTime;
				cout << "[ " << i << "]" << " total time: " << totalTime << " ms." << endl;
				printChessboard(temp3_chessboard);
				cout << "-----------------------------------------------------------" << endl;
			}
			average = sum * 1.0 / t;
			cout << "average time： " << average << " ms" << endl;
			cout << "longest time:  " << big << " ms" << endl;
			cout << "shortest time:  " << small << " ms" << endl;

			break;
		case 4:
			exit(0);
			break;
		default:
			break;
		}
	}
}