/*File Name: Lab 11 - Sorting.cpp
Author: Trinity Caitlin Atayan Belen
Description: The program will create 200 products, assign them random prices,
and then sorts them based on their price from low to high.*/

#include<iostream>
#include <iomanip>
#include<vector>
#include<chrono>
#include<ctime>
#include<utility>
using namespace std;


void printInfo(vector <pair<int, int>> numbers) {
	for (int i = 1; i <= numbers.size() - 1; ++i) {
		cout << "Item " << numbers[i].first << " " << setprecision(3) << numbers[i].second << endl;
	}
}

//Insertion Sort Function
void insertionSort(vector <pair<int, int>> & numbers) {
	int temp1 = 0, temp2 = 0;
	for (int i = 1; i <= 200; ++i) {
		int j = i;
		while (j > 0 && numbers.at(j).second < numbers.at(j - 1).second) {
			temp1 = numbers.at(j).first;
			temp2 = numbers.at(j).second;
			numbers.at(j).first = numbers.at(j - 1).first;
			numbers.at(j).second = numbers.at(j - 1).second;
			numbers.at(j - 1).first = temp1;
			numbers.at(j - 1).second = temp2;
			--j;
		}
	}
}

//The partitioning function for the quick sort function
int partition(vector <pair<int, int>> & numbers, int i, int k) {
	int l = 0;
	int h = 0;
	int midpoint = 0;
	int pivot = 0;
	int temp1 = 0, temp2 = 0;
	bool done = false;

	//Picks middle element as pivot
	midpoint = i + (k - i) / 2; 
	pivot = numbers[midpoint].second;

	l = i;
	h = k;

	while (!done) {

		//increments l while numbers[1] is less than pivot
		while (numbers[l].second < pivot) {
			++l;
		}

		//decrements pivot while numbers[h] is greater than pivot
		while (pivot < numbers[h].second) {
			--h;
		}

		//If there are zero or one elements remain, all numbers are partitioned
		//Then, it will eventually return h
		if (l >= h) {
			done = true;
		}

		else {

			//swaps numbers[l] and numbers[h]
			//also updates l and h
			temp1 = numbers[l].first;
			temp2 = numbers[l].second;
			numbers[l].first = numbers[h].first;
			numbers[l].second = numbers[h].second;
			numbers[h].first = temp1;
			numbers[h].second = temp2;

			++l;
			--h;
		}
	}
	return h;
}

//Quick Sort Function
void quickSort(vector <pair<int, int>>& numbers, int i, int k) {
	int j = 0;
	if (i >= k) {
		return;
	}
	j = partition(numbers, i, k);
	quickSort(numbers, i, j);
	quickSort(numbers, j + 1, k);
}

//Merge function for merge sort
void merge(vector <pair<int, int>> & numbers, int  i, int j, int k) {
	int mergePos = 0;
	int mergedSize = k - i + 1;
	int leftPos = i;
	int rightPos = j + 1;
	int temp1, temp2;
	vector<pair<int, int>> * tempVec = new vector <pair<int,int>>(mergedSize);

	while ((leftPos <= j) && (rightPos <= k)) {
		if (numbers[leftPos].second < numbers[rightPos].second) {
			tempVec->at(mergePos).first = numbers[leftPos].first;
			tempVec->at(mergePos).second = numbers[leftPos].second;
			leftPos++;
		}

		else {
			tempVec->at(mergePos).first = numbers[rightPos].first;
			tempVec->at(mergePos).second = numbers[rightPos].second;
			rightPos++;
		}

		mergePos++;
	}

	while (leftPos <= j) {
		tempVec->at(mergePos).first = numbers[leftPos].first;
		tempVec->at(mergePos).second = numbers[leftPos].second;
		leftPos++;
		mergePos++;
	}

	while (rightPos <= k) {
		tempVec->at(mergePos).first = numbers[rightPos].first;
		tempVec->at(mergePos).second = numbers[rightPos].second;
		rightPos++;
		mergePos++;
	}

	for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
		numbers[i + mergePos].first = tempVec->at(mergePos).first;
		numbers[i + mergePos].second = tempVec->at(mergePos).second;
	}
}

void mergeSort(vector <pair<int, int>> & numbers, int first, int last) {
	int middle = 0;
	
	if (first < last) {
		middle = (first + last) / 2;

		mergeSort(numbers, first, middle);
		mergeSort(numbers, middle + 1, last);
		merge(numbers, first, middle,last);
	}
}

//Returns the length of value in digihts
int radixGetLength(int value) {
	if (value == 0) {
		return 1;
	}

	int digits = 0;

	while (value != 0) {
		digits = digits + 1;
		value = value / 10;
	}
	
	return digits;
}

//Returns the maximum length out of all elements in the array in number of digits
int radixGetMaxLength(vector <pair<int, int>> & numbers, int size) {
	int maxDigits = 0;
	for (int i = 0; i < size; i++) {
		int digitCount = radixGetLength(numbers.at(i).second);
		if (digitCount > maxDigits) {
			maxDigits = digitCount;
		}
	}
	return maxDigits;
}


//Function for radix sort
void radixSort(vector <pair<int, int>> & numbers, int size) {
	vector< vector<pair<int, int>>> bucket(10); //a list of 10 buckets

	//Finds the max length in number of digits
	int maxDigits = radixGetMaxLength(numbers, size);

	//Starts with the least significant digit
	int powTen = 1;

	for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
		for (int i = 0; i < numbers.size(); i++) {
			int bucketIndex = abs(numbers[i].second / powTen) % 10; 
			bucket[bucketIndex].push_back(numbers[i]);  
		}

		int arrayIndex = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < bucket[i].size(); j++) {
				numbers[arrayIndex++] = bucket[i][j];
			}
		}
		powTen = 10 * powTen;

		// Clear the buckets
		for (int i = 0; i < bucket.size(); i++) {
			if (!bucket[i].empty()) {
				bucket[i].clear();
			}
		}
	}


}

int main() {
	pair<int, int> productPair;
	vector <pair<int, int>> productPrice(200+1);
	const int NUMBERS_SIZE = 200;
	int choice, price;
	srand(time(0));

	//Creates 200 products and then assign them random prices from 1 to 500
	for (int i = 1; i < productPrice.size(); i++)
	{
		price = rand() % 500;
		productPair = make_pair(i, price);
		productPrice.at(i) = productPair;
	}
	
	cout << "1) Insertion Sort" << endl;
	cout << "2) Quick Sort" << endl;
	cout << "3) Merge Sort" << endl;
	cout << "4) Radix Sort" << endl;

	cout << "Which type of sorting do you like to try? ";
	cin >> choice;
	cout << endl;

	if (choice == 1) {
		auto start = std::chrono::high_resolution_clock::now();
		insertionSort(productPrice);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>elapsed = finish - start;
		cout << "Elasped time: " << elapsed.count() << endl;
		printInfo(productPrice);
	}

	if (choice == 2) {
		auto start = std::chrono::high_resolution_clock::now();
		quickSort(productPrice, 0, NUMBERS_SIZE);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>elapsed = finish - start;
		cout << "Elasped time: " << elapsed.count() << endl;
		printInfo(productPrice);
	}

	if (choice == 3) {
		auto start = std::chrono::high_resolution_clock::now();
		mergeSort(productPrice, 0, NUMBERS_SIZE);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>elapsed = finish - start;
		cout << "Elasped time: " << elapsed.count() << endl;
		printInfo(productPrice);
	}

	if (choice == 4) {
		auto start = std::chrono::high_resolution_clock::now();
		radixSort(productPrice, NUMBERS_SIZE);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>elapsed = finish - start;
		cout << "Elasped time: " << elapsed.count() << endl;
		printInfo(productPrice);
	}

	system("pause");
}