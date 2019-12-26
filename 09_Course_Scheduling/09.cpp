#include "09.h"

int main() {
	std::string location = R"(./09_Input.txt)";  //Read in the Input files
	std::ifstream Input(location);
	if (!Input.is_open()) {
		std::cout << "Failed to open " << location << ". " << std::endl;
		std::cin.clear();
		std::cin.sync();
		getchar();
		exit(0);
	}
	Graph graph;
	Course course;
	std::string line;
	getline(Input, line);
	while (getline(Input, line)) {  //Read in the Points and Edges of the graph
		std::stringstream stream(line);
		stream >> course;
		graph.AddCourse(course);
	}
	Input.close();
	std::ifstream InputEdges(location);
	getline(InputEdges, line);
	while (getline(InputEdges, line)) {
		std::stringstream stream(line);
		stream >> course;
		std::string tmp;
		while (stream >> tmp) {
			graph.AddEdges(tmp);
		}
		graph.currentCourse++;
	}
	std::cout << "Course information is stored in " << location << ", the output is stored in ./Output.txt. " << std::endl;
	std::cout << "Enter 0 to decide numbers of courses in each term by default, enter 1 to input them manually: ";
	char option;
	while (true) {
		std::cin >> option;
		if (std::cin.fail() != true && (option == '1' || option == '0')) {
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
	switch (option) {  //Whether to input the numbers of courses in each term manually
	case '0':
	{
		long long sum = 0;
		for (int i = 0; i < 8; i++) {
			sum += courses_each_term[i];
		}
		if (sum != graph.totalCourses) {
			std::cout << "Default numbers failed. Please enter them manually. " << std::endl;
			option = 1;  //if default numbers fail, switch to case '1'
		}
		else {
			break;
		}
	}
	case '1':
	{
		std::cout << "NOTICE: It can be proved that 'Course Scheduling' is an NP-hard problem, and it is not guaranteed this program can find a solution (even if there is a solution)." << std::endl;
		std::cout << "There are " << graph.totalCourses << " courses in total, please enter eight numbers for term 1 to 8. Sum of the eight numbers must be " << graph.totalCourses << "." << std::endl;
		while (true) {
			long long sum = 0;
			for (int i = 0; i < 8; i++) {
				std::cin >> courses_each_term[i];
				sum += courses_each_term[i];
			}
			if (std::cin.fail() != true && sum == graph.totalCourses) {
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
		break;
	}
	}
	graph.TopologicalSort();
	std::cout << "Course Scheduling Success! " << std::endl;
	std::string destination = R"(./09_Output.txt)";  //Print the Schedule
	std::ofstream Output(destination);
	for (int term = 0; term < TERMS; term++) {
		Output << "Term " << 1 + term << std::endl;
		Output << "\t" << "\t" << "    ";
		for (int day = 0; day < 5; day++) {
			Output << "Day " << 1 + day << "\t" << "\t";
		}
		Output << std::endl;
		for (int class_ = 0; class_ < 10; class_++) {
			if (class_ <= 8) {
				Output << "Class " << 1 + class_ << " " << "\t";
			}
			else {
				Output << "Class " << 1 + class_ << "\t";
			}
			for (int day = 0; day < 5; day++) {
				if (graph.plan[term][day][class_].empty()) {
					Output << "None" << "\t" << "\t";
				}
				else {
					Output << graph.plan[term][day][class_] << "\t" << "\t";
				}
			}
			Output << std::endl;
		}
		Output << std::endl;
	}
	std::cout << "Please Check ./09_Output.txt for the Scheduling! " << std::endl;
	std::cout << "Press any key to exit... " << std::endl;
	std::cin.clear();
	std::cin.sync();	
	getchar();
	return 0;
}
