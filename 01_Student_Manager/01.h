#ifndef _01_H_
#define _01_H_
#include <iostream>
#include <string>
#include <new>   //To use std::nothrow to return a NULL pointer in case of memory allocation failure instead of throwing an exception.

//A Struct storing the registration information of candidates
struct StudentInfo {
	std::string ID;
	std::string name;
	std::string sex;
	int age = 0;
	std::string type;
	StudentInfo* next = NULL;
};

//Linked list class.
class NodeList {
private:
	StudentInfo* start = NULL;
	int length = 0;
public:
	void Print();
	void Insert();
	void Delete();
	void Search();
	void Change();
	void Count();
	void Init(int number);
};

//Print the current data sheet.
void NodeList::Print() {
	std::cout << std::endl;
	if (start == NULL) {
		std::cout << ("No data available in the current data sheet!") << std::endl;
	}
	else {
		StudentInfo* temp = start;
		std::cout << "The current data sheet: " << std::endl;
		std::cout << "ID" << '\t' << "Name" << '\t' << "Gender" << '\t' << "Age" << '\t' << "Application Category" << std::endl;
		while (temp != NULL) {
			std::cout << temp->ID << '\t' << temp->name << '\t' << temp->sex << '\t' << temp->age << '\t' << temp->type << std::endl;
			temp = temp->next;
		}
	}
}

//Initialize the data sheet when this program starts
void NodeList::Init(int number) {
	while (true) {
		StudentInfo* temp_node_ptr = NULL;
		for (int i = 0; i < number; ++i) {
			StudentInfo* new_node = new(std::nothrow) StudentInfo;
			if (new_node == NULL) {
				std::cout << ("Memory allocation failure, press any key to retry!") << std::endl;
				getchar();
				continue;
			}
			if (i == 0) {
				start = new_node;
			}
			else {
				temp_node_ptr->next = new_node;
			}
			temp_node_ptr = new_node;
			std::cin >> new_node->ID >> new_node->name >> new_node->sex >> new_node->age >> new_node->type;
			new_node->next = NULL;
		}
		if (std::cin.fail() != true) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		//Reset and clear the input stream if input data is incorrect, the same below.
		std::cin.clear();
		std::cin.sync();
		std::cout << "Input data do not meet the format requirements, please re-enter! " << std::endl;
	}
	length = number;
	Print();
}

//Insert a node at the specified position in the linked list
void NodeList::Insert() {
	int place;
	while (true) {
		std::cout << "Please enter where you want to insert the candidate (start from 1, and it will be inserted at the end of the sheet if you enter a oversize integer): ";
		std::cin >> place;
		if (std::cin.fail() != true && place > 0) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
		std::cout << "Please enter an appropriate positive integer!" << std::endl; 
	}
	StudentInfo* new_node = new(std::nothrow) StudentInfo;
	if (new_node == NULL) {
		std::cout << ("Memory allocation failure, press any key to retry!") << std::endl;
		return;
	}
	while (true) {
		std::cout << "Please enter the candidate's ID, name, gender, age and application category in sequence! " << std::endl;
		std::cin >> new_node->ID >> new_node->name >> new_node->sex >> new_node->age >> new_node->type;
		if (std::cin.fail() != true) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
		std::cout << "Input data do not meet the format requirements, please re-enter! " << std::endl;
	}
	new_node->next = NULL;
	if (place > length + 1) {
		place = length + 1;
	}
	if (place == 1) {
		new_node->next = start;
		start = new_node;
	}
	else {
		StudentInfo* temp = start;
		for (int i = 1; i < place - 1; ++i) {
			temp = temp->next;
		}
		new_node->next = temp->next;
		temp->next = new_node;
	}
	Print();
	length++;
}

//Delete the node retrieved with the given number
void NodeList::Delete() {
	std::string number;
	if (length == 0) {
		std::cout << "No data available, invalid deletion!" << std::endl;
		return;
	}
	int length_reduction = 0;
	while (true) {
		std::cout << "Please enter the ID of the candidate you want to delete: ";
		std::cin >> number;
		if (std::cin.fail() != true) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
		std::cout << "Please enter as required! " << std::endl;
	}
	StudentInfo* temp = start;
	for (int i = 0; i < length; i++) {
		if (temp == start && temp->ID == number) {
			if (length_reduction == 0) {
				std::cout << "The candidate you have deleted is: " << std::endl;
				std::cout << "ID" << '\t' << "Name" << '\t' << "Gender" << '\t' << "Age" << '\t' << "Application Category" << std::endl;
			}
			std::cout << temp->ID << '\t' << temp->name << '\t' << temp->sex << '\t' << temp->age << '\t' << temp->type << std::endl;
			temp = start->next;
			delete start;
			length_reduction++;
			start = temp;
		}
		else if (temp->next != NULL && temp->next->ID == number) {
			if (length_reduction == 0) {
				std::cout << "The candidate you have deleted is: " << std::endl;
				std::cout << "ID" << '\t' << "Name" << '\t' << "Gender" << '\t' << "Age" << '\t' << "Application Category" << std::endl;
			}
			std::cout << temp->next->ID << '\t' << temp->next->name << '\t' << temp->next->sex << '\t' << temp->next->age << '\t' << temp->next->type << std::endl;
			StudentInfo* temp_ptr = temp->next->next;
			delete temp->next;
			length_reduction++;
			temp->next = temp_ptr;
		}
	}
	if (length_reduction == 0) {
		std::cout << "Retrieved no candidate with the given ID! " << std::endl;
	}
	Print();
	length -= length_reduction;
}

//Print the node retrieved with the given ID
void NodeList::Search() {
	std::string number;
	if (length == 0) {
		std::cout << "No data available, invalid search! " << std::endl;
		return;
	}
	int if_search = 0;
	while (true) {
		std::cout << "Please enter the ID of the candidate you are searching for: ";
		std::cin >> number;
		if (std::cin.fail() != true) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
		std::cout << "Please enter as required!" << std::endl;
	}
	StudentInfo* temp = start;
	for (int i = 0; i < length; i++) {
		if (temp->ID == number) {
			if (if_search == 0) {
				std::cout << "The candidate you have searched for is: " << std::endl;
				std::cout << "ID" << '\t' << "Name" << '\t' << "Gender" << '\t' << "Age" << '\t' << "Application Category" << std::endl;
			}
			std::cout << temp->ID << '\t' << temp->name << '\t' << temp->sex << '\t' << temp->age << '\t' << temp->type << std::endl;
			if_search = 1;
		}
		temp = temp->next;
	}
	if (if_search == 0) {
		std::cout << "Candidate not found! " << std::endl;
	}
}

//Change the node retrieved with the given ID
void NodeList::Change() {
	std::string number;
	if (length == 0) {
		std::cout << "No data available, invalid change! " << std::endl;
		return;
	}
	int if_search = 0;
	while (true) {
		std::cout << "Please enter the ID of the candidate you are to change: ";
		std::cin >> number;
		if (std::cin.fail() != true) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
		std::cout << "Please enter as required!" << std::endl;
	}
	StudentInfo* temp = start;
	StudentInfo* temp_change = NULL;
	for (int i = 0; i < length; i++) {
		if (temp->ID == number) {
			if (if_search == 0) {
				std::cout << "You will change the candidate information of: " << std::endl;
				std::cout << "ID" << '\t' << "Name" << '\t' << "Gender" << '\t' << "Age" << '\t' << "Application Category" << std::endl;
				temp_change = temp;
			}
			std::cout << temp->ID << '\t' << temp->name << '\t' << temp->sex << '\t' << temp->age << '\t' << temp->type << std::endl;
			if_search = 1;
		}
		temp = temp->next;
	}
	if (if_search == 0) {
		std::cout << "Candidate not found! " << std::endl;
		return;
	}
	std::cin.clear();
	std::cin.sync();
	while (true) {
		std::cout << "Please enter the candidate's ID, name, gender, age and application category in sequence! (if there are candidates with the same ID, only the first found one will be changed)" << std::endl;
		std::cin >> temp_change->ID >> temp_change->name >> temp_change->sex >> temp_change->age >> temp_change->type;
		if (std::cin.fail() != true) {
			std::cin.clear();
			std::cin.sync();
			break;
		}
		std::cin.clear();
		std::cin.sync();
		std::cout << "Input data do not meet the format requirements, please re-enter! " << std::endl;
	}
	Print();
}

//Print the number of candidates in this data sheet
void NodeList::Count() {
	if (length == 0) {
		std::cout << "Blank data sheet! " << std::endl;
		return;
	}
	else {
		std::cout << "There are " << length << " candidate(s) in the data sheet. " << std::endl;
		return;
	}
}

#endif