//Trinity Caitlin Atayan Belen
//t_belen@u.pacific.edu
//ECPE 170

//Description: The c file for the function that reads the file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <errno.h>
#include <ctype.h>
#include "clue.h"
#include "size.h"

//Function to read the file by using the Clue class
Clue* read_File (FILE *fp, int size) {
  	char wrong; //Checks the amount of wrong letters
	
	//If the file isn't there, prints out that there's no file
	if (fp == NULL)
	{
        	printf("There's no file!\n");
    	}	

	Clue *Hints=(Clue*)malloc(size * sizeof(Clue)); //Allocates memory from the hints of the file according to the size of the board
 
	//Goes through the size of the clues/words so that the program could check the file
   	for(int i =0; i<size;i++)
    	{
       		fscanf(fp," %c %d %d %255s %255[^\n]",&Hints[i].pos,&Hints[i].rowX,&Hints[i].colY,Hints[i].wo,Hints[i].hint); //Checks each line for information
       		fscanf(fp,"%c",&wrong); //Checks what letters would be wrong (like letters not in the puzzle)
    	}

	return Hints;
}
