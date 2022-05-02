/*Filename:Lab 6 - Containers (Part 2).cpp
Author: Trinity Caitlin Atayan Belen
Description: In this program, the program will ask a student to open a account, which contains two sub accounts.
The program will then print information of the accounts, sort the accounts, and then ask the user to change it in some way.*/

#include <iostream>
#include <ctime>
#include <utility>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class BankAccount {
private:
	double balance = 0.0; //Stores the amount of money you have in your account
	double interestRate = 0.0; //Stores the rate you get interest
	int lastInterestDate = 0; //Stores the last date that you got your interest
	int newInterestDate = 0; //Stores the new interest date

protected:
	static int accountCount; //Counts the amount of accounts
public:

	BankAccount() //Default Constructor
	{
		balance = 0.0;
		interestRate = 0.0;
		lastInterestDate = 0;
		accountCount++;
	}

	BankAccount(double bal, double iR) //General Constructor
	{

		if (iR < 0 || iR > 1) {
			cout << "Invalid interest rate!" << endl;
		}

		else {
			balance = bal;
			interestRate = 100 * iR; //Also converts decimal to percent
		}

		lastInterestDate = storeDate();
		accountCount++;
	}

	~BankAccount() //Destructor
	{
		accountCount--; //Decrements the account counts
	}

	static int getAccountCount()
	{
		return accountCount;
	}

	void setBalance(double bal) //Gets a double argument as the balance
	{
		balance = bal;
	}

	double deposit(double addition) //Adds the amount of addition to the balance
	{
		balance += addition;
		return balance;
	}

	void withdraw(double deduction) //withdraws money from bank account
	{
		if (balance > deduction) {
			balance -= deduction;
		}

		else {
			cout << "Withdrawing denied! Not enough balance! \n" << endl;
		}
	}

	void setInterestRate(double newRate) //Gets a double argument and sets the interest rate to it
	{
		if (newRate < 0 || newRate > 1) {
			cout << "Invalid interest rate!" << endl;
		}

		else {
			interestRate = newRate;
		}
	}

	double getBalance() //Returns the balance amount
	{
		return balance;
	}

	double getInterestRate() //Returns the interest rate
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
			newInterestDay += 30;
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

	void printInfo(double b) //prints the information of the account
	{
		cout << "Account Information" << endl;
		cout << "-----------------------------" << endl;
		cout << "Balance: $" << balance << endl;
		cout << "Interest Rate: " << interestRate << "%" << endl;
		cout << "Last Interest Date: " << storeDate() << endl;
	}
};

class WalletAccount : public BankAccount
{
private:
	double maxWalletCapacity = 100000000;
public:
	WalletAccount() : BankAccount() //Default Constructor
	{
		maxWalletCapacity = 100000000;
	}

	WalletAccount(double bal, double rate) : BankAccount(bal, rate) //General Constructor
	{
		maxWalletCapacity = maxWalletCapacity;
	}

	double getMaxWalletCapacity() //Gets max wallet capacity
	{
		return maxWalletCapacity;
	}

	double deposit(double addition) //Calls for deposit function from the parent class if the balance and addition together is less than the max wallet capacity
	{
		if (BankAccount::getBalance() + addition < maxWalletCapacity) {
			return BankAccount::deposit(addition);
		}

		else {
			cout << "Deposit denied! Exceeding the max wallet capacity! \n" << endl;
			exit(0);
		}
	}

	void setBalance(double bal) //Calls for set balance function from the parent class if the balance is less than the max wallet capacity
	{
		if (bal < maxWalletCapacity) {
			BankAccount::setBalance(bal);
		}

		else {
			cout << "Setting balance denied! The balance will exceed the wallet capacity! \n" << endl;
		}
	}

	void printInfo(double b) //Calls for print info from the parent function and then outputs max wallet capacity
	{
		BankAccount::printInfo(b);
		cout << "Max Wallet Capacity: $" << maxWalletCapacity << "\n" << endl;
	}
};

class SavingsAccount : public BankAccount {
private:
	bool lock = false;
public:
	SavingsAccount() : BankAccount() //Default constructor
	{
		lock = false;
	}

	SavingsAccount(double bal, double rate, bool lock) :BankAccount(bal, rate) //General constructor
	{
		this->lock = lock;
	}

	void lockAccount() //Locks the account
	{
		lock = true;
		cout << "The account is now locked! \n" << endl;
	}

	void removeLock() //Removes the lock from the account
	{
		lock = false;
		cout << "The account is now open! \n" << endl;
	}

	void setBalance(double bal) //Setter for the balance and calls for the setBalance function from the parent class
	{
		if (!lock)
		{
			BankAccount::setBalance(bal);
		}

		else
		{
			cout << "Access denied! Account is locked! \n" << endl;
		}
	}

	void setInterestRate(double rate) //Setter for interest rate and calls for the setInterestRate function from the parent class
	{
		if (!lock)
		{
			BankAccount::setInterestRate(rate);
		}

		else
		{
			cout << "Access denied! Account is locked! \n" << endl;
		}
	}

	void addInterest() //Adds interest if the account is not locked
	{
		if (!lock)
		{
			BankAccount::addInterest();
		}

		else
		{
			cout << "Access denied! Account is locked!" << endl;
		}
	}

	double deposit(double addition) //Sdds depoist if the account is not locked
	{
		if (!lock)
		{
			return BankAccount::deposit(addition);
		}

		else
		{
			cout << "Access denied! Account is locked! \n" << endl;
			return 0;
		}
	}

	void withdraw(double deduction) //Withdraws the deduction if the account is not locked
	{
		if (!lock)
		{
			BankAccount::withdraw(deduction);
		}

		else
		{
			cout << "Access denied! Account is locked! \n" << endl;
		}
	}

	void printInfo(double b) //Prints info for Wallet Account by calling the printInfo function of the parent class and then says whether or not the account is locked
	{
		BankAccount::printInfo(b);
		if (lock) {
			cout << "The account is locked! \n" << endl;
		}

		else {
			cout << "The account is not locked! \n" << endl;
		}
	}
};

int BankAccount::accountCount = 0; //defines and initializes accountCount

int main() {
	SavingsAccount savCount; 
	map <int, double> savTotal; //saves the total of balances into a savings account
	map <int, map<int, double>> savBal; // saves a list of the savings account
	vector <int> list; //saves the list of maps
	char choice, accChoice; //the program will give the user choices
	double savingBal = 0, totalBal = 0;//the saving balances and how many are there in total in an account
	int accountID = 1000, subID = 0, totalID = 0; //ids of the accounts, subaccounts, and how many of them are in total
	int numSub = 0, accountNum = 0; //counts the number of subaccounts and accountNumbers
	int eraseAcc = 0; //the program will erase the account the user asks
	int lowestAcc = -1; //an account that will be used for the account with the lowest balance

	cout << "Do you want to open an account? (Y/N) ";
	cin >> accChoice;

	while (cin.fail() || accChoice != 'n' && accChoice != 'N' && accChoice != 'y' && accChoice != 'Y') {
		cout << "Error! Not a legitmate choice! Do you want to open an account? (Y/N) ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}

	if (accChoice == 'n' || accChoice == 'N') {
		cout << "Okay! Maybe next time! Bye-bye!" << endl;
		system("pause");
		exit(0);
	}

	while (accChoice == 'y' || accChoice == 'Y') {
		totalBal = 0; //resets total balance
		map <int, double> savings; //saves a list of subID and saving balance into a list

		if (accChoice == 'y' || accChoice == 'Y') {
			subID = 0; //resets subId
			do {
				cout << "Do you want to open a sub account? (Y/N) ";
				cin >> choice;

				while (cin.fail() || choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
					cout << "Not a legitmate choice! Do you want to open an account? (Y/N) ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> choice;
				}

				if (choice == 'y' || choice == 'Y') {
					cout << "Enter your savings balance: ";
					cin >> savingBal;

					while (savingBal < 0 || cin.fail()) {
						cout << "Error! Not a valid number for this program! Please re-enter your savings balance: ";
						cin.clear();
						cin.ignore(1000, '\n');
						savingBal = 0;
						cin >> savingBal;
					}
					savings.emplace(subID, savingBal); //creates a list into the map
					totalBal += savingBal; //the total balance of the account
					subID++; //increments subID
					numSub++; //increments the amount of sub accounts
				}
			} while (choice == 'y' || choice == 'Y'); //will not stop asking for sub account information until the user says no

			//creates the student accounts with one account ID and balances
			savBal.emplace(accountID, savings); //creates an account with account id and savings
			savTotal.emplace(accountID, totalBal); //creates an account with account id and total balance

			//increment
			accountID++;
			totalID++;
			accountNum++;
		}

		cout << "Do you want to open another account? (Y/N) ";
		cin >> accChoice;

		while (cin.fail() || accChoice != 'n' && accChoice != 'N' && accChoice != 'y' && accChoice != 'Y') {
			cout << "Error! Not a valid choice! Do you want to open another account? (Y/N) ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}
	}

	cout << "Number of sub-accounts: " << numSub << "\n" << endl;

	for (int i = 1000; i < accountID; i++) {
		int lowestNum = 2147483647; //eighth Mersenne prime
			
		//sorts the accounts based on balance, from lowest to greatest; all according to the instructions
		for (int j = 1000; j < accountID; j++) {
			if (lowestNum > savTotal.at(j)) {
				lowestNum = savTotal.at(j);
				lowestAcc = j;
				//if the lowest number is greater than the balance, the lowest account becomes j
			}
		}

		cout << "Account ID: " << lowestAcc << endl;

		//prints out account information
		for (int k = 0; k < savBal.at(lowestAcc).size(); k++) {
			SavingsAccount savCount(SavingsAccount(savBal.at(lowestAcc).at(k), 0.02, false));
			savCount.printInfo(savBal.at(lowestAcc).at(k));
		}

		list.push_back(lowestAcc); //push backs lowest account so it wouldn't be used more than once
		savTotal.erase(lowestAcc); //erases the lowest account
		savTotal.emplace(lowestAcc, 2147483647); //resets savTotal
	}

	cout << "Which account do you want to erase? ";
	cin >> eraseAcc;

	while (cin.fail() || eraseAcc < 1000 || eraseAcc > accountID - 1)
	{
		cout << "Error! That account does not exist! Which account do you want to close? ";
		cin.clear();
		cin.ignore(1000, '\n');
		eraseAcc = 0;
		cin >> eraseAcc;
	}

	savBal.erase(eraseAcc);

	system("pause");
}