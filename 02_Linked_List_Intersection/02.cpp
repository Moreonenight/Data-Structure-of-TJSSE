#include "02.h"

int main() {
	//Allocating memory for instances of the linked list class.
	NodeList* Node_in1 = new(std::nothrow) NodeList;
	if (Node_in1 == NULL) {
		std::cout << ("Memory allocation failure, press any key to exit. ") << std::endl;
		getchar();
		return 0;
	}
	NodeList* Node_in2 = new(std::nothrow) NodeList;
	if (Node_in2 == NULL) {
		std::cout << ("Memory allocation failure, press any key to exit. ") << std::endl;
		getchar();
		return 0;
	}
	NodeList* Node_out = new(std::nothrow) NodeList;
	if (Node_out == NULL) {
		std::cout << ("Memory allocation failure, press any key to exit. ") << std::endl;
		getchar();
		return 0;
	}
	//Enter the required linked lists
	std::cout << "Please enter the first linked list (positive integers divided by a space, end with -1, non-descending) ! " << std::endl;
	Node_in1->Init();
	std::cout << "Please enter the second linked list (positive integers divided by a space, end with -1, non-descending) !" << std::endl;
	Node_in2->Init();
	Node_out->Merge(Node_in1, Node_in2);  //Perform intersection
	std::cout << "The linked list resulting from intersection is as follows: " << std::endl;
	Node_out->Print();  //Print the result linked list
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.clear();
	std::cin.sync();
	getchar();
	return 0;
}
