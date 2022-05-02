//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170

#ifndef CLUE_H
#define CLUE_H

typedef struct
{
	int rowX; //Checks for the row or x coordinate
	int colY;  //Checks for the col or y coordinate
	int ifFound;  //Checks if the word has been found (1) or not found (0)
	char letter; //Checks for the letter in a word
	char pos; //Checks for the direction and position of an element in the board
	char answer; //Checks for the answer of the hint
	char wo [256]; //Checks for words of the board
	char hint [256]; //Checks for the hints of the board
} Clue;

#endif
