/*File Name: Lab 11.cpp
Author: Trinity Caitlin ATyan Belen
Description: The main function will call my recursive functions and display the results.*/

#include <iostream>
#include <ctime>
using namespace std;

//Adds numbers between 0 and x
int sumX(int x) {
	if (x == 0) {
		return 0;
	}

	if (x > 0) {
		return (x + sumX(x - 1));
	}

	else {
		return (x + sumX(x + 1));
	}
}

//Adds numbers between x and y
int sumXY(int x, int y) {
	if (x == y) {
		return x;
	}

	if (y > x) {
		return (y + sumXY(x, y - 1));
	}

	else {
		return (x + sumXY(x - 1, y));
	}
}

//Generates a random number (between 0 and 10) in the array
void fillArray(int arr[], int size) {
	if (size == 0) {
		return;
	}
	arr[size - 1] = 0 + rand() % 11; //Generates numbers between 0 and 10
	fillArray(arr, size - 1);
}

int main() {
	int arr[5];
	srand(time(NULL));

	cout << "Sum of numbers between 0 and x" << endl;
	cout << sumX(0) << endl;
	cout << sumX(5) << endl;
	cout << sumX(-5) << "\n" << endl;
	
	cout << "Sum of the numbers between x and y" << endl;
	cout << sumXY(5, 5) << endl;
	cout << sumXY(5, 2) << endl;
	cout << sumXY(5, 8) << "\n" << endl;

	cout << "The numbers randomly generated betweewn 0 and 10 in the arrays" << endl;
	fillArray(arr, 5);
	
	//The for loop displays the number generated in the array
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << endl;
	}
	system("pause");
}