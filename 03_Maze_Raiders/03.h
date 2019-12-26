#ifndef _03_H_
#define _03_H_
#define MAZE_SIZE 8
#include <iostream>
#include <cstdlib>  //To generate random numbers
#include <ctime>  //To get the current system time

//Storing data related to the maze
class Maze {
private:
	char grid[MAZE_SIZE][MAZE_SIZE] = { {0} };
	int solution[MAZE_SIZE * MAZE_SIZE][2] = { {0} };
	bool have_searched[MAZE_SIZE][MAZE_SIZE] = { {false} };
	int length = 0;
	void Randomize();
	bool judge_grid(int x, int y);
	bool is_in_bound(int x, int y);
public:
	Maze() {
		for (int i = 0; i < MAZE_SIZE; ++i) {
			for (int j = 0; j < MAZE_SIZE; ++j) {
				grid[i][j] = 'X';
			}
		}
	}
	void Generate();
	void Print();
	void Find_way();
};

//To make the maze more random
void Maze::Randomize() {
	for (int i = 0; i < MAZE_SIZE; ++i) {
		for (int j = 0; j < MAZE_SIZE; ++j) {
			if (grid[i][j] == 'X') {
				int temp = rand() % 4;
				int direction_plus[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
				int count = 0;
				for (int k = 0; k < 4; ++k) {
					if (is_in_bound(i + direction_plus[k][0], j + direction_plus[k][1]) && grid[i + direction_plus[k][0]][j + direction_plus[k][1]] == 'O') {
						count++;
					}
				}
				if (count < temp) {
					grid[i][j] = 'O';
				}
			}
		}
	}
}

bool Maze::is_in_bound(int x, int y) {
	if (x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE) {
		return true;
	}
	return false;
}

//Search for the path recursively
bool Maze::judge_grid(int x, int y) {
	int directions[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
	have_searched[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int new_x = x + directions[i][0];
		int new_y = y + directions[i][1];
		if (is_in_bound(new_x, new_y) && !have_searched[new_x][new_y] && grid[new_x][new_y] != 'X') {
			if (grid[new_x][new_y] == 'T') {
				solution[length][0] = new_x;
				solution[length][1] = new_y;
				length++;
				return true;
			}
			bool result = judge_grid(new_x, new_y);
			if (result) {
				solution[length][0] = new_x;
				solution[length][1] = new_y;
				length++;
				return true;
			}
		}
	}
	have_searched[x][y] = false;
	return false;
}

//To guarantee there is a path in the generated maze
void Maze::Generate() {
	grid[0][0] = 'S';
	grid[MAZE_SIZE - 1][MAZE_SIZE - 1] = 'T';
	int tempx = 0, tempy = 0;
	bool is_true_flag;
	while (true) {
		is_true_flag = false;
		bool directions[4] = { false,false,false,false };
		int direction_plus[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
		if (tempx - 1 >= 0) {
			if (grid[tempx - 1][tempy] == 'T') {
				Randomize();
				return;
			}
			if (grid[tempx - 1][tempy] == 'X') {
				int count = 0;
				for (int i = 0; i < 4; ++i) {
					if (is_in_bound(tempx - 1 + direction_plus[i][0], tempy + direction_plus[i][1]) && grid[tempx - 1 + direction_plus[i][0]][tempy + direction_plus[i][1]] == 'O') {
						count++;
					}
				}
				if (count <= 1) {
					directions[0] = true;
					is_true_flag = true;
				}
			}
		}
		if (tempy - 1 >= 0) {
			if (grid[tempx][tempy - 1] == 'T') {
				Randomize();
				return;
			}
			if (grid[tempx][tempy - 1] == 'X') {
				int count = 0;
				for (int i = 0; i < 4; ++i) {
					if (is_in_bound(tempx + direction_plus[i][0], tempy - 1 + direction_plus[i][1]) && grid[tempx + direction_plus[i][0]][tempy - 1 + direction_plus[i][1]] == 'O') {
						count++;
					}
				}
				if (count <= 1) {
					directions[1] = true;
					is_true_flag = true;
				}
			}
		}
		if (tempx + 1 <= MAZE_SIZE - 1) {
			if (grid[tempx + 1][tempy] == 'T') {
				Randomize();
				return;
			}
			if (grid[tempx + 1][tempy] == 'X') {
				int count = 0;
				for (int i = 0; i < 4; ++i) {
					if (is_in_bound(tempx + 1 + direction_plus[i][0], tempy + direction_plus[i][1]) && grid[tempx + 1 + direction_plus[i][0]][tempy + direction_plus[i][1]] == 'O') {
						count++;
					}
				}
				if (count <= 1) {
					directions[2] = true;
					is_true_flag = true;
				}
			}
		}
		if (tempy + 1 <= MAZE_SIZE - 1) {
			if (grid[tempx][tempy + 1] == 'T') {
				Randomize();
				return;
			}
			if (grid[tempx][tempy + 1] == 'X') {
				int count = 0;
				for (int i = 0; i < 4; ++i) {
					if (is_in_bound(tempx + direction_plus[i][0], tempy + 1 + direction_plus[i][1]) && grid[tempx + direction_plus[i][0]][tempy + 1 + direction_plus[i][1]] == 'O') {
						count++;
					}
				}
				if (count <= 1) {
					directions[3] = true;
					is_true_flag = true;
				}
			}
		}
		if (is_true_flag == false) {
			tempx = 0, tempy = 0;
			for (int i = 0; i < MAZE_SIZE; ++i) {
				for (int j = 0; j < MAZE_SIZE; ++j) {
					grid[i][j] = 'X';
				}
			}
			grid[0][0] = 'S';
			grid[MAZE_SIZE - 1][MAZE_SIZE - 1] = 'T';
			continue;
		}
		int temp;
		while (true) {
			temp = std::rand() % 4;
			if (directions[temp] == true) {
				break;
			}
		}
		tempx += direction_plus[temp][0];
		tempy += direction_plus[temp][1];
		grid[tempx][tempy] = 'O';
	}
}

//Print the maze 
void Maze::Print() {
	std::cout << "Maze Map: " << std::endl;
	std::cout << "S: Start" << "   " << "T: Terminal" << "   " << "O: Passable Grid" << "   " << "X: Impassable Grid" << std::endl;
	std::cout << std::endl;
	std::cout << "\t";
	for (int i = 0; i < MAZE_SIZE; ++i) {
		std::cout << "Column " << i << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < MAZE_SIZE; ++i) {
		std::cout << "Row " << i << "\t";
		for (int j = 0; j < MAZE_SIZE; ++j) {
			std::cout << grid[i][j] << "        ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//Find the path through the maze
void Maze::Find_way() {
	int start_x, start_y;
	bool is_find_start = false;
	for (int i = 0; i < MAZE_SIZE; ++i) {
		for (int j = 0; j < MAZE_SIZE; ++j) {
			if (grid[i][j] == 'S') {
				start_x = i;
				start_y = j;
				is_find_start = true;
				break;
			}
		}
	}
	if (is_find_start == false) {
		std::cout << "Wrong Maze: find no START!" << std::endl;
		return;
	}
	bool result = judge_grid(start_x, start_y);
	if (!result) {
		std::cout << "No path found." << std::endl;
		return;
	}
	std::cout << "An example path: " << std::endl;
	std::cout << "<" << start_x << "," << start_y << "> " << "---> ";
	for (int i = length - 1; i > 0; i--) {
		std::cout << "<" << solution[i][0] << "," << solution[i][1] << "> " << "---> ";
	}
	std::cout << "<" << solution[0][0] << "," << solution[0][1] << "> " << std::endl;
	std::cout << std::endl;
}
#endif
