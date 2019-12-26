#ifndef _08_H_
#define _08_H_
#define MAX_CITY_NUMBERS 100
#include <iostream>
#include <string>
#include <cstring> //For memset

class MST {
private:
	int point_numbers = 0;
	//Flags to show corresponding error messages
	bool has_setup = false;
	bool has_path = false;
	bool has_generated = false;
	std::string points[MAX_CITY_NUMBERS];
	int paths[MAX_CITY_NUMBERS][MAX_CITY_NUMBERS] = { {0} };
	int mst[MAX_CITY_NUMBERS][3] = { {0} };
public:
	void Setup(int number);
	void ReadinPath();
	bool GenerateMST();
	void Print();
};

////Create the System
void MST::Setup(int number) {
	point_numbers = number;
	std::cout << "Please enter names of the points: " << std::endl;
	for (int i = 0; i < point_numbers; i++) {
		std::string name;
		while (true) {
			bool is_duplicated = false;
			bool is_break = false;
			std::cin >> name;
			for (int j = 0; j < i; j++) {
				if (points[j] > name) {
					int tmp = i;
					while (j < tmp) {
						points[tmp] = points[tmp - 1];
						tmp--;
					}
					points[j] = name;
					is_break = true;
					break;
				}
				if (points[j] == name) {
					is_duplicated = true;
					break;
				}
			}
			if (is_break == false) {
				points[i] = name;
			}
			if (std::cin.fail() != true && is_duplicated == false) {
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			if (is_duplicated == false) {
				std::cout << "Please enter as required: ";
			}
			else {
				std::cout << "Duplicated names are not supported, please re-enter: ";
			}
		}
	}
	std::cout << "There are " << point_numbers << " points named as: " << std::endl;
	for (int i = 0; i < point_numbers; i++) {
		std::cout << points[i] << " ";
	}
	std::cout << "in the system. " << std::endl << std::endl;
	has_setup = true;
	has_generated = false;
	has_path = false;
}

////Read in Grid Paths
void MST::ReadinPath() {
	if (has_setup == false) {
		std::cout << "No points input. " << std::endl;
		return;
	}
	memset(paths, -1, sizeof(paths));
	std::cout << "Please enter '? ? 0' to indicate the end of input. " << std::endl;
	while (true) {
		std::cout << "Please enter two points and the cost: ";
		std::string name1, name2;
		bool fail_flag = false;
		int cost;
		std::cin >> name1 >> name2 >> cost;
		if (name1 == "?"&&name2 == "?") {
			std::cin.clear();
			std::cin.sync();
			has_path = true;
			has_generated = false;
			return;
		}
		if (name1 < name2) {
			std::string tmp;
			tmp = name1;
			name1 = name2;
			name2 = tmp;
		}
		if (name1 == name2) {
			fail_flag = true;
		}
		int tmp1 = 0, tmp2 = 0;
		bool find1 = false, find2 = false;
		for (int i = 0; i < point_numbers; i++) {
			if (points[i] == name1) {
				tmp1 = i;
				find1 = true;
				break;
			}
		}
		for (int i = 0; i < point_numbers; i++) {
			if (points[i] == name2) {
				tmp2 = i;
				find2 = true;
				break;
			}
		}
		if (find1 == false || find2 == false) {
			fail_flag = true;
		}
		if (cost < 0) {
			fail_flag = true;
		}
		if (std::cin.fail() == true || fail_flag == true) {
			std::cin.clear();
			std::cin.sync();
			std::cout << "Your input do not meet the requirements. Please re-try! " << std::endl;
			return;
		}
		paths[tmp1][tmp2] = cost;
	}
}

//Generate the Minimum Spanning Tree
bool MST::GenerateMST() {
	if (has_path == false) {
		return false;
	}
	int path_counter = 0;
	for (int k = 0; k < point_numbers * (point_numbers - 1) / 2; k++) {
		int temp_min[3] = { 0,0,INT_MAX };
		for (int i = 0; i < point_numbers; i++) {
			for (int j = 0; j < i; j++) {
				if (paths[i][j] >= 0 && temp_min[2] > paths[i][j]) {
					temp_min[2] = paths[i][j];
					temp_min[0] = i;
					temp_min[1] = j;
				}
			}
		}
		if (temp_min[2] == INT_MAX) {
			return false;
		}
		bool check1 = false, check2 = false;
		for (int n = 0; n < path_counter; n++) {
			if (mst[n][0] == temp_min[0] || mst[n][1] == temp_min[0]) {
				check1 = true;
				break;
			}
		}
		for (int n = 0; n < path_counter; n++) {
			if (mst[n][0] == temp_min[1] || mst[n][1] == temp_min[1]) {
				check2 = true;
				break;
			}
		}
		if (check1 == false || check2 == false) {
			mst[path_counter][0] = temp_min[0];
			mst[path_counter][1] = temp_min[1];
			mst[path_counter][2] = temp_min[2];
			path_counter++;
		}
		if (path_counter == point_numbers - 1) {
			has_generated = true;
			return true;
		}
		paths[temp_min[0]][temp_min[1]] = -1;
	}
	return false;
}

//Print the Minimum Spanning Tree
void MST::Print() {
	if (has_generated == false) {
		std::cout << "Your have not generated the Minimum Spanning Tree! " << std::endl;
		return;
	}
	std::cout << "The Minimum Spanning Tree is: " << std::endl;
	for (int i = 0; i < point_numbers - 1; i++) {
		std::cout << points[mst[i][0]] << "--(" << mst[i][2] << ")--" << points[mst[i][1]] << " ";
	}
	std::cout << std::endl;
}
#endif
