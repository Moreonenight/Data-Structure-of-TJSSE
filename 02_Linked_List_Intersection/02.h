#ifndef _02_H_
#define _02_H_
#include <iostream>
#include <string>
#include <new>   //In order to use std::nothrow to return a NULL pointer in case of memory allocation failure instead of throwing an exception.

//A Struct storing the numbers
struct Number {
	int number = 0;
	Number* next = NULL;
};

//Linked list class.
class NodeList {
private:
	Number* start = NULL;
public:
	void Print();
	void Init();
	void Merge(NodeList* Node1, NodeList* Node2);
};

//Print the current linked list.
void NodeList::Print() {
	if (start == NULL) {
		std::cout << "NULL";
	}
	else {
		Number* temp = start;
		while (temp != NULL && temp->next != NULL) {
			std::cout << temp->number << " ";
			temp = temp->next;
		}
		if(temp != NULL){
			std::cout << temp->number;
		}
	}
	std::cout << std::endl;
}

//Initialize the linked list
void NodeList::Init() {
	while (true) {
		Number* temp_node_ptr = NULL;
		int key = 0;
		int test_number = -1;
		bool is_failed = false;
		while (true) {
			Number* new_node = new(std::nothrow) Number;
			if (new_node == NULL) {
				std::cout << "Memory allocation failure, press any key to retry! " << std::endl;
				getchar();
				continue;
			}
			int temp_number;
			std::cin >> temp_number;
			//Break if input data is incorrect
			if (std::cin.fail() == true) {
				break;
			}
			if (temp_number == -1) {
				break;
			}
			if (temp_number < test_number) {
				std::cout << "The input linked list must be positive integers divided by a space, end with -1 and non-descending! " << std::endl;
				is_failed = true;
				break;
			}
			if (temp_number <= 0) {
				std::cout << "The input linked list must be positive integers divided by a space, end with -1 and non-descending! " << std::endl;
				is_failed = true;
				break;
			}
			test_number = temp_number;
			if (key == 0) {
				start = new_node;
				key = 1;
			}
			else {
				temp_node_ptr->next = new_node;
			}
			temp_node_ptr = new_node;
			new_node->number = temp_number;
			new_node->next = NULL;
		}
		//Reset and clear the input stream if input data is incorrect.
		if (std::cin.fail() != true && is_failed == false) {
			break;
		}
		std::cin.clear();
		std::cin.sync();
		std::cout << "Input data do not meet the format requirements, please re-enter! " << std::endl;
	}
}

//Perform intersection
void NodeList::Merge(NodeList* Node1, NodeList* Node2) {
	if (Node1->start != NULL && Node2->start != NULL) {
		Number* temp1 = Node1->start;
		Number* temp2 = Node2->start;
		Number* temp = NULL;
		while (temp1 != NULL && temp2 != NULL) {
			//As the input linked lists are non-descending, when one number is smaller than the other, just shift afterwards the iterator of that linked list by one.
			if (temp1->number > temp2->number) {
				temp2 = temp2->next;
				continue;
			}
			if (temp1->number < temp2->number) {
				temp1 = temp1->next;
				continue;
			}
			if (temp1->number == temp2->number) {
				Number* new_node = new(std::nothrow) Number;
				if (new_node == NULL) {
					std::cout << "Memory allocation failure, press any key to retry! " << std::endl;
					getchar();
					continue;
				}
				//Insert a node into the result linked list
				new_node->number = temp1->number;
				new_node->next = NULL;
				if (start == NULL) {
					start = new_node;
					temp = new_node;
				}
				else {
					temp->next = new_node;
					temp = temp->next;
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
	}
	//Either input linked list is NULL, the result linked list is NULL
	else {
		start = NULL;
		return;
	}
}

#endif
