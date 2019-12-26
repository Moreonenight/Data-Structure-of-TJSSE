#ifndef _09_H_
#define _09_H_
#include <iostream>
#include <string>
#include <fstream>  //To read/write files
#include <sstream>  //For stringstream
#define MAX_COURSE_NUMBER 80
#define TERMS 8

bool edges[MAX_COURSE_NUMBER][MAX_COURSE_NUMBER] = { {false} };
int courses_each_term[TERMS] = { 4,4,5,5,5,5,5,5 };

//The Course Class
class Course {
public:
	Course() = default;
	Course(const Course& course) {
		id = course.id;
		name = course.name;
		class_hours = course.class_hours;
		specified_term = course.specified_term;
	}
	std::string id;
	std::string name;
	int class_hours = 0;
	int specified_term = 0;
	friend std::istream& operator>>(std::istream& stream, Course& course);
};

std::istream& operator>>(std::istream& stream, Course& course) {
	stream >> course.id;
	stream >> course.name;
	stream >> course.class_hours;
	stream >> course.specified_term;
	return stream;
}


//The Graph Class
class Graph {
private:
	Course courses[MAX_COURSE_NUMBER];
public:
	int totalCourses = 0;
	int currentCourse = 0;
	std::string plan[TERMS][5][10];

	void AddCourse(const Course& course) {  //Add a point to the graph
		courses[totalCourses] = course;
		totalCourses++;
	}

	void AddEdges(const std::string& pre) {  //Add a edge to the graph
		for (int i = 0; i < totalCourses; i++) {
			if (courses[i].id == pre) {
				edges[currentCourse][i] = true;
				return;
			}
		}
		std::cout << "Prerequisites Non-existent!" << std::endl;
		exit(0);
	}

	bool CourseScheduling(const Course& course) {  //Course Scheduling
		int hours = course.class_hours;
		int terms = course.specified_term;
		if (hours <= 2 || hours >= 7) {
			std::cout << "Sorry. Course Scheduling for Class Hours<=2 or >=7 have not been implemented. " << std::endl;
			exit(0);
		}
		for (int term = 0; term < 8; term++) {
			bool break_flag = false;
			if (terms != 0) {
				term = terms - 1;
				break_flag = true;
			}
			if (courses_each_term[term] <= 0) {
				if (break_flag == false) {
					continue;
				}
				else {
					break;
				}
			}
			for (int day = 0; day < 5; day++) {
				int next = (day + 2) % 5;
				if (hours == 3) {
					if (plan[term][day][2].empty() && plan[term][day][3].empty() && plan[term][day][4].empty()) {
						plan[term][day][2] = course.name;
						plan[term][day][3] = course.name;
						plan[term][day][4] = course.name;
						courses_each_term[term]--;
						return true;
					}
					if (plan[term][day][7].empty() && plan[term][day][8].empty() && plan[term][day][9].empty()) {
						plan[term][day][7] = course.name;
						plan[term][day][8] = course.name;
						plan[term][day][9] = course.name;
						courses_each_term[term]--;
						return true;
					}
				}
				if (hours == 4) {
					while (next < 5) {
						if (plan[term][day][0].empty() && plan[term][day][1].empty() && plan[term][next][0].empty() && plan[term][next][1].empty()) {
							plan[term][day][0] = course.name;
							plan[term][day][1] = course.name;
							plan[term][next][0] = course.name;
							plan[term][next][1] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][5].empty() && plan[term][day][6].empty() && plan[term][next][5].empty() && plan[term][next][6].empty()) {
							plan[term][day][5] = course.name;
							plan[term][day][6] = course.name;
							plan[term][next][5] = course.name;
							plan[term][next][6] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][0].empty() && plan[term][day][1].empty() && plan[term][next][5].empty() && plan[term][next][6].empty()) {
							plan[term][day][0] = course.name;
							plan[term][day][1] = course.name;
							plan[term][next][5] = course.name;
							plan[term][next][6] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][5].empty() && plan[term][day][6].empty() && plan[term][next][0].empty() && plan[term][next][1].empty()) {
							plan[term][day][5] = course.name;
							plan[term][day][6] = course.name;
							plan[term][next][0] = course.name;
							plan[term][next][1] = course.name;
							courses_each_term[term]--;
							return true;
						}
						next++;
					}
				}
				if (hours == 5) {
					while (next < 5) {
						if (plan[term][day][2].empty() && plan[term][day][3].empty() && plan[term][day][4].empty() && plan[term][next][0].empty() && plan[term][next][1].empty()) {
							plan[term][day][2] = course.name;
							plan[term][day][3] = course.name;
							plan[term][day][4] = course.name;
							plan[term][next][0] = course.name;
							plan[term][next][1] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][7].empty() && plan[term][day][8].empty() && plan[term][day][9].empty() && plan[term][next][5].empty() && plan[term][next][6].empty()) {
							plan[term][day][7] = course.name;
							plan[term][day][8] = course.name;
							plan[term][day][9] = course.name;
							plan[term][next][5] = course.name;
							plan[term][next][6] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][7].empty() && plan[term][day][8].empty() && plan[term][day][9].empty() && plan[term][next][0].empty() && plan[term][next][1].empty()) {
							plan[term][day][7] = course.name;
							plan[term][day][8] = course.name;
							plan[term][day][9] = course.name;
							plan[term][next][0] = course.name;
							plan[term][next][1] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][2].empty() && plan[term][day][3].empty() && plan[term][day][4].empty() && plan[term][next][5].empty() && plan[term][next][6].empty()) {
							plan[term][day][2] = course.name;
							plan[term][day][3] = course.name;
							plan[term][day][4] = course.name;
							plan[term][next][5] = course.name;
							plan[term][next][6] = course.name;
							courses_each_term[term]--;
							return true;
						}
						next++;
					}
				}
				if (hours == 6) {
					while (next < 5) {
						if (plan[term][day][2].empty() && plan[term][day][3].empty() && plan[term][day][4].empty() && plan[term][next][2].empty() && plan[term][next][3].empty() && plan[term][next][4].empty()) {
							plan[term][day][2] = course.name;
							plan[term][day][3] = course.name;
							plan[term][day][4] = course.name;
							plan[term][next][2] = course.name;
							plan[term][next][3] = course.name;
							plan[term][next][4] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][2].empty() && plan[term][day][3].empty() && plan[term][day][4].empty() && plan[term][next][7].empty() && plan[term][next][8].empty() && plan[term][next][9].empty()) {
							plan[term][day][2] = course.name;
							plan[term][day][3] = course.name;
							plan[term][day][4] = course.name;
							plan[term][next][7] = course.name;
							plan[term][next][8] = course.name;
							plan[term][next][9] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][7].empty() && plan[term][day][8].empty() && plan[term][day][9].empty() && plan[term][next][7].empty() && plan[term][next][8].empty() && plan[term][next][9].empty()) {
							plan[term][day][7] = course.name;
							plan[term][day][8] = course.name;
							plan[term][day][9] = course.name;
							plan[term][next][7] = course.name;
							plan[term][next][8] = course.name;
							plan[term][next][9] = course.name;
							courses_each_term[term]--;
							return true;
						}
						if (plan[term][day][7].empty() && plan[term][day][8].empty() && plan[term][day][9].empty() && plan[term][next][2].empty() && plan[term][next][3].empty() && plan[term][next][4].empty()) {
							plan[term][day][7] = course.name;
							plan[term][day][8] = course.name;
							plan[term][day][9] = course.name;
							plan[term][next][2] = course.name;
							plan[term][next][3] = course.name;
							plan[term][next][4] = course.name;
							courses_each_term[term]--;
							return true;
						}
						next++;
					}
				}
			}
			if (break_flag == true) {
				break;
			}
		}
		return false;
	}

	void TopologicalSort() {  //Sort the Courses to a proper order
		int temp_course = 0;
		bool chosen[MAX_COURSE_NUMBER] = { false };
		for (int k = 0; k < totalCourses; k++) {
			for (int i = 0; i < totalCourses; i++) {
				if (chosen[i] == false) {
					bool break_flag = false;
					for (int j = 0; j < totalCourses; j++) {
						if (edges[i][j] != false) {
							break_flag = true;
							break;
						}
					}
					if (break_flag == true) {
						continue;
					}
					for (int j = 0; j < totalCourses; j++) {
						edges[j][i] = false;
					}
					if (!CourseScheduling(courses[i])) {
						continue;
					}
					chosen[i] = true;
					temp_course++;
					break;
				}
			}
		}
		if (temp_course < totalCourses) {
			std::cout << "Topological Sort Failed!" << std::endl;
			exit(0);
		}
	}
};
#endif
