//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170
//Description: The main c file, calls other functions to set up the board

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <errno.h>
#include "clue.h"
#include "size.h"
#include "sizer.h"
#include "readFile.h"
#include "arrayFunc.h"
#include "play.h"


int main() { 
	printf("\nCROSSWORD PUZZLE GAME\n");
	int check1 = 0, check2 = 0; //Checks if the player and board meets the criteria to end the game
	Size size = sizer(); //gets size of board, also asks player for text file so that it can read it and process the information that will be used later
	Clue* hints=read_File(size.fp,size.numLetter); //reads the file to get info, goes through the sizes of the words too
	struct Board** board = createBoard(size);//creates the board after getting the size
	printf("\nLoading game file %s",size.fileText);
	printf("\n");

	printf("Game is %i rows x %i cols with %i words\n", size.height, size.width, size.numLetter);
	
	makeBoard(board,size);

   	printBoard(board,size);

   	updateBoard(board,hints,size);

	//The program continues on until the player quits or win since these functions won't go to 1 unless the player solves every clue
   	do {
   		printBoard(board,size);
    		check1 = play(board,hints,size);
    		check2 = checkIndex(hints,size);   
   	} while((check1 != 1) && (check2 !=1));

 	if(check2 ==1)
  	{
    		printf("\nGame over, you win!\n");
  	}
    	
	printf("Current puzzle: \n");
	printBoard(board,size);

	//Frees memory from the pointers so that it won't use too much resources
	free(board);
	free(hints);
	return 0;

}


