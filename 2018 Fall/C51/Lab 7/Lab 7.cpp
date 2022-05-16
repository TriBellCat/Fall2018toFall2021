/*File Name: Lab 7.cpp
Author: Trinity Caitlin Atayan Belen
Description: This is a tic-tac-toe game and the program will check whether x or o won.*/

#include <iostream>
using namespace std;

//there's only 3 rows and 3 columns in a tic-tac-toe game
const int row = 3;
const int col = 3;

//This prints out the Board
void printBoard(char board[][3]) {
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

//checks if a spot is filled
bool isfilled(char board[][3], int row, int col) {

	if (board[row][col] == 'e') {
		return false;
	}

	else
		return true;
}	

//checks if the game is over
bool isGameOver(char board[][3]) {
	for (int i = 0; i < row; i++) // checks for row
	{
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 'e') {
			return true;
		}
	}

	for (int i = 0; i < col; i++) //check for col
	{
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != 'e') {
			return true;
		}
	}

	//checks for left to right diagonal
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 'e') { 
		return true;
	}

	//checks for right to left diagonal
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != 'e') {
		return true;
	}

	return false;
}

//this is the player's move
void move(char board[][3], char player) {
	int row, col;
	
		printBoard(board);

		cout << "Player " << player << ": please enter the coordinates of your move (row col): ";
		cin >> row >> col;

		while (isfilled(board, row, col) == true) {
			cout << "Invalid move! That cell is already taken!\n" << endl;
			cout << "Player " << player << ": please enter the coordinates of your move (row col): ";
			cin >> row >> col;
		}

		if (!isfilled(board, row, col)) {
			board[row][col] = player;
		}
}

int main() {
	char board[3][3] = { {'1','2','3'},{'4','5','6'}, {'7','8','9'} };
	char player = 'X';

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			board[i][j] = 'e';
		}
	}

	//the player's move will repeat until x or o wins
	do {
		move(board, player);
		if (player == 'X') {
			player = 'O';
		}
		else {
			player = 'X';
		}
	} while (!isGameOver(board));

	//prints the final results
	printBoard(board);

	//to switch the player to the correct symbols after one of them won
	if (player == 'X') {
		player = 'O';
	}
	else {
		player = 'X';
	}

	//the program will tell the user who won
	if (isGameOver(board)) {
		cout << "Player " << player << " has won!" << endl;
	}

	system("pause");
}