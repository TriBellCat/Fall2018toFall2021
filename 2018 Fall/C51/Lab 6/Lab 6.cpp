/*   Filename: Lab 6.cpp
	   Author: Trinity Caitlin Atayan Belen
  Description: The program will find the word and the word backwards using the letters the user inputted.
			   Also, it will try to find the position of a letter in the word.*/

#include <iostream>
# include <string>
using namespace std;

void find(char letter[], int size, char c)
{
	int index = 0;
	bool found = false;

	//this for loop will try to find the position of char c and prints out what position it is in.
	for (int i = 0; i < size; i++)
	{
		if (c == letter[i])
		{
			cout << "The letter is found at position " << i << ".\n";
			found = true;
		}
	}

	//otherwise, it will print out that the letter is not found in the world.
	if (!found)
	{
		cout << "The letter is not in the word.\n" << endl;
	}
}

int main() 
{
	char letter[8];
	char c;
	int size = 8;

	//int i starts at 0 and the for loop will ask for input until it is at letter #7.
	for (int i = 0; i < 8; i++)
	{
		cout << "Please enter letter # " << i << ": ";
		cin >> letter[i];
	}

	cout << "The word is ";

	//int i starts at 0 and will print out the letters, one at a time
	for (int i = 0; i < 8; ++i)
	{
			cout << letter[i];
	}

	cout << endl;
	cout << "The word backwards is ";

	//int i starts at 7 and will print out the letters backwards
	for (int i = 7; i >= 0; i--)
	{
			cout << letter [i];
	}

	cout << endl;

	cout << "What letter would you like to search for? ";
	cin >> c;
	find(letter, size, c);

	system("pause");
}

