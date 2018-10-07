/*************************************************************
	Author: qiuyihao
	Creation date: 2018/09/25
	Finished date: 2018/09/
	Description:  使用爬山法来解决N皇后问题
	Note: 爬山法采用了随机重启的原则，当爬山步数达到一定数量后
		  会将棋盘重新打乱。循环遍历每一行，每一行都选择最优的位置
		  直到冲突的个数为0
****************************************************************/

#ifndef CLIMBHILL_H
#define CLIMBHILL_H
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define random(x) (rand()%x)  // 定义产生随机数的函数

using namespace std;
class climbHill {
private:
	int N; // 棋盘大小
	int step;				   // 记录运行的步数
	int maxSteps;         // 达到最大扫描次数后，仍未解决则重启
	int rowPosition;           // 在该行位置检测最优位置
public:
	climbHill(int N) {
		step = 0;
		maxSteps = N * N *2;        
		this->N = N;
		rowPosition = 0;
	}

	//随机重启，达到一步的步数后，仍未求解那么就重新打乱棋盘
	//先生成对角线的皇后棋子，然后随机交换两行
	void reset(vector<int>& chessboard) {
		chessboard.clear();
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

	// 计算当前棋盘存在的相互攻击的皇后对数
	int getNumofConflicts(vector<int> *chessboard) {
		int numOfConflicts = 0;
		int width = this->N;
		for (int i = 0; i < width; i++) {
			for (int j = i + 1; j < width; j++) {
				// 当存在皇后位于对角线的时候 冲突数+1
				if (abs(j - i) == abs((*chessboard)[i] - (*chessboard)[j])) {
					numOfConflicts++;
				}
				// 当存在皇后位于同一列的时候，冲突数+1
				if ((*chessboard)[i] == (*chessboard)[j]) {
					numOfConflicts++;
				}
			}
		}
		return numOfConflicts;
	}
	
	// 计算某一行的最优位置
	int chooseTheBestPosition(vector<int>* chessboard, int row) {
		// 记录为移动之前的位置
		int originPosition = (*chessboard)[row];
		// 记录每一个位置对应的棋盘状态所对应的冲突数
		vector<int> conflictData;
		for (int i = 0; i < N; i++) {
			(*chessboard)[row] = i;
			conflictData.push_back(getNumofConflicts(chessboard));
		}
		//记录冲突数最小的几个位置，然后随机然后一个位置
		int less = 0;
		vector<int> bestPosition;
		for (int i = 0; i < N; i++) {
			if (i == 0) {
				bestPosition.push_back(0);
				less = conflictData[0];
				continue;
			}
			// 判断i位置冲突数小于最优位置,清空向量，存储更小冲突的位置
			if (conflictData[i] < less) {
				bestPosition.clear();
				bestPosition.push_back(i);
				less = conflictData[i];
			}
			// 将同样最小的冲突位置也添加到向量中
			else if(conflictData[i] == less) {
				bestPosition.push_back(i);
			}
		}
		if (bestPosition.size() == 1)
			return bestPosition[0];

		// 最佳位置有多个，则随机筛选
		srand((unsigned)time(0));
		return bestPosition[rand() % bestPosition.size()];
	}

	// 每行选择最优位置
	vector<int>* scanChessboard(vector<int>* chessboard, int row){
		(*chessboard)[row] = chooseTheBestPosition(chessboard, row);
		return chessboard;
	}

	// 求解，不断搜寻状态更好的情况，直到冲突数为0
	vector<int>* solve(vector<int> *chessboard) {
		// 随机播种
		srand(time(NULL));
		int resetTime = 0;  // 重启步数
		step = 0;   // 统计运行步数
		// 当冲突数为0时终止爬山
		while (getNumofConflicts(chessboard) > 0) {
			if (step >= maxSteps) {
				reset(*chessboard);
				resetTime++;
				step = 0;
				cout << "随机重启" << endl;
			}
			// 将rowPostion行的皇后移到同一行的最优位置
			chessboard = scanChessboard(chessboard,rowPosition++);
			// 判断rowPosition是否归零，防止越界
			rowPosition = rowPosition >= N ? rowPosition % N : rowPosition;
			step++;
		// 	cout << step << endl;
		}
		cout << "Solved the problem, totally " << step << " steps. Including "<< resetTime<< " reset times."  << endl;
		return chessboard;
	}
	
};

#endif // !

