#include "01.h"

int main() {
	//Allocating memory for an instance of the linked list class.
	NodeList* Node = new(std::nothrow) NodeList;
	if (Node == NULL) {
		std::cout << ("Memory allocation failure, press any key to exit. ") << std::endl;
		getchar();
		return 0;
	}
	std::cout << "Firstly, Please establish the candidate registration information system!" << std::endl;
	int number;
	while (true) {
		std::cout << "Please enter the total number of candidates: ";
		std::cin >> number;
		if (std::cin.fail() != true && number > 0) {
			break;
		}
		//Reset and clear the input stream if input data is incorrect, the same below.
		std::cin.clear();
		std::cin.sync();
		std::cout << "Please enter an appropriate positive integer!" << std::endl;
	}
	std::cout << "Please enter the candidate's ID, name, gender, age and application category in sequence!" << std::endl;
	//Initializing the linked list.
	Node->Init(number);
	std::cin.clear();
	std::cin.sync();
	std::cout << "Please choose the action you want to perform(1 to insert, 2 to delete, 3 to search, 4 to change, 5 to count, 0 to exit)." << std::endl;
	std::cout << std::endl;
	//Processing the actions the user wants to perform
	while (true) {
		int operation;
		while (true) {
			std::cout << "Please enter the option: ";
			std::cin >> operation;
			if (std::cin.fail() != true && operation >= 0 && operation <= 5) {
				break;
			}
			std::cin.clear();
			std::cin.sync();
			std::cout << "Non-existent option, please enter as required!" << std::endl;
		}
		switch (operation) {
		case 1:  //Insert
			Node->Insert();
			std::cin.clear();
			std::cin.sync();
			break;
		case 2:  //Delete
			Node->Delete();
			std::cin.clear();
			std::cin.sync();
			break;
		case 3:  //Search
			Node->Search();
			std::cin.clear();
			std::cin.sync();
			break;
		case 4:  //Change
			Node->Change();
			std::cin.clear();
			std::cin.sync();
			break;
		case 5:  //Count
			Node->Count();
			std::cin.clear();
			std::cin.sync();
			break;
		case 0:  //Exit
			return 0;
		}
		std::cin.clear();
		std::cin.sync();
	}
}