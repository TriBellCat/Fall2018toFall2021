/*File: Lab 2.cpp
Author: Trinity Caitlin Atayan Belen
Description: My solution to COMP 51 Lab 2: Calculator.
It adds, subtracts, multiples, divides, compares, and generates numbers.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int num1, num2, answer, compNum;
	char operation;
	cout << "Welcome to my calculator!" << endl;

	cout << "Please select an operation from the following list:" << endl; //List of menu choices
	cout << "(A)dd" << endl;
	cout << "(S)ubtraction" << endl;
	cout << "(M)ultiply" << endl;
	cout << "(D)ivide" << endl;
	cout << "(C)ompare" << endl;
	cout << "(R)andom" << endl;
	cin >> operation;

	switch (operation) {

	case 'a': //Addition
	case 'A':
		cout << "Please enter two numbers." << endl;
		cin >> num1 >> num2;
		answer = num1 + num2;
		cout << "The sum is " << answer << "." << endl;
		break;

	case 's': // Subtraction
	case 'S':
		cout << "Please enter two numbers." << endl;
		cin >> num1 >> num2;
		answer = num1 - num2;
		cout << "The difference is " << answer << "." << endl;
		break;

	case 'm':
	case 'M':
		cout << "Please enter two numbers." << endl;
		cin >> num1 >> num2;
		answer = num1 * num2;
		cout << "The product is " << answer << "." << endl;
		break;

	case 'd': // Division
	case 'D':
		cout << "Please enter two numbers." << endl;
		cin >> num1 >> num2;
		if (num2 != 0) {
			answer = num1 / num2;
			cout << "The quotient is " << answer << "." << endl;
		}
		else
			cout << "ERROR! Cannot divide by zero!" << endl;
		break;

	case 'c': // Compare
	case 'C':
		cout << "Please enter two numbers." << endl;
		cin >> num1 >> num2;
		if (num1 < num2 ) {
			cout << num1 << " is less than " << num2 << "." << endl;
		}
		if (num1 > num2) {
			cout << num1 << " is greater than " << num2 << "." << endl;
		}
		if (num1 == num2) {
			cout << num1 << " is equal to " << num2 << "." << endl;
		}
		break;

	case 'r': // Random
	case 'R':
		srand((unsigned)time(0));
		cout << "Please enter the range of numbers you want to be used, from the smallest number to the biggest." << endl;
		cin >> num1 >> num2;
		if (num1 >= num2) {
			cout << "Invalid!" << endl;
		}
		if (num1 < num2) {
			cout << "The five random numbers are:" << endl;
			compNum = rand() % (num1 - num2) + num1;
			cout << compNum << endl;
			compNum = rand() % (num1 - num2) + num1;
			cout << compNum << endl;
			compNum = rand() % (num1 - num2) + num1;
			cout << compNum << endl;
			compNum = rand() % (num1 - num2) + num1;
			cout << compNum << endl;
			compNum = rand() % (num1 - num2) + num1;
			cout << compNum << endl;
		}
	break;

	default: // Invalid menu choice
		cout << "Error!" << endl;
	}

	system("pause");
}