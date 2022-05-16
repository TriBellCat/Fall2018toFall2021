/*File: Lab 3.cpp
Author: Trinity Caitlin Atayan Belen
Description: My solution to COMP 51 Lab 3: Calculator Revisited.
It is a modified version of the calculator from Lab 2.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int num1, num2, answer, compNum, numStars;
	char star = '*';
	int counter = 0;
	char operation;
	bool loopback = true;
	cout << "Welcome to my calculator!" << endl;

		do {
		//List of menu choices
		cout << "Please select an operation from the following list:" << endl;
		cout << "(A)dd" << endl;
		cout << "(S)ubtraction" << endl;
		cout << "(M)ultiply" << endl;
		cout << "(D)ivide" << endl;
		cout << "(C)ompare" << endl;
		cout << "(R)andom" << endl;
		cout << "S(t)ars" << endl;
		cout << "(Q)uit" << endl;
		cin >> operation;
		
			switch (operation) {

			//Addition
			case 'a':
			case 'A':
				cout << "Please enter two numbers." << endl;
				cin >> num1 >> num2;
				answer = num1 + num2;
				cout << "The sum is " << answer << "." << endl;
				break;

			// Subtraction
			case 's':
			case 'S':
				cout << "Please enter two numbers." << endl;
				cin >> num1 >> num2;
				answer = num1 - num2;
				cout << "The difference is " << answer << "." << endl;
				break;

			// Multiplication
			case 'm':
			case 'M':
				cout << "Please enter two numbers." << endl;
				cin >> num1 >> num2;
				answer = num1 * num2;
				cout << "The product is " << answer << "." << endl;
				break;

			// Division
			case 'd':
			case 'D':
				cout << "Please enter two numbers." << endl;
				cin >> num1 >> num2;

				while (num2 == 0) {
					cout << "ERROR! Cannot divide by zero!" << endl;
					cout << "Please enter two numbers." << endl;
					cin >> num1 >> num2;
				}

					answer = num1 / num2;
					cout << "The quotient is " << answer << "." << endl;

				break;

			// Compare
			case 'c':
			case 'C':
				cout << "Please enter two numbers." << endl;
				cin >> num1 >> num2;
				if (num1 < num2) {
					cout << num1 << " is less than " << num2 << "." << endl;
				}

				else if (num1 > num2) {
					cout << num1 << " is greater than " << num2 << "." << endl;
				}
				
				else if (num1 == num2) {
					cout << num1 << " is equal to " << num2 << "." << endl;
				}
				break;

			// Random
			case 'r':
			case 'R':
				srand((unsigned)time(0)); //Seed randodm number generator
				cout << "Please enter the range of numbers you want to be used, from the smallest number to the biggest." << endl;
				cin >> num1 >> num2;
				while (num1 > num2) {
					cout << "Invalid!" << endl;
					cout << "Please enter the range of numbers you want to be used, from the smallest number to the biggest." << endl;
					cin >> num1 >> num2;
				}
				
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
				
				break;

			// Display the Number of Stars
			case 't':
			case 'T':
				cout << "Please enter the number of stars to display: ";
				cin >> numStars;

				while (numStars < 0) {
						cout << "Error!" << endl;
						cout << "Please enter the number of stars to display: ";
						cin >> numStars;
				}

				while (counter < numStars) {
					cout << star;
					counter++;
				} 
				cout << endl;
					break;

			// Quit
			case 'q':
			case 'Q':
				loopback = false;
				cout << "Goodbye." << endl;
				break;

			// Invalid menu choice
			default:
				cout << "Error!" << endl;
			}

		} while (loopback);

	system("pause");
}