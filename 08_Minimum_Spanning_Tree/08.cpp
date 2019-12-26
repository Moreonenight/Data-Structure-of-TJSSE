#include "08.h"

int main() {
	MST mst;
	std::cout << "**             Power Grid Cost Simulating System            **" << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "**                 A --- Create the System                  **" << std::endl;
	std::cout << "**                   B --- Add Grid Paths                   **" << std::endl;
	std::cout << "**          C --- Generate the Minimum Spanning Tree        **" << std::endl;
	std::cout << "**            D --- Print the Minimum Spanning Tree         **" << std::endl;
	std::cout << "**                       E --- Exit                         **" << std::endl;
	std::cout << "==============================================================" << std::endl << std::endl;
	while (true) {
		std::cout << "Please choose your option: ";
		char option;
		while (true) {
			std::cin >> option;
			if (std::cin.fail() != true && option >= 'A' && option <= 'E') {
				std::cin.clear();
				std::cin.sync();
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			std::cout << "Please enter as required! " << std::endl;
		}
		switch (option) {
		case 'A':  //Create the System
		{
			std::cout << "Please enter the number of points: ";
			int number;
			while (true) {
				std::cin >> number;
				if (std::cin.fail() != true && number >= 1 && number <= MAX_CITY_NUMBERS) {
					std::cin.clear();
					std::cin.sync();
					break;
				}
				//Reset and clear the input stream if input data is incorrect.
				std::cin.clear();
				std::cin.sync();
				std::cout << std::endl;
				if (number > MAX_CITY_NUMBERS) {
					std::cout << "Too big integer! Please re-enter an appropriate integer: ";
				}
				else {
					std::cout << "Please enter as required: ";
				}
			}
			mst.Setup(number);
			break;
		}
		case 'B':  //Add Grid Paths
		{
			mst.ReadinPath();
			break;
		}
		case 'C':  //Generate the Minimum Spanning Tree
		{
			if (mst.GenerateMST()) {
				std::cout << "Have Successfully Generated the Kruskal Minimum Spanning Tree! " << std::endl;
			}
			else {
				std::cout << "Generation Failed! " << std::endl;
			}
			break;
		}
		case 'D':  //Print the Minimum Spanning Tree
		{
			mst.Print();
			break;
		}
		case 'E':  //Exit
			exit(0);
			break;
		}
	}
	return 0;
}
