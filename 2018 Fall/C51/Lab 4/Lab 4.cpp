/*File:Project 2.cpp
Author: Trinity Caitlin Atayan Belen
Description: My solution to COMP 51 Lab 4: Interest Rates.
It asks users about their balance and interest rate(s) and tells them how much balance they would have.*/

#include <iostream>
#include <string>
#include <iomanip> 
using namespace std;

//Here is my only integer for this lab.
int numYears;

//Here are my doubles.
double maxRate;
double minRate;
double num1;
double num2;
double interestRate;
double balance;
double initialBalance;

int main() {
	//The balance, interest rate, and years are used to calculcate a new balance. 
	cout << "Please enter your initial balance: ";
	cin >> balance;
	initialBalance = balance;
	cout << "Please enter the interest rate: ";
	cin >> interestRate;
	cout << "Please enter the number of years you plan to save: ";
	cin >> numYears;

	//Loop Body; It calculates the balance after a number of years.
	for (int i = 0; i < numYears; i++) {
		balance = balance * (1 + interestRate / 100.0);
	}
	cout << "Your balance after " << numYears << " years will be $" << balance << "." << endl;
	cout << endl;

	//Input for interest rates
	cout << "Let's see how different interest rates affect your balance after one year..." << endl;
	cout << "Please enter your minimum and maximum rate: " << endl;
	cin >> num1;
	cin >> num2;
	cout << endl;

	//What the maximum and minimum rate will be if num1 is greater than num2.
	if (num1 < num2) {
		maxRate = num2;
		minRate = num1;
	}

	//A swap between the maximum and minimum rate just in case the user puts them in a different order.
	else {
		maxRate = num1;
		minRate = num2;
	} 

	//Loop Body; It calculates the use's account valance after one year at the specified interest rate.
	for (double i = minRate; i <= maxRate; i += 0.5) {
		cout.setf(ios::fixed);
		cout.precision(2);
		balance = initialBalance * (1 + i / 100.0);
		cout << i << ": " << setw(3) << "$" << balance << endl;
	}

system("pause");

}