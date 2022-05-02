/*Filename:Lab 5 - Containers.cpp
Author: Trinity Caitlin Atayan Belen
Description: In this program, the program will ask a student to open a account, which contains two sub accounts.
Then, the program will print information of the accounts, ask the user to change an account, and which account to erase.*/

#include <iostream>
#include <ctime>
#include <utility>
#include <set>
#include <map>
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
	char choice, accChoice; //the program will give the user choices
	double savingBal, wallBal, deposit = 0; //the balances of the saving and wallet accounts
	int numSub = 0, accountNumber = 1000, numCount = 999; //counts the sub accounts and account numbers
	int accChange = 0, eraseAcc = 0; //relevant when the program asks the user to change something from an account
	map <int, double> saAccount; //stores the account number and saving balance of savings account 
	map <int, double> waAccount; //stores the account number and wallet balance of wallet account
	SavingsAccount save; //object from SavingsAccount class
	WalletAccount wall; //object from WalletAccount class

	cout << "Number of sub-accounts: " << numSub << "\n" << endl;

	cout << "Do you want to open an account? (Y/N) ";
	cin >> choice;

	while (cin.fail() || choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
		cout << "Not a legitmate choice! Do you want to open an account? (Y/N) ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}

	if (choice == 'n' || choice == 'N') {
		cout << "Okay. Maybe next time!" << endl;
		system("pause");
		exit(0);
	}
		 
	while (choice == 'y' || choice == 'Y') {
		numCount = numCount + 1;
		cout << "What is your wallet balance? ";
		cin >> wallBal;

		while (cin.fail()) {
			cout << "Error! Please re-enter your wallet balance: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> wallBal;
		}

		cout << "What is your saving balance? ";
		cin >> savingBal;

		while (cin.fail()) {
			cout << "Error! Please re-enter your savings balance: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> savingBal;
		}

		//Sets the wallet and saving balance
		wall.setBalance(wallBal);
		save.setBalance(savingBal);

		//Creates the accounts
		waAccount.emplace(accountNumber, wallBal);
		saAccount.emplace(accountNumber, savingBal);

		accountNumber++;

		numSub += 2;
		cout << "Do you want to open another account? (Y/N) ";
		cin >> choice;
	}

	cout << "Number of sub-accounts: " << numSub << "\n" << endl;

	//Prints the information of all the accounts
	cout << "Wallet Accounts" << endl;
	for (auto account : waAccount) 
	{
		WalletAccount wall(WalletAccount(account.second, 0.02));
		cout << "Account Number: " << account.first << endl;
		wall.printInfo(account.second);
	}

	cout << "Saving Accounts" << endl;
	for (auto account : saAccount) 
	{
		SavingsAccount save(SavingsAccount(account.second, 0.02, false));
		cout << "Account Number: " << account.first << endl;
		save.printInfo(account.second);
	}
	
	cout << "Enter an account number to deposit into: ";
	cin >> accChange;

	while (cin.fail()||accChange < 1000|| accChange > numCount) {
		cout << "Error! That account does not exist! Please re-enter the account number to deposit into : ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> accChange;
	}

	cout << "Do you want to change savings or wallet account? (W/S) ";
	cin >> accChoice;
	
	while (cin.fail() || accChoice != 'w' && accChoice != 'W' && accChoice != 's' && accChoice != 'S') {
		cout << "Error! Not a legitmate choice! Do you want to change savings or wallet account? (W/S) ";
		cin.clear();
		cin.ignore(1000, '\n');
		accChoice = 0;
		cin >> accChoice;
	}

	if (accChoice == 'w' || accChoice == 'W') {
		double newBal, currentBal;
		currentBal = waAccount.at(accChange);
		waAccount.erase(accChange);

		cout << "How much money will you deposit? ";
		cin >> deposit;

		wall.setBalance(currentBal);
		newBal = wall.deposit(deposit);
		waAccount.emplace(accChange, newBal);
	}

	if (accChoice == 's' || accChoice == 'S') {
		double newSaveBal, currentSaveBal;
		currentSaveBal = saAccount.at(accChange);
		saAccount.erase(accChange);
		
		cout << "How much money will you deposit? ";
		cin >> deposit;

		save.setBalance(currentSaveBal);
		newSaveBal = save.deposit(deposit);
		saAccount.emplace(accChange, newSaveBal);
	}

	cout << "Which account do you want to close? ";
	cin >> eraseAcc;
	
	while (cin.fail() || eraseAcc < 1000 || eraseAcc > numCount)
	{
			cout << "Error! That account does not exist! Which account do you want to close? ";
			cin.clear();
			cin.ignore(1000, '\n');
			eraseAcc = 0;
			cin >> eraseAcc;
	}

	waAccount.erase(eraseAcc);
	saAccount.erase(eraseAcc);

	cout << "Number of sub-accounts: " << numSub - 2 << "\n" << endl;
	
	cout << "Wallet Accounts" << endl;
	for (auto account : waAccount)
	{
		WalletAccount wall(WalletAccount(account.second, 0.02));
		cout << "Account Number: " << account.first << endl;
		wall.printInfo(account.second);
	}

	cout << "Saving Accounts" << endl;
	for (auto account : saAccount)
	{
		SavingsAccount save(SavingsAccount(account.second, 0.02, false));
		cout << "Account Number: " << account.first << endl;
		save.printInfo(account.second);
	}
	
	system("pause");
}