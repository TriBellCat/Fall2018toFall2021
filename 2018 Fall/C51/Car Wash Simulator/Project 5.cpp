/*
 * Car Wash Simulation Program - This program will prompt the user for the amount of time to run the car wash. Cars
 * will randomly get in line (1 every 4 minutes). The program will track the number of cars washed, the average time to wait
 * in the queue, and the number of cars washed.
 *
 * Author : Trinity Caitlin Atayan Belen
 * Class : COMP 51
 *
*/

#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

/*
 * This class represent each car that goes through the car wash. Each car is assigned a number (counter starting from 1),
 * the time the car arrived in the queue, the time the car started to get washed, the type of wash requested, and whether
 * the car is currently in the wash or not.
 *
 * DO NOT MODIFY THIS CLASS. ALL METHODS CAN BE USED AS IS. JUST INVOKE THE METHODS FROM THE CAR WASH CLASS.
*/

class CarToWash {
public:
	CarToWash() {
		carNumber = 0;
		minuteArrival = 0;
		minuteWash = 0;
		washType = 1;
		isCarInWash = false;
	}
	// this setter function will update the car number, the arrival time, the type of wash and whether the car is in the wash all at once
	void setCar(int number, int minute, int type, bool status) {
		carNumber = number;
		minuteArrival = minute;
		isCarInWash = status;
		washType = type;
	}
	void setInCarWash(bool status) {
		isCarInWash = status;
	}

	int getStart() {
		return minuteArrival;
	}
	bool getInCarWash() {
		return isCarInWash;
	}
	int getWashStart() {
		return minuteWash;
	}
	int getWashEnd() {
		int result = 0;
		switch (washType) {
		case 1:
			result = minuteWash + 4;
			break;
		case 2:
			result = minuteWash + 6;
			break;
		case 3:
			result = minuteWash + 7;
			break;
		default:
			cout << "Invalid wash type = " << washType;
			system("pause");
			exit(1);
		}
		return result;
	}
	int getCarNum() {
		return carNumber;
	}
	void setWashStart(int startTime) {
		minuteWash = startTime;
	}
private:
	int carNumber;				// identifies the car number beginning with one
	int minuteArrival;			// minute the car arrive as the car wash and started waiting
	int minuteWash;				// time the car actually gets into the car wash
	int washType;				// 1 = standard, 2 = Special, 3 = Extreme
	bool isCarInWash;
};

/*
 * This is the main class for the program. See instructions for defining the properties and methods.
*/

class CarWash {
public:
	//default constructor
	CarWash() {
		numberCars = 0;
		maxQueue = 0;
		queueTime = 0;
		totalCars = 0;
		closingTime = 0;
		minutesOpen = 0;
		numberCarsRefused = 0;
	}
	
	//sets the closing time property to the input time
	void openUp(int time) {
		closingTime = time;
	}

	//Every minute will be updated and logged
	void updateTimer(bool car) {
		
		cout << "Time (" << minutesOpen << ") ";

		//If the car wash is not empty, the car is being washed
		if (!isCarWashEmpty()) {
			cout << "Car " << totalCars << " is being washed. ";
		}

		//If the minutes open equals the expected time that the car will leave the wash, the car wash is finished and the queueTime is being calculated.
		if (minutesOpen == getEndOfWash() && !isCarWashEmpty()) {
			cout << "Finished car " << totalCars << " at time : " << minutesOpen << endl;

			//Every time a car finishes, the cars processed will reset the car's information so that the next one could go in
			for (int i = 0; i < 5; i++) {
				if (totalCars == cars[i].getCarNum()) {
					cars[i].setCar(0, 0, 1, false);
				}			
			}

			//Decrements the number of cars
			numberCars--;

			//Gets the overall total number of cars
			getTotalNumber();

			// Handle a new car in the list here
			if (numberCars > 0) {
				runCarWash();
			}
		}

		if (car) {
			cout << "New car has arrived at time: " << minutesOpen << endl;
			
			//If there are 5 cars, the car will turn away and the program updates the number of cars refused
			if (numberCars == 5) {
				cout << "Car wash is full! Car turned away at minute : " << minutesOpen << endl;
				numberCarsRefused++;
			}

			//If the time it takes for a car wash to finish is more than the minutes left for the shop to open, the car will not be able to go in.
			else if (4 > closingTime - minutesOpen) {
				cout << "There's not enough time to wash! Car turned away at minute : " << minutesOpen << endl;
				numberCarsRefused++;
			}

			//The numbers of cars will be updated if a car has to wait in the queue, which will also become the maxQueue if the numberCars is more than maxQueue and then runs the runCarWash function
			else {
				numberCars++;
				cout << "Next car wash Type = 1 Cars in queue = " << numberCars << endl;

				if (maxQueue < numberCars) {
					maxQueue = numberCars;
				}
				runCarWash();
			}
		}
		else {
			cout << endl;
		}

		minutesOpen++; //the time will be updated
	}

	//The function will start the car wash
	void runCarWash()
	{
		//If the car wash is empty, the next car goes in to get washed.
		if (isCarWashEmpty()) {
			totalCars++;
			updateCarList();
			getStartOfWash();
			cout << "Car " << totalCars << " has started wash at time : " << minutesOpen << endl;
			//Finds the minute arrival from the car
			int minArrival;
			for (int i = 0; i < 5; i++) {
				if (cars[i].getInCarWash()) {
					minArrival = cars[i].getStart();
				}
			}
			//Calculates queue time
			queueTime += minutesOpen - minArrival;
		}

		//If the car wash is not empty, the car list will update and the next car will wait
		else {
			updateCarList();
		}	
	}

	//The car list will be updated depending on the status
	void updateCarList()
	{
		// First check if the carNumber already exists and update that one
		for (int i = 0; i < 5; i++) {
			if (cars[i].getCarNum() == totalCars && isCarWashEmpty()) {
				cars[i].setInCarWash(true);
				return;
			}
		}

		//It checks if the carNumber is zero and then updates the information of that car
		for (int i = 0; i < 5; i++) {
			if (cars[i].getCarNum() == 0) {
				cars[i].setCar(totalCars + (numberCars - 1), minutesOpen, 1, isCarWashEmpty());
				return;
			}
		}
	}

	//If the car wash is empty, the (next) car will go in. Otherwise, the car will be in the line for the car wash.
	bool isCarWashEmpty() {
		for (int i = 0; i < 5; i++) {
			if (cars[i].getInCarWash()) {
				return false;
			}
		}
		return true;
	}

	//Updates the start time for the wash
	void getStartOfWash() {
		for (int i = 0; i < 5; i++) {
			if (totalCars == cars[i].getCarNum()) {
				cars[i].setWashStart(minutesOpen);
			}
		}
	}

	//Returns the expected time the car will leave the wash
	int getEndOfWash() {
		for (int i = 0; i < 5; i++) {
			if (cars[i].getInCarWash()) {
				return cars[i].getWashEnd();
			}
		}
	}

	//Gets the total number of cars, which depends on the conditions, and then returns the total
	double getTotalNumber() {
		double total;

		//If there's cars in the queue and it's closing time, these cars will be added to the number of cars processed in the wash
		if (closingTime == minutesOpen && numberCars > 0) {
			total = totalCars + numberCars;
			return total;
		}

		//If there's no cars in the queue by the time it's closing time, the total of cars 
		else {
			total = totalCars;
			return total;
		}
	}

	//Calculates the average queue time
	double calculateQueueTime() {
		double average;
		average = (double) queueTime / getTotalNumber();
		return average;
	}

	//Displays the final report
	void displayStats() {
		double average = calculateQueueTime();
		cout << "---------------------------------" << endl;
		cout << "Total Number of Cars washed: " << getTotalNumber() << endl;
		cout << "Cars Turned Away: " << numberCarsRefused << endl;
		cout << "Average Time in the Queue: " << average << endl;
		cout << "Maximum Queue Size: " << maxQueue << endl;
		cout << "---------------------------------" << endl;
	}

private:
	int numberCars; //the number of cars in line and in the wash
	int maxQueue; //tracks the largest number of cars that had to wait
	int queueTime; //the total of all times that cars had to wait in the queue
	int totalCars; //counter for the number of cars processed in the wash
	int closingTime; //the time when car wash closes
	int minutesOpen; //tracks the number of minutes the car wash has been opened
	int numberCarsRefused; //tracks the number of cars that turned away
	CarToWash cars[5]; //tracks the information on each car
};
// Returns true 25% of the time
bool arrival() {
	if ((rand() % 4) == 0)
		return true;
	else
		return false;
}

/*
 * This is the main function which defines the car wash object. It prompts the user for how long to run the car wash
 * It then calls the timer function to simulate the car wash. Students should not have to change this code.
 */

int main()
{
	int runFor;
	int i;

	CarWash cw;		// main car wash variable
	srand((unsigned)time(0));
	cout << "Welcome to COMP 51 Car Wash Simulator\n";
	cout << "Please enter the number of minutes to operate: ";
	cin >> runFor;
	cw.openUp(runFor);

	for (i = 0; i < runFor; i++)
		cw.updateTimer(arrival());
	cw.displayStats();
	
	system("PAUSE");
	return 0;
}