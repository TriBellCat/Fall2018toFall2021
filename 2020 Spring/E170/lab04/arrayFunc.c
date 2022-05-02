//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170

//Description: c file for the functions that directly touch the board

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <errno.h>
#include <ctype.h>
#include "clue.h"
#include "size.h"

//Makes board by allocating its memory
struct Board** createBoard( Size clue) {
	 Clue **arr = calloc(clue.height, sizeof( Clue *));

	//Exits the program if there's an error of no more memory
  	if (arr == NULL) {
    		printf("Out of memory: %s\n", strerror(errno));
    		exit(EXIT_FAILURE);
  	}

	//Allocates board's memory in the width in a for loop after going through the board's height
  	for (int i = 0; i < clue.height; i++) {
		arr[i] = calloc(clue.width, sizeof( Clue));

    		if (arr[i] == NULL) {
    			printf("Out of memory: %s\n", strerror(errno));
      			exit(EXIT_FAILURE);
     		}
    	}
    	return arr;
}

//Makes the board and uses # as placeholders after going through the width's height and width
void makeBoard( Clue **arr,  Size clue) {
  	for (int i = 0; i < clue.height; i++) {
    		for (int j = 0; j < clue.width; j++) {
      			arr[i][j].letter = '#';
    		}
  	}
}

//Function to print the board
void printBoard( Clue** arr,  Size clue) {
	//prints new space and then new space
	printf("\n    ");

	//Goes through a for loop
 	for (int i = 0; i < clue.height; i++) {
   		printf("%d ",i+1);
	}

  	printf("\n \t \n");

	//Searches through the colums to see how many white spaces to print
  	for (int i = 0; i < clue.height; i++) {
		//Numbers since 10 requires extra spaces since there would would be an extra number to take up space
   		if(i <= 10)
   		{
   			printf("%d   ",i+1);
   		}

   		else 
   		{
   			printf("%d ",i+1);
   		}

		//Then it prints out the characters for each row
    		for (int j = 0; j < clue.width; j++) {
      			printf("%c ", arr[i][j].letter);
    		}
		printf("\n");	
	}
}

//Updates the board
void updateBoard ( Clue** arr,  Clue* clue,  Size size)
{
	int length = 0; //Will be initialized to the length of the clue later on
	int horiRowX, vertColY; //The row and column, respectively, that will be updated later on
	int si = size.numLetter; //Gets the clue size to search through
 	printf("%d",si);

	
//Traverses through the length of the clue, so that the program can insert elements into the board
	for(int i=0; i < si ;i++)
	{
		//Sets the row and column, respectively, so that they can be updated later on
 		horiRowX = clue[i].rowX-1;
		vertColY = clue[i].colY-1;

		length = strlen(clue[i].wo);
		//Traverses through the length of the board to find whether the current direction will be horizontal or vertical
 		for(int j=0; j < length;j++)
		{   
			//If the clue's current position is horizontal (or 'H' for short), update the board's information
			if(clue[i].pos == 'H')
     			{
				arr[horiRowX][vertColY+j].letter='_';//If the clue has not been found, insert '_' as a placeholder 


        			arr[horiRowX][vertColY+j].answer=clue[i].wo[j]; //Inserts the answer in the clue's array so that it can be 


				arr[horiRowX][vertColY+j].ifFound=0; //Since if it has not found, the ifFound will be set to 0


				strcpy(arr[horiRowX][vertColY+j].wo,clue[i].wo); //copies the word from the clue to the current position array's
     			}
			
			//If vertical, do the same as it would with horizontally, except vertically
    			if(clue[i].pos == 'V')
    			{  
       				arr[horiRowX+j][vertColY].letter='_';


       				arr[horiRowX+j][vertColY].answer=clue[i].wo[j];


       				arr[horiRowX+j][vertColY].ifFound=0;


       				strcpy(arr[horiRowX][vertColY+j].wo,clue[i].wo);	
   			}

    		}
	}
	
}
