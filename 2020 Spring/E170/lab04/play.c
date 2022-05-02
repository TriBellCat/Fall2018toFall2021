//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170

//Description: c file for the functions that touch the play input

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <errno.h>
#include <ctype.h>
#include "clue.h"
#include "size.h"
#include "arrayFunc.h"
#include "sizer.h"

//Checks the index to see if an clue has been found
int checkIndex( Clue* clue,  Size s)
{
  	for(int i = 0; s.numLetter > i; i++)
   	{
      		if(clue[i].ifFound == 0)
       		{
         		return 0;
       		}
   	}
	return 1; //By the time the player finished all the clues, returns 1, which will fulfill one of the criterias to break out of the while loop for this game
}

//When the player guesses a word right, use this function to initialize the clue to the answer on the board
void checkers( Clue** arr,  Clue clue)
{
	//Updates column and row 
 	int column=clue.colY-1;
 	int row=clue.rowX-1;
	int length = strlen(clue.wo);
	
	//Goes through the length of the word to see current direction of the clue 
 	for(int i=0; i< length;i++)
	{    
    		if(clue.pos == 'H')
     		{
			arr[row][column+i].letter= arr[row][column+i].answer;
     		}

    		else if(clue.pos == 'V')
	    	{  
       			arr[row+i][column].letter= arr[row+i][column].answer;
   		}
    	}
}

//Uppercases the player's solution since the puzzle's solutions are already in uppercase and so that the program doesn't think the player has the wrong answer
void uppercase(char* sol) 
{
	//Searches through the player's solution in a while loop that searches through the pointer and uppercases every letter in each element
	while(*sol)
	{
		*sol=toupper(*sol);
		sol++; //Increments letter so that it can continue on to the next one to uppercase
	}
}

//The function that allows the player to input their guesses
int play( Clue** arr,  Clue* clue,  Size s)
{

	int choice;//The choice of clue from the player
  	char sol[256]; //Solution from the player

	printf("Unsolved Clues:\n");
	printf("------------------------\n");
  	printf(" #   direction       Row/Col   Clue\n");

	//prints the headers of the board
  	for(int i =0;i <s.numLetter;i++)
    	{
		//Updates headers for those who are not found yet
      		if(clue[i].ifFound == 0){
        		printf(" %x   %c               %x/%x     %s",i+1,clue[i].pos,clue[i].rowX,clue[i].colY, clue[i].hint);
        		printf("\n"); 
     		}

	}
		
	printf("Current puzzle: \n");
	printBoard(arr, s); 

	printf("Enter clue to solve, or -1 to exit: ");
	scanf("%d",&choice);
	printf("\n");
	
	if (choice == -1) {
		printf("Exiting now...\n");
		exit(0);
	}

	printf("Enter your solution: ");
	scanf("%s",sol);
	uppercase(sol);

	//if the player's solution and the hint they choose to answer are compared and have the same letter, update information
	if(strcmp(sol,clue[choice-1].wo)==0)
  	{
    		clue[choice-1].ifFound=1;
    		checkers(arr,clue[choice-1]);
  	}

	//Else, point out they have the wrong answer
   	else 
   	{
    		printf("\nwrong answer\n");
   	}

	return 0;
}


