#include "07.h"

int main() {
	int total_number;
	int answer = 0;
	//Read in N
	while (true) {
		std::cin >> total_number;
		if (std::cin.fail() != true && total_number > 0 && total_number <= 10000) {
			break;
		}
		//Reset and clear the input stream if input data is incorrect.
		std::cin.clear();
		std::cin.sync();
		std::cout << std::endl;
		std::cout << "Please enter as required! " << std::endl;
	}
	//Read in the numbers
	int numbers[10000];
	for (int i = 0; i < total_number; i++) {
		int temp;
		while (true) {
			std::cin >> temp;
			if (std::cin.fail() != true && temp > 0) {
				break;
			}
			//Reset and clear the input stream if input data is incorrect.
			std::cin.clear();
			std::cin.sync();
			std::cout << std::endl;
			std::cout << "Please enter as required! " << std::endl;
		}
		numbers[i] = temp;
	}
	//Bubble Sort
	for (int i = 0; i < total_number - 1; i++) {
		for (int j = 0; j <= total_number - 1 - i; j++) {
			if (numbers[j] < numbers[j + 1]) {
				int tmp;
				tmp = numbers[j + 1];
				numbers[j + 1] = numbers[j];
				numbers[j] = tmp;
			}
		}
	}
	//Calculate the minimum total cost
    for (int i = total_number - 1; i >= 1; i--) {
        numbers[i - 1] = numbers[i] + numbers[i - 1];
        answer += numbers[i - 1];
        int j = i - 1;
        while (j > 0 && numbers[j - 1] < numbers[j]) {
            int tmp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = tmp;
            j--;
        }
    }
    //Print the answer
    std::cout << answer << std::endl;
    std::cin.clear();
    std::cin.sync();
    std::cout << "Press any key to exit..." << std::endl;
    getchar();
    return 0;
}
	
 
