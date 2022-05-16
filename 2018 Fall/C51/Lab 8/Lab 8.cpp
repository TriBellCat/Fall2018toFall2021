/*File Name: Lab 8.cpp
Author: Trinity Caitlin Atayan Belen
Description: In this lab, the program gets data (and put in a text file) about the months of birth
and exam scores to find out whether or not the smartest students are born in July.*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Function for getting data
void getData() {
	ofstream outStream;
	int monthBirth;
	double examScore;
	char anotherStudent;
	
	outStream.open("scores.txt");//it'll create a file

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	do {
		cout << "What is the month of your birthday (in number)? ";
		cin >> monthBirth;
		cout << "What is your exam score? ";
		cin >> examScore;

		outStream <<  monthBirth << " " << examScore << endl;

		cout << "Is there another student? (Y/N) ";
		cin >> anotherStudent;
	} while (anotherStudent == 'y' || anotherStudent == 'Y');
	outStream.close();
}

//Function for analyzing data
void analyzeData() {
	int julyCount = 0, otherCount = 0;
	double scoreJuly = 0, scoreOther = 0, examScore, avgJuly = 0, avgOther = 0;
	int monthBirth;	
	ifstream inStream;
	inStream.open("scores.txt"); //it'll read the file

	if (inStream.fail()) {
		cout << "Cannot open file" << endl;
		system("pause");
	}

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	//the instream reads monthBirth and examScore as TWO different things
	while (inStream >> monthBirth >> examScore) {
		if (monthBirth == 7) {
			julyCount++;
			scoreJuly += examScore;
			avgJuly = scoreJuly / julyCount;
		}
		if (monthBirth != 7) {
			otherCount++;
			scoreOther += examScore;
			avgOther = scoreOther / otherCount;
		}
	}

	if (avgJuly > avgOther) {
		cout << "Your theory seems right, Doctor!" << endl;
	}

	else {
		cout << "Time for a new theory, Doctor!" << endl;
	}

	cout << "Avg. Score for July Students: " << avgJuly << endl;
	cout << "Avg. Score for Other Students: " << avgOther << endl;
	cout << endl;

	inStream.close();
}

//Function for appending data
void appendData () {
	ofstream outStream;
	int monthBirth;
	double examScore;
	char anotherStudent;

	outStream.open("scores.txt", ios::app);

	if (outStream.fail()) {
		cout << "Cannot open file" << endl;
		system("pause");
	}

	do {
		cout << "What is the month of your birthday (in number)? ";
		cin >> monthBirth;
		cout << "What is your exam score? ";
		cin >> examScore;

		outStream << monthBirth << " " << examScore << endl;

		cout << "Is there another student? (Y/N) ";
		cin >> anotherStudent;
	} while (anotherStudent == 'y' || anotherStudent == 'Y');

	outStream.close();
}
int main() {
	int choice;

	do {
		cout << "1. Create new data file" << endl;
		cout << "2. Append to existing data file" << endl;
		cout << "3. Analyze data" << endl;
		cout << "4. Quit" << endl;
		cin >> choice;
		
		switch (choice) {
		case 1:
			getData();
			break;
		case 2:
			appendData();
			break;
		case 3:
			analyzeData();
			break;
		case 4:
			break;
		default:
			cout << "That's not a valid choice!\n" << endl;
			break;
		}

	} while (choice != 4);
	system("pause");
}