//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170

#ifndef SIZE_H
#define SIZE_H

typedef struct
{
	int width; //Checks for width of board
	int height; //Checks for height of board
	FILE* fp; //Checks for file of the board
	char fileText[256]; //Checks for fileText or fileName of the board
	int numLetter; //Checks for number of letters in the clue
} Size;


#endif
