#include "06.h"

int main() {
	std::cout << "**               Genealogy Information System               **" << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "**   Please choose the option you would like to perform:    **" << std::endl;
	std::cout << "**                 A --- Form a new family                  **" << std::endl;
	std::cout << "**               B --- Add new family members               **" << std::endl;
	std::cout << "**               C --- Remove family members                **" << std::endl;
	std::cout << "**                D --- Change information                  **" << std::endl;
	std::cout << "**                  E --- Print the tree                    **" << std::endl;
	std::cout << "**                        F --- Exit                        **" << std::endl;
	std::cout << "**    Please notice that if there are duplicated names,     **" << std::endl;
	std::cout << "** the option will only take effect on the FIRST FOUND one. **" << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "Firstly, please add a root for this system." << std::endl;
	std::cout << "Please enter the name of an ancestor (entering more than one person is invalid!): ";
	std::string root;
	while (true) {
		std::cin >> root;
		if (std::cin.fail() != true) {
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
	FamilyTree family(root);
	std::cout << "The root of this system is: " << root << std::endl;
	std::cout << std::endl;
	while (true) {
		std::cout << "Please choose the option you would like to perform: ";
		char option;
		while (true) {
			std::cin >> option;
			if (std::cin.fail() != true && option >= 'A' && option <= 'F') {
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
		case 'A':  //Form a new family
		{
			std::cout << "Please enter the name of the member who is forming a family: ";
			std::string name;
			Member* temp;
			while (true) {
				std::cin >> name;
				temp = family.Search(name, &(family.root));
				if (std::cin.fail() != true && temp != NULL) {
					std::cin.clear();
					std::cin.sync();
					break;
				}
				//Reset and clear the input stream if input data is incorrect.
				std::cin.clear();
				std::cin.sync();
				std::cout << std::endl;
				if (temp == NULL) {
					std::cout << "Member not found! Please re-enter:  ";
				}
				else {
					std::cout << "Please enter as required: ";
				}
			}
			std::cout << "Please enter the number of children (>0) : ";
			int number;
			while (true) {
				std::cin >> number;
				if (std::cin.fail() != true && number > 0) {
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
			family.Form(temp, number);
			break;
		}
		case 'B':  //Add new family members
		{
			std::cout << "Please enter the name of the member adding the child to: ";
			std::string name;
			Member* temp;
			while (true) {
				std::cin >> name;
				temp = family.Search(name, &(family.root));
				if (std::cin.fail() != true && temp != NULL) {
					std::cin.clear();
					std::cin.sync();
					break;
				}
				//Reset and clear the input stream if input data is incorrect.
				std::cin.clear();
				std::cin.sync();
				std::cout << std::endl;
				if (temp == NULL) {
					std::cout << "Member not found! Please re-enter:  ";
				}
				else {
					std::cout << "Please enter as required: ";
				}
			}
			family.Add(temp);
			break;
		}
		case 'C':  //Remove family members 
		{
			std::cout << "Please enter the name of the member you want to remove: ";
			std::string name;
			Member* temp;
			while (true) {
				std::cin >> name;
				temp = family.Search(name, &(family.root));
				if (std::cin.fail() != true && temp != NULL) {
					std::cin.clear();
					std::cin.sync();
					break;
				}
				//Reset and clear the input stream if input data is incorrect.
				std::cin.clear();
				std::cin.sync();
				std::cout << std::endl;
				if (temp == NULL) {
					std::cout << "Member not found! Please re-enter:  ";
				}
				else {
					std::cout << "Please enter as required: ";
				}
			}
			family.Remove(temp);
			break;
		}
		case 'D':  //Change information 
		{
			std::cout << "Please enter the name of the member you want to change: ";
			std::string name;
			Member* temp;
			while (true) {
				std::cin >> name;
				temp = family.Search(name, &(family.root));
				if (std::cin.fail() != true && temp != NULL) {
					std::cin.clear();
					std::cin.sync();
					break;
				}
				//Reset and clear the input stream if input data is incorrect.
				std::cin.clear();
				std::cin.sync();
				std::cout << std::endl;
				if (temp == NULL) {
					std::cout << "Member not found! Please re-enter:  ";
				}
				else {
					std::cout << "Please enter as required: ";
				}
			}
			family.Change(temp);
			break;
		}
		case 'E':  //Print the tree
			family.Print();
			break;
		case 'F':  //Exit
			exit(0);
			break;
		}
	}
	return 0;
}
