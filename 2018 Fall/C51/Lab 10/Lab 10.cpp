/*File Name: Lab 10.cpp
Author: Trinity Caitlin Atayan Belen
Description: The class Fraction will store a fractional value.*/

#include <iostream>
using namespace std;

class Fraction {
private:
	int num;
	int den;

public:

	//General Constructor
	Fraction(int numValue, int denValue) {
		while (den == 0||cin.fail()) {
			cout << "Invalid denominator! Please re-enter denominator: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> denValue;
		}
		num = numValue;
		den = denValue;
	};
	
	//Default Constructor
	Fraction() {
		num = 1;
		den = 1;
	};

	//the accessors
	int getNum() {
		return num;
	};

	int getDen() {
		return den;
	};

	//the mutators
	void setNum(int newNum) {
		 num = newNum;
	}

	void setDen(int newDen) {
		while (newDen == 0 || cin.fail()) {
			cout << "Invalid denominator! Please re-enter denominator: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> newDen;
		}
		den = newDen;
	};

	//Function to print the fraction as num/den
	void print() {
		cout << "The fraction is " << num << "/" << den << ".\n" << endl;
	}

	//Function to get the decimal of the fraction
	double getDecimal() {
		double decimal;
		decimal = double (num) / double (den);
		return decimal;
	}
};

int main() {
	int num, den;
	double decimal;
	Fraction object(6,10);
	object.print();

	Fraction fr[3];

	for (int i = 0; i < 3; i++) {
		cout << "Enter your numerator: ";
		cin >> num;

		fr[i].setNum(num);

		cout << "Enter your denominator: ";
		cin >> den;
		fr[i].setDen(den);
		cout << endl;

		fr[i].getDecimal();
	}

	//The general constructor, that's initialized to 6/10, is not included when finding the largest numerator, denominator, and decimal equivalent
	if (fr[0].getNum() > fr[1].getNum() && fr[0].getNum() > fr[2].getNum())
	{
		cout << fr[0].getNum() << " is the highest numerator!" << endl;
	}

	else if (fr[1].getNum() > fr[0].getNum() && fr[1].getNum() > fr[2].getNum())
	{
		cout << fr[1].getNum() << " is the highest numerator!" << endl;
	}

	else if (fr[2].getNum() > fr[0].getNum() && fr[2].getNum() > fr[0].getNum())
	{
		cout << fr[2].getNum() << " is the highest numerator!" << endl;
	}

	if (fr[0].getDen() > fr[1].getDen() && fr[0].getDen() > fr[2].getDen())
	{
		cout << fr[0].getDen() << " is the highest denominator!" << endl;
	}

	else if (fr[1].getDen() > fr[0].getDen() && fr[1].getDen() > fr[2].getDen())
	{
		cout << fr[1].getDen() << " is the highest denominator!" << endl;
	}

	else if (fr[2].getDen() > fr[0].getDen() && fr[2].getDen() > fr[0].getDen())
	{
		cout << fr[2].getDen() << " is the highest denominator!" << endl;
	}

	if (fr[0].getDecimal() > fr[1].getDecimal() && fr[0].getDecimal() > fr[2].getDecimal())
	{
		decimal = fr[0].getDecimal();
	}

	else if (fr[1].getDecimal() > fr[0].getDecimal() && fr[1].getDecimal() > fr[2].getDecimal())
	{
		decimal = fr[1].getDecimal();
	}

	else if (fr[2].getDecimal() > fr[0].getDecimal() && fr[2].getDecimal() > fr[1].getDecimal())
	{
		decimal = fr[2].getDecimal();
	}

	cout << decimal << " is the highest decimal!" << endl;
	system("pause");
}