#ifndef _10_H_
#define _10_H_
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#define MAX_NUMBERS 100000

int numbers[MAX_NUMBERS];
int working_numbers[MAX_NUMBERS];
int merge_working_numbers[MAX_NUMBERS]; //For Merge Sort
int radix_working_numbers[MAX_NUMBERS]; //For Radix Sort

void bubble_sort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	int tmp;
	long long operation_times = 0;
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number - i - 1; j++) {
			operation_times++;
			if (working_numbers[j] > working_numbers[j + 1]) {
				tmp = working_numbers[j];
				working_numbers[j] = working_numbers[j + 1];
				working_numbers[j + 1] = tmp;
			}
		}
	}
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Bubble Sort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Bubble Sort Operation Times: " << operation_times << std::endl;
}

void selection_sort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	int tmp, max;
	long long operation_times = 0;
	for (int i = 0; i < number; i++) {
		max = 0;
		for (int j = 0; j < number - i - 1; j++) {
			operation_times++;
			if (working_numbers[j] > working_numbers[max]) {
				max = j;
			}
		}
		operation_times++;
		if (working_numbers[number - i - 1] < working_numbers[max]) {
			tmp = working_numbers[max];
			working_numbers[max] = working_numbers[number - i - 1];
			working_numbers[number - i - 1] = tmp;
		}
	}
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Selection Sort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Selection Sort Operation Times: " << operation_times << std::endl;
}

void insertion_sort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	int tmp;
	long long operation_times = 0;
	for (int i = 0; i < number; i++) {
		int j = i - 1;
		tmp = working_numbers[i];
		while (j >= 0 && tmp < working_numbers[j]) {
			working_numbers[j + 1] = working_numbers[j];
			operation_times++;
			j--;
		}
		working_numbers[j + 1] = tmp;
	}
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Insertion Sort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Insertion Sort Operation Times: " << operation_times << std::endl;
}

void shellsort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	int step = number >> 1;
	int tmp, j;
	long long operation_times = 0;
	while (step > 0) {
		for (int i = step; i < number; i++) {
			tmp = working_numbers[i];
			for (j = i - step; j >= 0 && working_numbers[j] > tmp; j -= step) {
				operation_times++;
				working_numbers[j + step] = working_numbers[j];
			}
			working_numbers[j + step] = tmp;
		}
		step >>= 1;
	}
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Shellsort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Shellsort Operation Times: " << operation_times << std::endl;
}

//Quicksort
int part_sort(const int low, const int high, long long* operation_times) {
	int temp = low;
	int temp_number = working_numbers[low];
	for (int i = low + 1; i <= high; i++) {
		if (working_numbers[i] < temp_number) {
			temp++;
			(*operation_times)++;
			if (temp != i) {
				int temp_swap;
				temp_swap = working_numbers[i];
				working_numbers[i] = working_numbers[temp];
				working_numbers[temp] = temp_swap;

			}
		}
	}
	working_numbers[low] = working_numbers[temp];
	working_numbers[temp] = temp_number;
	return temp;
}

//Quicksort
void Quicksort(const int low, const int high, long long* operation_times) {
	if (low < high) {
		int temp = part_sort(low, high, operation_times);
		Quicksort(low, temp - 1, operation_times);
		Quicksort(temp + 1, high, operation_times);
	}
}

//Quicksort
void quicksort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	long long operation_times = 0;
	Quicksort(0, number - 1, &operation_times);
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Quicksort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Quicksort Operation Times: " << operation_times << std::endl;
}

//Heapsort
void siftDown(int start, int end, long long* times) {
	int m = start;
	int n = m * 2 + 1;
	int temp = working_numbers[m];
	while (n <= end) {
		if (n + 1 <= end && working_numbers[n] < working_numbers[n + 1]) {
			n++;
		}
		if (temp > working_numbers[n]) {
			break;
		}
		else {
			working_numbers[m] = working_numbers[n];
			m = n;
			n = m * 2 + 1;
			(*times)++;
		}
	}
	working_numbers[m] = temp;
}

//Heapsort
void heapsort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	long long operation_times = 0;
	for (int i = number / 2 - 1; i >= 0; i--) {
		siftDown(i, number - 1, &operation_times);
	}
	for (int i = number - 1; i >= 0; i--)
	{
		int tmp = working_numbers[0];
		working_numbers[0] = working_numbers[i];
		working_numbers[i] = tmp;
		siftDown(0, i - 1, &operation_times);
	}
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Heapsort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Heapsort Operation Times: " << operation_times << std::endl;
}

//Merge Sort
void Merge(int left, int mid, int right, long long* operation_times) {
	for (int i = left; i <= right; i++) {
		(*operation_times)++;
		merge_working_numbers[i] = working_numbers[i];
	}
	int m = left, n = mid + 1, t = left;
	while (m <= mid && n <= right) {
		(*operation_times)++;
		if (merge_working_numbers[m] <= merge_working_numbers[n]) {
			working_numbers[t] = merge_working_numbers[m];
			t++;
			m++;
		}
		else {
			working_numbers[t] = merge_working_numbers[n];
			t++;
			n++;
		}
	}
	while (m <= mid) {
		(*operation_times)++;
		working_numbers[t] = merge_working_numbers[m];
		t++;
		m++;
	}
	while (n <= right) {
		(*operation_times)++;
		working_numbers[t] = merge_working_numbers[n];
		t++;
		n++;
	}
}

//Merge Sort
void Merge_sort(int left, int right, long long* operation_times) {
	if (left >= right) {
		return;
	}
	(*operation_times)++;
	int mid = (left + right) / 2;
	Merge_sort(left, mid, operation_times);
	Merge_sort(mid + 1, right, operation_times);
	Merge(left, mid, right, operation_times);
};

//Merge Sort
void merge_sort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	long long operation_times = 0;
	Merge_sort(0, number - 1, &operation_times);
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Merge sort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Merge sort Operation Times: " << operation_times << std::endl;
}

//Radix Sort
int maxdigit(int number, long long* operation_times) {
	int maxData = working_numbers[0];
	for (int i = 1; i < number; ++i) {
		(*operation_times)++;
		if (maxData < working_numbers[i])
			maxData = working_numbers[i];
	}
	int digit = 1;
	int p = 10;
	while (maxData >= p) {
		p *= 10;
		digit++;
	}
	return digit;

}

//Radix Sort
void radix_sort(int number) {
	for (int i = 0; i < number; i++) {
		working_numbers[i] = numbers[i];
	}
	clock_t time_start = clock();
	long long operation_times = 0;
	int max_digit = maxdigit(number, &operation_times);
	int buckets[10] = { 0 };
	int radix = 1;
	for (int i = 1; i <= max_digit; i++) {
		for (int j = 0; j < 10; j++) {
			buckets[j] = 0;
		}
		for (int j = 0; j < number; j++) {
			int tmp = (working_numbers[j] / radix) % 10;
			buckets[tmp]++;
		}
		for (int j = 1; j < 10; j++) {
			buckets[j] = buckets[j - 1] + buckets[j];
		}
		for (int j = number - 1; j >= 0; j--) {
			operation_times++;
			int tmp = (working_numbers[j] / radix) % 10;
			radix_working_numbers[buckets[tmp] - 1] = working_numbers[j];
			buckets[tmp]--;
		}
		for (int j = 0; j < number; j++) {
			working_numbers[j] = radix_working_numbers[j];
		}
		radix *= 10;
	}
	clock_t time_end = clock();
	double time_passed = (float)(time_end - time_start) / CLOCKS_PER_SEC;
	std::cout << "Radix sort Time Cost: " << time_passed << "s" << std::endl;
	std::cout << "Radix sort Operation Times: " << operation_times << std::endl;
}
#endif
