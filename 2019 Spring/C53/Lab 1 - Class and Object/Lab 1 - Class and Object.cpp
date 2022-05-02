/*File Name: Lab 1 - Class and Object.cpp
Author: Trinity Caitlin Atayan Belen
Description: The program will store the user's bank account balance information through the use of objects and classes.*/

#include <iostream>
#include <ctime>
using namespace std;

class storeaccount {
private:
	double balance; //Stores the amount of money you have in your account
	float interestRate; //Stores the rate you get interest
	int lastInterestDate; //Stores the last date that you got your interest
	int newInterestDate = 0; //Stores the new interest date
public:
	storeaccount(double bal, float iR) //General Constructor
	{
		if (iR < 0 || iR > 1) {
			cout << "Invalid interest rate!" << endl;
		}

		else {
			balance = bal;
			interestRate = iR;
		}
	}

	storeaccount() //Default Constructor
	{
		balance = 0.0;
		interestRate = 0.0;
		lastInterestDate = 0;
	}

	void setBalance(int newBal) //Gets a double argument as the balance
	{
		balance = newBal;
	}

	double increaseBalanceBy(double money) //Gets a double argument and adds it to the balance
	{
		balance += money;
		return balance;
	}

	void setInterestRate(float newRate) //Gets a double argument and sets the interest rate to it
	{
		if (newRate < 0 || newRate > 1) {
			cout << "Invalid interest rate!" << endl;
		}

		else {
			interestRate = newRate;
		}
	}

	double getBalance () //Returns the balance amount
	{
		return balance;
	}

	double getInterestRate () //Returns the interest rate
	{
		return interestRate;
	}

	int getlastInterestDate() //Returns the last interest rate
	{
		return lastInterestDate;
	}

	int storeDate() //stores today's date, year, and month
	{
		time_t t = time(NULL);
		struct tm now;
		localtime_s(&now, &t);
		int today = (now.tm_year + 1900) * 10000 + (now.tm_mon + 1) * 100 + (now.tm_mday);
		lastInterestDate = today;
		return lastInterestDate;
	}

	void calculateNewInterestDate() //Calculates the new interest date in order to find the new date when the user pays his or her interest
	{
		time_t t = time(NULL);
		struct tm now;
		localtime_s(&now, &t);

		int daysInMonth[] = { 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //Assumes that there's no leap year and stays between 31 or 30 days
		int lastInterestMonth = now.tm_mon; //sets last interest month to today's month
		int lastInterestDay = now.tm_mday; //sets last interest day to today's day

		int newInterestMonth = lastInterestMonth; //stores the last interest month into new interest month
		int newInterestDay = lastInterestDay; //stores the last interest day into new interest day

		if ((lastInterestDay + 30) > 30 || (lastInterestDay + 30) > 31)  //if the last interest day is greater than 30 or 31, the new interest month and day will update
		{
			newInterestMonth++;
			newInterestDay+= 30;
		}

		newInterestDay -= daysInMonth[newInterestMonth - 1]; //the new interest day will be subtrated by the days in the month
		newInterestDate = (now.tm_year + 1900) * 10000 + (newInterestMonth + 1) * 100 + (newInterestDay); //the new interest date will be updated
	}

	void addInterest() //Calculates the amount of interest and adds it to the balance; otherwise it will tell the user that they already paid
	{
		int currentDate = storeDate(); //the current date stores today's date

		if (currentDate >= newInterestDate) //if the current date is greater than or equal to the new interest date, adds interest and then stores the last interest date into current date and then calculates a new interest date
		{
			balance += balance * interestRate;
			lastInterestDate = currentDate;
			calculateNewInterestDate();
		}

		else {
			cout << "The interest is already paid! Next interest will be paid in 30 or 31 days on " << newInterestDate << "." << endl;
		}
	}

	void info () //prints the information of the account
	{
		cout << "Balance: $" << balance << endl;
		cout << "Interest Rate: %" << interestRate << endl;
		cout << "Last Interest Payed On: " << lastInterestDate << endl;
	}
};

int main() {
	cout << "Account using the default constructor" << endl;
	storeaccount def;
	def.info();
	cout << endl;

	//Sets balance and interestRate to the account
	def.setBalance(1000);
	def.setInterestRate(0.2);
	def.info();
	cout << endl;

	//Adds balance to the account
	def.increaseBalanceBy(1000);
	def.info();
	cout << endl;

	//Tries the interest to the account twice, as the instruction says
	def.addInterest();
	def.info();
	cout << endl;

	def.addInterest();
	def.info();
	cout << endl;

	cout << "Account using the general constructor" << endl;
	storeaccount gen(4629.7, 0.4);
	gen.storeDate();
	gen.info();
	cout << endl;

	//Extra information from the general constructor to show the results when adding the balance and interest when it comes to using the general constructor
	gen.increaseBalanceBy(2462.4);
	gen.info();
	cout << endl;

	gen.addInterest();
	gen.info();
	cout << endl;

	gen.addInterest();
	gen.info();
	cout << endl;
	system("pause");
}