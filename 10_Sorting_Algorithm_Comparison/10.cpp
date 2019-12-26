#include "10.h"

int main() {
	std::cout << "**                Sorting Algorithm Comparison              **" << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "**                    1 --- Bubble sort                     **" << std::endl;
	std::cout << "**                   2 ---  Selection sort                  **" << std::endl;
	std::cout << "**                   3 ---  Insertion sort                  **" << std::endl;
	std::cout << "**                    4 --- Shellsort                       **" << std::endl;
	std::cout << "**                    5 --- Quicksort                       **" << std::endl;
	std::cout << "**                    6 --- Heapsort                        **" << std::endl;
	std::cout << "**                   7 --- Merge sort                       **" << std::endl;
	std::cout << "**                   8 --- Radix sort                       **" << std::endl;
	std::cout << "**                       9 --- Exit                         **" << std::endl;
	std::cout << "==============================================================" << std::endl << std::endl;
	std::cout << "Please enter how many random number you want to generate (no more than 100000) : ";
	int number;
	while (true) {
		std::cin >> number;
		if (std::cin.fail() != true && number > 0 && number <= 100000) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		//Reset and clear the input stream if input data is incorrect.
		std::cin.clear();
		std::cin.sync();
		std::cout << std::endl;
		std::cout << "Please enter as required: ";
	}
	srand(time(0));
	for (int i = 0; i < number; i++) {
		numbers[i] = rand();
	}
	while (true) {
		std::cout << std::endl << "Please choose your option: ";
		char option;
		while (true) {
			std::cin >> option;
			if (std::cin.fail() != true && option >= '1' && option <= '9') {
				std::cin.clear();
				std::cin.sync();
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			std::cout << "Please enter as required: ";
		}
		switch (option) {
		case '1':
			bubble_sort(number);
			break;
		case '2':
			selection_sort(number);
			break;
		case '3':
			insertion_sort(number);
			break;
		case '4':
			shellsort(number);
			break;
		case '5':
			quicksort(number);
			break;
		case '6':
			heapsort(number);
			break;
		case '7':
			merge_sort(number);
			break;
		case '8':
			radix_sort(number);
			break;
		case '9':  //Exit
			exit(0);
			break;
		}
	}
	return 0;
}
