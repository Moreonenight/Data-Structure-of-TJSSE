#include "04.h"
#define MAX_NUMBERS 1000

int main() {
	while (true) {
		std::cout << "Please enter a infix arithmetic expression, this program will evaluate it for you. " << std::endl;
		std::cout << "Example: -2*(3+5)+2^3/4=. Do not enter any space. Only enter integers. " << std::endl;
		std::cout << "Supported operators: *, +, ^, /, %, (, ), -, and any other operator will result in a error. Overflows may result in errors or wrong answers. " << std::endl;
		//Read the input expression
		std::string expression;
		while (true) {
			std::cin >> expression;
			bool is_expression_fail = false;
			for (std::string::iterator i = expression.begin(); i != expression.end(); i++) {
				if ((*i >= '0' && *i <= '9') || *i == '*' || *i == '+' || *i == '^' || *i == '/' || *i == '%' || *i == '(' || *i == ')' || *i == '-' || *i == '=') {
					continue;
				}
				is_expression_fail = true;
			}
			if (std::cin.fail() != true && is_expression_fail == false) {
				std::cin.clear();
				std::cin.sync();
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			std::cout << "Wrong expression, please re-enter a correct expression!" << std::endl;
		}
		if (*(expression.end() - 1) != '=') {
			expression += "=";
		}

		//Convert the input infix arithmetic expression into a suffix arithmetic expression
		std::string string_stack = "=";  //std::string can be used as Stack<char>, for there are pop_back() and push_back()
		std::string result_expression;
		bool is_reading_number = false;
		bool unary_operator = true;
		for (std::string::iterator i = expression.begin(); i != expression.end(); i++) {
			if (*i >= '0' && *i <= '9') {
				is_reading_number = true;
				unary_operator = false;
				result_expression.push_back(*i);
				continue;
			}
			if (unary_operator == true) {
				if (*i == '+') {
					continue;
				}
				if (*i == '-') {
					result_expression.push_back('.');
					continue;
				}
			}
			if (is_reading_number == true) {
				is_reading_number = false;
				result_expression.push_back('#');
			}
			if (unary_operator == false) {
				if (*i != '(' && *i != ')') {
					unary_operator = true;
				}
			}
			char top = *(string_stack.end() - 1);
			while (icp(*i) < isp(top)) {
				result_expression.push_back(top);
				string_stack.pop_back();
				top = *(string_stack.end() - 1);
			}
			if (icp(*i) > isp(top)) {
				string_stack.push_back(*i);
				continue;
			}
			if (icp(*i) == isp(top)) {
				string_stack.pop_back();
				continue;
			}
		}
		//Evaluate the suffix arithmetic expression
		int is_positive = 1;
		long long stack_int[MAX_NUMBERS];
		int stack_pointer = 0;
		int current_number = 0;
		int number_counter = 0;
		bool is_evaluation_fail = false;
		for (std::string::iterator i = result_expression.begin(); i != result_expression.end(); i++) {
			if (*i == '.') {
				is_positive = -is_positive;
				continue;
			}
			if (*i >= '0' && *i <= '9') {
				current_number = current_number * 10 + (*i - '0');
				number_counter++;
				if (number_counter >= 10) {
					std::cout << "Too big integers! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				continue;
			}
			if (*i == '#') {
				stack_int[stack_pointer] = (long long)current_number * is_positive;
				current_number = 0;
				number_counter = 0;
				is_positive = 1;
				stack_pointer++;
				continue;
			}
			if (*i == '+') {
				if (stack_pointer < 2) {
					std::cout << "Ill-formed expression, please re-enter an accurate expression! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_int[stack_pointer - 2] += stack_int[stack_pointer - 1];
				if (stack_int[stack_pointer - 2] >= INT_MAX || stack_int[stack_pointer - 2] <= -INT_MAX) {
					std::cout << "Math Overflow! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_pointer--;
				continue;
			}
			if (*i == '-') {
				if (stack_pointer < 2) {
					std::cout << "Ill-formed expression, please re-enter an accurate expression! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_int[stack_pointer - 2] -= stack_int[stack_pointer - 1];
				if (stack_int[stack_pointer - 2] >= INT_MAX || stack_int[stack_pointer - 2] <= -INT_MAX) {
					std::cout << "Math Overflow! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_pointer--;
				continue;
			}
			if (*i == '*') {
				if (stack_pointer < 2) {
					std::cout << "Ill-formed expression, please re-enter an accurate expression! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_int[stack_pointer - 2] *= stack_int[stack_pointer - 1];
				if (stack_int[stack_pointer - 2] >= INT_MAX || stack_int[stack_pointer - 2] <= -INT_MAX) {
					std::cout << "Math Overflow! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_pointer--;
				continue;
			}
			if (*i == '/') {
				if (stack_pointer < 2) {
					std::cout << "Ill-formed expression, please re-enter an accurate expression! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				if (stack_int[stack_pointer - 1] == 0) {
					std::cout << "Math Error: Divided by 0! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_int[stack_pointer - 2] /= stack_int[stack_pointer - 1];
				if (stack_int[stack_pointer - 2] >= INT_MAX || stack_int[stack_pointer - 2] <= -INT_MAX) {
					std::cout << "Math Overflow! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_pointer--;
				continue;
			}
			if (*i == '%') {
				if (stack_pointer < 2) {
					std::cout << "Ill-formed expression, please re-enter an accurate expression! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_int[stack_pointer - 2] %= stack_int[stack_pointer - 1];
				if (stack_int[stack_pointer - 2] >= INT_MAX || stack_int[stack_pointer - 2] <= -INT_MAX) {
					std::cout << "Math Overflow! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_pointer--;
				continue;
			}
			if (*i == '^') {
				if (stack_pointer < 2) {
					std::cout << "Ill-formed expression, please re-enter an accurate expression! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				if (stack_int[stack_pointer - 1] >= 1) {
					int temp = stack_int[stack_pointer - 2];
					for (long long i = 1; i < stack_int[stack_pointer - 1]; i++) {
						stack_int[stack_pointer - 2] *= temp;
						if (stack_int[stack_pointer - 2] >= INT_MAX || stack_int[stack_pointer - 2] <= -INT_MAX) {
							std::cout << "Math Overflow! " << std::endl;
							is_evaluation_fail = true;
							break;
						}
					}
				}
				else if (stack_int[stack_pointer - 1] == 0) {
					if (stack_int[stack_pointer - 2] != 0) {
						stack_int[stack_pointer - 2] = 1;
					}
					else {
						std::cout << "Math Error: 0^0" << std::endl;
						is_evaluation_fail = true;
						break;
					}
				}
				else {
					std::cout << "Math Error: Powering by a Negative Integer(eg: 12^(-5))is NOT Supported! " << std::endl;
					is_evaluation_fail = true;
					break;
				}
				stack_pointer--;
				continue;
			}
		}

		//Print the evaluation
		if (stack_pointer == 1 && is_evaluation_fail == false) {
			std::cout << stack_int[0] << std::endl;
		}
		else if (is_evaluation_fail == false) {
			std::cout << "Ill-formed expression, please re-enter an accurate expression! " << std::endl;
		}
		char option;
		while (true) {
			std::cout << std::endl;
			std::cout << "Do you want to evaluate another expression? (Y/N) ";
			std::cin >> option;
			if (std::cin.fail() != true && (option == 'N' || option == 'n' || option == 'Y' || option == 'y')) {
				std::cin.clear();
				std::cin.sync();
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			std::cout << "Please enter Y or N !" << std::endl;
		}
		if (option == 'y' || option == 'Y') {
			std::cout << std::endl;
			continue;
		}
		return 0;
	}
	return 0;
}
