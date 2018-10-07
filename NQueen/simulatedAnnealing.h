/**************************************************
	Author: qiuyihao
	Creation date: 2018/10/04
	Finished date: 2018/10/05
	Description:  使用模拟退火来解决N皇后问题
	Note：循环遍历每一行，如果下一状态优于当前状态，则接受移动，
		  如果下一状态劣于或等于当前状态，则以一定的概率接受移动。
****************************************************/

#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>

class simulatedAnnealing {
private:
	int N;              // 皇后的数目
public:
	// 默认构造函数
	simulatedAnnealing(int N) {
		this->N = N;
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

	//利用模拟退火算法得到该行的合适位置
	int properPosition(const vector<int> *chessboard, int row) {
		double T = 100.0;          // 当前温度
		double Tmin = 1.0;         // 最小温度
		double decreaseRate = 0.8; // 降温速率
		
		// 当前状态和下一状态
		vector<int>* currentChessboard = new vector<int>(N);
		vector<int>* nextChessboard = new vector<int>(N);

		for (int i = 0; i < this->N; i++) {
			(*currentChessboard)[i] = ((*chessboard)[i]);
			(*nextChessboard)[i] = ((*chessboard)[i]);
		}

		//int queenPosition = 0;
		// 开始模拟退火
		while (T > Tmin) {
			// 修改下一状态，改变row行的皇后位置
			for (int queenPosition = 0; queenPosition < this->N; queenPosition++) {
				(*nextChessboard)[row] = queenPosition;
				// 得到前后状态的能量差
				double dE = getNumofConflicts(nextChessboard) - getNumofConflicts(currentChessboard);
				// 如果下一步更优则，接受该移动
				if (dE <= 0) {
					(*currentChessboard)[row] = (*nextChessboard)[row];
					//cout << "更优，接受该移动" << " pos = " << queenPosition << endl;
				}
				//  如果下一步更差，则一定几率接受该移动，几率逐渐变小
				else {
					if (exp((-1) * dE / T) > random(100)* 1.0 / 100) {
					//	cout << "更差，但还是接受该移动" << " pos = " << queenPosition << endl;
						(*currentChessboard)[row] = (*nextChessboard)[row];
					}
					else {
				//		cout << "  不接受该移动 pos = " << queenPosition << endl;
					}
				}
			}
			//  降温
				T = decreaseRate * T;
			
		}
	//	cout << "-----------------------------" << endl;
		return (*currentChessboard)[row];
	}

	// 利用模拟退火算法修改该行，得到一个合适的位置
	//（不一定是当前最优，以一定几率接受一个更差的解）
	vector<int>* nextState(vector<int> *chessboard, int row) {
		(*chessboard)[row] = properPosition(chessboard, row);
		return chessboard;
	}

	// 求解主函数，在不同的行中不断搜寻下一步合适的位置
	vector<int>* solve(vector<int> *chessboard) {
		int rowPosition = 0;
		int step = 0;
		while (getNumofConflicts(chessboard)) {
			if (rowPosition == this->N) {
				rowPosition %= rowPosition;
			}
			chessboard = nextState(chessboard, rowPosition++);
			step++;
		}
		cout << "Solved the problem, totally " << step << " steps. "<< endl;
		return chessboard;
	}

};

#endif // !SIMULATED_ANNEALING_
