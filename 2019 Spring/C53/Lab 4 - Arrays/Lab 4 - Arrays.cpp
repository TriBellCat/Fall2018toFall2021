/*File Name: Lab 4 - Arrays.cpp
Author: Trinity Caitlin Atayan Belen
Description: In this program, the user will open savings account, the information will be printed, and the user will pick which one they want to delete*/

#include <iostream>
#include <ctime>
#include <vector>
#include<set>
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

	void deposit(double addition) //Adds the amount of addition to the balance
	{
		balance += addition;
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

	void printInfo() //prints the information of the account
	{
		cout << "Account Information: " << endl;
		cout << "Balance: $" << balance << endl;
		cout << "Interest Rate: " << interestRate << "%" << endl;
		cout << "Last Interest Date: " << lastInterestDate << endl;
	}
};

class WalletAccount : public BankAccount
{
private:
	double maxWalletCapacity = 100;
public:
	WalletAccount() : BankAccount() //Default Constructor
	{
		maxWalletCapacity = 100;
	}

	WalletAccount(double bal, double rate) : BankAccount(bal, rate) //General Constructor
	{
		maxWalletCapacity = maxWalletCapacity;
	}

	double getMaxWalletCapacity() //Gets max wallet capacity
	{
		return maxWalletCapacity;
	}

	void deposit(double addition) //Calls for deposit function from the parent class if the balance and addition together is less than the max wallet capacity
	{
		if (BankAccount::getBalance() + addition < maxWalletCapacity) {
			BankAccount::deposit(addition);
		}

		else {
			cout << "Deposit denied! Exceeding the max wallet capacity! \n" << endl;
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

	void printInfo() //Calls for print info from the parent function and then outputs max wallet capacity
	{
		BankAccount::printInfo();
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

	void deposit(double addition) //Sdds depoist if the account is not locked
	{
		if (!lock)
		{
			BankAccount::deposit(addition);
		}

		else
		{
			cout << "Access denied! Account is locked! \n" << endl;
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

	void printInfo() //Prints info for Wallet Account by calling the printInfo function of the parent class and then says whether or not the account is locked
	{
		BankAccount::printInfo();
		if (lock) {
			cout << "The account is locked! \n" << endl;
		}

		else {
			cout << "The account is not locked! \n" << endl;
		}
	}
};

int BankAccount::accountCount = 0; //defines and initializes account count to 0

int main() {
	char choice;
	int index = 0;
	double balance = 0;
	double maxBal = 0;
	int tempAccount = 0;
	int newNumberofAccounts = 0;
	SavingsAccount saving;
	vector<SavingsAccount> account(index); //creates vector accounts
	
	cout << "Current number of accounts is: " << account.size() << "\n" << endl;
	cout << "Do you want to create a savings account? (Y/N)" << endl;
	cin >> choice;

	if (choice == 'n' || choice == 'N') {
		cout << "Okay. Maybe next time!" << endl;
		system("pause");
		exit(0);
	}

	//Asks the user if they want to open a savings account and will not stop until they say no
	while (choice == 'y'|| choice == 'Y') {
		newNumberofAccounts++;

		cout << "What is your balance?" << endl;
		cin >> balance;

		SavingsAccount saving(SavingsAccount(balance, 0.02, false)); //Creates a new SavingsAccount object
		account.push_back(saving); //Adds the object to the vector
		account.resize(newNumberofAccounts); //Resizes the vector

		cout << "Do you want to create another savings account? (Y/N)" << endl;
		cin >> choice;
	}
	
	cout << "Current number of accounts is: " << account.size() << "\n" << endl;

	//Prints the information of all the accounts that has been opened
	for (int i = 0; i < account.size(); i++) {
		cout << "Account number: " << i << endl; //Prints the index number as account number
		account[i].printInfo();
	}

	//Extra Credit; The program will find the ccount with maximum blaance and prints its info
	for (int i = 0; i < account.size(); i++) {

		if (maxBal < account[i].getBalance()) {
			maxBal = account[i].getBalance();
			tempAccount = i;
		}

		else {
			maxBal;
			tempAccount;
		}
	}

	cout << "The account with the highest maximum balance is account number " << tempAccount << " and its balance is $" << maxBal << endl;

	cout << "Which account do you want to delete?" << endl;
	cin >> index;

	//Makes sure the index is in valid range
	while (index < 0 || index >= account.size()) {
		cout << "Invalid! Which account do you want to delete?" << endl;
		cin >> index;
	}

	//Deletes the account the user selected
	account.erase(account.begin()+index);

	cout << "Current number of accounts is: " << account.size() << "\n" << endl;
	system("pause");
}