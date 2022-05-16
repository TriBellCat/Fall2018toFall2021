/*File Name: Project 4.cpp
Author: Trinity Caitlin Atayan Belen
Description: For project 4, the program will calculate the gross wages,
deductions for health care benefits, and fereal income tax withholding.
The results will be saved to an output file and summary statistics will be calculated and displayed onto the command console.*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class Employee {
private:
	int ID; //ID of the workers
	string recType; //What kind of type are the workers
	string Name; //The name of the workers
	string healthCare; //Which health care plan the workers have
	int hours; //how many hours the worker has
	double hourlyRate; //the hourly rate the worker has

public:

	//General Constructor
	Employee(int i, string rt, string n, string hc, int hrs, double hlr) {
		ID = i;
		recType = rt;
		Name = n;
		healthCare = hc;
		hours = hrs;
		hourlyRate = hlr;
	};

	//Default Constructor
	Employee() {
		ID = 0;
		recType = "";
		Name = "";
		healthCare = "";
		hours = 0;
		hourlyRate = 0;
	};

	//Prints the employee information
	void printEmployee() {
		cout << recType << " " << ID << " " << Name << " " << healthCare << " " << hours << " " << hourlyRate << endl;
	}


	//The getters to get information from a list
	int getID() {
		return ID;
	}

	string getrecType() {
		return recType;
	}

	string getName() {
		return Name;
	}

	string gethealthCare() {
		return healthCare;
	}

	int getHours() {
		return hours;
	}

	double gethourlyRate() {
		return hourlyRate;
	}

};

//Function to calculate the gross from the workers
double gross(string recType, double hourlyRate, int hours) {
	double g;
	if (recType == "Part" || recType == "Full") {
		g = hourlyRate * hours;
		return g;
	}

	else if (recType == "Salary") {
		g = hourlyRate + hours;
		return g;
	}
}

//Function to calculate the tax withholding from the workers
double tax(double g) {
	double t;
	if (g <= 500 && g > 0) {
		t = g * .10;
		return t;
	}

	else if (g >= 501 && g <= 1000) {
		t = g * .15;
		return t;
	}

	else if (g > 1000) {
		t = g * .25;
		return t;
	}
}

//Function to find the deduction from the health care of workers
int healthDed(string recType, string healthCare) {
	int deduction;

	if (healthCare == "Cadillac")
	{
		deduction = 75;
		return deduction;
	}

	else if (healthCare == "Standard") {
		deduction = 25;
		return deduction;
	}

	else if (healthCare == "Basic") {
		deduction = 10;
		return deduction;
	}

	else {
		deduction = 0;
		return deduction;
	}
}

//Function to calculate the net of each worker
double netValue(double g, double t, int deduction) {
	double net;
	net = g - (t + deduction);
	return net;
}

//This function will read from both lists in order to sort the IDs
void processPayroll(Employee R[], Employee V[]) {
	ofstream Summary; //Summary is the output file that will have information from both files
	string empName, type, hCare; // The name, health care, and type of the workers
	bool EndofList = false; //The while loop will read the liar until it reaches the end of it
	bool moveReno = false, moveVegas = false; //Either Reno or Vegas will be moved later on
	double hrRate = 0, t = 0, g = 0, net = 0; //the hourlyRate, tax, gross, and net of workers
	int rC = 0, vC = 0; //The counter of Reno and Vegas; to see if they will move on or not
	int renID, vegID; // The IDs of the workers
	int time = 0, deduction = 0; //The hours and deductions the workers have
	double totalGrossR = 0, totalHealthDedR = 0, totalTaxR = 0, totalNetR = 0, AllR = 0; //the totals are initialized to find the total altogether for Vegas
	double totalGrossV = 0, totalHealthDedV = 0, totalTaxV = 0, totalNetV = 0, AllV = 0; //the totals are initialized to find the total altogether for Vegas
	
	//Creates the output file
	Summary.open("Project 4 - Payroll Summary.txt");
	if (Summary.fail()) {
		cout << "Cannot open file, please check if files match the format described in Project 4 instructions or if the file has been named correctly." << endl;
		system("pause");
	}

	while (!EndofList) {
		//Initial Condition
		if (!moveReno && !moveVegas) {
			renID = R[rC].getID();
			vegID = V[vC].getID();
		}

		//It checks if Reno is at the end of file and then it will add Vegas to the Summary at the end
		if (R[rC].getID() == 0) {
			EndofList = true;
			while (V[vC].getID() != 0) {
				vegID = V[vC].getID();

				//Gets the information so that they could be used to do calcualations
				empName = V[vC].getName();
				type = V[vC].getrecType();
				hCare = V[vC].gethealthCare();
				time = V[vC].getHours();
				hrRate = V[vC].gethourlyRate();

				//The calculations to find the gross, tax withholding, deduction, and net
				g = gross(type, hrRate, time);
				t = tax(g);
				deduction = healthDed(type, hCare);
				net = netValue(g, t, deduction);

				//The calculations to find the totals from a location 
				totalGrossV += g;
				totalHealthDedV += deduction;
				totalTaxV += t;
				totalNetV += net;

				vC++;
				Summary << vegID << " " << empName << " " << g << " " << deduction << " " << t << " " << net << endl;
			}
		}

		if (V[vC].getID() == 0) {
			EndofList = true;
			while (R[rC].getID() != 0) {
				renID = R[rC].getID();

				empName = R[rC].getName();
				type = R[rC].getrecType();
				hCare = R[rC].gethealthCare();
				time = R[rC].getHours();
				hrRate = R[rC].gethourlyRate();

				g = gross(type, hrRate, time);
				t = tax(g);
				deduction = healthDed(type, hCare);
				net = netValue(g, t, deduction);

				totalGrossR += g;
				totalHealthDedR += deduction;
				totalTaxR += t;
				totalNetR += net;

				rC++;

				Summary << renID << " " << empName << " " << g << " " << deduction << " " << t << " " << net << endl; ;
			}
		}

		if (!EndofList) {

			// These will toggle which list to move through
			if (renID < vegID) {
				moveReno = true;
				moveVegas = false;
			}

			else if (renID > vegID) {
				moveReno = false;
				moveVegas = true;
			}

			//It will move either Reno or Vegas and calculates some information
			if (moveReno) {
				renID = R[rC].getID();

				empName = R[rC].getName();
				type = R[rC].getrecType();
				hCare = R[rC].gethealthCare();
				time = R[rC].getHours();
				hrRate = R[rC].gethourlyRate();

				g = gross(type, hrRate, time);
				t = tax(g);
				deduction = healthDed(type, hCare);
				net = netValue(g, t, deduction);

				totalGrossR += g;
				totalHealthDedR += deduction;
				totalTaxR += t;
				totalNetR += net;

				Summary << renID << " " << empName << " " << g << " " << deduction << " " << t << " " << net << endl;
				rC++;
				renID = R[rC].getID();
			}

			if (moveVegas) {
				vegID = V[vC].getID();

				empName = V[vC].getName();
				type = V[vC].getrecType();
				hCare = V[vC].gethealthCare();
				time = V[vC].getHours();
				hrRate = V[vC].gethourlyRate();

				g = gross(type, hrRate, time);
				t = tax(g);
				deduction = healthDed(type, hCare);
				net = netValue(g, t, deduction);

				totalGrossV += g;
				totalHealthDedV += deduction;
				totalTaxV += t;
				totalNetV += net;

				Summary << vegID << " " << empName << " " << g << " " << deduction << " " << t << " " << net << endl;
				vC++;
				vegID = V[vC].getID();
			}
		}
	}

	//Combines the total for each location
	AllR = totalGrossR + totalHealthDedR + totalTaxR + totalNetR;
	AllV = totalGrossV + totalHealthDedV + totalTaxV + totalNetV;

	//Shows the totals for Reno and Vegas
	cout << "Totals for Reno" << endl;
	cout << "Total Gross: " << totalGrossR << endl;
	cout << "Total Health Deduction: " << totalHealthDedR << endl;
	cout << "Total Tax: " << totalTaxR << endl;
	cout << "Total Net Value: " << totalNetR << endl;
	cout << "Overall Total: " << AllR << "\n" << endl;

	cout << "Totals for Vegas" << endl;
	cout << "Total Gross: " << totalGrossV << endl;
	cout << "Total Health Deduction: " << totalHealthDedV << endl;
	cout << "Total Tax: " << totalTaxV << endl;
	cout << "Total Net Value: " << totalNetV << endl;
	cout << "Overall Total:" << AllV << "\n" << endl;

	Summary.close();
}

//Function to calculate the total of the file
void sumAll() {
	ifstream Summary; //The Summary will be read instead of writter
	int ID; //The ID of the workers
	string name; //The names of the workers
	double totalGross = 0, totalHealthDed = 0, totalTax = 0, totalNet = 0, overallTotal = 0; //Initializes the totals to 0
	double g, tax, netVal, healthDed; //The variables of the file

	Summary.open("Project 4 - Payroll Summary.txt");

	if (Summary.fail()) {
		cout << "Cannot open file, please check if files match the format described in Project 4 instructions or if the file has been named correctly." << endl;
		system("pause");
	}

	//It will stop reading the file once it reaches the end
	while (Summary >> ID >> name) {
		Summary >> g >> healthDed >> tax >> netVal;
		totalGross += g;
		totalHealthDed += healthDed;
		totalTax += tax;
		totalNet += netVal;
	}

	//Adds everything together
	overallTotal = totalGross + totalHealthDed + totalTax + totalNet;

	cout << "Total Together" << endl;
	cout << "Total Gross: " << totalGross << endl;
	cout << "Total Health Deduction: " << totalHealthDed << endl;
	cout << "Total Tax: " << totalTax << endl;
	cout << "Total Net Value: " << totalNet << endl;
	cout << "Overall Total: " << overallTotal << "\n" << endl;
}

int main() {
	Employee R[25], V[25]; //Variables that are part of class Employee will be the lists for the information
	ifstream Reno, Vegas; //Reno and Vegas will be read in order to find the information for each worker
	string RecType1, RecType2; //The RecTypes are the types of workers
	int i = 0; //The counter is initialized to 0
	int error = 0; //The error count is initialized to 0

	//Opens the files
	Reno.open("Project 4 - Payroll Reno.txt");
	Vegas.open("Project 4 - Payroll Vegas.txt");

	//Error statements if the files are not there
	if (Vegas.fail() || Reno.fail()) {
		cout << "Cannot open file, please check if files match the format described in Project 4 instructions or if the file has been named correctly." << endl;
		system("pause");
		return 0;
	}

	//Reads the Reno/first file to a list
	while (Reno >> RecType1) {
		int ID1;
		string Name1, HealthCare1;
		double HourlyRate1, Hours1, PayRate1;

		if (RecType1 == "Part") {
			Reno >> ID1 >> Name1 >> Hours1 >> HourlyRate1;
			R[i] = Employee(ID1, RecType1, Name1, " ", Hours1, HourlyRate1);
			cout << "ID1 :" << ID1 << endl;
			cout << "Name1 :" << Name1 << endl;
			cout << "Hours1 :" << Hours1 << endl;
			cout << "PayRate1 :" << HourlyRate1 << endl;
			i++;
			cout << endl;
		}

		else if (RecType1 == "Salary") {
			Reno >> ID1 >> Name1 >> HealthCare1 >> PayRate1;

			//checks to see if there is an error with health care and skips the record if it does
			if (HealthCare1 != "Standard" && HealthCare1 != "Cadillac" && HealthCare1 != "Basic") {
				error++;
				cout << "Error: " << error << endl;
			}

			else {
				R[i] = Employee(ID1, RecType1, Name1, HealthCare1, 0, PayRate1);
				cout << "ID1 :" << ID1 << endl;
				cout << "Name1 :" << Name1 << endl;
				cout << "HealthCare1 :" << HealthCare1 << endl;
				cout << "PayRate1 :" << PayRate1 << endl;
				i++;
				cout << endl;
			}
		}

		else if (RecType1 == "Full") {
			Reno >> ID1 >> Name1 >> HealthCare1 >> Hours1 >> HourlyRate1;

			if (HealthCare1 != "Standard" && HealthCare1 != "Cadillac" && HealthCare1 != "Basic") {
				error++;
				cout << "Error: " << error << endl;
			}

			else {
				R[i] = Employee(ID1, RecType1, Name1, HealthCare1, Hours1, HourlyRate1);

				cout << "ID1 :" << ID1 << endl;
				cout << "Name1 :" << Name1 << endl;
				cout << "HealthCare1 :" << HealthCare1 << endl;
				cout << "HourlyRate1 :" << HourlyRate1 << endl;
				i++;
				cout << endl;
			}
		}

		//counts the error everytime the RecType is not any of the three types
		else {
			char line[256];
			Reno.getline(line, 256); // Read in the rest of the line with an error to skip
			error++;
		}
	}

	//Resets the counter
	i = 0;

	//Reads the Vegas/second file
	while (Vegas >> RecType2) {
		int ID2;
		string Name2, HealthCare2;
		double HourlyRate2, Hours2, PayRate2;

		if (RecType2 == "Part") {
			Vegas >> ID2 >> Name2 >> Hours2 >> HourlyRate2;
			V[i] = Employee(ID2, RecType2, Name2, " ", Hours2, HourlyRate2);

			cout << "ID2 :" << ID2 << endl;
			cout << "Name2 :" << Name2 << endl;
			cout << "Hours2 :" << Hours2 << endl;
			cout << "PayRate2 :" << HourlyRate2 << endl;
			i++;
			cout << endl;
		}

		else if (RecType2 == "Salary") {
			Vegas >> ID2 >> Name2 >> HealthCare2 >> PayRate2;

			if (HealthCare2 != "Standard" && HealthCare2 != "Cadillac" && HealthCare2 != "Basic") {
				error++;
				cout << "Error: " << error << endl;
			}

			else {
				V[i] = Employee(ID2, RecType2, Name2, HealthCare2, 0, PayRate2);
				cout << "ID2 :" << ID2 << endl;
				cout << "Name2 :" << Name2 << endl;
				cout << "HealthCare2 :" << HealthCare2 << endl;
				cout << "PayRate2 :" << PayRate2 << endl;
				i++;
			}
			cout << endl;
		}

		else if (RecType2 == "Full") {
			Vegas >> ID2 >> Name2 >> HealthCare2 >> Hours2 >> HourlyRate2;

			if (HealthCare2 != "Standard" && HealthCare2 != "Cadillac" && HealthCare2 != "Basic") {
				error++;
				cout << "Error: " << error << endl;
			}

			else {
				V[i] = Employee(ID2, RecType2, Name2, HealthCare2, Hours2, HourlyRate2);
				cout << "ID2 :" << ID2 << endl;
				cout << "Name2 :" << Name2 << endl;
				cout << "HealthCare2 :" << HealthCare2 << endl;
				cout << "HourlyRate2 :" << HourlyRate2 << endl;
				i++;
			}
			cout << endl;
		}

		else {
			char line[256];
			Vegas.getline(line, 256);
			error++;
		}
	}

	//Calls on other functions to process the totals
	processPayroll(R, V);
	sumAll();

	//Displays the error total
	cout << "Error Total: " << error << endl;

	//Closes the Files
	Reno.close();
	Vegas.close();

	system("pause");
}