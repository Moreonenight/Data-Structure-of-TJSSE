#ifndef _06_H_
#define _06_H_
#include <iostream>
#include <string>

//A struct storing each family member
struct Member {
	int layer = 0;
	std::string name;
	Member* parent = NULL, * leftChild = NULL, * rightChild = NULL, * fakeParent = NULL;
	Member() = default;
	Member(const std::string myname) : name(myname) {}
};

//A struct storing genealogy information
class FamilyTree {
public:
	int total_layer = 0;
	Member root;
	Member* Search(std::string name, Member* search_root);
	Member* Print_Search(int temp_layer, Member* search_root);
	Member* Remove_Search(Member* search_root);
	FamilyTree(std::string first) {
		root.name = first;
	}
	void Print();
	void Form(Member* current, int number);
	void Add(Member* current);
	void Change(Member* current);
	void Remove(Member* current);
};

//Traverse the tree recursively
Member* FamilyTree::Search(std::string name, Member* search_root) {
	if (search_root != NULL) {
		if (search_root->name == name) {
			return search_root;
		}
		Member* temp = Search(name, search_root->leftChild);
		if (temp != NULL) {
			return temp;
		}
		return Search(name, search_root->rightChild);
	}
	else {
		return NULL;
	}
}

//Traverse the tree recursively
Member* FamilyTree::Print_Search(int temp_layer, Member* search_root) {
	if (search_root != NULL) {
		if (search_root->layer == temp_layer) {
			std::cout << search_root->name << "->" << search_root->parent->name << " ";
		}
		Print_Search(temp_layer, search_root->leftChild);
		Print_Search(temp_layer, search_root->rightChild);
		return NULL;
	}
	else {
		return NULL;
	}
}

//Print the tree
void FamilyTree::Print() {
	std::cout << "The Genealogy Tree is as follows (A->B means B is a parent of A) : " << std::endl;
	std::cout << "Layer 0: " << root.name << std::endl;
	for (int i = 1; i <= total_layer; i++) {
		std::cout << "Layer " << i << ": ";
		Print_Search(i, &root);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//Form a new family
void FamilyTree::Form(Member* current, int number) {
	int temp_layer = current->layer + 1;
	Member* temp_parent = current;
	if (temp_layer > total_layer) {
		total_layer = temp_layer;
	}
	std::cout << "Please enter the names of children : ";
	for (int i = 0; i < number; i++) {
		std::string name;
		while (true) {
			std::cin >> name;
			if (std::cin.fail() != true) {
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			std::cout << "Please enter as required! " << std::endl;
		}
		Member* tmp = new Member(name);
		if (i == 0) {
			current->leftChild = tmp;
		}
		else {
			current->rightChild = tmp;
		}
		tmp->fakeParent = current;
		tmp->parent = temp_parent;
		tmp->layer = temp_layer;
		current = tmp;
	}
	std::cin.clear();
	std::cin.sync();
}

//Add new family members 
void FamilyTree::Add(Member* current) {
	std::cout << "Please enter the name of the child : ";
	std::string name;
	while (true) {
		std::cin >> name;
		if (std::cin.fail() != true) {
			break;
		}
		//Reset and clear the input stream if input data is incorrect.
		std::cin.clear();
		std::cin.sync();
		std::cout << std::endl;
		std::cout << "Please enter as required! " << std::endl;
	}
	Member* tmp = new Member(name);
	tmp->layer = current->layer + 1;
	if (tmp->layer > total_layer) {
		total_layer = tmp->layer;
	}
	tmp->rightChild = current->leftChild;
	tmp->parent = current;
	tmp->fakeParent = current;
	current->leftChild = tmp;
	if (tmp->rightChild != NULL) {
		tmp->rightChild->fakeParent = tmp;
	}
}

//Change information 
void FamilyTree::Change(Member* current) {
	std::cout << "Please enter the new name: ";
	std::string name;
	while (true) {
		std::cin >> name;
		if (std::cin.fail() != true) {
			break;
		}
		//Reset and clear the input stream if input data is incorrect.
		std::cin.clear();
		std::cin.sync();
		std::cout << std::endl;
		std::cout << "Please enter as required! " << std::endl;
	}
	current->name = name;
}

//Traverse part of the tree recursively
Member* FamilyTree::Remove_Search(Member* search_root) {
	if (search_root != NULL) {
		Remove_Search(search_root->leftChild);
		Remove_Search(search_root->rightChild);
		delete search_root;
		return NULL;
	}
	return NULL;
}

//Remove family members
void FamilyTree::Remove(Member* current) {
	if (current->leftChild != NULL) {
		Remove_Search(current->leftChild);
	}
	if(current->fakeParent == NULL){
		std::cout << "You cannot delete the root node! " << std::endl;
		return;
	}
	if (current->fakeParent->leftChild == current) {
		current->fakeParent->leftChild = current->rightChild;
	}
	else {
		current->fakeParent->rightChild = current->rightChild;
	}
	delete current;
}

#endif
