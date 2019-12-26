#include "05.h"
#define MAX_NUMBERS 1000

int main() {
	std::cout << "Please enter your integers divided by a space, the first integer is to indicate the total number of following integers." << std::endl;
	std::cout << "The first integer must be no more than 1000. " << std::endl;
	//Read the input numbers
	int N;
	int queue_A[MAX_NUMBERS], queue_B[MAX_NUMBERS];
	int A = 0, B = 0, a = 0, b = 0;
	std::cin >> N;
	if (std::cin.fail() == true || N > MAX_NUMBERS || N <= 0) {
		std::cout << "The First integer N must be 0<N<=1000!" << std::endl;
		std::cout << "Press any key to exit..." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getchar();
		return 0;
	}
	for (int i = 0; i < N; i++) {
		int temp;
		std::cin >> temp;
		if (std::cin.fail() == true || N > MAX_NUMBERS || N <= 0) {
			std::cout << "Please enter as required! " << std::endl;
			std::cout << "Press any key to exit..." << std::endl;
			std::cin.clear();
			std::cin.sync();
			getchar();
			return 0;
		}
		if ((temp & 1) != 0) {
			queue_A[A] = temp;
			A++;
		}
		else {
			queue_B[B] = temp;
			B++;
		}
	}
	while (a < A && b < B) {
		if (N != 1) {
			std::cout << queue_A[a] << " ";
			N--;
			a++;
		}
		else {
			//To make sure there is no extra space in the end of the line, the same below
			std::cout << queue_A[a];
			a++;
		}
		if (a < A) {
			if (N != 1) {
				std::cout << queue_A[a] << " ";
				N--;
				a++;
			}
			else {
				std::cout << queue_A[a];
				a++;
			}
		}
		if (N != 1) {
			std::cout << queue_B[b] << " ";
			N--;
			b++;
		}
		else {
			std::cout << queue_B[b];
			b++;
		}
	}
	while (a < A) {
		if (N != 1) {
			std::cout << queue_A[a] << " ";
			N--;
			a++;
		}
		else {
			std::cout << queue_A[a];
			a++;
		}
	}
	while (b < B) {
		if (N != 1) {
			std::cout << queue_B[b] << " ";
			N--;
			b++;
		}
		else {
			std::cout << queue_B[b];
			b++;
		}
	}
	std::cout << std::endl;
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.clear();
	std::cin.sync();
	getchar();
	return 0;
}
