/*File:Project 2.cpp
Author: Trinity Caitlin Atayan Belen
Description: My solution to COMP 51 Project 2: Subtract a Square.
It uses indefinite repetition and perform user input validation. There's two heaps of marbles and the one who draws the last marble in the last heap loses.*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int numHeap;
	int numMarbles;
	int squareMarbles;
	int compMarbles;
	int compsquareMarbles;

	bool userTurn = true; //to provide a true statement when it is the user's turn and so that it is going to be the computer's turn otherwise
	bool heapEmpty = true; //to provide a true statement when a heap is empty

	//to generate the amount of marbles of heaps 1 and 2 between 1 and 100
	srand((unsigned)time(0)); 
	int firstHeap = rand() % 100 + 1;
	int secondHeap = rand() % 100 + 1;

	while (true) {

		//to show the amount of marbles left after the computer took some
		cout << "Heap 1: " << firstHeap << endl;
		cout << "Heap 2: " << secondHeap << endl;

		if (userTurn) { 

			cout << "It's the user's turn." << endl;
			cout << endl;

			//to ask the user which heap to take marbles from
			cout << "Which heap would you would like to draw from: ";
			cin >> numHeap;
			cout << endl;

				//to reprompt the user if the heap is less than 1 or greater than 2 in order to stop them from making an illegal move
				while (numHeap < 1 || numHeap > 2) {
					cout << "That's not a valid heap! Please re-enter the heap you would like to draw from: ";
					cin.clear(); //to clear the error flag of a possible invalid input; also used in other statements to make sure they do not crash
					cin.ignore(1000,'\n'); //to skip over 1000 amount of chars before it reaches the breaking point; also used in other statements to make sure they do not crash
					cin >> numHeap;
					cout << endl;
				}

				//to reprompt the user if the heap does not have any marbles in order to stop them from making an illegal move
				heapEmpty = true;
				while (heapEmpty) {					
					if (firstHeap == 0 && numHeap == 1 || secondHeap == 0 && numHeap == 2) {
						heapEmpty = true;
						cout << "Sorry that heap is empty. Please enter again: ";
						cin.clear();
						cin.ignore(1000,'\n');
						cin >> numHeap;
						cout << endl;
					}
					else {
						heapEmpty = false;
					}
				}

				//to prevent the program from crashing if the user picks an invalid input
				while (cin.fail()) {
					cout << "Invalid! Please re-enter heap you would like to draw from: ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> numHeap;
				}

			//to ask the user how many marbles they would like to draw
			cout << "How many marbles would you like to draw? "; 
			cin >> numMarbles;
			squareMarbles = numMarbles * numMarbles;
			cout << endl;

				//to remprompt the user if the amount of marbles they chose is between 1 and 9 in order to stop them from making an illegal move
				while (numMarbles < 1) {
					cout << "Invalid amount!  You must choose a square number between 1 and 9.  Please enter again: ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> numMarbles;
					squareMarbles = numMarbles * numMarbles;
					cout << endl;
				}
				while (numMarbles > 9) {
					cout << "Invalid amount!  You must choose a square number between 1 and 9.  Please enter again: ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> numMarbles;
					squareMarbles = numMarbles * numMarbles;
					cout << endl;
				}

				//to remprompt the user if the number of marbles is greater than the marbles in the heap(s) in order to stop them from making an illegal move
				bool greaterthanHeap = true;
				while (greaterthanHeap) {
					if (squareMarbles > firstHeap && numHeap == 1) {
						cout << "That's greater than the heap! Please re-enter your marbles again: ";
						cin.clear();
						cin.ignore(1000, '\n');
						cin >> numMarbles;
						squareMarbles = numMarbles * numMarbles;
						cout << endl;
					}

					if (squareMarbles > secondHeap && numHeap == 2) {
						cout << "That's greater than the heap! Please re-enter your marbles again: ";
						cin.clear();
						cin.ignore(1000, '\n');
						cin >> numMarbles;
						squareMarbles = numMarbles * numMarbles;
						cout << endl;
					}

					else {
						greaterthanHeap = false;
					}
				}

				//to generate take away a specific amount of marbles from the heap the user chose
				if (numHeap == 1) {
					firstHeap = firstHeap - squareMarbles;
					cout << "Heap 1: " << firstHeap << endl;
					cout << "Heap 2: " << secondHeap << endl;
					cout << endl;
				}
				else {
					secondHeap = secondHeap - squareMarbles;
					cout << "Heap 1: " << firstHeap << endl;
					cout << "Heap 2: " << secondHeap << endl;
					cout << endl;
				}

				//to prevent the program from crashing if the user picks an invalid input
				while (cin.fail()) {
					cout << "Invalid! Please re-enter number of marbles: ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> numMarbles;
					squareMarbles = numMarbles * numMarbles;
					cout << endl;
				}

				//to show the win conditions on the player's side
				if (firstHeap == 0 && secondHeap == 0) {
					cout << "Better luck next time!" << endl;
					cout << endl;
					break;
				}
		}

		userTurn = !userTurn;
		if (!userTurn) {
			cout << "It's the computer's turn." << endl;
			cout << endl;

			numHeap = rand() % 2 + 1; // to generate the heaps
			compMarbles = rand() % 9 + 1; // to generate marbles
			compsquareMarbles = compMarbles * compMarbles; //the square number the computer will calculate

			//to switch the computer's heap if one of the heaps is empty
			if (firstHeap == 0 && numHeap == 1) {
				numHeap = 2;
			}
			if (secondHeap == 0 && numHeap == 2) {
				numHeap = 1;
			}

			//to generate the number of marbles that the computer will draw so that the heaps will not be in the negatives
			bool genMarbles = true;
			while (genMarbles) {
				if (compsquareMarbles > firstHeap && numHeap == 1) {
					compMarbles = rand() % 9 + 1;
					compsquareMarbles = compMarbles * compMarbles;
				}
				else if (compsquareMarbles > secondHeap && numHeap == 2) {
					compMarbles = rand() % 9 + 1;
					compsquareMarbles = compMarbles * compMarbles;
				}
				else {
					genMarbles = false;
				}
			}

			//to calculate the number of marbles the computer draws
			if (numHeap == 1) {
				firstHeap = firstHeap - compsquareMarbles;
				cout << compsquareMarbles << " marbles is drawn from heap " << numHeap << "." << endl; 
				cout << endl;
			}
			else if (numHeap == 2) {
				secondHeap = secondHeap - compsquareMarbles;
				cout << compsquareMarbles << " marbles is drawn from heap " << numHeap << "." << endl;
				cout << endl;
			}

			//to show the win conditions on the computer's side
			if (firstHeap == 0 && secondHeap == 0) {
				cout << "Congratulations! You've won!" << endl;
				cout << endl;
				break;
			}

		}

	}

	system("pause");

}