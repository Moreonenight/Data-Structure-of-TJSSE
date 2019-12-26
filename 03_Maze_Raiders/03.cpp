#include "03.h"

int main() {
	int option = 0;
	while (true) {
		std::srand(std::time(0));
		Maze maze;
		maze.Generate();
		maze.Print();
		maze.Find_way();
		while (true) {
			std::cout << std::endl;
			std::cout << "Enter 0 to regenerate a random 8*8 maze, enter 1 to exit. " << std::endl;
			std::cout << "(If you generate more than one maze in a second, they will be the same!): ";
			std::cin >> option;
			if (std::cin.fail() != true && option >= 0 && option < 2) {
				std::cin.clear();
				std::cin.sync();
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			std::cout << "Please enter an appropriate option!" << std::endl;
		}
		if (option == 1) {
			exit(0);
		}
	}
	return 0;
}
