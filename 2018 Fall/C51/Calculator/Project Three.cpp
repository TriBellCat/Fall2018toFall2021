/*     File: Project Three.cpp
	   Name: Trinity Caitlin Atayan Belen
Description: In "Project 3: Fun with Formulas!," there is a set of functions that solves famous math functions.
			 First, the user has to input some numbers in order for the program to solve the equation.*/

#include <iostream>
#include <string>
using namespace std;

/*Function: Celsius to Fahrenheit
Parameters: degC
Description: The computer will convert Celsius to Fahrenheit*/
double CtoF(double degC) 
{
	double degF;

	if (degC < -273.15) //Error statement for an illegal input
	{
		cout << "Error! Celsius must not be less than -273.15!" << endl;
		return 0; //If there's a display of an error message of an illegal input, it has to return something and go back to the menu
	}

	degF = (1.8)*degC + 32;
	return degF;

}

/*Function: Fahrenheit to Celsius
Parameters: degF
Description: The computer will convert Fahrenheit to Celsius*/
double FtoC(double degF)
{
	double degC;

	if (degF < -459.67)
	{
		cout << "Error! Fahrenheit must not be less than -459.67!" << endl;
		return 0;
	}

	degC = (5.0 / 9.0) * (degF - 32);
	return degC;
}

/*Function: Factorial of a Number
Parameters: n
Description: The computer will find the factorial of a number*/
int factorial(int n)
{
	int factor = 1;

	if (n < 0) {
		cout << "Error! Number must be greater than 0!" << endl;
		return 0;
	}

	for (int i = 1; i <= n; ++i)
	{
		factor *= i;
	}

	return factor;
}

/*Function: Pythagoren Theorem
Parameters: sideA, sideB, sideC
Description: The program will find the missing vlaue (the value inputted as 0)*/
double pythTheorem(double sideA, double sideB, double sideC)
{

	double missingSide = 0;

	if (sideA < 0 || sideB < 0 || sideC < 0)
	{
		cout << "Error! Cannot input a negative number!" << endl;
		return 0;
	}

	if (sideA > 0 && sideB == 0 && sideC == 0 || sideA == 0 && sideB == 0 && sideC > 0 || sideA == 0 && sideB > 0 && sideC == 0)
	{
		cout << "Error! Can't have two sides with zero!" << endl;
		return 0;
	}

	if (sideA > 0 && sideB > 0 && sideC > 0 || sideA == 0 && sideB == 0 && sideC == 0)
	{
		cout << "Error! Only ONE of your numbers must be zero!" << endl;
		return 0;
	}

	if (sideA > 0 && sideB > 0 && sideC == 0) 
	{
		missingSide = sqrt((sideA*sideA) + (sideB*sideB));
	}

	if (sideC > 0 && sideB > 0 && sideA == 0) 
	{
		missingSide = sqrt((sideC*sideC) + (sideB*sideB));
	}

	if (sideA > 0 && sideC > 0 && sideB == 0) 
	{
		missingSide = sqrt((sideA*sideA) + (sideC*sideC));
	}

	return missingSide;
}

/*Function: Fibonacci
Parameters: num
Description: The program will calculate the Fibonacci of a number*/
int fib (int num) 
{
	int F0 = 0, F1 = 1, nextFib = 0, total = 0;

	if (num < 0) 
	{
		cout << "Error! Can't use a negative number!" << endl;
		return 0;
	}

	//if num is greather than or equal to 1, it'll print F0
	if (num >= 0)
	{
		cout << F0 << " ";
	}

	//if num is greather than or equal to 1, it'll print F1
	if (num >= 1)
	{
		cout << F1 << " ";
	}

	//i starts at 0 and must be greater than num - 1; it'll repeat until it gets to the last number, which is the total.
	//Example: The Fibonacci Sequence of 7 is 0, 1, 1, 2, 3, 5, 8, 13. 
	//0 + 1 = 1, 1 + 1 = 2, 2 + 1 = 3, and so on until you get to the total, which is 13.
	for (int i = 0; i < num - 1; i++)
	{
		nextFib = F0 + F1; //The next number will be added to the old number
		cout << nextFib << " "; //this will show the Fibonacci Sequence
		F0 = F1; //F0 will store F1
		F1 = nextFib; //F1 will store nextFib
	}

	cout << endl;
	cout << "\n";
	return nextFib;
}

/*Function: Square Root
Parameters: square number
Description: The program will calculate the square root of a number*/
double squareRoot(double squareNumber)
{
	double temp = 0;
	double oldTemp = 0;
	double lowerBound = 0;
	double upperBound = squareNumber;
	bool squarePool = false;
	bool negative = true;

	if (squareNumber < 0)
	{
		cout << "Error! Cannot find the square root of a negative!\n" << endl;
		return 0;
	}

	while (!squarePool)
	{
		temp = (lowerBound + upperBound) / 2;

		//If there's non-perfect squares, this will compare the previous temp value to the current one. For example, the square root of 3 will be a decimal. 
		//Or, if temp square equals to square number, we found the square root.
		if (temp == oldTemp|| temp * temp == squareNumber)
		{
			squarePool = true;
		}

		//If temp squared is greater than squareNumber, the square root lies between 0 and temp & the upperBound remains the same.
		if (temp * temp > squareNumber)
		{
			upperBound = temp;
		}

		//If temp squared is less than squareNumber, the lowerBound will become temp.
		if (temp * temp < squareNumber)
		{
			lowerBound = temp;
		}

		oldTemp = temp;
	}

	return temp;

}

/*Function: Power
Parameters: x, y
Description: x will be calculated to the power of y*/
double power(double x, double y)
{
	double result = 1;
	double newY = y;//newY holds the value of y

	//If y is less than negative, newY will become positive after being multiplied by -1.
	if (y < 0)
	{
		newY *= -1;
	}

	//The for loop will multiply x by itself by newY times.
	for (int i = 0; i < newY; i++)
	{
		result = result * x;
	}

	//If y is less than 0, after the newY became a positive and the for loop happened, it will become 1 over the result because it's a negative exponent before.
	if (y < 0)
	{
		result = 1 / result;
	}

	return result;
}

/*Function: Speed, EXTRA CREDIT FUNCTION
Parameters: distance, time
Description: Distance will be calculated by time to find the speed.*/
double milesperhour(double distance, double time)
{
	double speed;

	if (distance <= 0||time <= 0)
	{
		cout << "Error! You can't have zero or negative distance or time!" << endl;
		return 0;
	}

	speed = distance / time;
	return speed;
}

/*Function: Test Case
Parameters: none
Description: The computer will show the test cases to the user.*/
void testCases()
{
	cout << "This is the test case for Celsius to Fahrenheit." << endl;
	cout << "COMMON CASE" << endl;
	cout << CtoF(32.0) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << CtoF(-500) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << CtoF(-273.15) << "\n" << endl;

	cout << "This is the test case for Fahrenheit to Celsius." << endl;
	cout << "COMMON CASE" << endl;
	cout << FtoC(100) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << FtoC(-500) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << FtoC(-459.17) << "\n" << endl;

	cout << "This is the test case for Factorial." << endl;
	cout << "COMMON CASE" << endl;
	cout << factorial(12) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << factorial(-1) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << factorial(0) << "\n" << endl;

	cout << "This is the test case for the Pythagorean Theorem." << endl;
	cout << "COMMON CASE" << endl;
	cout << pythTheorem(0, 3, 4) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << pythTheorem(-1, 5, 0) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << pythTheorem(1, 1, 0) << "\n" << endl;

	cout << "This is the test case for Fibonacci." << endl;
	cout << "COMMON CASE" << endl;
	cout << fib(10) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << fib(-5) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << fib(0) << "\n" << endl;

	cout << "This is the test case for Square Root." << endl;
	cout << "COMMON CASE" << endl;
	cout << squareRoot(49) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << squareRoot(-2) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << squareRoot(0) << "\n" << endl;

	cout << "This is the test case for X to the Power of Y." << endl;
	cout << "COMMON CASE" << endl;
	cout << power(10, 2) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << power('a', 0) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << power(4, -2) << "\n" << endl;

	cout << "This is the test case for calculating speed." << endl;
	cout << "COMMON CASE" << endl;
	cout << milesperhour(100, 10) << endl;
	cout << "ERROR TEMP CASE" << endl;
	cout << milesperhour(2, -1) << endl;
	cout << "BOUNDARY CASE" << endl;
	cout << milesperhour(1, 1) << "\n" << endl;
}

int main()
{
	int choice;//choice for the menu

	double degC; //Celsius
	double degF; //Fahrenheit
	double sideA, sideB, sideC; //the side of a triangle
	double missingSide; //one of the sides the user inputted as 0
	double squareNum; //the number to find the square root of
	double temp; //the result of the square root
	double x, y; // x will be calculated to the power of y
	double result; //the result of the power of x to the power of y
	double distance, time; //used to calculate speed
	double speed; //the result of distance divided by time

	int n; //the number to find the Factorial of
	int num; // the number to find the Fibonacci of
	int nextFib; //the total of the Fibonacci

	do { //The program will loop back to the menu until the user chooses to exit
		cout << "Choose an option." << endl;
		cout << "1) Convert Celsius to Fahrenheit" << endl;
		cout << "2) Convert Fahrenheit to Celsius" << endl;
		cout << "3) Compute the Factorial of a number" << endl;
		cout << "4) Solve the Pythagoran Theorem" << endl;
		cout << "5) Compute the Fibonacci of a number" << endl;
		cout << "6) Calculate the square root of X" << endl;
		cout << "7) Calculate the power of x to y." << endl;
		cout << "8) Calculate speed." << endl; //EXTRA CREDIT; using the speed-time-distance formula
		cout << "9) Run Test Cases" << endl;
		cout << "10) Exit" << endl;
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			cout << "This is the option to convert Celsius to Fahrenheit." << endl;
			cout << "Please enter your Celsius: ";
			cin >> degC;

			//In this case, a symbol or letter is not an illegal value. Rather, it's an invalid value because it's a char instead or int or double.
			//this while loop will only end if a number is inserted
			while (cin.fail()) 
			{
				cout << "Invalid input! Please re-enter your Celsius: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> degC;
			}

			degF = CtoF(degC);
			cout << degC << " Celsius is converted to " << degF << " Fahrenheit.\n" << endl;
			break;

		case 2:
			cout << "This is the option to convert Fahrenheit to Celsius." << endl;
			cout << "Please enter your Fahrenheit: " << endl;
			cin >> degF;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter your Fahrenheit: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> degF;
			}

			degC = FtoC(degF);
			cout << degF << " Fahrenheit is converted to " << degC << " Celsius.\n" << endl;
			break;

		case 3:
			cout << "This is the option to compute the Factorial of a number." << endl;
			cout << "Please choose a number: ";
			cin >> n;

			while (cin.fail())
			{
				cout << "Invalid input! Please enter a number: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> n;
			}

			cout << "The Factorial of " << n << " is " << factorial(n) << ".\n" << endl;
			break;

		case 4:
			cout << "This is the option to solve the Pythagorean Theroem." << endl;
			cout << "Please enter side A: ";
			cin >> sideA;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter side A: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> sideA;

			}

			cout << "Please enter side B: ";
			cin >> sideB;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter side B: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> sideB;
			}

			cout << "Please enter side C: ";
			cin >> sideC;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter side C: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> sideC;
			}

			missingSide = pythTheorem(sideA, sideB,sideC);
			cout << missingSide << " is the value of the missing side.\n" << endl;
			break;

		case 5:
			cout << "This is the option to compute the Fibonacci of a number." << endl;
			cout << "Enter a number: ";
			cin >> num;

			while (cin.fail())
			{
				cout << "Invalid input! Please enter a number: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> num;
			}

			nextFib = fib(num);
			cout << "The total of the Fibonacci of " << num << " is " << nextFib << ".\n" << endl;
			break;

		case 6:
			cout << "This is the option to calculate the square root of a number." << endl;
			cout << "Please enter a number: ";
			cin >> squareNum;

			while (cin.fail())
			{
				cout << "Invalid input! Please enter a number: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> squareNum;
			}

			temp = squareRoot(squareNum);
			cout << temp << " is the square root of " << squareNum << ".\n" << endl;
			break;

		case 7:
			cout << "This is the option to calculate x power of y." << endl;
			cout << "Please enter x: ";
			cin >> x;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter x: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> x;
			}

			cout << "Please enter y: ";
			cin >> y;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter y: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> y;
			}

			result = power(x, y);
			cout << x << " to the power of " << y << " is " << result << ".\n" << endl;
			break;

		//Extra Credit Case
		case 8:
			cout << "This is the option to calculate speed." << endl;
			cout << "Please a number of miles: ";
			cin >> distance;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter miles: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> distance;
			}

			cout << "Please a number of hours: ";
			cin >> time;

			while (cin.fail())
			{
				cout << "Invalid input! Please re-enter hours: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> time;
			}

			speed = milesperhour(distance, time);
			cout << "The speed is " << speed << " miles per hours.\n" << endl;
			
			break;

		case 9:
			cout << "This is the option to run test cases." << endl;
			testCases();
			break;

		case 10:
			break;

		default:
			cout << "That's not an option!\n" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			break;
		}

	} while (choice != 10);
	
	system("pause");
}